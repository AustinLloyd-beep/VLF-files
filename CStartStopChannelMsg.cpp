
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CStartStopChannelMsg.cpp
//
// Description:
//    This file contains the class definition for the CStartStopChannelMsg
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "CStartStopChannelMsg.h"
#include "CVlf.h"
#include "CControlVars.h"
#include "CMsgHandler.h"
#include "CResponseStatusMessage.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: CStartStopChannelMsg::ValidateMsgParam
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
Msg_Error_Codes_Type CStartStopChannelMsg::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;           // error code

   Start_Stop_Channel_Msg_Type* msgData =
      (Start_Stop_Channel_Msg_Type*)&msg.GetMsgData()->theData;  // msg data

   // Check message data parameters, the header is checked when the
   // message is received
   if (((msgData->channelID < 1) || (msgData->channelID > MAX_VLF_CHANNEL)) ||
       (msgData->action >= OES_CHANNEL_ACTION_TYPE_MAX) ||
       (msgData->reserved != UNUSED_VARIABLE_VAL))
   {
      error = PARAM_OUT_OF_RANGE;
   }
   // Validate message action
   else if ((msgData->action == START_CHANNEL) &&
         (CVlf::Instance()->chan[(msgData->channelID - 1)]->
            mCommPlanValid == false))
   {
      error = CHANNEL_NOT_CONFIGURED;
      CVlf::Instance()->chan[msgData->channelID-1]->mChannelError = error;
   }
   else if ((msgData->action == STOP_CHANNEL) &&
            ((CVlf::Instance()->chan[msgData->channelID-1]->mMode15->
             mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
            (CVlf::Instance()->chan[msgData->channelID-1]->mMode9->
             mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
            (CVlf::Instance()->chan[msgData->channelID-1]->mModeHidar->
             mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
            (CVlf::Instance()->chan[msgData->channelID-1]->mMode23->
             mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
            (CVlf::Instance()->chan[msgData->channelID-1]->mModeSMA->
             mChanModeStatus.modeScanState == MODE_IN_SYNC) ))
   {
      error = CHANNEL_IN_SYNC;
   }
   else
   {
      error = VLF_NO_ERROR;
   }

   return (error);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CStartStopChannelMsg::HandleMsg
//!
//! Description: This method handles the start and stop message
//!              from the OES.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: The channel specified must have a valid communication plan
//!        loaded. If a channel is started without a valid comm plan,
//!        the VLF receiver will send an error code of "channel not
//!        configured".  To stop a channel that is in a sync state,
//!        a stop force must be used.  If a stop channel is used, the
//!        VLF receiver will send an error code of "Channel in Sync"
//!        to the OES.
//!
//!        The actual starting and stopping of each Mode Channel will be
//!        performed by one of the sec#_Msg_Proc_Tasks.  This will allow
//!        for time response back from the crypto prior to starting a
//!        Special Mode.
//!
//!
////////////////////////////////////////////////////////////////////////////////
void CStartStopChannelMsg::HandleMsg(CMessage *msg)
{
   if ( check4Null( msg, __FILE__, __LINE__ ))
   {
      return;// All errors handled within check4Null
   }

   Msg_Error_Codes_Type msgError = ValidateMsgParam( *msg ); // msg error

   Start_Stop_Channel_Msg_Type* msgData =
            (Start_Stop_Channel_Msg_Type*)msg->GetMsgData()->theData;  // msg data

   Response_Status_Type msgStatus = NAK;          // msg status

   // Send Nak Message to OES
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

      CMsgHandler::Instance()->SendAckNak( msg->GetSrc(),
                                           msg->GetMsgId(),
                                           msg->GetActionId(),
                                           msgStatus,
                                           msgError);
   }
   // Send out error msg
   else if ( msgError != VLF_NO_ERROR )
   {
      // Change the status based on error code
      if ( ( msgError == CHANNEL_NOT_CONFIGURED ) ||
           ( msgError == CHANNEL_IN_SYNC ) )
      {
         msgStatus = ACK;
      }//else nothing- do not change status

      CMsgHandler::Instance()->SendAckNak( msg->GetSrc(),
                                           msg->GetMsgId(),
                                           msg->GetActionId(),
                                           msgStatus,
                                           msgError,
                                           msgData->channelID );
   }
   // Else, ( msgError == VLF_NO_ERROR )
   else if ( Success != TryToObtainSemaphore( CControlVars::Instance()->
                                              sec_msg_proc_struct[msgData->channelID-1].sMsgAction ) )
   {
      msgStatus = ACK;
      msgError = OPERATION_IN_PROGRESS;
      CMsgHandler::Instance()->SendAckNak( msg->GetSrc(),
                                           msg->GetMsgId(),
                                           msg->GetActionId(),
                                           msgStatus,
                                           msgError,
                                           msgData->channelID );
   }
   // We are within a semaphore, data ok to modify
   else
   {
      // Pass in msg info to the secondary processing variable
      Secondary_Msg_Proc_Type *pSecProcVar = &CControlVars::Instance()->sec_msg_proc_struct[msgData->channelID-1];
      pSecProcVar->secProcMsg.msgActionID = msg->GetActionId();
      pSecProcVar->secProcMsg.msgAction = msgData->action;
      SignalCondition( pSecProcVar->conAction );
      ReleaseSemaphore( pSecProcVar->sMsgAction );
   }
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
