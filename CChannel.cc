///////////////////////////////////////////////////////////////////////////////
// Class: CChannel
//
// File Name: cchannel.cc
//
// Description: This file contains the class methods for the CChannel class.
//              This class is used to manage the 5 mode processing channels.
//
// Notes: All the VLF channels are created in the CVlf singleton class
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include "CMsgHandler.h"
#include "CVlf.h"
#include "FpgaDeviceSingleton.h"
#include "FpgaIoDevice.h"
#include "CChannel.h"
#include "mqueue.h"
#include "TMemStrUtility.h"
#include "Utility.h"
#include <util/error_string.h>


////////////////////////////////////////////////////////////////////////////////
//! Function: Constructor
//!
//! Description:
//!   This method constructs the channel object and create the
//!   channel shared message queue.
//!
//! Parameters:
//!   chan - channel number
//!   freq - channel frequency
//!   cmdConn - connection object
//!   fpgaRegChAddr - FpgaDevice channel address register
//!   chSetFreqFPtr - FpgaDevice set frequency function pointer
//!   chGetOutputSampleAddrFPtr - FpgaDevice get output sample function pointer
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
CChannel::CChannel(Channel_ID_Type chan, unsigned short freq,
                   Connection cmdConn, Value fpgaRegChAddr,
                   FpgaSetFreqPFuncType chSetFreqFPtr,
                   FpgaGETSampleAddrPFuncType chGetOutputSampleAddrFPtr)
{
    if ((chan >= MAX_VLF_CHANNEL) || (chan < 0))
    {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chan=" << chan << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
    } // else - this will not end well

    if (NULL == chSetFreqFPtr)
    {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "NULL parameter (chSetFreqFPtr)." << std::ends;
      send_sa_msg( str.str().c_str() );
    } // else - this will not end well

    if (NULL == chGetOutputSampleAddrFPtr)
    {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "NULL parameter (chGetOutputSampleAddrFPtr)." << std::ends;
      send_sa_msg( str.str().c_str() );
    } // else - this will not end well

    //Clear out memory & initialize default comm plan
    memset_safe(&mCommPlan, 0, sizeof(Vlf_Channel_Type));
    mCommPlan.channelID = (chan + 1); // increase chan number
    mCommPlan.mode15       = false;
    mCommPlan.mode9        = false;
    mCommPlan.modeHIDAR    = false;
    mCommPlan.mode23       = false;
    mCommPlan.modeSMA      = false;
    mCommPlan.frequency    = freq;

    mEnableHidarOpstat   = false;
    mEnableVlf_Pm        = false;
    mCEPEnabled          = true;
    mAntiJamOnly         = false;
    mCommPlanValid       = false;
    mCpChanOpStatValid   = false;
    mSampleOutputEnabled = false;
    mNum20msecs2send     = 0;
    mChannelError        = VLF_NO_ERROR;  // default
    mCurrentChanAction = CHANNEL_OFFLINE;

    mChCmd.freq = freq;
    mChCmd.connection = cmdConn;
    mFpgaRegChanAddress = fpgaRegChAddr;

    // set the function pointers
    mChanSetFreqFPtr = chSetFreqFPtr;
    mChanGetOutputSampleAddrFPtr = chGetOutputSampleAddrFPtr;

    // initialize the Modes
    mMode15 = new CMode15();
    mMode9 = new CMode9();
    mModeHidar = new CModeHidar();
    mMode23 = new CMode23();
    mModeSMA = new CModeSMA();

    // init channel status
    memset_safe(&mStatus, 0, sizeof (VLF_Receiver_Channel_Status_Type));
    mPrevStatus = mStatus;

    //initialize channel states
    setState(&IChannelState::theChOfflineState);

    ////////////////////////////////////////////////////////////////////////////
    // Create and share buffer used with the MODE:Channel AddressSpaces.
    ////////////////////////////////////////////////////////////////////////////
    CHECK(CreateMessageQueue(CH_CMD_QUEUE_NUM_BUFFER, CH_CMD_QUEUE_BUFFER_SZ,
       MESSAGE_QUEUE_SHARED, &mChCmd.queueChCmd),
       __FILE__, __FUNCTION__, __LINE__,mCommPlan.channelID);
    CHECK(ShareMessageQueue(mChCmd.queueChCmd, cmdConn),
       __FILE__, __FUNCTION__, __LINE__,mCommPlan.channelID);
}
///////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//!   This destructor method is used to cleanup the channel object
//!   once it is deleted.
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
CChannel::~CChannel()
{
   // close the message queue
   CHECK(CloseMessageQueue(mChCmd.queueChCmd),
            __FILE__, __FUNCTION__, __LINE__, mCommPlan.channelID);

   // delete the mode objects
   if (mMode15 != NULL)
   {
      delete mMode15;
      mMode15 = NULL;
   }
   //else do nothing, mMode15 not active

   if (mMode9 != NULL)
   {
      delete mMode9;
      mMode9 = NULL;
   }
   //else do nothing, mMode9 not active

   if (mModeHidar != NULL)
   {
      delete mModeHidar;
      mModeHidar = NULL;
   }
   //else do nothing, mModeHIDAR not active

   if (mMode23 != NULL)
   {
      delete mMode23;
      mMode23 = NULL;
   }
   //else do nothing, mMode23 not active

   if (mModeSMA != NULL)
   {
      delete mModeSMA;
      mModeSMA = NULL;
   }
   //else do nothing, mModeSMA not active
}

////////////////////////////////////////////////////////////////////////////////
//! Function: SendChCmd
//!
//! Description:
//!   This method sends a command out the channel command queue to
//!   be received by the channel address space
//!
//! Parameters:
//!   cmdBuff - channel buffer
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChannel::SendChCmd(ChannelCmdStruct *pCmdBuff)
{
   Error err = AllocateMessageQueueBuffer(mChCmd.queueChCmd, &mChCmd.cmdBuffer);  // alloc msg queue buf

   while (err != Success)
   {
      // do not use CHECK here, the loop will repeat until success
      FreeMessageQueueBuffer(mChCmd.queueChCmd, &mChCmd.cmdBuffer);
      err = AllocateMessageQueueBuffer(mChCmd.queueChCmd,
            &mChCmd.cmdBuffer);
   }
   memcpy_safe (mChCmd.cmdBuffer, pCmdBuff, sizeof (ChannelCmdStruct));
   CHECK(SendOnMessageQueue(mChCmd.queueChCmd, mChCmd.cmdBuffer),
          __FILE__, __FUNCTION__, __LINE__,mCommPlan.channelID);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: HandleMgrCmd
//!
//! Description:
//!   This method handles a command received from the Message
//!   Processing Task.  The command is then sent to the channel
//!   address space for processing
//!
//! Parameters:
//!   mgrCmd - manager command structure
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChannel::HandleMgrCmd (ChannelCmdStruct *mgrCmd)
{
   if ( !check4Null(mgrCmd, __FILE__, __LINE__) )
   {
      switch (mgrCmd->cmd)
      {
         case COMM_PLAN_CMD:
              // set comm plan valid and activate mode
              SetChFreq (mCommPlan.frequency);
              mgrCmd->channel = mCommPlan.channelID;
              mgrCmd->index   = -1;
              SendChCmd(mgrCmd);
              break;

         case CONFIG_PARAM_CMD:
              mgrCmd->index   = -1;
              SendChCmd (mgrCmd);
              break;

         case PM_ENABLE_CMD:
              mgrCmd->index   = -1;
              SendChCmd (mgrCmd);
              break;

         case CHAN_MODE_CMD:
              if (mCommPlan.mode15)
              {
                 mMode15->HandleMgrCmd (mgrCmd);
              }
              //else
              //   do nothing, Comm Plan not received for mode.

              if (mCommPlan.mode9)
              {
                 mMode9->HandleMgrCmd (mgrCmd);
              }
              //else
              //   do nothing, Comm Plan not received for mode.

              if (mCommPlan.modeHIDAR)
              {
                 mModeHidar->HandleMgrCmd (mgrCmd);
              }
              //else
              //   do nothing, Comm Plan not received for mode.

              if (mCommPlan.mode23)
              {
                 mMode23->HandleMgrCmd (mgrCmd);
              }
              //else
              //   do nothing, Comm Plan not received for mode.

              if (mCommPlan.modeSMA)
              {
                 mModeSMA->HandleMgrCmd (mgrCmd);
              }
              //else
              //   do nothing, Comm Plan not received for mode.
              break;

         default:
               // str is initialized in the constructor
               std::ostringstream str ( "" );  // string stream
               str << "VLF/LF RELIABILITY ERROR: "
               << __FILE__ << "Line: " << __LINE__ << " "
               << "Integrity ErrorReceived Invalid Mgr Command" << std::ends;
               send_sa_msg ( str.str().c_str() );
              break;

      }
   }//else nothing- error handled in if statement
}
////////////////////////////////////////////////////////////////////////////////
//! Function: HandleChStatus
//!
//! Description:
//!   This method is used to handle a status message from the channel
//!   address space.
//!
//! Parameters:
//!   chstatus - channel status structure
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChannel::HandleChStatus(ChanStatusQueueStruct *chstatus)
{
   if ( !check4Null(chstatus, __FILE__, __LINE__) )
   {
      switch(chstatus->statusBuffer->msg)
      {
         case CHAN_MODE_STATUS:
              mMode15->HandleStatus(chstatus);
              mMode9->HandleStatus(chstatus);
              mModeHidar->HandleStatus(chstatus);
              mMode23->HandleStatus(chstatus);
              mModeSMA->HandleStatus(chstatus);
             break;

         case CHAN_STATUS_ALIVE:
              //link to the CH space is still up.
              //Channel may or may not be active.
              break;

         default:
              {
              std::ostringstream str ( "" );  // string stream
              str << "VLF/LF RELIABILITY ERROR: "
                  << __FILE__ << "Line: " << __LINE__ << " "
                  << "Unexpected Status message from : CH = "
                  << chstatus->statusBuffer->channel << std::ends;
              send_sa_msg( str.str().c_str() );
              }
              break;
      }
   }//else nothing- error handled in if statement
}

////////////////////////////////////////////////////////////////////////////////
//! Function: ReportChStatus
//!
//! Description:
//!   This method is used to send status changes to the OES.  Status
//!   messages are sent only if the current status does not equal
//!   the previous status
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChannel::ReportChStatus()
{
   if (mCommPlan.channelID != 0)
   {
      // get a reference to the channel status struct
      VLF_Receiver_System_Status_Msg_Type* stat = &(CVlf::Instance()->mRcvrStatus);
      VLF_Receiver_Channel_Status_Type* chan = &(stat->chanStatus[mCommPlan.channelID - 1]);
      
      // update the channel status
      chan->VLFChanState = mVlfChanState;
      chan->antiJamOnly  = mAntiJamOnly;
      chan->chanError    = mChannelError;
      
      // update each mode state
      chan->modeHIDARStatus = mCommPlan.modeHIDAR ? mModeHidar->GetStatus() : CH_NOT_SETUP_FOR_MODE;
      chan->modeVM23Status  = mCommPlan.mode23    ? mMode23->GetStatus()    : CH_NOT_SETUP_FOR_MODE;
      chan->modeSMAStatus   = mCommPlan.modeSMA   ? mModeSMA->GetStatus()   : CH_NOT_SETUP_FOR_MODE;
      chan->mode15Status    = mCommPlan.mode15    ? mMode15->GetStatus()    : CH_NOT_SETUP_FOR_MODE;
      chan->mode9Status     = mCommPlan.mode9     ? mMode9->GetStatus()     : CH_NOT_SETUP_FOR_MODE;
      
      // fill message and send
      // snd_msg is initialized in the constructor of CMessage::CMessage
      CMessage snd_msg;    // send msgs
      snd_msg.SetMsgId(VV_VLF_CHANNEL_STATE_MSGTYPE);
      snd_msg.SetSrc(CVlf::Instance()->mId);
      snd_msg.SetDest(DSP2);
      snd_msg.SetActionId(UNSOLICIT_ACTION_ID);
      
      // send out the higher level variable so that all channel info is sent out to dsp2
      (void) snd_msg.SetMsgData(&(stat->chanStatus), sizeof(VLF_Channel_State_Msg_Type));
      CMsgHandler::Instance()->SendMsg(&snd_msg);
   }
   //else - do nothing, comm plan does not specify channel.
}

////////////////////////////////////////////////////////////////////////////////
//! Function: SetChFreq
//!
//! Description:
//!   This method is used to set a new frequency in the FPGA
//!
//! Parameters:
//!   freq - frequency to set
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChannel::SetChFreq(const unsigned int freq)
{
   (FpgaDeviceSingleton::instance()->*mChanSetFreqFPtr)(freq);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: SetChFreq
//!
//! Description:
//!   This method is used to set a frequency in the FPGA
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChannel::SetChFreq()
{
   (FpgaDeviceSingleton::instance()->*mChanSetFreqFPtr)(mChCmd.freq);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: LoadChOutputSample
//!
//! Description:
//!   This method is used to load a channel output sample
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChannel::LoadChOutputSample()
{
   CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, mFpgaRegChanAddress,
         (FpgaDeviceSingleton::instance()->*mChanGetOutputSampleAddrFPtr)()),
         __FILE__, __FUNCTION__, __LINE__,mCommPlan.channelID);
}
////////////////////////////////////////////////////////////////////////////////
//
// State Machine: All state change events come through this context.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//! Function: GetChState
//!
//! Description:
//!   This method is used to get the information stored in
//!       private member mVlfChanState.
//!
//! Parameters:
//!   None
//!   Returns mVlfChanState - Channel State
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
VLF_Channel_State_Type CChannel::GetChState()
{
   return (mVlfChanState);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: SetChState
//!
//! Description:
//!   This method is used to set the information stored in
//!       private member mVlfChanState.
//!
//! Parameters:
//!   VLF_Channel_State_Type chstate
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChannel::SetChState(VLF_Channel_State_Type chstate)
{
   if ((chstate >= VLF_CHANNEL_STATE_TYPE_MAX) || (chstate < 0))
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chstate=" << chstate << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else
   {
      mVlfChanState = chstate;
   }
}
////////////////////////////////////////////////////////////////////////////////
//! Function: setState
//!
//! Description:
//!   This method is used to set the state of the VLF channel.
//!   It will then send a message to the Active OES to update status
//!   Through the ReportChStatus() member function.
//!
//! Parameters:
//!   IChannelState* newChannelState- ptr to state class
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChannel::setState(IChannelState* newChannelState)
{
   if ( !check4Null(newChannelState, __FILE__, __LINE__) )
   {
      mChannelState = newChannelState;
      SetChState(mChannelState->getChannelState());

      // If VLF State is not Init, report the new state to the OES
      if (CVlf::Instance()->mRcvrStatus.receiverState != VLF_INITIALIZATION)
      {
         // Send OES the channel State Change Status
         ReportChStatus();
      }
      //else
      //   do nothing, still initializing

      // Report Channel State Change to VLF Receiver State
      CVlf::Instance()->ChannelStateChange();
   }//else nothing- error handled in if statement
}
////////////////////////////////////////////////////////////////////////////////
//! Function: StartChannel
//!
//! Description:
//!   This method is used to change the channel State
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
////////////////////////////////////////////////////////////////////////////////
void CChannel::StartChannel()
{
   mChannelState->StartChannel(this);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: StopChannel
//!
//! Description:
//!   This method is used to change the channel State
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
////////////////////////////////////////////////////////////////////////////////
void CChannel::StopChannel()
{
   mChannelState->StopChannel(this);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: LoadTime
//!
//! Description:
//!   This method is used to change the channel State
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
////////////////////////////////////////////////////////////////////////////////
void CChannel::LoadTime()
{
   mChannelState->LoadTime(this);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: ChangeCpChanOpStatus
//!
//! Description:
//!   This method is used to change the channel State
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
//! Notes:
//!   Called from file secondary_Msg_Proc_Task.cc Method wait4configReturn
//!
////////////////////////////////////////////////////////////////////////////////
void CChannel::ChangeCpChanOpStatus()
{
   mChannelState->ChangeCpChanOpStatus(this);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoStatus
//!
//! Description:
//!   This method is used to change the channel State
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
////////////////////////////////////////////////////////////////////////////////
void CChannel::CryptoStatus()
{
   mChannelState->CryptoStatus(this);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoChannel
//!
//! Description:
//!   This method is used to change the channel State
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
////////////////////////////////////////////////////////////////////////////////
void CChannel::CryptoChannelUpdate()
{
   mChannelState->CryptoChannelUpdate(this);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoBIT
//!
//! Description:
//!   This method is used to change the channel State
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
////////////////////////////////////////////////////////////////////////////////
void CChannel::CryptoBIT()
{
   mChannelState->CryptoBIT(this);
}
////////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
////////////////////////////////////////////////////////////////////////////////
