
///////////////////////////////////////////////////////////////////////////////
//
// Function:
//
// File Name: main_Eth_Task.cc
//
// Description:
//   This file contains the tasks will act as the DSP-1's TCP/IP Client. The
//   client will be assigned the port number 40003 and will only talk with the
//   DSP-2 TCP/IP Server at port number 50000.
//
//   The main_Eth_Rx_Task() is used to receive message from DSP-2. The
//   main_Eth_Tx_Task() will send message to a DSP-2, if the socket is valid.
//
// Notes:
//   There is no semaphore to cordinate between the RX and TX Ethernet Tasks.
//   We are going to try it this way and add it later if it becomes a problem.
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include "utility.h"
#include "CMsgHandler.h"
#include "TcpClient.h"
#include "mqueue.h"
#include "CVlf.h"
#include "CDspBIT.h"
#include "TMemStrUtility.h"
#include "IPAddresses.h"
#include "CControlVars.h"
#include "InitTcpTxCommon.h"

//******************************************************************************
//
// Static Data and Constants.
//
//******************************************************************************

static const char* serverIpAddress = SERVER_IP_ADDRESS1;    // server IP addr
static const int SLEEP_PERIOD_20MSEC = 20000;               // 20 millisecond sleep
static const int serverPort = 50000; // The server uses this port number
                                     //    to communicate with the outside
                                     //    world.
static const int clientPort = 40003; // This client uses this port number
                                     //    to communicate with the outside
                                     //    world.

//
// TCP/IP Client with DSP-2 Server.
//
TcpClient dsp2Client(serverIpAddress, serverPort, clientPort,
                     TcpClient::NO_TCPIP_TIMEOUT,
                     TcpClient::DEFAULT_TCPIP_TIMEOUT);
                                                // Create client with no RX timeout. Wait Forever
                                                // on RX messages and a 3 second timeout
                                                // on TX messages.

// Pointer the the RX Ethernet Message Queue.
static MessageQueue queueEthRx;
// Pointer the the TX Ethernet Message Queue.
static MessageQueue queueEthTx;
// Pointer the the PRI RX Ethernet Message Queue.
static MessageQueue queuePriEthRx;
// Pointer the the PRI TX Ethernet Message Queue.
static MessageQueue queuePriEthTx;

// function declarations
void receiveEntireMsg();
void sendMessage(void* buffer);
Msg_Error_Codes_Type checkActiveOES(CMessage& msg);

////////////////////////////////////////////////////////////////////////////////
//! Function: checkActiveOES
//!
//! Description:
//!   This function will check the msg source to ensure that if the message
//!   came from an OES, that it is either active, or we are not clearing memory.
//!
//! Parameters:
//!   CMessage ptr - msg
//! Return:
//!   Msg_Error_Codes_Type - error returned
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
Msg_Error_Codes_Type checkActiveOES(CMessage& msg)
{
   Msg_Error_Codes_Type msgError = UNKNOWN_ERROR;   // msg error
   Subsystem_Type src = msg.GetSrc();               // source
   Message_ID_Type msgID = msg.GetMsgId();          // msg ID

   // Check for ACTIVE OES, If msg comes from non-Active OES
   // Check the message type and only allow link-is-alive,controller ident,
   // BIT and status requests. Error all other messages
   if (((src == OES1) || (src == OES2)) &&
      ((src != CVlf::Instance()->mActiveOES) &&
       ((msgID != OV_CONTROLLER_IDENTIFICATION_MSGTYPE )&&
        (msgID != OV_REQUEST_BIT_STATUS_MSGTYPE ) &&
        (msgID != OV_REQUEST_SYSTEM_STATUS_MSGTYPE ) &&
        (msgID != OV_READ_VLF_CHANNEL_MSGTYPE ))))
   {
      msgError = NOT_ACTIVE_OES;
      // Send ACK msg to OES
      CMsgHandler::Instance()->SendAckNak(msg.GetSrc(),
         msg.GetMsgId(), msg.GetTimestamp(), ACK, msgError);
   }
   // if we are in the memory clear operation, due not allow any
   // additional OES commands
   else if ( ((src == OES1) || (src == OES2)) &&
             (CVlf::Instance()->mMemoryClearRcvd) )
   {
      msgError = OPERATION_IN_PROGRESS;
      // Send ACK msg to OES
      CMsgHandler::Instance()->SendAckNak(msg.GetSrc(),
         msg.GetMsgId(), msg.GetTimestamp(), ACK, msgError);
   }
   else
   {
      msgError = VLF_NO_ERROR;
   }

   return msgError;

}

////////////////////////////////////////////////////////////////////////////////
//! Function: sendMessage
//!
//! Description:
//!   This function will send out the message to Ethernet.
//!
//! Parameters:
//!   buffer - message to send
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void sendMessage(void* buffer)
{
   if ( !check4Null(buffer, __FILE__, __LINE__) )
   {
      CMessage* msg = (CMessage*)buffer;   // msg

      //
      // We have a message to send, check to make sure the connection
      // with the DSP-2 Server is still up. If so, try to send the message.
      // Report the success or failure to the user.
      //
      if (dsp2Client.IsConnectionUp())
      {
         int len = msg->GetMsgLen();    // msg len

         if (!(dsp2Client.TxMessage((const char*) msg->GetMsgData(), len)))
         {
            if (dsp2Client.IsDiagEnabled())
            {
               std::ostringstream str ( "" );  // string stream
               str << "ERROR: 'TxMessage' failed. "
                   << "Connection with DSP-2 down" << std::ends;
               send_sa_msg ( str.str().c_str() );
            }
            //else
            //   do nothing, diagnostic is disabled
         }
         //else message sent successfully.
      }
      // The connection must be down. Just flush the message.
      else
      {
         if (dsp2Client.IsDiagEnabled())
         {
            std::ostringstream str ( "" ); // string stream
            str << "ERROR: Connection with DSP-2 Server is down." << std::ends;
            send_sa_msg ( str.str().c_str() );
         }
         //else
         //   do nothing, diagnostic is disabled
      }
   }//else nothing- error handled in if statement
}
////////////////////////////////////////////////////////////////////////////////
//! Function: InitTcpClientRx
//!
//! Description:
//!   This function will initalize the data used with the
//!   main_Eth_Rx_Task().
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
static void InitTcpClientRx()
{
   //
   // Disable Diagnostic.
   //
   dsp2Client.DisableDiag();

   //
   // Wait here until the Priority RX Ethernet Queue and
   //  RX Ethernet Queue are up and running.
   //
   queueEthRx = NULL;
   queuePriEthRx = NULL;

   // try until RX Ethernet queue is successfully registered
   while (queueEthRx == NULL)
   {
      Error err = OpenRegisteredMessageQueue(EthRcvQStr, &queueEthRx);  // open queue
      if (err != Success)
      {
         if (err != ResourceNotAvailable)
         {
            CHECK(err, __FILE__, __FUNCTION__, __LINE__);
         }
         //else
         //  do nothing, don't need to log ResourceNotAvailable error.

         sleep(1);
      }
      //else
      //   do nothing, RX Ethernet queue is successfully registered
   }

   // try until Priority RX Ethernet queue is successfully registered
   while (queuePriEthRx == NULL)
   {
      Error err = OpenRegisteredMessageQueue(PRI_EthRcvQStr, &queuePriEthRx);  // open queue
      if (err != Success)
      {
         if (err != ResourceNotAvailable)
         {
            CHECK(err, __FILE__, __FUNCTION__, __LINE__);
         }
         //else
         //  do nothing, don't need to log ResourceNotAvailable error.

         sleep(1);
      }
      //else
      //   do nothing, Priority RX Ethernet queue is successfully registered
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: main_Eth_Rx_Task
//!
//! Description:
//!   This is a main task that will receives ethernet message
//!   from the DSP-2 server and puts the message into the queue to
//!   be processed by the 'main_Msg_Proc_Task'.
//!
//! Parameters:
//!   Return Value – Nothing
//!
//! Notes:
//!   If PBIT never completes or fails to run this task will wait forever and
//!    no Ethernet Connections will be allowed.  It will be up to DSP2 to FAULT
//!    DSP1.
//!
////////////////////////////////////////////////////////////////////////////////
void main_Eth_Rx_Task()
{
   //
   // Initialize data used with the main_Eth_Rx_Task().
   //
   InitTcpClientRx();

   //Wait for Power-Up BIT to finish
   while (!CDspBIT::Instance()->PBitCompleted)
   {
      usleep (SLEEP_PERIOD_20MSEC);
   }

   //
   // Begin to receive new message from the DSP-2 Server. Do it forever.
   //
   // If the connection with the DSP-2 Server is up or we can
   // establish a connection with the DSP-2 Server, wait for a message
   // from the DSP-2 Server.
   //
   while (true)
   {
      if (!(dsp2Client.IsConnectionUp()))
      {
         // Establish a connection and call event to transition VLFState
         if (dsp2Client.EstConnection())
         {
         // Call event to transition VLFState
         CVlf::Instance()->DSPCommunications();

         // Send Version Data to DSP2
         CVlf::Instance()->SendDSP2VersionData();
         }
         //
         // Connection with the DSP-2 Server does not or could not be brought
         // up. Tell the user and sleep for 5 seconds and then try again.
         //
         else
         {
            if (dsp2Client.IsDiagEnabled())
            {
               std::ostringstream str ( "" );  // string stream
               str << "ERROR: Connection with DSP-2 Server is down." << std::ends;
               send_sa_msg ( str.str().c_str() );
            }
            //else
            //   do nothing, diagnostic is disabled

            sleep(5);
         }
      }
      else
      {
         receiveEntireMsg();
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: receiveEntireMsg
//!
//! Description:
//!   This function is the main work done by the main_Eth_Rx_Task.  The task
//!   will block on the RxEntireMessage until a message is available.  It will
//!   then place the message on the correct buffer so that another task can
//!   handle the message.
//!
//! Parameters:
//!   Return Value – Nothing
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void receiveEntireMsg()
{
   CMessage msg;                    // msg
   int len = sizeof( Message_Type );// msg len

   if ( dsp2Client.RxEntireMessage( (char*)msg.GetMsgData(), len ) )
   {
      //
      // Check its header. If the header is bad,
      //  send a NAK back to the client.
      //
      Msg_Error_Codes_Type msgError = UNKNOWN_ERROR;  // msg error

      msgError = msg.IsMsgHeaderValid();
      if ( msgError != VLF_NO_ERROR )
      {
         if ( dsp2Client.IsDiagEnabled() )
         {
            std::ostringstream str ( "" );  // string stream
            str << "ERROR: Ethernet RX Msg from DSP-2 Server. error="
               << msgError << "Send NAK to Client." << std::ends;
            send_sa_msg( str.str().c_str() );
         }//else
          //   do nothing, diagnostic is disabled

         // Send NAK msg to OES
         CMsgHandler::Instance()->SendAckNak( msg.GetSrc(), msg.GetMsgId(),
                                              msg.GetTimestamp(), NAK, msgError );
      }
      // Verify the entire message was received
      else if ( len != msg.GetMsgLen() )
      {
         msgError = DATA_LENGTH_ERROR;
         if ( dsp2Client.IsDiagEnabled() )
         {
            std::ostringstream str ( "" );  // string stream
            str << "ERROR: Ethernet RX Msg from DSP-2 Server. error="
                << msgError << "Send NAK to Client." << std::ends;
            send_sa_msg( str.str().c_str() );
         }//else
         //   do nothing, diagnostic is disabled

         // Send NAK msg to OES
         CMsgHandler::Instance()->SendAckNak( msg.GetSrc(), msg.GetMsgId(),
                                              msg.GetTimestamp(), NAK, msgError );
      }
      //
      // Good Ethernet Message,
      // Determine if msg is Priority Msg for storage on PRI-Ethernet
      // RX Queue.
      // Default: store it in the Ethernet RX Queue to be processed.
      //
      else
      {
         Message_Type *buffer = NULL;   // buffer
         Error error = Failure;         // error code

         // Message From Good Client
         msgError = checkActiveOES( msg );
         if ( msgError == VLF_NO_ERROR )
         {
            switch (msg.GetMsgId())
            {
               case OV_SELECTIVE_ZEROIZE_KEY_DATA_MSGTYPE:
               case VO_VLF_LF_DATA_MSGTYPE:
                  CHECK( error = AllocateMessageQueueBuffer( queuePriEthRx,(void **)&buffer ),
                         __FILE__, __FUNCTION__, __LINE__ );

                  if ( error == Success )
                  {
                     memcpy_safe( buffer, msg.GetMsgData(), msg.GetMsgLen() );
                     CHECK( SendOnMessageQueue( queuePriEthRx, buffer ),
                            __FILE__, __FUNCTION__, __LINE__ );
                  }
                  //else nothing- failed to allocate buffer
               break;

             default:
                  CHECK( error = AllocateMessageQueueBuffer( queueEthRx,(void **)&buffer ),
                         __FILE__, __FUNCTION__, __LINE__ );

                  if ( error == Success )
                  {
                     memcpy_safe (buffer, msg.GetMsgData(), msg.GetMsgLen());
                     CHECK(SendOnMessageQueue(queueEthRx, buffer)
                        ,__FILE__, __FUNCTION__, __LINE__);
                  }
                  //else nothing- failed to allocate buffer
               break;
            }//end switch
         }// else nothing- checkActiveOES will send error code
      }
   }

   //
   // We had a problem receiving the message, notify the user and
   // remove the socket from the 'master file descriptor' list.
   //
   else
   {
      dsp2Client.CloseConnection();

      if ( dsp2Client.IsDiagEnabled() )
      {
         std::ostringstream str ( "" );  // string stream
         str << "ERROR: 'RxMessage' failed. "
             << "Connection to DSP2 closed." << std::ends;
         send_sa_msg( str.str().c_str() );
      }//else
       //   do nothing, diagnostic is disabled
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: InitTcpClientTx
//!
//! Description:
//!   This function will initalize the data used with the
//!   main_Eth_Tx_Task().
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
static void InitTcpClientTx()
{
   // Invoke the helper function to eliminate duplicate algorithm detected
   // by customer's analysis tool.
   TCPTX::InitTcpTx(EthTxQStr, PRI_EthTxQStr, queueEthTx, queuePriEthTx);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: main_Eth_Tx_Task
//!
//! Description:
//!   This is a main task that transmits ethernet message, that is put
//!   in the queue by the 'main_Msg_Proc_Task', to the DSP-2 Ethernet
//!   Server Task.
//!
//! Parameters:
//!   Return Value – Nothing
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void main_Eth_Tx_Task()
{
   bool lMsgSent = false; // Flag to indicate if a message was sent

   //
   // Initialize data used with the main_Eth_Tx_Task().
   //
   InitTcpClientTx();

   //Wait for Power-Up BIT to finish
   while (!CDspBIT::Instance()->PBitCompleted)
   {
      usleep (SLEEP_PERIOD_20MSEC);
   }

   //
   // Begin to transmit ethernet messages. When a message comes into the
   // Ethernet TX Queue, send it to the DSP-2 Ethernet Server if a
   // connection exists. If the connection is down, just flush the message.
   //
   while (true)
   {
      //
      // Check Priority Queue first, to determine if Msg(s) are available
      // Continue to process msgs from priority queue until exhausted
      //
      void* buffer = NULL;    // buffer
      Error err = Failure;    // error code

      lMsgSent = false;
      while (err != ResourceNotAvailable)
      {
         err = TryReceiveOnMessageQueue(queuePriEthTx, (void**)&buffer);
         if (err == Success)
         {
            lMsgSent = true;

            // send message out Ethernet
            sendMessage(buffer);

            //
            // We are done with the message. Flush the message.
            //
            CHECK(FreeMessageQueueBuffer(queuePriEthTx, (void**)&buffer),
                  __FILE__, __FUNCTION__, __LINE__);
         }
         //else
         //   do nothing, message not available.
      }


      //
      // Check for a message on the manager's transmit queue.
      //
      err = TryReceiveOnMessageQueue(queueEthTx, (void**)&buffer);
      if (err == Success)
      {
         lMsgSent = true;

         // send message out Ethernet
         sendMessage(buffer);

         //
         // We are done with the message. Flush the message.
         //
         CHECK(FreeMessageQueueBuffer(queueEthTx, (void**)&buffer),
               __FILE__, __FUNCTION__, __LINE__);
      }
      //else
      //   do nothing, message not available.

      // sleep 20 milliseconds to allow other tasks to perform
      if ( !lMsgSent )
      {
         usleep( SLEEP_PERIOD_20MSEC );
      }
      // Else we are busy, don't sleep yet
   }
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
