
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVConfigVlfChannel.cpp
//
// Description:
//    This file contains the class definition for the COVConfigVlfChannel
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVConfigVlfChannel.h"
#include "CVlf.h"
#include "CMsgHandler.h"
#include "TMemStrUtility.h"

extern MessageQueue queueCmd; // Local Address Space Shared Queue

////////////////////////////////////////////////////////////////////////////////
//! Function: COVConfigVlfChannel::ValidateMsgParam
//!
//! Description: This method validates the message parameters.
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
Msg_Error_Codes_Type COVConfigVlfChannel::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;  // error code

   Config_Vlf_Channel_Msg_Type* cp_msg =
      (Config_Vlf_Channel_Msg_Type*)&msg.GetMsgData()->theData;   // CP msg

   // Check message data parameters, the header is checked when the
   // message is received
   if (((cp_msg->commPlan.channelID < 1) ||
        (cp_msg->commPlan.channelID > MAX_VLF_CHANNEL)) ||
       ((cp_msg->commPlan.frequency < MIN_FREQUENCY_RANGE) ||
        (cp_msg->commPlan.frequency > MAX_FREQUENCY_RANGE)))
   {
      error = PARAM_OUT_OF_RANGE;
   }
   // check to ensure frequency is in 10Hz increment
   else if ( (cp_msg->commPlan.frequency % 10) != 0 )
   {
      error = PARAM_OUT_OF_RANGE;
   }
   // If Mode 23 is in the Comm Plan, the other modes cannot be present
   else if ( (cp_msg->commPlan.mode23) &&
             ((cp_msg->commPlan.mode15) ||
              (cp_msg->commPlan.mode9) ||
              (cp_msg->commPlan.modeHIDAR) ||
              (cp_msg->commPlan.modeSMA) ) )
   {
      error = PARAM_OUT_OF_RANGE;
   }
   // handle Error if mode 15 is active and
   // the commplan being entered changes any value other than short title
   else if ((CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->mMode15->
         mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) &&
         (!OnlyShortTitleChanged(msg)))
   {
         error = CHANNEL_ACTIVE;
   }
   // handle error if SModes 9 and HIDAR are active
   else if ((CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->mMode9->
             mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
            (CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->mModeHidar->
             mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
            (CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->mMode23->
             mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
            (CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->mModeSMA->
             mChanModeStatus.modeScanState != MODE_SEARCH_HALTED))
   {
      error = CHANNEL_ACTIVE;
   }
   else
   {
      error = VLF_NO_ERROR;
   }

   return (error);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: COVConfigVlfChannel::HandleMsg
//!
//! Description:
//!   This method handles the COVConfigVlfChannel message from the VCI to
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
//!    active" is sent back to the VCI.
//!
//!
////////////////////////////////////////////////////////////////////////////////
void COVConfigVlfChannel::HandleMsg( CMessage *msg )
{
   // Check the input parameter
   if ( check4Null( msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }

   Msg_Error_Codes_Type msgError = ValidateMsgParam( *msg );   // error code

   Config_Vlf_Channel_Msg_Type *msgData =
      (Config_Vlf_Channel_Msg_Type*)msg->GetMsgData()->theData;    // channel msg

   ChannelCmdStruct *pCmdBuffer = NULL;             // cmd buffer
   void *pBuffer = NULL;                            // buffer
   Response_Status_Type msgStatus = NAK;            // status
   int chanIdIdx = 0;                               // channel ID index

   // Send Ack/Nak Message to VCI
   if ( PARAM_OUT_OF_RANGE == msgError )
   {
      // Send software anamoly message to the OES
      // errStr is initialized in the constructor
      std::ostringstream errStr ( "" );  // error string
      errStr << "Invalid Msg Param, Msgid: "
      << msg->GetMsgId() << "ActionId: "
      << msg->GetActionId()
      << " (" << __FILE__ << " Line: " << __LINE__<< ")" << std::ends;
      send_sa_msg( errStr.str().c_str() );

      CMsgHandler::Instance()->SendAckNak( msg->GetSrc(), msg->GetMsgId(),
                                           msg->GetActionId(), msgStatus, msgError );
   }
   else
   {
      // Change status based on error code
      if ( msgError == CHANNEL_ACTIVE )
      {
         msgStatus = ACK;
      }
      // If no error, update and send the response
      else if ( msgError == VLF_NO_ERROR )
      {
         msgStatus = ACK;
         chanIdIdx = msgData->commPlan.channelID - 1; // subtract 1 for array index

         // Check comm plan
         // If comm plan changes only short title and mode 15 is active
         //  (mode 9, HIDAR, and mode 23 are checked in ValidateMsgParam)
         //  change the short title do not send info to mode code
         if ( ( OnlyShortTitleChanged( *msg ) ) &&
              ( CVlf::Instance()->chan[chanIdIdx]->mMode15->mChanModeStatus.modeScanState !=
                MODE_SEARCH_HALTED ) )
         {
            memcpy_safe( &CVlf::Instance()->chan[chanIdIdx]->mCommPlan,
                         &msgData->commPlan,
                         sizeof( Vlf_Channel_Type ) );
         }
         // Else change the entire comm plan variable and pass info to mode code
         else
         {
            // Save the commplan for the channel
            CVlf::Instance()->chan[chanIdIdx]->mCommPlanValid = true; // Channel CommPlan

            memcpy_safe( &CVlf::Instance()->chan[chanIdIdx]->mCommPlan,
                         &msgData->commPlan,
                         sizeof( Vlf_Channel_Type ) );

            // Set VLF comm plan valid
            CVlf::Instance()->mRcvrStatus.CommPlanLoaded = true;

            // Update the channel error code
            CVlf::Instance()->chan[chanIdIdx]->mChannelError = VLF_NO_ERROR;

            // Send DSP2 the updated status of the comm plan
            CVlf::Instance()->UpdateRcvrStatus();

            // Send DSP2 the updated channel status
            CVlf::Instance()->chan[chanIdIdx]->ReportChStatus();

            // Request a buffer to send the message
            Error err = AllocateMessageQueueBuffer( queueCmd, (void**)&pBuffer );   // alloc buffer
            if ( err != Success )
            {
               CHECK( err, __FILE__, __FUNCTION__, __LINE__ );
            }
            // Send the comm plan to main_Coord_SP_Task for processing
            else
            {
               pCmdBuffer = (ChannelCmdStruct*)pBuffer;
               pCmdBuffer->cmd = COMM_PLAN_CMD;
               pCmdBuffer->channel = msgData->commPlan.channelID;
               pCmdBuffer->cmdData.commPlanConfig.freqOfChannel = msgData->commPlan.frequency;
               pCmdBuffer->cmdData.commPlanConfig.transmitterNum = MIN_TX_NUMBER;
               pCmdBuffer->cmdData.commPlanConfig.mode15_enabled = msgData->commPlan.mode15;
               pCmdBuffer->cmdData.commPlanConfig.mode9_enabled = msgData->commPlan.mode9;
               pCmdBuffer->cmdData.commPlanConfig.modeHIDAR_enabled = msgData->commPlan.modeHIDAR;
               pCmdBuffer->cmdData.commPlanConfig.mode23_enabled = msgData->commPlan.mode23;
               pCmdBuffer->cmdData.commPlanConfig.modeSMA_enabled = msgData->commPlan.modeSMA;

               CHECK( SendOnMessageQueue( queueCmd, pBuffer ),
                      __FILE__, __FUNCTION__, __LINE__ );
            }
         }
      } // else - no action required

      // Send Ack/Nak Message to OES
      CMsgHandler::Instance()->SendAckNak( msg->GetSrc(), msg->GetMsgId(),
                                           msg->GetActionId(), msgStatus, msgError,
                                           msgData->commPlan.channelID );
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: COVConfigAllVlfChannels::OnlyShortTitleChanged
//!
//! Description: This method determines if anything other than the short title
//!   changed in the new comm plan.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return:
//!    bool - (true) if only short title changed
//!         - (false) all else
//!
//! Notes: Input parameters checked by calling function.
//!
////////////////////////////////////////////////////////////////////////////////
bool COVConfigVlfChannel::OnlyShortTitleChanged(const CMessage& msg)
{
   bool return_code = false;   // return code

   Config_Vlf_Channel_Msg_Type* cp_msg =
       (Config_Vlf_Channel_Msg_Type*)&msg.GetMsgData()->theData;

   if ( CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->
         mCommPlan.mode15 != cp_msg->commPlan.mode15 )
   {
       return_code = false;
   }
   else if ( CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->
            mCommPlan.mode9 != cp_msg->commPlan.mode9 )
   {
       return_code = false;
   }
   else if ( CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->
            mCommPlan.modeHIDAR != cp_msg->commPlan.modeHIDAR )
   {
       return_code = false;
   }
   else if ( CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->
            mCommPlan.mode23 != cp_msg->commPlan.mode23 )
   {
       return_code = false;
   }
   else if ( CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->
            mCommPlan.modeSMA != cp_msg->commPlan.modeSMA )
   {
       return_code = false;
   }
   else if ( CVlf::Instance()->chan[cp_msg->commPlan.channelID - 1]->
            mCommPlan.frequency != cp_msg->commPlan.frequency )
   {
       return_code = false;
   }
   else
   {
      return_code = true;
   }

   return (return_code);
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
