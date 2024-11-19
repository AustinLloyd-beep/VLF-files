
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CVOKeyDispositionStatus.cpp
//
// Description:
//    This file contains the class definition for the CVOKeyDispositionStatus
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "CVOKeyDispositionStatus.h"
#include "CVlf.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: BuildDispMsg
//!
//! Description:
//!   This method sends an VO_KEY_DISPOSITION_STATUS message
//!
//! Parameters:
//!   const unsigned int keyBankLoc,
//!   const unsigned int keyBankSegLoc,
//!   const unsigned int status,
//!   const unsigned int reserved
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
CMessage* CVOKeyDispositionStatus::BuildDispMsg (Key_Disposition_Status_Msg_Type& KeyDispMsgData)
{
   snd_msg.SetMsgId(VO_KEY_DISPOSITION_STATUS);
   snd_msg.SetSrc(CVlf::Instance()->mId);
   snd_msg.SetDest(CVlf::Instance()->mActiveOES);
   snd_msg.SetActionId(UNSOLICIT_ACTION_ID); // internal message
   snd_msg.SetMsgData(&KeyDispMsgData, sizeof(Key_Disposition_Status_Msg_Type));

   // send response message
   return (&snd_msg);
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
