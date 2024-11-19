
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVLinkIsAlive.cpp
//
// Description:
//    This file contains the class definition for the COVLinkIsAlive
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#include "COVLinkIsAlive.h"
#include "CMsgHandler.h"
////////////////////////////////////////////////////////////////////////////////
//! Function: COVLinkIsAlive::ValidateMsgParam
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
Msg_Error_Codes_Type COVLinkIsAlive::ValidateMsgParam(const CMessage& msg)
{
   // There are parameters to validate so just return no error
   return (VLF_NO_ERROR);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVLinkIsAlive::HandleMsg
//!
//! Description: This method handles the COVLinkIsAlive message
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! NOTE: None
//!
////////////////////////////////////////////////////////////////////////////////
void COVLinkIsAlive::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type error = ValidateMsgParam (*msg);   // error code
   Response_Status_Type status = NAK;

   if (error == VLF_NO_ERROR)
   {
      status = ACK;
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

   // send Ack/Nak Message to OES
   CMsgHandler::Instance()->SendAckNak(msg->GetSrc(), msg->GetMsgId(),
                            msg->GetActionId(), status, error);
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
