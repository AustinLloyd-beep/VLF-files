///////////////////////////////////////////////////////////////////////////////
//
// File Name: CMsgHandler.cc
//
// Description: This is the message handler class definition
//
// Notes: The CMsgHandler class is a singleton
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include "CMsgHandler.h"
#include "CVlf.h"
#include "msg_defs.h"
#include "utility.h"
#include "TMemStrUtility.h"
#include "CResponseStatusMessage.h"

extern MessageQueue queueEthTx;
extern MessageQueue queuePriEthTx;
///////////////////////////////////////////////////////////////////
//! Function: CMsgHandler
//!
//! Description:
//!   This is the class default constructor method
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CMsgHandler::CMsgHandler(){}
///////////////////////////////////////////////////////////////////
//! Function: ~CMsgHandler
//!
//! Description:
//!   This is the class default destructor method
//!
//! Parameters:
//!   none
//!
//! Return:
//!   none
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CMsgHandler::~CMsgHandler()
{
   // if mInstance still exists, delete it
   if (mInstance != NULL)
   {
       delete mInstance;
       mInstance = NULL;
   }
   //else NULL - no action necessary
}
///////////////////////////////////////////////////////////////////
//! Function: RegisterMsg
//!
//! Description:
//!   This method is used to register a message handler
//!
//! Parameters:
//!   msgNo - Message number
//!   ih - pointer to a message handler object
//!
//! Return:
//!   Pointer to message handler
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
InterfaceHandler* CMsgHandler::RegisterMsg(int msgNo, InterfaceHandler *ih)
{
   if ((msgNo >= MAX_MSG_ID_MSGTYPE) || (msgNo < 0))
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (msgNo=" << msgNo << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else
   {
      if ( !check4Null(ih, __FILE__, __LINE__) )
      {
         CMsgHandler::mMsgHandlers[msgNo] = ih;
      }//else nothing- error handled in if statement
   }

   return (ih);
}
///////////////////////////////////////////////////////////////////
//! Function: Instance
//!
//! Description:
//!   This method is used to obtain an instance of the CMsgHandler
//!   class
//!
//! Parameters:
//!   None
//!
//! Return:
//!   Pointer to CMsgHandler object
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CMsgHandler* CMsgHandler::Instance()
{
   if (mInstance == NULL)
   {
      mInstance = new CMsgHandler;

      // Check to see of mInstance is NULL
      (void)check4Null(mInstance, __FILE__, __LINE__);
   }
   //else nothing- mInstance is not NULL

   return mInstance;
}
///////////////////////////////////////////////////////////////////
//! Function: InvokeHandler
//!
//! Description:
//!   This method is used to invoke a registered message handler
//!
//! Parameters:
//!   msg - Message
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CMsgHandler::InvokeHandler(CMessage* msg)
{
   if ( !check4Null(msg, __FILE__, __LINE__) )
   {
      if (CMsgHandler::mMsgHandlers[msg->GetMsgId()] != NULL)
      {
          CMsgHandler::mMsgHandlers[msg->GetMsgId()]->HandleMsg(msg);
      }
      // else null message don't handle message.
   }//else nothing- error handled in if statement
}
///////////////////////////////////////////////////////////////////
//! Function: SendMsgHelper
//!
//! Description:
//!   This method is used to send a message out the Ethernet
//!
//! Parameters:
//!   msg - Message to send
//!   queue - Message queue to use for message
//!
//! Notes:
//!   This helper function was created to eliminate the detection of
//!   duplicate algorithms in the code as reported by the customer's
//!   analysis tool
//!
///////////////////////////////////////////////////////////////////
void CMsgHandler::SendMsgHelper(CMessage* msg, MessageQueue queue)
{
   // check message queue buffer
   if ( ( !check4Null(msg, __FILE__, __LINE__) ) &&
        ( !check4Null(queue, __FILE__, __LINE__)))
   {
      Message_Type* sendbuff = NULL;  // send buffer

      // calculate and set the message checksum
      msg->SetMsgChecksum();
      // send message to EthTxQueue
      Error error = AllocateMessageQueueBuffer(queue, (void **)&sendbuff);  // alloc buffer
      if (error == Success)
      {
         memcpy_safe (sendbuff, msg->GetMsgData(), msg->GetMsgLen());
         CHECK(SendOnMessageQueue(queue, sendbuff),
                        __FILE__, __FUNCTION__, __LINE__);
      }
      else
      {
         CHECK(error, __FILE__, __FUNCTION__, __LINE__);
      }
   }//else nothing- queue not registered, do not send msgs
}
///////////////////////////////////////////////////////////////////
//! Function: SendMsg
//!
//! Description:
//!   This method is used to send a message out the Ethernet
//!
//! Parameters:
//!   msg - Message to send
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CMsgHandler::SendMsg(CMessage* msg)
{
   // Invoke the helper function to eliminate duplicate algorithm detected
   // by customer's analysis tool.
   SendMsgHelper(msg, queueEthTx);
}
///////////////////////////////////////////////////////////////////
//! Function: SendPriMsg
//!
//! Description:
//!   This method is used to send a priority message out the Ethernet
//!
//! Parameters:
//!   msg - Message to send
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CMsgHandler::SendPriMsg(CMessage* msg)
{
   // Invoke the helper function to eliminate duplicate algorithm detected
   // by customer's analysis tool.
   SendMsgHelper(msg, queuePriEthTx);
}
///////////////////////////////////////////////////////////////////
//! Function: SendAckNak
//!
//! Description:
//!   This method sends an Ack/Nak response message
//!
//! Parameters:
//!   dest - destination subsystem
//!   toMsgId - original message ID
//!   actionId - Action ID
//!   status - response status
//!   error - reponse error
//!   channelID - channel ID
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CMsgHandler::SendAckNak(Subsystem_Type dest, Message_ID_Type toMsgId,
                         int actionId, Response_Status_Type status,
                         Msg_Error_Codes_Type error, short channelID)
{
   // fill response data
   // rsp_data is initialized using the memset_safe following the declaration
   Response_Status_Msg_Type rsp_data;  // rsp data
   memset_safe(&rsp_data, 0, sizeof(Response_Status_Msg_Type));
   rsp_data.Status = status;
   rsp_data.respToMsgID = toMsgId;
   rsp_data.errorCode = error;
   rsp_data.channelID = channelID;

   // fill message and send
   // rsp_msg is initialized in the constructor
   CMessage rsp_msg;  // rsp msg
   rsp_msg.SetMsgId(RESPONSE_STATUS_MSGTYPE);
   rsp_msg.SetSrc(CVlf::Instance()->mId);
   rsp_msg.SetDest(dest);
   rsp_msg.SetActionId(actionId);
   (void)rsp_msg.SetMsgData(&rsp_data, sizeof(Response_Status_Msg_Type));
   SendMsg(&rsp_msg);
}
///////////////////////////////////////////////////////////////////
//! Function: SendPriAckNak
//!
//! Description:
//!   This method sends an Ack/Nak response message on the priority
//!   queue
//!
//! Parameters:
//!   dest - destination subsystem
//!   toMsgId - original message ID
//!   actionId - Action ID
//!   status - response status
//!   error - reponse error
//!   channelID - channel ID
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CMsgHandler::SendPriAckNak(Subsystem_Type dest, Message_ID_Type toMsgId,
                         int actionId, Response_Status_Type status,
                         Msg_Error_Codes_Type error, short channelID)
{
   // fill response data
   // rsp_data is initialized using the memset_safe following the declaration
   Response_Status_Msg_Type rsp_data;  // rsp data
   memset_safe(&rsp_data, 0, sizeof(Response_Status_Msg_Type));
   rsp_data.Status = status;
   rsp_data.respToMsgID = toMsgId;
   rsp_data.errorCode = error;
   rsp_data.channelID = channelID;

   // fill message and send
   // rsp_msg is initialized in the constructor
   CMessage rsp_msg;  // rsp msg
   rsp_msg.SetMsgId(RESPONSE_STATUS_MSGTYPE);
   rsp_msg.SetSrc(CVlf::Instance()->mId);
   rsp_msg.SetDest(dest);
   rsp_msg.SetActionId(actionId);
   (void)rsp_msg.SetMsgData(&rsp_data, sizeof(Response_Status_Msg_Type));
   SendPriMsg(&rsp_msg);
}
InterfaceHandler* CMsgHandler::mMsgHandlers[MAX_MSG_ID_MSGTYPE] = {0};
// mInstance is used throughout CMsgHandler
CMsgHandler* CMsgHandler::mInstance = NULL;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification:  UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
