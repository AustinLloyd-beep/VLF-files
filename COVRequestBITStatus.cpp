
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVRequestBITStatus.cpp
//
// Description:
//    This file contains the class definition for the COVRequestBITStatus
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVRequestBITStatus.h"
#include "CVlf.h"
#include "CMsgHandler.h"
#include "TMemStrUtility.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVRequestBITStatus::ValidateMsgParam
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
Msg_Error_Codes_Type COVRequestBITStatus::ValidateMsgParam(const CMessage& msg)
{
   // There are parameters to validate so just return no error
   return (VLF_NO_ERROR);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVRequestBITStatus::HandleMsg
//!
//! Description: This method handles the COVRequestBITStatus message
//!              received from DSP.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! NOTE: None
//!
////////////////////////////////////////////////////////////////////////////////
void COVRequestBITStatus::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type error = ValidateMsgParam (*msg);   // error

   // fill response data
   // rsp_data is initialized with the memset_safe following declaration
   BIT_Result_Type  rsp_data;  // rsp data
   memset_safe(&rsp_data, UNUSED_VARIABLE_VAL, sizeof(BIT_Result_Type));

   if (error == VLF_NO_ERROR)
   {
      // send PBIT Status to DSP2.
      rsp_data.result = CVlf::Instance()->mDspPBit.result;

      // fill response message and send to DSP2.
      // DSP2 then forward this message to OES.
      // rsp_msg is initialized in the constructor
      CMessage rsp_msg;   // rsp msg
      rsp_msg.SetMsgId(VV_DSP1_PBIT_RESULT_MSGTYPE);
      rsp_msg.SetSrc(CVlf::Instance()->mId);
      rsp_msg.SetDest(DSP2);
      rsp_msg.SetActionId(msg->GetActionId());
      (void) rsp_msg.SetMsgData(&rsp_data, sizeof(BIT_Result_Type));
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
