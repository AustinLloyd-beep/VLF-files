
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CMode.cc
//
// Description: This file contains the Base class CMode definition and
//              the specific Mode class definitions
//
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include <sstream>
#include "CMode.h"
#include "CVlf.h"
#include "chan_struct.h"
#include "msg_defs.h"
#include "CKeyEffectData.h"
#include "utility.h"


///////////////////////////////////////////////////////////////////
//! Function: Constructor
//!
//! Description:
//!   This method constructs the base mode object and initialize
//!   the mode specific data
//!
//! Parameters:
//!   chan - channel number
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CMode::CMode()
{
    //initialize mCommand
    mCommand = UNDEFINED;
    mPrevCommand = UNDEFINED;

    //Status to be sent to OES
    mModeStatus = CH_NOT_SETUP_FOR_MODE;

    //Initialize
    mChanModeStatus.modeCmdError = NO_ERROR_PRESENT;
    mChanModeStatus.modeScanState = MODE_SEARCH_HALTED;

    mPrevChanModeStatus.modeCmdError = NO_ERROR_PRESENT;
    mPrevChanModeStatus.modeScanState = MODE_SEARCH_HALTED;

    // 20 ms counter
    mCnt20ms = -1;
}

///////////////////////////////////////////////////////////////////
//! Function: GetNextCmd
//!
//! Description:
//!   This method returns the next command to be sent to the mode
//!   address space. The mode is started using the
//!   Init_Mode_Search command.
//!
//! Parameters:
//!   None
//!
//! Return:
//!   mCommand - Mode_Command_Type
//!
//! Notes:
//!   A typical sequence looks like the following:
//!    continue, continue,init, continue, continue, Data_Valid,
//!    continue, continue, continue, Halt, continue,continue....
//!
///////////////////////////////////////////////////////////////////
Mode_Command_Type CMode::GetNextCmd()
{
   if (mCnt20ms >= 0)
   {
      mCnt20ms++;
      if (mCnt20ms == NUM_20MSEC_FOR_INIT)
      {
          mCommand =INIT_MODE_SEARCH;
          if (mPrevCommand != mCommand)
          {
             mPrevCommand =  mCommand;
          }
         //else do nothing, same command
      }
      else if (mCnt20ms >= NUM_20MSEC_FOR_DATA_VALID)
      {
         mCommand =DATA_VALID;
         if (mPrevCommand != mCommand)
         {
            mPrevCommand =  mCommand;
         }
         //else do nothing, same command
      }
      else
      {
         if (mCnt20ms >=0)
         {
            mCommand =CONTINUE_IDLE_OPERATION;
            if (mPrevCommand != mCommand)
            {
               mPrevCommand =  mCommand;
            }
            //else do nothing, same command
         }//else nothing- else unreachable
      }
   }
   else //mCnt20ms == -1
   {
      mCommand =HALT_SEARCH;
      if (mPrevCommand != mCommand)
      {
         mPrevCommand =  mCommand;
      }
      //else do nothing, same command
   }
   return (mCommand);
}

///////////////////////////////////////////////////////////////////
//! Function: GetStatus
//!
//! Description:
//!   Retrieve the overall reported mode status
//!
//! Parameters:
//!   None
//!
//! Return:
//!   overall mode status
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
Channel_Mode_Processing_Status_Type CMode::GetStatus(){
    // maintain an internal state of IN_SYNC during SYNC_HOLD, while reporting a searching state
    return (mModeStatus == IN_SYNC && mChanModeStatus.modeScanState == MODE_SYNC_HOLD) ? 
        SEARCHING : mModeStatus;
}

///////////////////////////////////////////////////////////////////
//! Function: HandleStatus
//!
//! Description:
//!   This method is used to handle a status message from the channel
//!   address space for all modes except Mode 15.
//!
//! Parameters:
//!   chstatus - channel status structure
//!
//! Notes:
//!   This base class method was created to eliminate the detection of duplicate
//!   algorithms in the code as reported by the customer's analysis tool.
//!
///////////////////////////////////////////////////////////////////
void CMode::HandleStatus(ChanStatusQueueStruct *chstatus)
{
   if (( !check4Null(chstatus, __FILE__, __LINE__) ) &&
       ( !check4Null(chstatus->statusBuffer, __FILE__, __LINE__) ) )
   {
      if ( chstatus->statusBuffer->msg == CHAN_MODE_STATUS )
      {
         //Set channel mode status - ModeStatusDataType from chan_struct.h
         mChanModeStatus = GetModeSignalStatusType( chstatus );
         if (mPrevChanModeStatus.modeScanState != mChanModeStatus.modeScanState)
         {
            // If previous channel mode status was in-sync check TEK
            // Perform a rollover if required.
            if (mPrevChanModeStatus.modeScanState == MODE_IN_SYNC)
            {
               if (CKeyEffectData::Instance()->
                   get_mTEKRollover (chstatus->statusBuffer->channel - 1))
               {
                  CKeyEffectData::Instance()->
                     rolloverEffectivity(chstatus->statusBuffer->channel - 1);
               }
               //else
               //   do nothing, no rollover
            }
            //else
            //   do nothing if not in sync.

            mPrevChanModeStatus.modeScanState = mChanModeStatus.modeScanState;
            
            // set mode status to be sent to HMI by channel object
            if ((mChanModeStatus.modeScanState == MODE_IN_SYNC)  ||
                (mChanModeStatus.modeScanState == MODE_SYNC_HOLD))
            {
               mModeStatus = IN_SYNC;
            }
            else if ((mChanModeStatus.modeScanState == MODE_SEARCH_INITIALIZING) ||
                     (mChanModeStatus.modeScanState == MODE_SEARCHING) ||
                     (mChanModeStatus.modeScanState == MODE_NO_SYNC) ||
                     (mChanModeStatus.modeScanState == MODE_SCAN_HOLD))
            {
                mModeStatus = SEARCHING;
            }
            else if  (mChanModeStatus.modeScanState == MODE_SEARCH_HALTED)
            {
                mModeStatus = SEARCH_HALTED;
                // Call StopChannel() event
                CVlf::Instance()->
                  chan[chstatus->statusBuffer->channel - 1]->StopChannel();
            }
            else
            {
               mModeStatus = VLF_ERROR;
            }
            // Report channel status
            CVlf::Instance()->chan[chstatus->statusBuffer->channel - 1]->ReportChStatus();
         }//else nothing- state equal
      }
      else
      {
         // str is initialized in the constructor
         std::ostringstream str ( "" ); // string stream
         str << "Unexpected Status message from : CH = "
             << chstatus->statusBuffer->channel << std::ends;
         send_sa_msg ( str.str().c_str() );
      }
   }
   else
   {
      // str is initialized in the constructor
      std::ostringstream str ( "" ); // string stream
      str << "NULL reference in chstatus for CMode9::HandleStatus()"
          << std::ends;
      send_sa_msg ( str.str().c_str() );
   }

}

///////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////
void CMode::HandleMgrCmd(ChannelCmdStruct *mgrCmd)
{
   if ( !check4Null(mgrCmd, __FILE__, __LINE__) )
   {
      // Start channel
      if (mgrCmd->cmdData.modeCmdData.commands[mChanMode] == INIT_MODE_SEARCH)
      {
         // start only if channel is not active
         if ((mChanModeStatus.modeScanState == MODE_SEARCH_HALTED) ||
             (mPrevCommand == HALT_SEARCH))
         {
            mCnt20ms = 0;

            // Call StartChannel() event
            CVlf::Instance()->chan[mgrCmd->channel - 1]->StartChannel();
         }
         //else
         //   do nothing, channel already active
      }
      else if (mgrCmd->cmdData.modeCmdData.commands[mChanMode] == HALT_SEARCH)
      {
         // Check if channel is in sync
         if (mChanModeStatus.modeScanState != MODE_IN_SYNC)
         {
            mCnt20ms = -1;
         }
         //else nothing- channel in sync,
      }
      // Force shutdown of channel
      else if (mgrCmd->cmdData.modeCmdData.commands[mChanMode] == HALT_SEARCH_FRCD)
      {
         mCnt20ms = -1;
      }
      else
      {
         // str is initialized in the constructor
         std::ostringstream str ( "" ); // string stream
         str << "VLF/LF RELIABILITY ERROR: "
             << __FILE__ << "Line: " << __LINE__
             << " Illegal Manager Command." << std::ends;
         send_sa_msg ( str.str().c_str() );
      }
   }//else nothing- error handled in if statement
}

///////////////////////////////////////////////////////////////////
//! Function: Constructor
//!
//! Description:
//!   This method constructs the mode 15 object and initialize
//!   it for a channel
//!
//! Parameters:
//!   chan - channel number
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CMode15::CMode15() : CMode()
{
   mChanMode = NORMAL_MODE_15;
}
///////////////////////////////////////////////////////////////////
//! Function: Constructor
//!
//! Description:
//!   This method constructs the mode 9 object and initialize
//!   it for a channel
//!
//! Parameters:
//!   chan - channel number
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CMode9::CMode9() : CMode()
{
   mChanMode = SPECIAL_MODE_9;
}
///////////////////////////////////////////////////////////////////
//! Function: Constructor
//!
//! Description:
//!   This method constructs the mode HIDAR object and initialize
//!   it for a channel
//!
//! Parameters:
//!   chan - channel number
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CModeHidar::CModeHidar() : CMode()
{
   mChanMode = SPECIAL_MODE_HIDAR;
}
///////////////////////////////////////////////////////////////////
//! Function: Constructor
//!
//! Description:
//!   This method constructs the Mode 23 object and initialize
//!   it for a channel
//!
//! Parameters:
//!   chan - channel number
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CMode23::CMode23() : CMode()
{
   mChanMode = VERDIN_MODE_23;
}
///////////////////////////////////////////////////////////////////
//! Function: Constructor
//!
//! Description:
//!   This method constructs the Mode SMA object and initialize
//!   it for a channel
//!
//! Parameters:
//!   chan - channel number
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CModeSMA::CModeSMA() : CMode()
{
   mChanMode = SPECIAL_MODE_A;
}
///////////////////////////////////////////////////////////////////
//! Function: HandleStatus
//!
//! Description:
//!   This method is used to handle a status message from the channel
//!   address space for Mode 15.
//!
//! Parameters:
//!   chstatus - channel status structure
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CMode15::HandleStatus(ChanStatusQueueStruct *chstatus)
{
   if (( !check4Null(chstatus, __FILE__, __LINE__) ) &&
       ( !check4Null(chstatus->statusBuffer, __FILE__, __LINE__) ) )
   {
      switch(chstatus->statusBuffer->msg)
      {
         case CHAN_MODE_STATUS:
            //Set channel mode status - ModeStatusDataType from chan_struct.h
            mChanModeStatus = GetModeSignalStatusType( chstatus );
            if (mPrevChanModeStatus.modeScanState != mChanModeStatus.modeScanState)
            {
               mPrevChanModeStatus.modeScanState = mChanModeStatus.modeScanState;
               // set mode status to be sent to OES by channel object
               if (mChanModeStatus.modeScanState == MODE_IN_SYNC)
               {
                  mModeStatus = IN_SYNC;
               }
               else if ((mChanModeStatus.modeScanState == MODE_SEARCH_INITIALIZING) ||
                        (mChanModeStatus.modeScanState == MODE_SEARCHING) ||
                        (mChanModeStatus.modeScanState == MODE_NO_SYNC))
               {
                   mModeStatus = SEARCHING;
               }
               else if  (mChanModeStatus.modeScanState == MODE_SEARCH_HALTED)
               {
                   mModeStatus = SEARCH_HALTED;
                   // Call StopChannel() event
                   CVlf::Instance()->
                     chan[chstatus->statusBuffer->channel - 1]->StopChannel();
               }
               else
               {
                  mModeStatus = VLF_ERROR;
               }
               // Report channel status
               CVlf::Instance()->chan[chstatus->statusBuffer->channel - 1]->ReportChStatus();
            }//else nothing- states equal
            break;
         default:
            {
               // str is initialized in the constructor
               std::ostringstream str ( "" );  // string stream
               str << "Unexpected Status message from : CH = "
                   << chstatus->statusBuffer->channel << std::ends;
               send_sa_msg ( str.str().c_str() );
            }
            break;
      }
   }//else nothing- error handled in if statement
}

///////////////////////////////////////////////////////////////////
//! Function: GetModeSignalStatusType
//!
//! Description:
//!   This method retrieves the status type from
//!   the ChanStatusQueueStruct data for Mode 15.
//!
//! Parameters:
//!   chstatus - channel status structure
//    Return value - Mode_Signal_Status_Type
//!
//! Notes:
//!   Caller is responsible for ensuring chstatus and statusBuffer
//!   pointers are non-NULL before calling this method.
//!
///////////////////////////////////////////////////////////////////
Mode_Signal_Status_Type CMode15::GetModeSignalStatusType(ChanStatusQueueStruct *chstatus)
{
   return chstatus->statusBuffer->modeStatus.statusMode15;
}

///////////////////////////////////////////////////////////////////
//! Function: GetModeSignalStatusType
//!
//! Description:
//!   This method retrieves the status type from
//!   the ChanStatusQueueStruct data for Mode 9.
//!
//! Parameters:
//!   chstatus - channel status structure
//!   Return value - Mode_Signal_Status_Type
//!
//! Notes:
//!   Caller is responsible for ensuring chstatus and statusBuffer
//!   pointers are non-NULL before calling this method.
//!
///////////////////////////////////////////////////////////////////
Mode_Signal_Status_Type CMode9::GetModeSignalStatusType(ChanStatusQueueStruct *chstatus)
{
   return chstatus->statusBuffer->modeStatus.statusMode9;
}

///////////////////////////////////////////////////////////////////
//! Function: GetModeSignalStatusType
//!
//! Description:
//!   This method retrieves the status type from
//!   the ChanStatusQueueStruct data for Mode HIDAR.
//!
//! Parameters:
//!   chstatus - channel status structure
//!   Return value - Mode_Signal_Status_Type
//!
//! Notes:
//!   Caller is responsible for ensuring chstatus and statusBuffer
//!   pointers are non-NULL before calling this method.
//!
///////////////////////////////////////////////////////////////////
Mode_Signal_Status_Type CModeHidar::GetModeSignalStatusType(ChanStatusQueueStruct *chstatus)
{
   return chstatus->statusBuffer->modeStatus.statusModeHIDAR;
}

///////////////////////////////////////////////////////////////////
//! Function: GetModeSignalStatusType
//!
//! Description:
//!   This method retrieves the status type from
//!   the ChanStatusQueueStruct data for Mode 23.
//!
//! Parameters:
//!   chstatus - channel status structure
//!   Return value - Mode_Signal_Status_Type
//!
//! Notes:
//!   Caller is responsible for ensuring chstatus and statusBuffer
//!   pointers are non-NULL before calling this method.
//!
///////////////////////////////////////////////////////////////////
Mode_Signal_Status_Type CMode23::GetModeSignalStatusType(ChanStatusQueueStruct *chstatus)
{
   return chstatus->statusBuffer->modeStatus.statusMode23;
}

///////////////////////////////////////////////////////////////////
//! Function: GetModeSignalStatusType
//!
//! Description:
//!   This method retrieves the status type from
//!   the ChanStatusQueueStruct data for Mode SMA.
//!
//! Parameters:
//!   chstatus - channel status structure
//!   Return value - Mode_Signal_Status_Type
//!
//! Notes:
//!   Caller is responsible for ensuring chstatus and statusBuffer
//!   pointers are non-NULL before calling this method.
//!
///////////////////////////////////////////////////////////////////
Mode_Signal_Status_Type CModeSMA::GetModeSignalStatusType(ChanStatusQueueStruct *chstatus)
{
   return chstatus->statusBuffer->modeStatus.statusModeSMA;
} 

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
