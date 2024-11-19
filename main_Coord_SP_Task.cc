
///////////////////////////////////////////////////////////////////////////////
//
// File Name: main_Coord_SP_Task.cc
//
// Description:
//    The main_Coord_SP_Task is task that is responsible for coordinating the mode
//    processing every 20ms. When a 20ms ANI sample is ready, the IO device
//    (via IRQ2) in the kernel will notify the Coor_SP_Task. The Coor_SP_Task
//    which blocks on the IO device notification will read the IO device status
//    to get the sample index for all the channels. Next, it will de-queue any
//    commands that were sent from the Message Processing Task.  The command and
//    the sample index are queued in their corresponding Channel queue to be
//    consumed by the Ada tasks in the channel address space.  If there is an
//    existing command on the channel queue prior to adding the new command,
//    an error message will be generated and sent to the Ethernet TX queue.
//    The Ada tasks in each of the channel address space blocks on its
//    corresponding channel queue.  When a command is available, it will de-queue
//    the message which contains a command and an index to the share memory buffers.
//    The share memory buffers are a contiguous memory block of ANI sample data
//    that is mapped to each channel's address space. Once the mode code completed
//    it's processing, it must send a status message to the status queue.
//    The Corrd_SP_Task will check the status queue for status or errors.
//    If there is an error or a missing status message from a channel, an error
//    message is generated and sent to the Ethernet TX queue.
//
// Notes: None
//    The Coor_SP_Task is statically defined using Integrity Integrate graphical
//    editor. The configure file generated are:
//    \GEMS\SD&D\Software\VLF_Software\Source\Projects\VpGemsApp\src\VpGemsApp.int
//    \GEMS\SD&D\Software\VLF_Software\Source\Projects\VpGemsApp\src
//    \VpGemsApp_integrate.h
//
///////////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include "rc_bsp_defs.h"
#include "utility.h"
#include "KgrVpApp_integrate.h"
#include "FpgaDeviceSingleton.h"
#include "FpgaIoDevice.h"
#include "chan_struct.h"
#include "CVlf.h"
#include "mqueue.h"
#include "CTimeload.h"
#include "Dsp1BitFuncs.h"
#include "CDspBIT.h"
#include "TMemStrUtility.h"
#include "VersionIoDevice.h"
#include "CControlVars.h"
#include "msg_defs.h"
#include "CDspConfig.h"

using namespace DSP1_TEST;

//******************************************************************************
//
// Static Data and Pointers.
//
//******************************************************************************

// Pointer the the Manager Command Message Queue.
extern MessageQueue queueCmd;

// Channel Structure that holds channel info
// and the pointer to channel status queue
static ChanStatusQueueStruct chanStatus = {NULL, NULL, NULL};

////////////////////////////////////////////////////////////////////////////////
//! Function: InitQueueConnections
//!
//! Description:
//!   This function will initalize connection to the Manager Command Queue and
//!   Create the Channel Status Message Queue
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void InitQueueConnections()
{
   Error error = Failure;  // error code
   queueCmd = NULL;        // queue cmd

   // Clear out structure prior to first use
   memset_safe(&chanStatus, 0, sizeof(ChanStatusQueueStruct));

   // Create Channel Status Queue
   CHECK(CreateMessageQueue(CH_STAT_QUEUE_NUM_BUFFER, CH_STAT_QUEUE_BUFFER_SZ,
      MESSAGE_QUEUE_SHARED, &chanStatus.queueChStatus),__FILE__, __FUNCTION__, __LINE__);

   CHECK(RegisterMessageQueue(chanStatus.queueChStatus, ChStatQStr),
      __FILE__, __FUNCTION__, __LINE__);

   //
   // Create Connection to manager Command Queue Created by
   // Priority Msg Proc Task.  Try until queue is successfully
   // registered.
   while (queueCmd == NULL)
   {
      error = OpenRegisteredMessageQueue(MgrCmdQStr, &queueCmd);
      if (error != Success)
      {
         if (error != ResourceNotAvailable)
         {
            CHECK(error, __FILE__, __FUNCTION__, __LINE__);
         }
         // else nothing- other error type

         sleep(1);
      }
      //else nothing- queue is registered
   }
}

///////////////////////////////////////////////////////////////////
//!
//! Function: checkStatusAndCommandQueues
//!
//! Description:
//!    This function is used to check the channel status queue and
//!    the manager command queue for messages.
//!
//! Parameters:
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////
void checkStatusAndCommandQueues()
{
   ChannelCmdStruct* cmdBuffer;     // cmd buffer
   Error err = Failure;             // error code

   ////////////////////////////////////////////////////////////
   // check the status queue for messages from the Channels
   // This queue services all 5 channel address spaces
   ////////////////////////////////////////////////////////////
   while (err != ResourceNotAvailable)
   {
      err = TryReceiveOnMessageQueue(chanStatus.queueChStatus,
            (void**) &chanStatus.statusBuffer);
      if (err == Success)
      {
         CVlf::Instance()->chan[chanStatus.statusBuffer->channel-1]->
            HandleChStatus(&chanStatus);

         CHECK(FreeMessageQueueBuffer(chanStatus.queueChStatus,
               (void**) &chanStatus.statusBuffer),
               __FILE__, __FUNCTION__, __LINE__);
      }
      //else
      //   Do nothing, no message to process
   }

   ///////////////////////////////////////////////////////////////////
   // Check the manager command queue for commands from the Message
   // processing task.  If a command is avaliable, handle the command
   // for that channel.
   ///////////////////////////////////////////////////////////////////
   err = TryReceiveOnMessageQueue(queueCmd, (void**) &cmdBuffer);
   if (err == Success)
   {
      CVlf::Instance()->chan[cmdBuffer->channel-1]->HandleMgrCmd(cmdBuffer);

      CHECK(FreeMessageQueueBuffer(queueCmd, (void**) &cmdBuffer),
            __FILE__, __FUNCTION__, __LINE__);
   }
   //else
   //   Do nothing, no message to process
}
//////////////////////////////////////////////////////////////////////
//!
//! Function: init_main_Coord_SP_Task_Options
//!
//! Description:
//!    This function is used to initialize all items that are needed
//!    before the main part of the task can run forever.  This includes
//!    queue setup, FPGA initializations, and sending default variables
//!    to the 5 channel mode VAS.
//!
//! Parameters:
//!
//! Notes:
//!    strncpy will automatically NULL terminate string due to the size of
//!    the char array and word boundary requirements.  The max text allowed
//!    is 32, and the max size of the container variable is 64.
//!
//////////////////////////////////////////////////////////////////////
void init_main_Coord_SP_Task_Options()
{
   FpgaDeviceSingleton::ERROR fpgaError;    // FPGA error
   ChannelCmdStruct cmdBuff;                // cmd buffer
   memset_safe(&cmdBuff, 0, sizeof(ChannelCmdStruct));
   unsigned int chanNum;                    // channel #
   Value flag;                              // flag

   ///////////////////////////////////////////////////////////////////////////
   // Check to make sure the FpgaDeviceSingleton came up without any errors.
   // Otherwise, report the problem and exit.
   ///////////////////////////////////////////////////////////////////////////
   FpgaDeviceSingleton* fpgaDevice = FpgaDeviceSingleton::instance();   // FPGA object
   fpgaError = fpgaDevice->GetLastError();

   if (fpgaError != FpgaDeviceSingleton::FpgaSuccess)
   {
      std::ostringstream str ( "" );  // string stream
      str << "Last FpgaDeviceSingleton Error: "
         << fpgaDevice->XltLastError(fpgaError) << std::ends;
      send_sa_msg( str.str().c_str() );

   }
   //else
   //   Do nothing, no error

   if (!(fpgaDevice->IsConfigured()))
   {
      send_sa_msg( "WARNING: FpgaDeviceSingleton is not Configured!");
   }
   //else
   //   Do nothing, it is configured

   //run power-up BIT
   CVlf::Instance()->mDspPBit = CDspBIT::Instance()->runDspPBIT();

   if (CDspConfig::ONE_ANT_1_INP_TEST_DISABLED ==
       CVlf::Instance()->mDspIOConfig.getEquipSelectConfig())
   {

      // Create the channel objects
      CVlf::Instance()->chan[CH_1] = new CChannel(CH_1, CH1_FREQ, Ch1CmdConnection, FpgaRegChan1Address,
            (FpgaSetFreqPFuncType)&FpgaDevice::SetFreqChan1InHz,
            (FpgaGETSampleAddrPFuncType)&FpgaDevice::RFA1_GetOutputSample1Address);

      CVlf::Instance()->chan[CH_2] = new CChannel(CH_2, CH2_FREQ, Ch2CmdConnection, FpgaRegChan2Address,
            (FpgaSetFreqPFuncType)&FpgaDevice::SetFreqChan2InHz,
            (FpgaGETSampleAddrPFuncType)&FpgaDevice::RFA1_GetOutputSample2Address);

      CVlf::Instance()->chan[CH_3] = new CChannel(CH_3, CH3_FREQ, Ch3CmdConnection, FpgaRegChan3Address,
            (FpgaSetFreqPFuncType)&FpgaDevice::SetFreqChan3InHz,
            (FpgaGETSampleAddrPFuncType)&FpgaDevice::RFA1_GetOutputSample3Address);

      CVlf::Instance()->chan[CH_4] = new CChannel(CH_4, CH4_FREQ, Ch4CmdConnection, FpgaRegChan4Address,
            (FpgaSetFreqPFuncType)&FpgaDevice::SetFreqChan4InHz,
            (FpgaGETSampleAddrPFuncType)&FpgaDevice::RFA1_GetOutputSample4Address);

      CVlf::Instance()->chan[CH_5] = new CChannel(CH_5, CH5_FREQ, Ch5CmdConnection, FpgaRegChan5Address,
            (FpgaSetFreqPFuncType)&FpgaDevice::SetFreqChan5InHz,
            (FpgaGETSampleAddrPFuncType)&FpgaDevice::RFA1_GetOutputSample5Address);
   }
   else
   {
      // Create the channel objects
      CVlf::Instance()->chan[CH_1] = new CChannel(CH_1, CH1_FREQ, Ch1CmdConnection, FpgaRegChan1Address,
            (FpgaSetFreqPFuncType)&FpgaDevice::SetFreqChan1InHz,
            (FpgaGETSampleAddrPFuncType)&FpgaDevice::GetOutputSample1Address);

      CVlf::Instance()->chan[CH_2] = new CChannel(CH_2, CH2_FREQ, Ch2CmdConnection, FpgaRegChan2Address,
            (FpgaSetFreqPFuncType)&FpgaDevice::SetFreqChan2InHz,
            (FpgaGETSampleAddrPFuncType)&FpgaDevice::GetOutputSample2Address);

      CVlf::Instance()->chan[CH_3] = new CChannel(CH_3, CH3_FREQ, Ch3CmdConnection, FpgaRegChan3Address,
            (FpgaSetFreqPFuncType)&FpgaDevice::SetFreqChan3InHz,
            (FpgaGETSampleAddrPFuncType)&FpgaDevice::GetOutputSample3Address);

      CVlf::Instance()->chan[CH_4] = new CChannel(CH_4, CH4_FREQ, Ch4CmdConnection, FpgaRegChan4Address,
            (FpgaSetFreqPFuncType)&FpgaDevice::SetFreqChan4InHz,
            (FpgaGETSampleAddrPFuncType)&FpgaDevice::GetOutputSample4Address);

      CVlf::Instance()->chan[CH_5] = new CChannel(CH_5, CH5_FREQ, Ch5CmdConnection, FpgaRegChan5Address,
            (FpgaSetFreqPFuncType)&FpgaDevice::SetFreqChan5InHz,
            (FpgaGETSampleAddrPFuncType)&FpgaDevice::GetOutputSample5Address);
   }
   // check the "new" for NULL
   for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
   {
      (void)check4Null(CVlf::Instance()->chan[chanNum], __FILE__, __LINE__);
   }

   ///////////////////////////////////////////////////////////////////////////////
   // Create and share the status message queue. This queue is used to receive
   // mode specific statuses from the Channel's addresspace.
   // Open connection to Shared Manager Command Queue.
   ///////////////////////////////////////////////////////////////////////////////
   InitQueueConnections();

   ///////////////////////////////////////////////////////////////////
   // Set FPGA Version Info
   ///////////////////////////////////////////////////////////////////
   CVlf::Instance()->setFpgaVersion( fpgaDevice->GetImageConfigDoc().c_str() );

   ///////////////////////////////////////////////////////////////////
   // Initialize Values for each Channel and send defaults to
   //  the 5 Mode VAS.
   ///////////////////////////////////////////////////////////////////
   cmdBuff.index   = -1;
   cmdBuff.cmd     = COMM_PLAN_CMD;
   for (chanNum=0; chanNum < MAX_VLF_CHANNEL; chanNum++)
   {
      //////////////////////////////////////////////////////////
      // Set frequencies in the FPGA Hardware.
      //////////////////////////////////////////////////////////
      CVlf::Instance()->chan[chanNum]->SetChFreq();

      //////////////////////////////////////////////////////////////////////
      // Tell the CHx AddressSpaces what is their current frequencies.
      //////////////////////////////////////////////////////////////////////
      cmdBuff.channel = chanNum + 1; //add 1 to array index which is based 0
      cmdBuff.cmdData.commPlanConfig.freqOfChannel = CVlf::Instance()->chan[chanNum]->mChCmd.freq;
      cmdBuff.cmdData.commPlanConfig.transmitterNum = MIN_TX_NUMBER;
      CVlf::Instance()->chan[chanNum]->SendChCmd(&cmdBuff);

      ///////////////////////////////////////////////////////////////////
      // Load up the address of the FPGA Output Sample into the
      // FpgaIODeviceObject_MGR.
      ///////////////////////////////////////////////////////////////////
      CVlf::Instance()->chan[chanNum]->LoadChOutputSample();
   }
   ///////////////////////////////////////////////////////////////////////
   // Turn on the FpgaIoDevice Performance Monitoring of the 20 msec IRQ.
   ///////////////////////////////////////////////////////////////////////
   CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegTimePm,
         (Value)true), __FILE__, __FUNCTION__, __LINE__);
   CHECK(ReadIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegTimePm, &flag),
         __FILE__, __FUNCTION__, __LINE__);

   ////////////////////////////////////////////////////////////////////////////
   // FPGA Initialization is complete, finish the FPGA configuration and turn on
   // the FPGA so it can start gathering data and tell the FpgaIoDeviceObject_MGR,
   // the address of the FPGA's Interrupt Register so the FpgaIoDeviceObject_MGR
   // can begin to process the FPGA's Output Samples.
   ////////////////////////////////////////////////////////////////////////////

   // Initialize WB_Noise_Reduct_Enabled parameter
   if (CVlf::Instance()->mConfigParms.WB_Noise_Reduction_Enabled)
   {
      fpgaDevice->SetUseAnbBit();
   }
   else
   {
      fpgaDevice->ClrUseAnbBit();
   }

   // Initialize WB_Limiter_Enabled parameter to either blank or limit samples
   if (CVlf::Instance()->mConfigParms.WB_Limiter_Enabled)
   {
      fpgaDevice->SetLimitBit();
   }
   else
   {
      fpgaDevice->ClrLimitBit();
   }

   // Initialize NB_Noise_Reduct_Enabled parameter for ANL (atomospheric noise limiter)
   if (CVlf::Instance()->mConfigParms.NB_Noise_Reduction_Enabled)
   {
      fpgaDevice->SetUseAnlBit();
   }
   else
   {
      fpgaDevice->ClrUseAnlBit();
   }

   // turn on FPGA
   fpgaDevice->SetRunBit();

}

///////////////////////////////////////////////////////////////////
//!
//! Function: main_Coord_SP_Task
//!
//! Description:
//!   This is a main task that initializes the FPGA Hardware and
//!   passes a notification that new Output Sample data has arrived
//!   from the FpgaIoDevice to the different MODE:Channel AddressSpaces.
//!
//! Parameters:
//!   Return Value – None
//!
//! Notes: This task was designed to only work if the Manager Commands
//!  PM Data, Config Params, occur when a Channel is not active as
//!  a 20ms loss will accure as the Ada does not process both commands
//!  in the same 20ms.  When a Start/Stop command is issued the loss of
//!  the 20ms is not an issue. These commands can be found as part of the
//!  checkStatusAndCommandQueues().
//!
//!  For future implementations, this might be fixed with adding more
//!  buffers to the command queue and adding another call to
//!  CVlf::Instance()->chan[##]->SendChCmd() if a valid
//!  call TryReceiveOnMessageQueue (queueCmd , etc) returns a buffer.
//!
///////////////////////////////////////////////////////////////////
void main_Coord_SP_Task()
{
   Value count[MAX_VLF_CHANNEL] = {0,0,0,0,0};             // channel counts
   unsigned int chanNum;                                // channel #
   ChannelCmdStruct tmpBuff;                            // temp buffer
   memset_safe(&tmpBuff, 0, sizeof(ChannelCmdStruct));
   Absolute_Time_Type absTime = {0,0,0,0};              // absolute time

   //
   // Call the function that will intitalize all the items needed before the
   // task is set to run.
   init_main_Coord_SP_Task_Options();

   //////////////////////////////////////////////////
   // Process FpgaIoDevice Driver messages forever.
   //////////////////////////////////////////////////

   while (true)
   {
      ////////////////////////////////////////////////////////////////////////////
      // Wait to hear from the FpgaIoDeviceObject_MGR. Get the status from the
      // FpgaIoDeviceObject_MGR. This status should include the indexes of the
      // 5 FPGA Output Sample that was just filled. This will be passes onto the
      // MODE:Channel AddressSpace.
      ////////////////////////////////////////////////////////////////////////////
      CHECK(SynchronousReceive((Connection)FpgaIoDeviceObject_MGR, NULL),
            __FILE__, __FUNCTION__, __LINE__);
      CHECK(ReadIODeviceStatus(FpgaIoDeviceObject_MGR, IODEV_FPGA_STAT_IDX,
            count, sizeof(count)), __FILE__, __FUNCTION__, __LINE__);

      // Get VLF Time from FPGA
      CTimeLoad::Instance()->GetAbsTime(&absTime);

      ////////////////////////////////////////////////////////////
      // check the command and status queues
      ////////////////////////////////////////////////////////////
      checkStatusAndCommandQueues();

      /////////////////////////////////////////////////////////////////
      // Tells the CHx AddressSpace to process the new Output Sample.
      ////////////////////////////////////////////////////////////////
      for (chanNum=0; chanNum < MAX_VLF_CHANNEL; chanNum++)
      {
         // reset channel command
         tmpBuff.channel = chanNum + 1;
         tmpBuff.index   = count[chanNum];
         tmpBuff.cmd     = CHAN_MODE_CMD;

         // only send mode 15 data if anti-jam is disabled
         if (CVlf::Instance()->chan[chanNum]->mAntiJamOnly == false)
         {
            tmpBuff.cmdData.modeCmdData.commands[NORMAL_MODE_15] =
               CVlf::Instance()->chan[chanNum]->mMode15->GetNextCmd();
         }
         else
         {
            tmpBuff.cmdData.modeCmdData.commands[NORMAL_MODE_15] = HALT_SEARCH;
         }

         // only send SM_Mode data if crypto is available and operational
         if ( ( CVlf::Instance()->mCPLinkUp ) &&
              ( CVlf::Instance()->mRcvrStatus.CMState.ECUState == ECU_OPERATIONAL ))
         {
            tmpBuff.cmdData.modeCmdData.commands[SPECIAL_MODE_9] =
               CVlf::Instance()->chan[chanNum]->mMode9->GetNextCmd();
            tmpBuff.cmdData.modeCmdData.commands[SPECIAL_MODE_HIDAR] =
               CVlf::Instance()->chan[chanNum]->mModeHidar->GetNextCmd();
            tmpBuff.cmdData.modeCmdData.commands[VERDIN_MODE_23] =
               CVlf::Instance()->chan[chanNum]->mMode23->GetNextCmd();
            tmpBuff.cmdData.modeCmdData.commands[SPECIAL_MODE_A] =
               CVlf::Instance()->chan[chanNum]->mModeSMA->GetNextCmd();
         }
         else
         {
            tmpBuff.cmdData.modeCmdData.commands[SPECIAL_MODE_9] =
               HALT_SEARCH;

            tmpBuff.cmdData.modeCmdData.commands[SPECIAL_MODE_HIDAR] =
               HALT_SEARCH;

            tmpBuff.cmdData.modeCmdData.commands[VERDIN_MODE_23] =
               HALT_SEARCH;

            tmpBuff.cmdData.modeCmdData.commands[SPECIAL_MODE_A] =
               HALT_SEARCH;
         }

         tmpBuff.cmdData.modeCmdData.absTime = absTime;
         CVlf::Instance()->chan[chanNum]->SendChCmd(&tmpBuff);

         // Output a copy of the FPGA sample data for Testing
         if (CVlf::Instance()->chan[chanNum]->mSampleOutputEnabled == true)
         {
            storeFPGAOutputSample(count[chanNum], chanNum);
         }
         //else nothing- test not enabled
      }
   }
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification:  UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
