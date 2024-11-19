
///////////////////////////////////////////////////////////////////////////////
//
// Function: process key disposition
//
// File Name: key_Mgr_Proc_Task.cc
//
// Description: The task handles the key management for automatically removing
//              outdated keys.
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include <sstream>
#include "KgrVpApp_integrate.h"
#include "CMessage.h"
#include "utility.h"
#include "CMsgHandler.h"
#include "CVlf.h"
#include "TMemStrUtility.h"
#include "mqueue.h"
#include "CControlVars.h"
#include "CKeyEffectData.h"
#include "CTimeLoad.h"

// Local Address Space queue
MessageQueue queueKeyMgr;

//function predeclarations
void init_task_variables ();
void wait4CryptoResponse ();
void handleKeyDisposition ( Key_Bank_Info_Type* msgData );


////////////////////////////////////////////////////////////////////////////////
//! Function: key_Mgr_Proc_Task
//!
//! Description: This is the main body of the task.  It is called in the INT file
//!              as part of the OS startup.  This task is responsible for actions
//!              for key disposition.
//!
//! Parameters:  None
//!
//! Return:  None
//!
//! Notes:
//!   This task performs the following functions:
//!
//!   1) This task will wait until a message is received on the queue.
//!   2) It will send the message to the crypto processor to delete
//!       the selected key.
//!   3) The task will then use a timed-wait on condition to wait for
//!       the pass or failure of the key. (failures are reported to
//!       operator in the software anomaly message)
//!   4) repeat
//!
//!
////////////////////////////////////////////////////////////////////////////////
void key_Mgr_Proc_Task ()
{
   Key_Bank_Info_Type *buffer = NULL;   // buffer

   // setup all variables
   init_task_variables ( );

   while ( true )
   {
      // Wait for message from the Key Manager queue
      CHECK(ReceiveOnMessageQueue(queueKeyMgr, (void**)&buffer),
         __FILE__, __FUNCTION__, __LINE__);

      // call the handler to use the data
      handleKeyDisposition ( buffer );

      // release the message buffer
      CHECK(FreeMessageQueueBuffer(queueKeyMgr, (void**)&buffer),
         __FILE__, __FUNCTION__, __LINE__);

      // hold on condition variable
      wait4CryptoResponse( );

   }//end task loop
}

////////////////////////////////////////////////////////////////////////////////
//! Function: init_task_variables
//!
//! Description: This is the function is used to initialize the semaphores and
//!              condition variable and setup the queue.
//!
//! Parameters: None
//!
//! Return:  None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void init_task_variables ( )
{
   queueKeyMgr = NULL;

   ///////////////////////////////////////////////////////////////////////////
   // Create the Key Manager message queue.  This is a Local Queue to the
   // Manager Address Space.
   ///////////////////////////////////////////////////////////////////////////
   CHECK(CreateMessageQueue(KEY_MGR_QUEUE_NUM_BUFFER, KEY_MGR_QUEUE_BUFFER_SZ,
      MESSAGE_QUEUE_LOCAL, &queueKeyMgr),__FILE__, __FUNCTION__, __LINE__);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: wait4CryptoResponse
//!
//! Description: The purpose of this function is to wait for an the response
//!              message from crypto.
//!
//! Parameters:  None
//!
//! Return:  None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void wait4CryptoResponse( )
{
   const int RESPONSE_TIMEOUT = 10;               // wait 10 seconds
   Time responseTimeOut = {RESPONSE_TIMEOUT, 0};  // rsp timeout
   Error error = Failure;                         // error code

   // set up the Condition Variable that will wait until response from CP
   WaitForSemaphore(CControlVars::Instance()->sSelZerMsgResponse);
   {
      error = WaitForCondition(CControlVars::Instance()->conSelZerResponse,
                               &responseTimeOut, false);

      if (error != Success)
      {
         CKeyEffectData::Instance()->setKeyDispStatus(FAILURE);
      }//else nothing - do not change status

      CKeyEffectData::Instance()->sendKeyDispMsg();
   }
   ReleaseSemaphore(CControlVars::Instance()->sSelZerMsgResponse);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: handleKeyDisposition
//!
//! Description: The purpose of this function is to send the
//!              VC_SELECTIVE_ZEROIZE_KEY_DATA_MSGTYPE message to the crypto.
//!
//! Parameters:  Key_Bank_Info_Type* msgData- pointer to the data to be sent
//!              For Key rollover (SPECIFIC_TEK):
//!                keyBankLoc [4,5]
//!                keyBankSegLoc [1-100]
//!              For CDE Data Erasure (CDE):
//!                keyBankLoc = 0
//!                keyBankSegLoc = 0
//!
//! Return:  None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void handleKeyDisposition( Key_Bank_Info_Type* msgData )
{
   if ( !check4Null(msgData, __FILE__, __LINE__) )
   {
      //keep track of key disposition data
      CKeyEffectData::Instance()->setKeyDispData( msgData->keyBankLoc,
                                                  msgData->keyBankSegLoc,
                                                  FAILURE );

      if ( ( CVlf::Instance()->mCPLinkUp ) &&
           ( CVlf::Instance()->mRcvrStatus.CMState.ECUState == ECU_OPERATIONAL ) )
      {
         Selective_Zeroize_Keys_Msg_Type msg_data;   // msg data
         memset_safe (&msg_data, 0, sizeof (Selective_Zeroize_Keys_Msg_Type));

         if ( ( 0 < msgData->keyBankLoc ) && ( 0 < msgData->keyBankSegLoc ) )
         {
            msg_data.action = SPECIFIC_TEK;
         }
         else
         {
            msg_data.action = CDE;
         }
         msg_data.algorithm = 0;
         msg_data.keyBankLoc = msgData->keyBankLoc;
         msg_data.keyBankSegLoc = msgData->keyBankSegLoc;

         // fill message and send
         CMessage snd_msg;     // send msg
         snd_msg.SetMsgId(VC_SELECTIVE_ZEROIZE_KEY_DATA_MSGTYPE);
         snd_msg.SetSrc(CVlf::Instance()->mId);
         snd_msg.SetDest(CP);
         snd_msg.SetActionId(UNSOLICIT_ACTION_ID); // internal message
         (void)snd_msg.SetMsgData(&msg_data, sizeof(Selective_Zeroize_Keys_Msg_Type));
         CMsgHandler::Instance()->SendPriMsg(&snd_msg);
      }
      // send failure to delete key
      else
      {
         CKeyEffectData::Instance()->setKeyDispStatus(FAILURE);
         CKeyEffectData::Instance()->sendKeyDispMsg();
      }
   }
   else
   {
      //reset key disposition data
      CKeyEffectData::Instance()->setKeyDispData( UNUSED_VARIABLE_VAL,
                                                  UNUSED_VARIABLE_VAL,
                                                  FAILURE );
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: rolloverTimeOutHandlerTask
//!
//! Description:
//!   This is the task that will control the automatic key rollover process.
//!   It will wait on the receive of the alarm from the system clock.
//!
//! Parameters: none
//!
//! Return: none
//!
//! Notes:
//!   This task performs the following functions:
//!
//!   1) This task will wait until a message is received on the clock.
//!   2) It will process a rollover command for each channel.
//!   3) repeat
//!
////////////////////////////////////////////////////////////////////////////////
void rolloverTimeOutHandlerTask()
{
   Error error = Failure;  // error code

   while(true)
   {
      //wait forever until a clock alarm occurs.
      CHECK(error = SynchronousReceive((Connection)SystemClock, NULL),
          __FILE__, __FUNCTION__, __LINE__);

      // only perform rolloever operations if the msg rcvd ok
      if (Success == error)
      {
         // Process each channel for the new crypto period
         for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
         {
            // Perform Automatic Rollover
            CKeyEffectData::Instance()->rolloverEffectivity(chanNum);
         }

         VlfTime vlfTime = CTimeLoad::Instance()->GetVlfTime();  // VLF time
         std::ostringstream str ( "" );   // string stream
         str << "VLF/LF ADVISORY MESSAGE: "
             << " Rollover Alarm Action Timeout@ "
             << vlfTime.doy << "." << vlfTime.sec << ":" << vlfTime.frames
             << std::ends;
         send_sa_msg ( str.str().c_str() );

      }
      //else nothing, the rcv connection had an error
      //  the error will be reported by the CHECK function
   }
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
