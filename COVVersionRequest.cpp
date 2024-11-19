
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVVersionRequest.cpp
//
// Description:
//    This file contains the class definition for the COVVersionRequest
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVVersionRequest.h"
#include "CVlf.h"
#include "CMsgHandler.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVVersionRequest::ValidateMsgParam
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
Msg_Error_Codes_Type COVVersionRequest::ValidateMsgParam(const CMessage& msg)
{
   // There are parameters to validate so just return no error
   return (VLF_NO_ERROR);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVVersionRequest::HandleMsg
//!
//! Description: This method handles the COVVersionRequest message
//!              from DSP2
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! NOTE:  None
//!
////////////////////////////////////////////////////////////////////////////////
void COVVersionRequest::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type error = ValidateMsgParam (*msg);   // error code

   if (error == VLF_NO_ERROR)
   {
      // Send Version Data to DSP2
      CVlf::Instance()->SendDSP2VersionData();
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
