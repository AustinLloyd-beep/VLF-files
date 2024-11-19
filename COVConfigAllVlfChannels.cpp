
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVConfigAllVlfChannels.cpp
//
// Description:
//    This file contains the class definition for the  Responce Status Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVConfigAllVlfChannels.h"

#include "CVlf.h"
#include "TMemStrUtility.h"
#include "CMsgHandler.h"

extern MessageQueue queueCmd; // Local Address Space Shared Queue

////////////////////////////////////////////////////////////////////////////////
//! Function: COVConfigAllVlfChannels::ValidateMsgParam
//!
//! Description: This method validates the message parameters.
//!   channelID = 0 means blank comm plan will skip validation of the fields
//!   Error conditions:
//!      1) duplicate Channel ID used on different comm plans
//!      2) any field fails validation
//!      3) any channels are active
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return:
//!    Msg_Error_Codes_Type
//!
//! Notes: Input parameters checked by calling function.
//!
////////////////////////////////////////////////////////////////////////////////
Msg_Error_Codes_Type COVConfigAllVlfChannels::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;   // error code

   Config_All_Vlf_Channels_Msg_Type* cp_msg =
         (Config_All_Vlf_Channels_Msg_Type*)&msg.GetMsgData()->theData;   // CP msg

   int chIdx = 0;    // channel index
   int numValid = 0; // num of valid commplan must be at least 1
   bool chNumUsed [MAX_VLF_CHANNEL] = {false,false,false,false,false};  // channel used

   // Check message data parameters, the header is checked when the
   // message is received
   for ( chIdx = 0; chIdx < MAX_VLF_CHANNEL; chIdx++)
   {
      commPlanValid[chIdx] = false;
   }
   // check for channel active in
   for ( chIdx = 0; chIdx < MAX_VLF_CHANNEL; chIdx++)
   {
      if ((CVlf::Instance()->chan[chIdx]->mMode15->
            mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
          (CVlf::Instance()->chan[chIdx]->mMode9->
            mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
          (CVlf::Instance()->chan[chIdx]->mModeHidar->
            mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
          (CVlf::Instance()->chan[chIdx]->mMode23->
            mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
          (CVlf::Instance()->chan[chIdx]->mModeSMA->
            mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) )
      {
         error = CHANNEL_ACTIVE;
         return (error);
      } // else - no action required
   }

   for ( chIdx = 0; chIdx < MAX_VLF_CHANNEL; chIdx++)
   {
      // skip validation when channelID = 0 which indicates blank comm plan
      if ( cp_msg->commPlans[chIdx].channelID == 0 )
      {
         continue;
      } // else - no action required
      // validate the fields
      if (((cp_msg->commPlans[chIdx].channelID < 1) ||
           (cp_msg->commPlans[chIdx].channelID > MAX_VLF_CHANNEL)) ||
          ((cp_msg->commPlans[chIdx].frequency < MIN_FREQUENCY_RANGE) ||
           (cp_msg->commPlans[chIdx].frequency > MAX_FREQUENCY_RANGE)))
      {
         error = PARAM_OUT_OF_RANGE;
         numValid = 0;
         break;
      }
      // check to ensure frequency is in 10Hz increment
      else if ( (cp_msg->commPlans[chIdx].frequency % 10) != 0 )
      {
         error = PARAM_OUT_OF_RANGE;
         numValid = 0;
         break;
      }
      // If Mode 23 is in the Comm Plan, the other modes cannot be present
      else if ( (cp_msg->commPlans[chIdx].mode23) &&
                ((cp_msg->commPlans[chIdx].mode15)    ||
                 (cp_msg->commPlans[chIdx].mode9)     ||
                 (cp_msg->commPlans[chIdx].modeHIDAR) ||
                 (cp_msg->commPlans[chIdx].modeSMA)) )
      {
         error = PARAM_OUT_OF_RANGE;
      }
      // Check for duplicate Channel ID
      else if ( chNumUsed [cp_msg->commPlans[chIdx].channelID - 1] )
      {
         error = DUPLICATE_CHAN_ID_USED_IN_COMMPLAN;
         numValid = 0;
         break;
      }
      else
      {
         chNumUsed [cp_msg->commPlans[chIdx].channelID -1] = true;
         commPlanValid [cp_msg->commPlans[chIdx].channelID -1] = true;
         numValid++;
      }
   }
   // If at least one comm plan is valid set it to no error
   if ( numValid > 0 )
   {
      error = VLF_NO_ERROR;
   }
   else
   {
      if ( error == UNKNOWN_ERROR )
      {
         error = NO_VALID_COMMPLAN_FOUND;
      }
      //else - no action needed
   }

   return (error);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: COVConfigAllVlfChannels::HandleMsg
//!
//! Description:
//!   This method handles the WriteAllCommPlans message from the HMI to
//!   configure a VLF channel for a specific frequency and modes.
//!   Comm Plans containing Mode 23 are supported with this message type.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes:
//!    This message must be sent prior to starting a VLF channel
//!    If a channel is started without a valid comm plan, the VLF
//!    will send an error code of "channel not configured".  If
//!    a channel is already started and the VLF receives a write
//!    comm plan message for that channel, an error of "channel
//!    active" is sent back to the OES.
//!
//!
////////////////////////////////////////////////////////////////////////////////
void COVConfigAllVlfChannels::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type mError = ValidateMsgParam (*msg);// error

   Config_All_Vlf_Channels_Msg_Type* msgData =
      (Config_All_Vlf_Channels_Msg_Type*)msg->GetMsgData()->theData;    // msg data

   ChannelCmdStruct* cmdBuffer = NULL;                  // cmd buffer
   void* buffer = NULL;                                 // buffer
   Response_Status_Type mStatus = NAK;                  // status
   int chanID = 0;                                      // channel ID
   int chIdx = 0;                                       // channel index

   if (mError == VLF_NO_ERROR)
   {
      mStatus = ACK; // parameters checked good

      for ( chIdx = 0; chIdx < MAX_VLF_CHANNEL; chIdx++)
      {
         if ( commPlanValid [chIdx] )
         {
            chanID = msgData->commPlans[chIdx].channelID - 1; // reduce for array

            // save the commplan for the channel
            CVlf::Instance()->chan[chanID]->mCommPlanValid = true; //Channel CommPlan

            memcpy_safe (&CVlf::Instance()->chan[chanID]->mCommPlan,
                     &msgData->commPlans[chIdx], sizeof (Vlf_Channel_Type));

            // Set VLF comm plan valid
            CVlf::Instance()->mRcvrStatus.CommPlanLoaded = true;

            //update the channel error code
            CVlf::Instance()->chan[chanID]->mChannelError = VLF_NO_ERROR;

            // send DSP2 the updated status of the comm plan
            CVlf::Instance()->UpdateRcvrStatus();

            // send DSP2 the updated channel status
            CVlf::Instance()->chan[chanID]->ReportChStatus();

            // send the commplan to main_Coord_SP_Task for processing
            Error err = AllocateMessageQueueBuffer(queueCmd, (void**)&buffer);  // alloc buffer
            if (err == Success)
            {
               cmdBuffer = (ChannelCmdStruct*)buffer;
               cmdBuffer->cmd = COMM_PLAN_CMD;
               cmdBuffer->channel = msgData->commPlans[chIdx].channelID;
               cmdBuffer->cmdData.commPlanConfig.freqOfChannel =
                  msgData->commPlans[chIdx].frequency;

               cmdBuffer->cmdData.commPlanConfig.transmitterNum =
                  MIN_TX_NUMBER;

               cmdBuffer->cmdData.commPlanConfig.mode15_enabled =
                  msgData->commPlans[chIdx].mode15;

               cmdBuffer->cmdData.commPlanConfig.mode9_enabled =
                  msgData->commPlans[chIdx].mode9;

               cmdBuffer->cmdData.commPlanConfig.modeHIDAR_enabled =
                  msgData->commPlans[chIdx].modeHIDAR;

               cmdBuffer->cmdData.commPlanConfig.mode23_enabled =
                  msgData->commPlans[chIdx].mode23;

               cmdBuffer->cmdData.commPlanConfig.modeSMA_enabled =
                  msgData->commPlans[chIdx].modeSMA;

               CHECK(SendOnMessageQueue (queueCmd, buffer),
                  __FILE__, __FUNCTION__, __LINE__);
            }
            else
            {
               CHECK(err, __FILE__, __FUNCTION__, __LINE__);
            }
         } // else comm plan not valid
      } //end for
   }// else there is an error

   // send Ack/Nak Message to HMI
   if ( mError == PARAM_OUT_OF_RANGE )
   {
      // Send software anamoly message to the OES
      // errStr is initialized in the constructor
      std::ostringstream errStr ( "" );  // error string
      errStr << "Invalid Msg Param, Msgid: "
             << msg->GetMsgId() << "ActionId: "
             << msg->GetActionId()
             << " (" << __FILE__ << " Line: " << __LINE__<< ")" << std::ends;
      send_sa_msg ( errStr.str().c_str() );

      CMsgHandler::Instance()->SendAckNak(msg->GetSrc(), msg->GetMsgId(),
                            msg->GetActionId(), mStatus, mError);

   }
   else
   {
      CMsgHandler::Instance()->SendAckNak(msg->GetSrc(), msg->GetMsgId(),
                            msg->GetActionId(), mStatus, mError, 0);
   }
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////

