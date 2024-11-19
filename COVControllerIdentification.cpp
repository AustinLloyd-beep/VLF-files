
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVControllerIdentification.cpp
//
// Description:
//    This file contains the class definition for the COVControllerIdentification
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVControllerIdentification.h"
#include "CVlf.h"
#include "CMsgHandler.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVControllerIdentification::ValidateMsgParam
//!
//! Description:
//!   This method validates the message parameters.
//!
//! Parameters:
//!    msg - Message class reference
//!
//! Return:
//!    Msg_Error_Codes_Type
//!
//! Notes: Input parameters checked by calling function.
//!
////////////////////////////////////////////////////////////////////////////////
Msg_Error_Codes_Type COVControllerIdentification::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;  // error code

   Controller_Identification_Msg_Type* msgData =
      (Controller_Identification_Msg_Type*)&msg.GetMsgData()->theData;  // msg data

   // Check message data parameters, the header is checked when the
   // message is received
   if ( ((msgData->mainOES != OES1) && (msgData->mainOES != OES2)) ||
        ((msgData->forceCnrtl != TCN_NORMAL) && (msgData->forceCnrtl != TCN_FORCED)) ||
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
//! Function: COVControllerIdentification::HandleMsg
//!
//! Description:
//!   This method handles the COVControllerIdentification message.  This
//!   will cause the VLF receiver to switch to the newly active OES
//!   for all reponse messages.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: This message maybe received from the standby OES.
//!
////////////////////////////////////////////////////////////////////////////////
void COVControllerIdentification::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type error = ValidateMsgParam (*msg); // validate msg

   Controller_Identification_Msg_Type* msgData =
      (Controller_Identification_Msg_Type*)msg->GetMsgData()->theData;  // msg data

   if (error == VLF_NO_ERROR)
   {
      if (msgData->mainOES == 0)
      {
         CVlf::Instance()->mActiveOES = OES1;
      }
      else
      {
         CVlf::Instance()->mActiveOES = OES2;
      }
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
