
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVReadVlfChannel.cpp
//
// Description:
//    This file contains the class definition for the COVReadVlfChannel
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVReadVlfChannel.h"
#include "CVlf.h"
#include "TMemStrUtility.h"
#include "CMsgHandler.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVReadVlfChannel::ValidateMsgParam
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
Msg_Error_Codes_Type COVReadVlfChannel::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;      // error code

Read_Vlf_Channel_Msg_Type* msgData =
      (Read_Vlf_Channel_Msg_Type*)&msg.GetMsgData()->theData;  // msg data

   // Check message data parameters, the header is checked when the
   // message is received
   if ( (msgData->channelID > MAX_VLF_CHANNEL) ||
        (msgData->channelID < 1) ||
        (msgData->reserved != UNUSED_VARIABLE_VAL) )
   {
      error = PARAM_OUT_OF_RANGE;
   }
   else
   {
      error = VLF_NO_ERROR;
   }

   return (error);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: COVReadVlfChannel::HandleMsg
//!
//! Description:
//!   This method handles the COVReadVlfChannel message.
//!
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: This message is currently not used by the VCI.
//!
////////////////////////////////////////////////////////////////////////////////
void COVReadVlfChannel::HandleMsg( CMessage *msg )
{
   if ( check4Null( msg, __FILE__, __LINE__ ) )
   {
      return;// All errors handled within check4Null
   }// else nothing

   Msg_Error_Codes_Type msgError = ValidateMsgParam( *msg );  // msg error code
   Response_Status_Type msgStatus = NAK;           // msg status
   int chanIdIdx = 0;                              // the channel ID index
   Read_Vlf_Channel_Msg_Type *msgData =
      (Read_Vlf_Channel_Msg_Type*)msg->GetMsgData()->theData;     // msg data

   if ( PARAM_OUT_OF_RANGE == msgError )
   {
      // errStr is initialized in the constructor
      std::ostringstream errStr ( "" );  // error string
      errStr << "Invalid Msg Param, Msgid: "
      << msg->GetMsgId() << "ActionId: "
      << msg->GetActionId()
      << " (" << __FILE__ << " Line: " << __LINE__<< ")" << std::ends;
      send_sa_msg ( errStr.str().c_str() );

      CMsgHandler::Instance()->SendAckNak( msg->GetSrc(), msg->GetMsgId(),
                                           msg->GetActionId(), msgStatus, msgError );
   }
   // Send Nak Message to OES
   else if ( msgError != VLF_NO_ERROR )
   {
      CMsgHandler::Instance()->SendAckNak( msg->GetSrc(), msg->GetMsgId(),
                                           msg->GetActionId(), msgStatus, msgError,
                                           msgData->channelID );
   }
   // Else ( msgError == VLF_NO_ERROR ), send Ack Message to VCI
   else
   {
      msgStatus = ACK;
      chanIdIdx = msgData->channelID - 1;

      // Comm plan is not valid, send back error msg
      if ( !CVlf::Instance()->chan[chanIdIdx]->mCommPlanValid )
      {
         msgError = CHANNEL_NOT_CONFIGURED;
         CMsgHandler::Instance()->SendAckNak( msg->GetSrc(), msg->GetMsgId(),
                                              msg->GetActionId(), msgStatus, msgError,
                                              msgData->channelID );
      }
      // If there is valid data send all data
      else
      {
         // rsp_msg is initialized in the constructor
         CMessage rsp_msg;  // rsp msg
         // rsp_data is initialized with the memset_safe following declaration
         Vlf_Channel_Data_Msg_Type rsp_data;    // rsp data

         // Fill response data
         memset_safe( &rsp_data, UNUSED_VARIABLE_VAL, sizeof( rsp_data ) );
         rsp_data.validCommPlan = true;
         rsp_data.commPlan = CVlf::Instance()->chan[chanIdIdx]->mCommPlan;

         // Fill message and send
         rsp_msg.SetMsgId( VO_VLF_CHANNEL_DATA_MSGTYPE );
         rsp_msg.SetSrc( CVlf::Instance()->mId );
         rsp_msg.SetDest( msg->GetSrc() );
         rsp_msg.SetActionId( msg->GetActionId() );
         rsp_msg.SetMsgData( &rsp_data, sizeof( rsp_data ) );

         // Send response message to OES
         CMsgHandler::Instance()->SendMsg( &rsp_msg );
      }
   }
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
