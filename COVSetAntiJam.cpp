
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVSetAntiJam.cpp
//
// Description:
//    This file contains the class definition for the COVSetAntiJam
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVSetAntiJam.h"
#include "CVlf.h"
#include "CMsgHandler.h"
#include "CControlVars.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVSetAntiJam::ValidateMsgParam
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
Msg_Error_Codes_Type COVSetAntiJam::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;    // error

   AJ_Cmd_Msg_Type* msgData =
      (AJ_Cmd_Msg_Type*)&msg.GetMsgData()->theData;  // msg data

   // Check message data parameters, the header is checked when the
   // message is received
   if (((msgData->channelID < 1) || (msgData->channelID > MAX_VLF_CHANNEL)) ||
       ((msgData->antiJamOnly != 0) &&
        (msgData->antiJamOnly != 1)) ||
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
//! Function: COVSetAntiJam::HandleMsg
//!
//! Description:
//!   This method handles the COVSetAntiJam message from the OES.  The
//!   anti jam parameter is sent to DSP1 and than to mode address
//!   space via the command queue for processing.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void COVSetAntiJam::HandleMsg( CMessage *msg )
{
   if ( check4Null( msg, __FILE__, __LINE__ ) )
   {
      return;// All errors handled within check4Null
   }//else nothing

    Msg_Error_Codes_Type msgError = ValidateMsgParam( *msg ); // error code
   AJ_Cmd_Msg_Type *msgData = (AJ_Cmd_Msg_Type*)msg->GetMsgData()->theData; // msg data
   Response_Status_Type msgStatus = NAK;          // status
   int chanIdIdx = 0;                             // the channel ID index

   // Send Nak Message to VCI
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
      if ( msgError == VLF_NO_ERROR )
      {
         chanIdIdx = msgData->channelID - 1;
         msgStatus = ACK;

         // Set the antiJam flag
         CVlf::Instance()->chan[chanIdIdx]->mAntiJamOnly = msgData->antiJamOnly;

         // Send out a channel status update if channel is not active
         if ( CVlf::Instance()->chan[chanIdIdx]->mCurrentChanAction != START_CHANNEL )
         {
            CVlf::Instance()->chan[chanIdIdx]->ReportChStatus();
         }
         // Only send action to channels if started
         else if ( Success != TryToObtainSemaphore( CControlVars::Instance()->
                                                    sec_msg_proc_struct[chanIdIdx].sMsgAction ) )
         {
            msgError = OPERATION_IN_PROGRESS;
         }
         // Pass in msg info to the secondary processing variable
         // We are within a semaphore, data ok to modify
         else
         {
            CControlVars::Instance()->sec_msg_proc_struct[chanIdIdx].
               secProcMsg.msgActionID = UNSOLICIT_ACTION_ID;

            CControlVars::Instance()->sec_msg_proc_struct[chanIdIdx].
               secProcMsg.msgAction = msgData->antiJamOnly ? ACTIVATE_ANTI_JAM : DEACTIVATE_ANTI_JAM;

            SignalCondition( CControlVars::Instance()->sec_msg_proc_struct[chanIdIdx].conAction );
            ReleaseSemaphore( CControlVars::Instance()->sec_msg_proc_struct[chanIdIdx].sMsgAction );
         }
      }
      // Else, NAK with the message error

      // Send Ack/Nak Message to OES
      CMsgHandler::Instance()->SendAckNak( msg->GetSrc(), msg->GetMsgId(),
                                           msg->GetActionId(), msgStatus, msgError,
                                           msgData->channelID );
   }
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
