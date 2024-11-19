
///////////////////////////////////////////////////////////////////////////////
//
// Function:
//
// File Name: main_Msg_Proc_Task.cc
//
// Description: The task handles the sending and receiving of Ethernet data
//              from the eth Tx and Rx queues. If it receives a message, the
//              task will check the message Header for errors and send a NAK
//              ACK to the sender.  If there are no errors, the task invokes
//              the callback function that was registered with the message Id.
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include "KgrVpApp_integrate.h"
#include "mqueue.h"
#include "chan_struct.h"
#include "CMessage.h"
#include "CMsgHandler.h"
#include "utility.h"
#include "CKeyEffectData.h"
#include "CVlf.h"
#include "CDspBIT.h"
#include "CControlVars.h"

// Message Includes
#include "CResponseStatusMessage.h"
#include "COVConfigVlfChannel.h"
#include "COVConfigAllVlfChannels.h"
#include "COVReadVlfChannel.h"
#include "CStartStopChannelMsg.h"
#include "COVRunIBIT.h"
#include "COVSetAntiJam.h"
#include "COVVersionRequest.h"
#include "COVRequestSystemStatus.h"
#include "COVLinkIsAlive.h"
#include "COVTimeAtTheToneMsg.h"
#include "CCVCryptoSystemStatusMsg.h"
#include "CCVLoadedKeyInfoMsg.h"
#include "COVRequestBITStatus.h"
#include "COVWriteKeyEffectivityData.h"
#include "COVControllerIdentification.h"
#include "COVFPGAOutputSampleDataEnable.h"
#include "COVSetConfigParam.h"
#include "COVPMEnable.h"

// Global queues
MessageQueue queueEthTx = NULL;    // ETH Tx queue
MessageQueue queueEthRx = NULL;    // ETH Rx queue

// Link is Live Alarm Timer
static const unsigned char  LINK_IS_LIVE_TIMEOUT = 2;  // link alive timeout
static AlarmTimer mLinkisLiveTimer = NULL;             // is link alive timer
static void LinkisLiveTimeOutHandler();

////////////////////////////////////////////////////////////////////////////////
//! Function: main_Msg_Proc_Task
//!
//! Description:
//!   This is the main task that will process the sending and receiving of
//!   Ethernet data from the eth Tx and Rx queues.
//!
//! Parameters:
//!   Return Value – Nothing
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////

void main_Msg_Proc_Task ()
{
    void *buffer = NULL;           // buffer
    MessageQueue queueCmd = NULL;  // queue cmd
    Error error;                   // error code

    WaitForSemaphore(CControlVars::Instance()->sPowerupBit);

    ///////////////////////////////////////////////////////////////////////////
    // Register the command message queue.
    ///////////////////////////////////////////////////////////////////////////
    // try until queue is successfully registered
    while (queueCmd == NULL)
    {
       error = OpenRegisteredMessageQueue(MgrCmdQStr, &queueCmd);
       if (error != Success)
       {
          if (error != ResourceNotAvailable)
          {
              CHECK(error, __FILE__, __FUNCTION__, __LINE__);
          }
          //else nothing- other error type
          sleep(1);
       }
       //else nothing- failed to open queue continue
    }

    ///////////////////////////////////////////////////////////////////////////
    // Create and register the Ethernet TX and RX message queues. These
    // queues use memory regions created in the kernel
    ///////////////////////////////////////////////////////////////////////////
    CHECK(CreateMessageQueueFromMemoryRegion(EthernetRxQueueMemRegionLink,
       ETH_RCV_QUEUE_NUM_BUFFER, ETH_RCV_QUEUE_BUFFER_SZ,
       MESSAGE_QUEUE_SHARED, &queueEthRx),__FILE__, __FUNCTION__, __LINE__);

    CHECK(RegisterMessageQueue(queueEthRx, EthRcvQStr),
     __FILE__, __FUNCTION__, __LINE__);

    CHECK(CreateMessageQueueFromMemoryRegion(EthernetTxQueueMemRegionLink,
       ETH_SND_QUEUE_NUM_BUFFER, ETH_SND_QUEUE_BUFFER_SZ,
       MESSAGE_QUEUE_SHARED, &queueEthTx),__FILE__, __FUNCTION__, __LINE__);

    CHECK(RegisterMessageQueue(queueEthTx, EthTxQStr),
     __FILE__, __FUNCTION__, __LINE__);
    ///////////////////////////////////////////////////////////////////////////
    // Register to functions handle messages from the OES
    ///////////////////////////////////////////////////////////////////////////
    COVConfigVlfChannel configVlfChannelHandler;  // channel handler
    CMsgHandler::Instance()->RegisterMsg(OV_CONFIG_VLF_CHANNEL_MSGTYPE,
       &configVlfChannelHandler);

    COVConfigAllVlfChannels configAllVlfChannels;  // all channels handler
    CMsgHandler::Instance()->RegisterMsg(OV_CONFIG_ALL_VLF_CHANNELS_MSGTYPE,
       &configAllVlfChannels);

    COVReadVlfChannel readVlfChannelHandler;       // read channel handler
    CMsgHandler::Instance()->RegisterMsg(OV_READ_VLF_CHANNEL_MSGTYPE,
       &readVlfChannelHandler);

    CStartStopChannelMsg startStopChanHandler;    // start/stop channel handler
    CMsgHandler::Instance()->RegisterMsg(OV_START_STOP_CHANNEL_MSGTYPE,
       &startStopChanHandler);

    COVRunIBIT runIBITHandler;                    // IBIT handler
    CMsgHandler::Instance()->RegisterMsg(OV_RUN_IBIT_MSGTYPE,
       &runIBITHandler);

    COVSetAntiJam setAntiJamHandler;              // anti-jam handler
    CMsgHandler::Instance()->RegisterMsg(OV_SET_ANTI_JAM_MSGTYPE,
       &setAntiJamHandler);

    COVVersionRequest versionRequestHandler;      // version request handler
    CMsgHandler::Instance()->RegisterMsg(OV_VERSION_REQUEST_MSGTYPE,
       &versionRequestHandler);

    COVRequestSystemStatus requestSystemStatusHandler;  // system status handler
    CMsgHandler::Instance()->RegisterMsg(OV_REQUEST_SYSTEM_STATUS_MSGTYPE,
       &requestSystemStatusHandler);

    COVLinkIsAlive linkIsAliveHandler;            // link alive handler
    CMsgHandler::Instance()->RegisterMsg(OV_LINK_IS_LIVE_MSGTYPE,
       &linkIsAliveHandler);

    COVTimeAtTheToneMsg TimeAtTheToneHandler;     // time at tone handler
    CMsgHandler::Instance()->RegisterMsg(OV_TIME_AT_THE_TONE_MSGTYPE,
       &TimeAtTheToneHandler);

    COVWriteKeyEffectivityData writeKeyEffectivityDataHandler;  // key effectivity handler
    CMsgHandler::Instance()->RegisterMsg(OV_WRITE_KEY_EFFECTIVITY_DATA_MSGTYPE,
      &writeKeyEffectivityDataHandler);

    COVRequestBITStatus requestBITHandler;        // BIT request handler
    CMsgHandler::Instance()->RegisterMsg(OV_REQUEST_BIT_STATUS_MSGTYPE,
       &requestBITHandler);

    COVControllerIdentification controllerIdentificationHandler;  // controller ID handler
    CMsgHandler::Instance()->RegisterMsg(OV_CONTROLLER_IDENTIFICATION_MSGTYPE,
       &controllerIdentificationHandler);

    COVSetConfigParam setConfigParamHandler;       // set config param handler
    CMsgHandler::Instance()->RegisterMsg(OV_CONFIGURATION_PARAMS_MSGTYPE,
       &setConfigParamHandler);

    ///////////////////////////////////////////////////////////////////////////
    // Register functions to handle messages from the CP
    ///////////////////////////////////////////////////////////////////////////
    CResponseStatusMessage ResponseStatusHandler;  // rsp handler
    CMsgHandler::Instance()->RegisterMsg(RESPONSE_STATUS_MSGTYPE,
       &ResponseStatusHandler);

    CCVCryptoSystemStatusMsg CryptoSystemStatusMsgHandler;  // CP system status handler
    CMsgHandler::Instance()->RegisterMsg(CV_CRYPTO_SYSTEM_STATUS_MSGTYPE,
       &CryptoSystemStatusMsgHandler);

    CCVLoadedKeyInfoMsg LoadedKeyInfoMsgHandler;    // loaded key info handler
    CMsgHandler::Instance()->RegisterMsg(CV_LOADED_KEY_INFO_MSGTYPE,
       &LoadedKeyInfoMsgHandler);

    ///////////////////////////////////////////////////////////////////////////
    // Register functions to handle messages for Software Certification
    ///////////////////////////////////////////////////////////////////////////
    COVPMEnable setPMEnableHandler;                 // PM enable handler
    CMsgHandler::Instance()->
       RegisterMsg(OV_PERFORMANCE_MONITORING_ENABLE_MSGTYPE,
       &setPMEnableHandler);

    COVFPGAOutputSampleDataEnable outputDataSampleHandler;  // output data sample handler
    CMsgHandler::Instance()->RegisterMsg(OV_OUTPUT_SAMPLE_TEST_ENABLE_MSGTYPE,
       &outputDataSampleHandler);

    //create instance of effectTable
    CKeyEffectData::Instance();

   //
   // Create an Alarm Timer to Perform the Link is Live,
   //
   Time LinkisLiveTimeOut = {LINK_IS_LIVE_TIMEOUT, 0};  // link alive timeout

   CHECK(CreateAlarmTimer((Address)LinkisLiveTimeOutHandler,
                          (Address)0, &LinkisLiveTimeOut,
                           true, true, &mLinkisLiveTimer)
                           , __FILE__, __FUNCTION__, __LINE__);

    while (true)
    {
       // Wait for message from the Ethernet rcv queue
       CHECK(ReceiveOnMessageQueue(queueEthRx, (void**)&buffer),
           __FILE__, __FUNCTION__, __LINE__);

       // call the registered handler for the received message
       CMsgHandler::InvokeHandler((CMessage*)buffer);

       // release the received message buffer
       CHECK(FreeMessageQueueBuffer(queueEthRx, (void**)&buffer),
          __FILE__, __FUNCTION__, __LINE__);
    }
}
////////////////////////////////////////////////////////////////////////////////
//! Function: LinkisLiveTimeOutHandler
//!
//! Description:
//!   This is the method handler for Link is Live Timeout.
//!
//! Parameters: None
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
static void LinkisLiveTimeOutHandler()
{
   CMessage snd_msg;     // send msg
   CMessage snd_msg1;    // send msg 1
   snd_msg.SetMsgId(VC_DSP1_LINK_IS_LIVE_MSGTYPE);
   snd_msg.SetSrc(CVlf::Instance()->mId);
   snd_msg.SetDest(CP);
   snd_msg.SetActionId(0);
   snd_msg.SetDataLen(0);
   CMsgHandler::Instance()->SendMsg(&snd_msg);
   //send message to DSP2
   snd_msg1.SetMsgId(VV_LINK_IS_LIVE_MSGTYPE);
   snd_msg1.SetSrc(CVlf::Instance()->mId);
   snd_msg1.SetDest(DSP2);
   snd_msg1.SetActionId(0);
   snd_msg1.SetDataLen(0);
   CMsgHandler::Instance()->SendMsg(&snd_msg1);
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////

