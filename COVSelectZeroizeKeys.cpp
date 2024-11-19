
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVSelectZeroizeKeys.cpp
//
// Description:
//    This file contains the class definition for the COVSelectZeroizeKeys
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVSelectZeroizeKeys.h"
#include "CMsgHandler.h"
#include "CKeyEffectData.h"
#include "TMemStrUtility.h"
#include "CControlVars.h"
#include "Utility.h"
#include "CVlf.h"

extern MessageQueue queueCmd; // Local Address Space Shared Queue

////////////////////////////////////////////////////////////////////////////////
//! Function: COVSelectZeroizeKeys::Constructor
//!
//! Description:
//!   This is the class constructor, it initializes variables
//!
//! Parameters:
//!   None
//!
//! Return:
//!    None
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
COVSelectZeroizeKeys::COVSelectZeroizeKeys()
{
   //create alarm timer that allows for stopping channels
   Time clearCommPlanTimeOut = {HALT_TIMEOUT, 0};   // comm plan timeout
   CHECK( CreateAlarmTimer((Address)clearCommPlanTimeOutHandler,
         (Address)&rcv_msg, &clearCommPlanTimeOut, true, false,
         &HaltChanTimer), __FILE__, __FUNCTION__, __LINE__ );
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVSelectZeroizeKeys::ValidateMsgParam
//!
//! Description:
//!   This method validates the message parameters.
//!   No parameters so return VLF_NO_ERROR
//!
//! Parameters:
//!    msg - Message class pointer - NOT USED
//!
//! Return:
//!    Msg_Error_Codes_Type
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
Msg_Error_Codes_Type COVSelectZeroizeKeys::ValidateMsgParam(const CMessage& msg)
{
   // The parameters are validated by DSP2 so just return no error
   return (VLF_NO_ERROR);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVSelectZeroizeKeys::HandleMsg
//!
//! Description:
//!   This method handles the COVSelectZeroizeKeys message.
//!   This message can be used to zeroize a single TEK, all TEKs
//!   associated with an algorithm type or all TEKs.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! NOTE: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVSelectZeroizeKeys::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type error = ValidateMsgParam (*msg);    // error

   Selective_Zeroize_Keys_Msg_Type* msgData =
      (Selective_Zeroize_Keys_Msg_Type*)msg->GetMsgData()->theData;        // msg data

   if (error == VLF_NO_ERROR)
   {

      // clear out all comm plans, if needed
      if (msgData->action == ALL_COMM_PLANS)
      {
         haltChannels();

         // save a copy of the message for the alarm timer
         rcv_msg = *msg;

         // set timer to wait for response message back from CP
         CHECK( SetAlarmTimer ( HaltChanTimer ),
             __FILE__, __FUNCTION__, __LINE__);

      }
      else
      {
         if ( msgData->action == ALL_TEKS )
         {
            // call Key Effectivity Handler
            CKeyEffectData::Instance()->deleteData(*msgData);

            // Set key table data invalid - table was just cleared
            CVlf::Instance()->setKeyTblLoadedStatus(false);

            // send DSP2 the updated status of the key table
            CVlf::Instance()->UpdateRcvrStatus();

            haltChannels();

            // save a copy of the message for the alarm timer
            rcv_msg = *msg;

            // set timer to wait for response message back from CP
            CHECK( SetAlarmTimer ( HaltChanTimer ),
                __FILE__, __FUNCTION__, __LINE__);
         }
         // else nothing- we do not have to delete the comm plan of the table flag
      }
   }
   else
   {
      // Send software anamoly message to the VCI
      // errStr is initialized in the constructor
      std::ostringstream errStr ( "" );  // error string
      errStr << "Invalid Msg Param, Msgid: "
             << msg->GetMsgId() << "ActionId: "
             << msg->GetActionId() << " ("
             << __FILE__ << " Line: " << __LINE__<< ")" << std::ends;
      send_sa_msg ( errStr.str().c_str() );
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: COVSelectZeroizeKeys::haltChannels
//!
//! Description:
//!   This method will halt all the channels athat are active prior to calling
//!   clearCommPlans function.
//!
//!
//! Parameters:
//!    None
//!
//! Return:
//!    None
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVSelectZeroizeKeys::haltChannels()
{
   Error condError = Failure;   // error condition

   // send forced channel halt to each channel and each mode
   for(int chanNum =0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
   {
      condError = TryToObtainSemaphore(CControlVars::Instance()->
         sec_msg_proc_struct[chanNum].sMsgAction);

      if (Success == condError)
      {
         //pass in msg info to the secondary processing variable
         //we are within a semaphore, data ok to modify
         CControlVars::Instance()->sec_msg_proc_struct[chanNum].
         secProcMsg.msgActionID = UNSOLICIT_ACTION_ID;

         CControlVars::Instance()->sec_msg_proc_struct[chanNum].
         secProcMsg.msgAction = STOP_CHANNEL_FORCED;

         SignalCondition(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].conAction);

         ReleaseSemaphore(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].sMsgAction);
      }
      else
      {
         // str is initialized in the constructor
         std::ostringstream str ( "" ); // string stream
         str << "VLF/LF RELIABILITY ERROR: "
             << __FILE__ << " Line: " << __LINE__ << " "
             << "Unable to shutdown channel " << chanNum
             << ".  Semaphore sec_msg_proc_struct[" << chanNum
             << "].sMsgActionOperation in Progress" << std::ends;
         send_sa_msg ( str.str().c_str()  );
      }
   }// end for loop
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVSelectZeroizeKeys::clearCommPlans
//!
//! Description:
//!   This method will zeoize the loaded comm plans,  each comm plan will
//!   be set to a default value at VLF initialization.
//!
//!
//! Parameters:
//!    None
//!
//! Return:
//!    None
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVSelectZeroizeKeys::clearCommPlans()
{
   ChannelCmdStruct* cmdBuffer = NULL;  // cmd buffer
   void* buffer = NULL;                 // buffer
   Error err = Failure;                 // error

   // loop to clear out all CommPlans
   for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
   {
      //if the channel has halted process the comm plan clear
      if ((CVlf::Instance()->chan[chanNum]->mMode15->
         mChanModeStatus.modeScanState == MODE_SEARCH_HALTED) &&
        (CVlf::Instance()->chan[chanNum]->mMode9->
         mChanModeStatus.modeScanState == MODE_SEARCH_HALTED) &&
        (CVlf::Instance()->chan[chanNum]->mModeHidar->
         mChanModeStatus.modeScanState == MODE_SEARCH_HALTED) &&
        (CVlf::Instance()->chan[chanNum]->mMode23->
         mChanModeStatus.modeScanState == MODE_SEARCH_HALTED) &&
        (CVlf::Instance()->chan[chanNum]->mModeSMA->
         mChanModeStatus.modeScanState == MODE_SEARCH_HALTED))
      {
         // clear the commplan flag for the channel
         CVlf::Instance()->chan[chanNum]->mCommPlanValid = false;

         // clear out comm plan structure in each channel
         memset_safe (&CVlf::Instance()->chan[chanNum]->mCommPlan,
            UNUSED_VARIABLE_VAL, sizeof (Vlf_Channel_Type));

         // send the commplan to main_Coord_SP_Task for processing
         err = AllocateMessageQueueBuffer(queueCmd, (void**)&buffer);
         if (err == Success)
         {
            cmdBuffer = (ChannelCmdStruct*)buffer;
            cmdBuffer->cmd = COMM_PLAN_CMD;
            cmdBuffer->channel = chanNum + 1; // increase channel to match msg
            cmdBuffer->cmdData.commPlanConfig.freqOfChannel = MIN_FREQUENCY_RANGE;
            cmdBuffer->cmdData.commPlanConfig.transmitterNum = MIN_TX_NUMBER;
            cmdBuffer->cmdData.commPlanConfig.mode15_enabled = false;
            cmdBuffer->cmdData.commPlanConfig.mode9_enabled = false;
            cmdBuffer->cmdData.commPlanConfig.modeHIDAR_enabled = false;
            cmdBuffer->cmdData.commPlanConfig.mode23_enabled = 0;
            cmdBuffer->cmdData.commPlanConfig.modeSMA_enabled = false;
            CHECK(SendOnMessageQueue (queueCmd, buffer),
               __FILE__, __FUNCTION__, __LINE__);
         }
         else
         {
            CHECK(err, __FILE__, __FUNCTION__, __LINE__);
         }

         // Set VLF comm plan invalid in status message
         CVlf::Instance()->mRcvrStatus.CommPlanLoaded = false;

         // send DSP2 the updated status of the comm plan
         CVlf::Instance()->UpdateRcvrStatus();
      }// else nothing- the channel is still active
   }
}

AlarmTimer COVSelectZeroizeKeys::HaltChanTimer;   // halt channel timer
////////////////////////////////////////////////////////////////////////////////
//! Function: COVSelectZeroizeKeys::clearCommPlanTimeOutHandler
//!
//! Description:
//!   This method handles the comm plan zeroize time out handler.  It will
//!   check to ensure that all channels are not active and then clear out the
//!   comm plan.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVSelectZeroizeKeys::clearCommPlanTimeOutHandler(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   // try to clear comm plans 2 times
   static int counter = TIMER_RETRY;  // retry counter

   // clear out the comm plans
   clearCommPlans();

   //stop timer if all comm plan are clear
   if ((!CVlf::Instance()->chan[CH_1]->mCommPlanValid) &&
       (!CVlf::Instance()->chan[CH_2]->mCommPlanValid) &&
       (!CVlf::Instance()->chan[CH_3]->mCommPlanValid) &&
       (!CVlf::Instance()->chan[CH_4]->mCommPlanValid) &&
       (!CVlf::Instance()->chan[CH_5]->mCommPlanValid))
   {
      //free alarm timer resources
      CancelAlarmTimer(HaltChanTimer);

      //reset counter
      counter = TIMER_RETRY;

      // The Timer is a repeating timer that will continue to activate until all
      // Comm Plans have been cleared.  Once all have been cleared, send ACK
      // to VCI with VLF_NO_ERROR.
      // send Ack/Nak Message to VCI
      CMsgHandler::Instance()->SendPriAckNak(CVlf::Instance()->mActiveOES,
            msg->GetMsgId(), msg->GetActionId(), ACK, VLF_NO_ERROR);
   }
   else
   {
      if (0 != counter--)
      {
         //try to halt the channel again
         haltChannels();
      }
      else
      {
         //free alarm timer resources
         CancelAlarmTimer(HaltChanTimer);

         //reset counter
         counter = TIMER_RETRY;

         // send Ack/Nak Message to VCI
         CMsgHandler::Instance()->SendPriAckNak(CVlf::Instance()->mActiveOES,
               msg->GetMsgId(), msg->GetActionId(), ACK, CLEAR_COMM_PLNS_FAILED);
      }
   }
}


//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
