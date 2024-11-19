
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVCDEDataErasure.cpp
//
// Description:
//    This file contains the class definition for the COVCDEDataErasure
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVCDEDataErasure.h"
#include "CMsgHandler.h"
#include "CKeyEffectData.h"
#include "CControlVars.h"
#include "Utility.h"
#include "CVlf.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVCDEDataErasure::Constructor
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
COVCDEDataErasure::COVCDEDataErasure()
{
   //create alarm timer that allows for stopping channels
   Time zeroizeAllKeysTimeOut = {CDE_TIMEOUT, 0};        // zeroize keys timeout
   CHECK( CreateAlarmTimer((Address)zeroizeAllKeysTimeOutHandler,
         (Address)&rcv_msg, &zeroizeAllKeysTimeOut, true, false,
         &CDETimer), __FILE__, __FUNCTION__, __LINE__ );
}

////////////////////////////////////////////////////////////////////////////////
//! Function: COVCDEDataErasure::ValidateMsgParam
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
Msg_Error_Codes_Type COVCDEDataErasure::ValidateMsgParam(const CMessage& msg)
{
   return (VLF_NO_ERROR);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVCDEDataErasure::HandleMsg
//!
//! Description:
//!   This method handles the COVCDEDataErasure message.
//!              This message is used to halt all channels clear the
//!              Key Effectivity table, delete all TEKs and KEK and response
//!              with key disposition message
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! NOTE: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVCDEDataErasure::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type error = ValidateMsgParam (*msg);  // error
   Response_Status_Type status = ACK;                    // status

   Selective_Zeroize_Keys_Msg_Type msgData = {CDE, 0, 0, 0};  // msgs data

   if (error == VLF_NO_ERROR)
   {
      // Send the
      // specific response
      CMsgHandler::Instance()->SendPriAckNak(msg->GetSrc(), msg->GetMsgId(),
                               msg->GetActionId(), status, error);

      // call Key Effectivity Handler
      CKeyEffectData::Instance()->deleteData(msgData);

      // Set key table data invalid - table was just cleared
      CVlf::Instance()->setKeyTblLoadedStatus(false);

      // send DSP2 the updated status of the key table
      CVlf::Instance()->UpdateRcvrStatus();

      haltChannels();

      // set timer to wait for response message back from CP
      CHECK( SetAlarmTimer ( CDETimer ),
          __FILE__, __FUNCTION__, __LINE__);

   }
   else
   {
      // Send software anamoly message to the HMI
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
//! Function: COVCDEDataErasure::haltChannels
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
void COVCDEDataErasure::haltChannels()
{
   Error condError = Failure;     // error condition

   // send forced channel halt to each channel and each mode
   for(int chanNum =0; chanNum < MAX_VLF_CHANNEL; chanNum++) // loop thru channels
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
         std::ostringstream errStr ( "" );  // error string
         errStr << "VLF/LF RELIABILITY ERROR: "
             << __FILE__ << " Line: " << __LINE__ << " "
             << "Unable to shutdown channel " << chanNum
             << ".  Semaphore sec_msg_proc_struct[" << chanNum
             << "].sMsgActionOperation in Progress" << std::ends;
         send_sa_msg ( errStr.str().c_str() );
      }
   }// end for loop
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVCDEDataErasure::zeroizeAllKeys
//!
//! Description:
//!   This method will zeoize all TEKs and KEKs
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
void COVCDEDataErasure::zeroizeAllKeys()
{
   Zeroize_Keys_Action_Type action = CDE;     // action
   unsigned int keyBank = 0;                  // key bank
   unsigned int segLoc = 0;                   // segment location
   CKeyEffectData::Instance()->selectiveZeroizeCryptoKey( action, keyBank, segLoc );
}

AlarmTimer COVCDEDataErasure::CDETimer;       // CDE timer
////////////////////////////////////////////////////////////////////////////////
//! Function: COVCDEDataErasure::zeroizeAllKeysTimeOutHandler
//!
//! Description:
//!   This method handles the all keys (TEKs and KEK) zeroize time out handler.
//!   It will check to ensure that all channels are not active and then
//!   zeroize Keys.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVCDEDataErasure::zeroizeAllKeysTimeOutHandler()
{
   // try to halt channels 2 times
   static int counter = TIMER_RETRY;    // retry counter
   int numChanHalted = 0;               // # of channels halted

   // loop to to ensure all channels are Halted
   for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
   {
      // update the count of number of channels halted
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
         numChanHalted++;
      }// else nothing- the channel is still active
   }

   //stop timer if all channel halted
   if ( MAX_VLF_CHANNEL == numChanHalted )
   {
      //free alarm timer resources
      CancelAlarmTimer(CDETimer);

      //reset counter
      counter = TIMER_RETRY;
      // clear out keys
      zeroizeAllKeys();
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
         CancelAlarmTimer(CDETimer);

         //reset counter
         counter = TIMER_RETRY;

      }
   }
}
////////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
////////////////////////////////////////////////////////////////////////////////

