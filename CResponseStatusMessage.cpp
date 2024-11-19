
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CResponceStatusMessage.cpp
//
// Description:
//    This file contains the class definition for the  Responce Status Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>

#include "CResponseStatusMessage.h"
#include "CControlVars.h"
#include "utility.h"
#include "CVlf.h"
#include "CKeyEffectData.h"
#include "CMsgHandler.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: CResponseStatusMessage::ValidateMsgParam
//!
//! Description: This method validates the message parameters.
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
Msg_Error_Codes_Type CResponseStatusMessage::ValidateMsgParam(const CMessage& msg)
{
   return ValidateResponseStatusMsgParam( msg );
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CResponseStatusMessage::HandleMsg
//!
//! Description:
//!   This method handles the message status responses received
//!              by DSP1
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! NOTE: None
//!
////////////////////////////////////////////////////////////////////////////////
void CResponseStatusMessage::HandleMsg( CMessage* msg )
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type error = ValidateMsgParam ( *msg );
   Response_Status_Msg_Type* msgData =
     ( Response_Status_Msg_Type* )msg->GetMsgData()->theData;   // get msg data

   if (error == VLF_NO_ERROR)
   {
      if ( msg->GetSrc() == CP )
      {
         CDspBIT::Instance()->updateLinkAliveCount ( CDspBIT::CP_TO_DSP1_COMM );
         HandleCpResponses ( msg );
      }
      else
      {
         if ( msg->GetSrc() == DSP2 )
         {
            CDspBIT::Instance()->updateLinkAliveCount ( CDspBIT::DSP2_TO_DSP1_COMM );
         }
         //else nothing- do not monitor other sources
      }
   }
   // This condition should not happen,
   // If it does send out software anomaly msg
   else
   {
      // str is initialized in the constructor
      std::ostringstream str ( "" );  // string stream
      str << "ResponseStatusMessage Error. "
          << __FILE__ << " Line: " << __LINE__
          << " MsgID: "  << msgData->respToMsgID << "Error: "
          << msgData->errorCode << " Status: " << msgData->Status
          << ". From:: Src-"<< msg->GetSrc() << std::ends;
      send_sa_msg ( str.str().c_str() );
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CResponseStatusMessage::HandleCpResponses
//!
//! Description: This method handles the responses for Crypto Messages.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return:
//!    None
//!
//! Notes: class pointer checked by calling function
//!
////////////////////////////////////////////////////////////////////////////////
void CResponseStatusMessage::HandleCpResponses(CMessage* msg)
{
   if (NULL != msg)
   {
      Response_Status_Msg_Type* msgData =
         (Response_Status_Msg_Type*)msg->GetMsgData()->theData;    // msg data

      //
      // Handle Responses from CP
      // Process any commands that need to be done here
      switch ( msgData->respToMsgID )
      {
         case VC_CONFIGURE_CHANNEL_MSGTYPE:
            HandleConfigureChannelResponse ( msgData, msg->GetActionId() );
            break;

         case VC_RUNUP_CHANNEL_MSGTYPE:
            HandleRunupChannelResponse ( msgData, msg->GetActionId() );
            break;

         case VC_ZEROIZE_CHANNEL_MSGTYPE:
            HandleZeroizeChannelResponse ( msgData, msg->GetActionId() );
            break;

         case VC_SELECTIVE_ZEROIZE_KEY_DATA_MSGTYPE:
            HandleSelectiveZeroizeResponse( msgData );
            break;

         default:
            // only print out error codes, this should not happen
            // send out software anomaly if it does
            if (msgData->errorCode != VLF_NO_ERROR)
            {
               // str is initialized in the constructor
               std::ostringstream str ( "" ); // string stream
               str << "ResponseStatusMessage Error. "
                   << __FILE__ << " Line: " << __LINE__
                   << " MsgID: "  << msgData->respToMsgID << "Error: "
                   << msgData->errorCode <<
                      ". From:: Src-"<< msg->GetSrc() << std::ends;
               send_sa_msg ( str.str().c_str() );
            } // else nothing - no error to output
            break;
      }
   }
   else
   {
      // str is initialized in the constructor
      std::ostringstream str ( "" ); // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "NULL parameter (msg)." << std::ends;
      send_sa_msg ( str.str().c_str() );
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CResponseStatusMessage::HandleSelectiveZeroizeResponse
//!
//! Description: This method handles the Selective Zeroize Responses
//!              from the Crypto CSCI.
//!
//! Parameters:
//!    Response_Status_Msg_Type* msgData- pointer to message data
//!
//! Return:
//!    None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void CResponseStatusMessage::HandleSelectiveZeroizeResponse
                                  (Response_Status_Msg_Type* msgData)
{
   if ( check4Null(msgData, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Error condError = Failure;   // condition error

   // get semaphore- signal condition variable
   condError = TryToObtainSemaphore(CControlVars::Instance()->sSelZerMsgResponse);

   if (Success == condError)
   {
      // set key disposition status
      if (msgData->errorCode == VLF_NO_ERROR)
      {
         CKeyEffectData::Instance()->setKeyDispStatus(PASS);
      }
      else
      {
         CKeyEffectData::Instance()->setKeyDispStatus(FAILURE);
      }

      SignalCondition( CControlVars::Instance()->conSelZerResponse );
      ReleaseSemaphore( CControlVars::Instance()->sSelZerMsgResponse );
   }
   else
   {
      // str is initialized in the constructor
      std::ostringstream str ( "" ); // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Semaphore sSelZerMsgResponse Locked, Unable to Signal Key_Mgr_Proc_Task." << std::ends;
      send_sa_msg ( str.str().c_str() );
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CResponseStatusMessage::GetHandleChanData
//!
//! Description: This method retrieves channel-specific data used by the
//!              common channel response handler.
//!
//! Parameters:
//!    Hndl_Ch_Resp_Type hndlType- identifies the message type being handled
//!    const unsigned int chanNum- channel number
//!    Semaphore& hndlrSem- pointer for applicable semaphore
//!    Condition& hndlrCon- pointer for applicable condition
//!    Msg_Error_Codes_Type& hndlrErr- reference to be filled in for error
//!
//! Return:
//!    None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void CResponseStatusMessage::GetHandlerChanData
                                   (const Hndl_Ch_Resp_Type hndlType,
                                    const unsigned int chanNum,
                                    Semaphore** hndlrSem,
                                    Condition** hndlrCon,
                                    Msg_Error_Codes_Type& hndlrErr )
{
   if (HNDL_CONFIG_CH_RESP == hndlType)
   {
      hndlrErr = CP_CHANNEL_NOT_CONFIGURED;
      *hndlrSem = &(CControlVars::Instance()->sec_msg_proc_struct[chanNum].sMsgConfig);
      *hndlrCon = &(CControlVars::Instance()->sec_msg_proc_struct[chanNum].conConfig);
   }
   else if (HNDL_RUNUP_CH_RESP == hndlType)
   {
      hndlrErr = CP_CHANNEL_NOT_STARTED;
      *hndlrSem = &(CControlVars::Instance()->sec_msg_proc_struct[chanNum].sMsgRunup);
      *hndlrCon = &(CControlVars::Instance()->sec_msg_proc_struct[chanNum].conRunup);
   }
   else if (HNDL_ZEROIZE_CH_RESP == hndlType)
   {
      hndlrErr = CHANNEL_NOT_ZEROIZED;
      *hndlrSem = &(CControlVars::Instance()->sec_msg_proc_struct[chanNum].sMsgZeroize);
      *hndlrCon = &(CControlVars::Instance()->sec_msg_proc_struct[chanNum].conZeroize);
   }
   else
   {
      hndlrErr = UNKNOWN_ERROR;
      std::ostringstream errStr;  // error string
      errStr << "Invalid Hndl_Ch_Resp_Type in GetHandlerChanData: "
             << __FUNCTION__
             << " (" << __FILE__ << " Line: " << __LINE__<< ")" << std::ends;
      send_sa_msg ( errStr.str().c_str() );
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CResponseStatusMessage::DisplayUnsolicitActionIdMsg
//!
//! Description: This method displays an error message used by the
//!              common channel response handler.
//!
//! Parameters:
//!    Hndl_Ch_Resp_Type hndlType- identifies the message type being handled
//!    unsigned int chanNum- channel number
//!
//! Return:
//!    None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void CResponseStatusMessage::DisplayUnsolicitActionIdMsg
                                  (const Hndl_Ch_Resp_Type hndlType,
                                   const unsigned int chanNum )
{
   // str is initialized in the constructor
   std::ostringstream str ( "" ); // string stream
   str << "VLF/LF RELIABILITY ERROR: "
       << __FILE__ << " Line: " << __LINE__ << " "
       << "Semaphore sec_msg_proc_struct["
       << chanNum
       << "].sMsg"
       << (hndlType == HNDL_CONFIG_CH_RESP ? "Config" :
           hndlType == HNDL_RUNUP_CH_RESP ? "Runup" :
           hndlType == HNDL_ZEROIZE_CH_RESP ? "Zeroize" :
           "Unknown")
       << "Locked, "
       << (hndlType == HNDL_CONFIG_CH_RESP ? "Configure" :
           hndlType == HNDL_RUNUP_CH_RESP ? "Runup" :
           hndlType == HNDL_ZEROIZE_CH_RESP ? "Zeroize" :
           "Unknown")
       << " CP Channel, Failed for Channel "
       << chanNum +1U << std::ends;
   send_sa_msg ( str.str().c_str() );
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CResponseStatusMessage::HandleCommonChannelResponse
//!
//! Description: This method implements a common algorithm for handling
//!              selected Channel Response messages from the Crypto CSCI.
//!
//! Parameters:
//!    Response_Status_Msg_Type* msgData- pointer to message data
//!    const unsigned int& actionID- reference to action ID
//!    Hndl_Ch_Resp_Type hndlType- handle response type
//!
//! Return:
//!    None
//!
//! Notes:
//!   This helper function was created to eliminate the detection of duplicate
//!   algorithms in the code as reported by the customer's analysis tool.

//!
////////////////////////////////////////////////////////////////////////////////
void CResponseStatusMessage::HandleCommonChannelResponse
                                  (Response_Status_Msg_Type* msgData,
                                   const unsigned int& actionID,
                                   Hndl_Ch_Resp_Type hndlType)
{
   if ((msgData != NULL) &&
      ((msgData->channelID <= MAX_VLF_CHANNEL) &&
       (msgData->channelID > 0)) )
   {
      Response_Status_Type rspStatus = (Response_Status_Type)msgData->Status;     // rsp status
      Msg_Error_Codes_Type rspError = (Msg_Error_Codes_Type)msgData->errorCode;   // rsp error
      Error condError = Failure;                     // condition error
      unsigned int chanNum = msgData->channelID - 1; // reduce for array index
      Semaphore *hndlrSem = NULL;
      Condition *hndlrCon = NULL;
      Msg_Error_Codes_Type hndlrErr = UNKNOWN_ERROR;

      GetHandlerChanData( hndlType, chanNum, &hndlrSem, &hndlrCon, hndlrErr );

      condError = TryToObtainSemaphore( *hndlrSem );

      if ( Success == condError )
      {
         //save the error code
         CControlVars::Instance()->
         sec_msg_proc_struct[chanNum].secProcMsg.msgError = rspError;

         SignalCondition( *hndlrCon );

         ReleaseSemaphore( *hndlrSem );
      }
      else
      {
         // Send Ack/Nak Message Back to OES if valid ActionID
         if ( actionID != UNSOLICIT_ACTION_ID )
         {
            rspError = hndlrErr;
            // send OES response message
            CMsgHandler::Instance()->SendAckNak(CVlf::Instance()->mActiveOES,
               OV_START_STOP_CHANNEL_MSGTYPE, actionID, rspStatus, rspError);
         }
         else
         {
            DisplayUnsolicitActionIdMsg( hndlType, chanNum );
         }
      }
   }
   else
   {
      std::ostringstream errStr;  // error string
      errStr << "Invalid Msg Param in ResponseStatusMessage: "
             << __FUNCTION__
             << " (" << __FILE__ << " Line: " << __LINE__<< ")" << std::ends;
      send_sa_msg ( errStr.str().c_str() );
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CResponseStatusMessage::HandleConfigureChannelResponse
//!
//! Description: This method handles the Configure CP Channel Responses
//!              from the Crypto CSCI.
//!
//! Parameters:
//!    Response_Status_Msg_Type* msgData- pointer to message data
//!    unsigned int actionID- action identifier
//!
//! Return:
//!    None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void CResponseStatusMessage::HandleConfigureChannelResponse
                                  (Response_Status_Msg_Type* msgData,
                                   const unsigned int& actionID)
{
   // Invoke the helper function to eliminate duplicate algorithm detected
   // by customer's analysis tool.
   HandleCommonChannelResponse( msgData, actionID, HNDL_CONFIG_CH_RESP );
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CResponseStatusMessage::HandleRunupChannelResponse
//!
//! Description: This method handles the Runup CP Channel Responses
//!              from the Crypto CSCI.
//!
//! Parameters:
//!    Response_Status_Msg_Type* msgData- pointer to message data
//!    unsigned int actionID- action identifier
//!
//! Return:
//!    None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void CResponseStatusMessage::HandleRunupChannelResponse
                                  (Response_Status_Msg_Type* msgData,
                                   const unsigned int& actionID)
{
   // Invoke the helper function to eliminate duplicate algorithm detected
   // by customer's analysis tool.
   HandleCommonChannelResponse( msgData, actionID, HNDL_RUNUP_CH_RESP );
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CResponseStatusMessage::HandleZeroizeChannelResponse
//!
//! Description: This method handles the Zeroize CP Channel Responses
//!              from the Crypto CSCI.
//!
//! Parameters:
//!    Response_Status_Msg_Type* msgData- pointer to message data
//!    const unsigned int& actionID- for response msg
//!
//! Return:
//!    None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void CResponseStatusMessage::HandleZeroizeChannelResponse
                                  (Response_Status_Msg_Type* msgData,
                                   const unsigned int& actionID)
{
   // Invoke the helper function to eliminate duplicate algorithm detected
   // by customer's analysis tool.
   HandleCommonChannelResponse( msgData, actionID, HNDL_ZEROIZE_CH_RESP );
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////

