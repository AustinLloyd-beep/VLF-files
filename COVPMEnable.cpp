
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVPMEnable.cpp
//
// Description:
//    This file contains the class definition for the COVPMEnable
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVPMEnable.h"
#include "CVlf.h"
#include "CMsgHandler.h"

extern MessageQueue queueCmd; // Local Address Space Shared Queue

////////////////////////////////////////////////////////////////////////////////
//! Function: COVPMEnable::ValidateMsgParam
//!
//! Description:
//!   This method validates the message parameters.
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
Msg_Error_Codes_Type COVPMEnable::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;         // error

   Performance_Monitoring_Enable_Msg_Type* msgData =
      (Performance_Monitoring_Enable_Msg_Type*)&msg.GetMsgData()->theData;  // msg data

   // Check message data parameters, the header is checked when the
   // message is received
   if (((msgData->channelID < 1) || (msgData->channelID > MAX_VLF_CHANNEL)) ||
       ((msgData->enableHIDAROPSTAT != 0) &&
        (msgData->enableHIDAROPSTAT != 1)) ||
       ((msgData->enableVLFPM != 0) &&
        (msgData->enableVLFPM != 1)))
   {
      error = PARAM_OUT_OF_RANGE;
   }
   // handle error if trying to load PMdata when Crypto not available
   else if (!CVlf::Instance()->mCPLinkUp)
   {
      error = INT_COMM_ERROR;
   }
   else
   {
      error = VLF_NO_ERROR;
   }

   return (error);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVPMEnable::HandleMsg
//!
//! Description:
//!   This method handles the PM enable message from the OES.  The
//!   PM enable parameter is sent to DSP1 and than to mode address
//!   space via the command queue for processing.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVPMEnable::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type mError = ValidateMsgParam (*msg);   // error
   ChannelCmdStruct* cmdBuffer = NULL;                      // cmd buffer
   Response_Status_Type mStatus = NAK;                      // status
   Performance_Monitoring_Enable_Msg_Type* msgData =
      (Performance_Monitoring_Enable_Msg_Type*)msg->GetMsgData()->theData;  // msg data

   if (mError == VLF_NO_ERROR)
   {
      mStatus = ACK;

      CVlf::Instance()->chan[msgData->channelID-1]->mEnableHidarOpstat = ( msgData->enableHIDAROPSTAT != 0 );
      CVlf::Instance()->chan[msgData->channelID-1]->mEnableVlf_Pm = ( msgData->enableVLFPM != 0 );

      Error err = AllocateMessageQueueBuffer(queueCmd, (void**)&cmdBuffer);  // alloc buffer

      if (err == Success)
      {
         cmdBuffer->cmd = PM_ENABLE_CMD;
         cmdBuffer->channel = msgData->channelID;
         cmdBuffer->cmdData.pmEnableConfig.enableHIDAROPSTAT = ( msgData->enableHIDAROPSTAT != 0 );
         cmdBuffer->cmdData.pmEnableConfig.enableVLFPM = ( msgData->enableVLFPM != 0 );
         CHECK(SendOnMessageQueue (queueCmd, cmdBuffer),
            __FILE__, __FUNCTION__, __LINE__);
      }
      else
      {
         CHECK(err, __FILE__, __FUNCTION__, __LINE__);
         mError = INT_COMM_ERROR;
      }
   }// else nothing- error set

   // send Ack/Nak Message to OES
   if ( mError == PARAM_OUT_OF_RANGE )
   {
      // Send software anamoly message to the HMI
      // errStr is initialized in the constructor
      std::ostringstream errStr ( "" );  // error string
      errStr << "Invalid Msg Param, (OV_PERFORMANCE_MONITORING_ENABLE_MSGTYPE) Msgid: "
          << msg->GetMsgId() << " ActionId: "
          << msg->GetActionId()
          << " (" << __FILE__ << " Line: " << __LINE__<< ")" << std::ends;
      send_sa_msg ( errStr.str().c_str() );

      CMsgHandler::Instance()->SendAckNak(msg->GetSrc(), msg->GetMsgId(),
                            msg->GetActionId(), mStatus, mError);
   }
   else
   {
      CMsgHandler::Instance()->SendAckNak(msg->GetSrc(), msg->GetMsgId(),
                            msg->GetActionId(), mStatus, mError,
                            msgData->channelID);
   }
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
