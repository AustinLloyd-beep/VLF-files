
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVRequestSystemStatus.cpp
//
// Description:
//    This file contains the class definition for the COVRequestSystemStatus
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVRequestSystemStatus.h"
#include "CVlf.h"
#include "CMsgHandler.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVRequestSystemStatus::ValidateMsgParam
//!
//! Description:
//!   This method validates the message parameters.
//!   No parameters so return VLF_NO_ERROR
//!
//! Parameters:
//!    msg - Message class reference - NOT USED
//!
//! Return:
//!    Msg_Error_Codes_Type
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
Msg_Error_Codes_Type COVRequestSystemStatus::ValidateMsgParam(const CMessage& msg)
{
   // There are parameters to validate so just return no error
   return (VLF_NO_ERROR);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVRequestSystemStatus::HandleMsg
//!
//! Description: This method handles the COVRequestSystemStatus message
//!              from DSP2.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! NOTE: None
//!
////////////////////////////////////////////////////////////////////////////////
void COVRequestSystemStatus::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type error = ValidateMsgParam (*msg);   // error code

   if (error == VLF_NO_ERROR)
   {
      // fill message and send
      // rsp_msg is initialized in the constructor
      CMessage rsp_msg;  // rsp msg
      rsp_msg.SetMsgId(VO_CVR_SYSTEM_STATUS_MSGTYPE);
      rsp_msg.SetSrc(CVlf::Instance()->mId);
      rsp_msg.SetDest(DSP2);
      rsp_msg.SetActionId(msg->GetActionId());
      (void)rsp_msg.SetMsgData(&CVlf::Instance()->mRcvrStatus,
         sizeof(VLF_Receiver_System_Status_Msg_Type));

      // send response message to DSP2
      CMsgHandler::Instance()->SendMsg(&rsp_msg);
   }
   else
   {
      // Send software anamoly message to the OES
      // errStr is initialized in the constructor
      std::ostringstream errStr ( "" );  // error string
      errStr << "Invalid Msg Param, Msgid: "
             << msg->GetMsgId() << "ActionId: "
             << msg->GetActionId() << " ("
             << __FILE__ << " Line: " << __LINE__<< ")" << std::ends;
      send_sa_msg ( errStr.str().c_str() );
   }
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
