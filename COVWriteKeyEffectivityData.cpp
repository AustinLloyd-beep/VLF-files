
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVWriteKeyEffectivityData.cpp
//
// Description:
//    This file contains the class definition for the COVWriteKeyEffectivityData
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVWriteKeyEffectivityData.h"
#include "CVlf.h"
#include "CMsgHandler.h"
#include "CKeyEffectData.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVWriteKeyEffectivityData::ValidateMsgParam
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
Msg_Error_Codes_Type COVWriteKeyEffectivityData::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;    // error

   Write_Key_Effectivity_Data_Msg_Type* msgData =
      (Write_Key_Effectivity_Data_Msg_Type*)&msg.GetMsgData()->theData;  // msg data

   // Check message data parameters, the header is checked when the
   // message is received
   if ((msgData->numKeys < MIN_NUM_KEYS) ||
       (msgData->numKeys > MAX_NUM_KEYS) ||
       (msgData->reserved != UNUSED_VARIABLE_VAL) ||
       ((msgData->lastMsg != 0) && (msgData->lastMsg != 1)))
   {
      error = PARAM_OUT_OF_RANGE;
   }
   else
   {
      for (int keyNum = 0; keyNum < msgData->numKeys; keyNum++)  // loop thru keys
      {
         if ((msgData->KeyEffectData[keyNum].keyValid != 0) &&
               (msgData->KeyEffectData[keyNum].keyValid != 1))
         {
            error = PARAM_OUT_OF_RANGE;
            break;
         }//else nothing- no error

         if (msgData->KeyEffectData[keyNum].keyValid == 1)
         {
            if (((msgData->KeyEffectData[keyNum].keyBankLoc > KEY_BANK_IDX_LAST) ||
                 (msgData->KeyEffectData[keyNum].keyBankLoc < KEY_BANK_IDX_FIRST)) ||
                ((msgData->KeyEffectData[keyNum].keyBankSegLoc < MIN_KEY_BANK_SEG_LOC) ||
                 (msgData->KeyEffectData[keyNum].keyBankSegLoc > MAX_KEY_BANK_SEG_LOC)) ||
                ((msgData->KeyEffectData[keyNum].keyEffectDate.Year < MIN_YEAR_VALUE) ||
                 (msgData->KeyEffectData[keyNum].keyEffectDate.Year > MAX_YEAR_VALUE)) ||
                ((msgData->KeyEffectData[keyNum].keyEffectDate.Month < MIN_MONTH_VALUE) ||
                 (msgData->KeyEffectData[keyNum].keyEffectDate.Month > MAX_MONTH_VALUE)) ||
                ((msgData->KeyEffectData[keyNum].keyEffectDate.Day < MIN_DAY_VALUE) ||
                 (msgData->KeyEffectData[keyNum].keyEffectDate.Day > MAX_DAY_VALUE)) ||
                 (msgData->KeyEffectData[keyNum].reserved != UNUSED_VARIABLE_VAL) )
            {
               error = PARAM_OUT_OF_RANGE;
               break;
            }// else nothing- no error
         }//else nothing- key not valid no need to check data

         error = VLF_NO_ERROR;
      }
   }

   return (error);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVWriteKeyEffectivityData::HandleMsg
//!
//! Description:
//!   This method handles the COVWriteKeyEffectivityData message. This message
//!   is used to support key message sequence.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVWriteKeyEffectivityData::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok
   Msg_Error_Codes_Type error = ValidateMsgParam (*msg);           // error
   Write_Key_Effectivity_Data_Msg_Type* msgData =
      (Write_Key_Effectivity_Data_Msg_Type*)msg->GetMsgData()->theData;  // msgs data
   Response_Status_Type status = NAK;                    // status

   if (error == VLF_NO_ERROR)
   {
      status = ACK;

      //Load Effectivity Data into Class Data Table
      CKeyEffectData::Instance()->setData(*msgData);

      // Set key table data valid if this is the last key message
      CVlf::Instance()->setKeyTblLoadedStatus(msgData->lastMsg);

      // send DSP2 the updated status of the key table
      CVlf::Instance()->UpdateRcvrStatus();

   }//else nothing parameter out of range

   // Send Response back to VCI
   CMsgHandler::Instance()->SendAckNak(msg->GetSrc(), msg->GetMsgId(),
                              msg->GetActionId(), status, error);
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
