
///////////////////////////////////////////////////////////////////////////////
// TASK: Continuous BIT Task (CBIT_Task)
//
// File Name: main_CBit_Task.cc
//
// Description: The task handles the Continuous BIT testing that is activated
//              with a semiphore. This task will wait forever until it receives
//              the notification.  When the task receives the release it will
//              perform BIT tests as required.
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include <sstream>
#include "KgrVpApp_integrate.h"
#include "CDspBIT.h"
#include "CControlVars.h"
#include "CVlf.h"
#include "CMessage.h"
#include "TMemStrUtility.h"
#include "CMsgHandler.h"
#include "RcvrStatusIoDevice.h"
#include "CBitTaskLoop.h"

bool mSendCBITResult = false;        // send CBIT result
BIT_Result_Type mPrevDspCBit = {0};  // previous CBIT result

void checkCBITStatus();
void updateEthernetStatus();
void HaltAllChannels( const Channel_Action_Type& action );

////////////////////////////////////////////////////////////////////////////////
//! Function: main_CBit_Task
//!
//! Description: This is the main body of the task.  It is called in the INT file
//!              as part of the OS startup.  This task is responsible for actions
//!              for continuous BIT.
//!
//! Parameters:  None
//!
//! Return:  None
//!
//! Notes:
//!   This task performs the following functions:
//!
//!   1) This task will wait until the binary semiphore is released.
//!   2) It will perform all CBit actions.
//!   3) The task will then send out CBit status as necessary.
//!   4) repeat
//!
//!
////////////////////////////////////////////////////////////////////////////////
void main_CBit_Task ()
{
   // Invoke the common task loop helper function.
   DSPBIT::mainCBitTaskLoop( checkCBITStatus );
}

///////////////////////////////////////////////////////////////////
//! Function: checkCBITStatus
//!
//! Description:
//!   This method is used to initiate Continuous BIT
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
void checkCBITStatus()
{
   bool statusChanged    = false;      // status changed flag

   //run CBIT.
   CVlf::Instance()->mDspCBit = CDspBIT::Instance()->runDspCBIT();

   // run watchdog effort as part of CBIT
   ReleaseSemaphore( CControlVars::Instance()->sWatchDog );

   //update ethernet status
   updateEthernetStatus();

   //update status
   if ( CVlf::Instance()->mDspCBit.result != mPrevDspCBit.result )
   {
      mPrevDspCBit.result = CVlf::Instance()->mDspCBit.result;
      statusChanged = true;
   }
   // else status has not changed

   // Report CBIT to DSP2 if status changed or the first
   // CBIT results being sent to DSP2 since CBIT may have started before
   // connection to an DSP2 is established.
   if ( ( mSendCBITResult ) || ( statusChanged ) )
   {
      //Report CBIT to DSP2
      if (CVlf::Instance()->mDSP2LinkUp)
      {
         BIT_Result_Type msgData;
         memset_safe(&msgData, 0, sizeof(BIT_Result_Type));
         msgData = CVlf::Instance()->mDspCBit;

         //VO_VLF_RECEIVER_CBIT_RESULT_MSGTYPE
         // fill message and send to DSP2
         CMessage rsp_msg;  // rsp msg
         rsp_msg.SetMsgId(VV_DSP1_CBIT_RESULT_MSGTYPE);
         rsp_msg.SetSrc(DSP1);
         rsp_msg.SetDest(DSP2);
         rsp_msg.SetActionId(0);
         (void) rsp_msg.SetMsgData(&msgData, sizeof(BIT_Result_Type));

         // send response message to DSP2
         CMsgHandler::Instance()->SendMsg(&rsp_msg);
         mSendCBITResult = false;

      }
      else //Link to DSP2 is still down, set flag to send CBIT
      {
         mSendCBITResult = true;
      }
   }
   //else nothing- no work to be done
}

///////////////////////////////////////////////////////////////////
//! Function: updateEthernetStatus
//!
//! Description:
//!   This method is used to update the link status of both cp
//!   and dsp2.  It will also clear up status info if the status
//!   changes.
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
void updateEthernetStatus()
{
   bool currentLinkStatus = false;      // link status holder
   Rcvr_Status_Iodevice_Type statData;  // status
   memset_safe (&statData, 0, sizeof(Rcvr_Status_Iodevice_Type));

   currentLinkStatus = CDspBIT::Instance()->isCPLinkUp();

   //update crypto status only if diffeerent from last time checked
   if ( CVlf::Instance()->mCPLinkUp != currentLinkStatus )
   {
      CVlf::Instance()->mCPLinkUp = currentLinkStatus;

      // halt all channels and clear out status info if cp link down
      if ( !CVlf::Instance()->mCPLinkUp )
      {
         // clear out the system status variable
         CVlf::Instance()->mRcvrStatus.CMState.ECUState = ECU_ALARM;
         CVlf::Instance()->mRcvrStatus.CMState.ECUSubstate = NO_SUBSTATE;

         for(int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
         {
             CVlf::Instance()->mRcvrStatus.chanStatus[chanNum].cryptoChanState = CH_ALARM;
         }//end for loop

         // Call State Transition Event
         CVlf::Instance()->CryptoStatusChange();

         //halt any active channels
         HaltAllChannels( CP_CHAN_ALARM_HALT );
      }
      //else nothing- link is up

      //set cp eth status in the rcvr io device
      statData.cpEthStatus = CVlf::Instance()->mCPLinkUp;

      // write the status of the cp ethernet
      CHECK(WriteIODeviceStatus(RcvrStatusIODeviceObject_Mgr,
            IODEV_CP_STATUS, &statData, sizeof(statData)),
            __FILE__, __FUNCTION__, __LINE__);
   }
   //else nothing- do nothing no change in status

   currentLinkStatus = CDspBIT::Instance()->isDSP2LinkUp();

   //update dsp2 status only if diffeerent from last time checked
   if ( CVlf::Instance()->mDSP2LinkUp != currentLinkStatus )
   {
      CVlf::Instance()->mDSP2LinkUp = currentLinkStatus;

      // halt all channels if link is down
      if ( !CVlf::Instance()->mDSP2LinkUp )
      {
         mSendCBITResult = true; // Enable sending of CBIT results to DSP2 when connection (to DSP2) is regained
         HaltAllChannels( STOP_CHANNEL_FORCED );
      }
      //else nothing- do nothing the link is up

      //set dsp eth status in the rcvr io device
      statData.dspEthStatus = CVlf::Instance()->mDSP2LinkUp;

      // write the status of the dsp ethernet
      CHECK(WriteIODeviceStatus(RcvrStatusIODeviceObject_Mgr,
            IODEV_DSP_STATUS, &statData, sizeof(statData)),
            __FILE__, __FUNCTION__, __LINE__);
   }
   //else nothing- do nothing no change in status

}

///////////////////////////////////////////////////////////////////
//! Function: HaltAllChannels
//!
//! Description:
//!   This method is used to halt all channels.  It is called when
//!   the status of a link to dsp2 or cp is lost.
//!
//! Parameters:
//!   const Channel_Action_Type& action - reference to an action
//!                [STOP_CHANNEL_FORCED, CP_CHAN_ALARM_HALT]
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void HaltAllChannels( const Channel_Action_Type& action )
{
   int chanNum = 0;             // channel #
   Error condError = Failure;   // error code

   //loop through all channels and force halt
   for ( chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++ )
   {
      //only halt the channel if it is active any mode
      if (( CVlf::Instance()->chan[chanNum]->mMode15->
               mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) ||
          ( CVlf::Instance()->chan[chanNum]->mMode9->
               mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) ||
          ( CVlf::Instance()->chan[chanNum]->mModeHidar->
               mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) ||
          ( CVlf::Instance()->chan[chanNum]->mMode23->
               mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) ||
          ( CVlf::Instance()->chan[chanNum]->mModeSMA->
               mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) )
      {
         condError = TryToObtainSemaphore(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].sMsgAction);

         if (Success == condError)
         {
            //pass in msg info to the secondary processing variable
            //we are within a semaphore, data ok to modify
            CControlVars::Instance()->sec_msg_proc_struct[chanNum].
               secProcMsg.msgActionID = UNSOLICIT_ACTION_ID;

            CControlVars::Instance()->sec_msg_proc_struct[chanNum].
               secProcMsg.msgAction = action;

            //send Condition and Release Semaphore
            SignalCondition(CControlVars::Instance()->
               sec_msg_proc_struct[chanNum].conAction);

            ReleaseSemaphore(CControlVars::Instance()->
               sec_msg_proc_struct[chanNum].sMsgAction);
         }
         else
         {
            std::ostringstream str ( "" );   // string stream
            str << "VLF/LF RELIABILITY ERROR: "
                << __FILE__ << "Line: " << __LINE__
                << "Channel " << chanNum+1 <<
                   " could not be Halted after Ethernet Link Down." << std::ends;
            send_sa_msg ( str.str().c_str() );
         }
      }
      //else nothing- do not halt the channel
   }//end for loop
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
