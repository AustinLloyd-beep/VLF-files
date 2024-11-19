
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CCVLoadedKeyInfoMsg.cpp
//
// Description:
//    This file contains the class definition for the CCVLoadedKeyInfoMsg
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "CCVLoadedKeyInfoMsg.h"
#include "CMessage.h"
#include "CMsgHandler.h"
#include "CKeyEffectData.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: CCVLoadedKeyInfoMsg::ValidateMsgParam
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
Msg_Error_Codes_Type CCVLoadedKeyInfoMsg::ValidateMsgParam(const CMessage& msg)
{
   // No parameters to check so just pass no error
   return (VLF_NO_ERROR);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CCVLoadedKeyInfoMsg::HandleMsg
//!
//! Description:
//!   This method handles the CCVLoadedKeyInfoMsg message
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes:
//!    None
//!
////////////////////////////////////////////////////////////////////////////////
void CCVLoadedKeyInfoMsg::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   if ((ValidateMsgParam (*msg)) == VLF_NO_ERROR)
   {
      Loaded_Key_Info_Msg_Type* msgData =
      (Loaded_Key_Info_Msg_Type*)msg->GetMsgData()->theData;   // get msg data

      if ( check4Null(msgData, __FILE__, __LINE__) )
      {
         return;// All errors handled within check4Null
      }//else nothing- input parameter check ok

      CKeyEffectData::Instance()->setKeyPresent(*msgData);
   }
   else
   {
      // Send software anamoly message
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
