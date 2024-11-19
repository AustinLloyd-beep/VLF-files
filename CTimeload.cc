///////////////////////////////////////////////////////////////////////////////
//
// Class: TimeLoad
//
// File Name: CTimeload.cc
//
// Description:
//
// Notes: The time loading process allows for a manual time load using an
//        Ethernet message and a time pulse (ex. 1PPM/PPS), or using a
//        GPS-0-60 42 BIT STOD into the FPGA.
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include <sstream>
#include "rc_bsp_defs.h"
#include "utility.h"
#include "KgrVpApp_integrate.h"
#include "CTimeLoad.h"
#include "utility.h"
#include "CKeyEffectData.h"
#include "TMemStrUtility.h"
#include "CVLF.h"
#include "CControlVars.h"

//********************************************************************
//
// Global Data and Constants.
//
//********************************************************************


///////////////////////////////////////////////////////////////////
//! Function: Constructor
//!
//! Description: This function initialize the member elements and
//!             setup the FPGA for Time Load
//!
//! Parameters:
//!    None
//!
//! Notes:
//!
///////////////////////////////////////////////////////////////////
CTimeLoad::CTimeLoad()
{
   // set TimeLoad initial state
   mState = TimeNotLoaded;

   // initialize error
   mErr = NoError;
   mStodErr = ErrNoStodReceived; // init to faulted

   memset_safe( &mTimeOfDay, UNUSED_VARIABLE_VAL, sizeof(Date_Time_Type) );
   mStyleOfTimeLoad = NO_LOAD;
}
///////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//!   This method is used to destroy the TimeLoad object. It will also
//!   free up any allocated memory.
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CTimeLoad::~CTimeLoad()
{
   // if mInstance still exists, delete it.
   if (mInstance != NULL)
   {
      delete mInstance;
      mInstance = NULL;
   }//else NULL - No action necessary
}
///////////////////////////////////////////////////////////////////
//! Function: Instance
//!
//! Description:
//!   This method is used to obtain an instance of the CTimeLoad
//!   class
//!
//! Parameters:
//!
//! Return:
//!   Pointer to CTimeLoad object
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CTimeLoad* CTimeLoad::Instance()
{
   if (mInstance == NULL)
   {
      mInstance = new CTimeLoad;

      // Check to see of mInstance is NULL
      (void) check4Null(mInstance, __FILE__, __LINE__);
   }//else nothing- else unreachable
   return mInstance;
}
///////////////////////////////////////////////////////////////////
//! Function: SendTimeLoadCmd
//!
//! Description: This method sends a command to the FPGA Device IO
//!              Object
//! Parameters:
//!   TimeLoadCmd cmd - command to send the FPGA
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CTimeLoad::SendTimeLoadCmd(TimeLoadCmd cmd)
{
   CHECK(WriteIODeviceStatus(FpgaIoDeviceObject_MGR, IODEV_FPGA_DATA_TIMELOAD,
       &cmd, sizeof(TimeLoadCmd)), __FILE__, __FUNCTION__, __LINE__);
}
///////////////////////////////////////////////////////////////////
//! Function: GetTimeStatus
//!
//! Description:  This method will retrieve the time load status
//!               from the FPGA device IO object
//!
//! Parameters:
//!   None
//!
//! Notes:
//!      timeLoadStatus[0] = TimeLoadState - state of time load
//!      timeLoadStatus[1] = TimeLoadError - error during time load
//!      timeLoadStatus[2] = 1PPSError - error in PPS signal
//!      timeLoadStatus[3] = StodError - error in detection of stod
//!
///////////////////////////////////////////////////////////////////
void CTimeLoad::GetTimeStatus()
{
   Value timeLoadStatus[NUM_TIMELOAD_STATUS_ELEMENTS] =
         {TimeNotLoaded, ErrTimeLoadWarning, ErrNoPPSInterrupt, ErrNoStodReceived};   // timeload status
   Error err = Failure;   // error code

   CHECK(err = ReadIODeviceStatus(FpgaIoDeviceObject_MGR, IODEV_FPGA_STAT_TIMELOAD,
       timeLoadStatus, sizeof(timeLoadStatus)), __FILE__, __FUNCTION__, __LINE__);

   if (err == Success)
   {
      mState   = (TimeLoadState)timeLoadStatus[0];
      mErr     = (TimeLoadError)timeLoadStatus[1];
      mPpsErr  = (TimeLoadError)timeLoadStatus[2];
      mStodErr = (TimeLoadError)timeLoadStatus[3];
   }//else nothing- error sent out by CHECK
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CTimeLoad::RestartChannelAfterTimeLoad
//!
//! Description:
//!   This method handles the abililty to restart each channel as necessary after
//!   a time load event.  Each channel is restarted based on current comm plan
//!   configuration.  Time Load is a major event and requires time to be reset
//!   through the VLF System.  This function send the RESTART_CHANNEL action
//!   to the secondary message processing task for each channel.
//!
//! Parameters:
//!    int - channel number
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void CTimeLoad::RestartChannelAfterTimeLoad(int& chanNum)
{
   Error condError = Failure;   // error code

   //only restart the channel if it is active in SModes
   if (( CVlf::Instance()->chan[chanNum]->mMode9->
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
            secProcMsg.msgAction = RESTART_CHANNEL;

         //send Condition and Release Semaphore
         SignalCondition(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].conAction);

         ReleaseSemaphore(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].sMsgAction);
      }
      else
      {
         // str is initialized in the constructor
         std::ostringstream str ( "" ); // string stream
         str << "VLF/LF RELIABILITY ERROR: "
             << __FILE__ << " Line: " << __LINE__ << " "
             << "Channel " << chanNum+1
             << " could not be restarted after Time Load." << std::ends;
         send_sa_msg ( str.str().c_str() );
      }
   }
   //else nothing- do not restart the channel
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CTimeLoad::LoadTime
//!
//! Description:
//!   This method handles loading of time,
//!       [TimeNotLoaded] - then load time
//!       reload time if no channel is in sync for sm modes
//!
//! Parameters:
//!    cmd - time load cmd
//!    timeLoadStyle - load type
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void CTimeLoad::LoadTime(TimeLoadCmd cmd, Load_Type timeLoadStyle)
{
   bool insynch = false;  // in sync flag

   // time has not been loaded
   if ( TimeNotLoaded == mState )
   {
      SendTimeLoadCmd(cmd);
      setLoadType( timeLoadStyle );
   }
   // time is loaded so see if we can reload time
   else
   {
      if ( TimeLoaded == mState )
      {
         // Error if any mode on any channel (1-5) is in sync.
         // Time Load is not allowed if any mode of the channels are in sync
          for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
         {
            if ((CVlf::Instance()->chan[chanNum]->mMode15->
                  mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
                (CVlf::Instance()->chan[chanNum]->mMode9->
                  mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
                (CVlf::Instance()->chan[chanNum]->mModeHidar->
                  mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
                (CVlf::Instance()->chan[chanNum]->mMode23->
                  mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
                (CVlf::Instance()->chan[chanNum]->mModeSMA->
                  mChanModeStatus.modeScanState == MODE_IN_SYNC)  )
            {
               insynch = true;
               break;
            } // else - no action required
         }//end for loop

         if ( !insynch )
         {
            SendTimeLoadCmd(cmd);
            setLoadType( timeLoadStyle );

            std::ostringstream str ( "" ); // string stream
            str << "VLF/LF ADVISORY MESSAGE: "
                << __FUNCTION__ << " Time Reload Command." << std::ends;
            send_sa_msg ( str.str().c_str() );
         }// else nothing - do not load time
      }
      //else nothing
   }
}
///////////////////////////////////////////////////////////////////
//! Function: GetVlfTime
//!
//! Description:  This method will retrieve the time load status
//!               from the FPGA device IO object
//!
//! Parameters:
//!   None
//! Return:
//!   VlfTime - time load status
//!
//! Notes:
//!      timeLoadStatus[0] = vlfTime.sec - VLF internal time (seconds)
//!      timeLoadStatus[1] = vlfTime.frames - VLF internal time (frames)
//!      timeLoadStatus[2] = vlfTime.doy - VLF internal time (day of year)
//!      timeLoadStatus[2] = vlfTime.offset - FPGA Offset value
//!
///////////////////////////////////////////////////////////////////
VlfTime CTimeLoad::GetVlfTime()
{
   Value timeLoadStatus[NUM_TIME_STATUS_ELEMENTS] = {0,0,0,0};  // time load status
   VlfTime time = {0,0,0,0};   // VLF time
   Error err = Failure;        // error code

   CHECK(err = ReadIODeviceStatus(FpgaIoDeviceObject_MGR, IODEV_FPGA_STAT_TIME,
       timeLoadStatus, sizeof(timeLoadStatus)), __FILE__, __FUNCTION__, __LINE__);

   if (err == Success)
   {
      time.sec = timeLoadStatus[0];
      time.frames = timeLoadStatus[1];
      time.doy = timeLoadStatus[2];
      time.offset = timeLoadStatus[3];
   }//else nothing- error sent out by CHECK

   return time;
}
////////////////////////////////////////////////////////////////////////////////
//! Function: GetAbsTime
//!
//! Description:  This method will retrieve the time load status
//!               from the FPGA device IO object, then format the data
//!               into a data type used in the chan_struct.h file for mode code.
//!
//! Parameters:
//!   absolute_time_type pointer- pointer to time structure used by mode code
//!
//! Notes:
//!      timeLoadStatus[0] = vlfTime.sec - VLF internal time (seconds)
//!      timeLoadStatus[1] = vlfTime.frames - VLF internal time (frames)
//!      timeLoadStatus[2] = vlfTime.doy - VLF internal time (day of year)
//!
////////////////////////////////////////////////////////////////////////////////
void CTimeLoad::GetAbsTime(Absolute_Time_Type* absTime)
{
   Value timeLoadStatus[NUM_TIME_STATUS_ELEMENTS] = {0,0,0,0};   // time load status
   VlfTime time = {0,0,0};  // VLF time
   Error err = Failure;     // error code

   if ( !check4Null(absTime, __FILE__, __LINE__) )
   {
      CHECK(err = ReadIODeviceStatus(FpgaIoDeviceObject_MGR, IODEV_FPGA_STAT_TIME,
          timeLoadStatus, sizeof(timeLoadStatus)), __FILE__, __FUNCTION__, __LINE__);


      if (err == Success)
      {
         time.sec = timeLoadStatus[0];
         time.frames = timeLoadStatus[1];
         time.doy = timeLoadStatus[2];

         // Convert the seconds into (hours, minutes, seconds)
         absTime->Hours   = (unsigned short) (time.sec / NUM_SEC_PER_HOUR);
         absTime->Minutes = (unsigned short) ((time.sec % NUM_SEC_PER_HOUR) / NUM_MINUTES);
         absTime->Seconds = (unsigned short) ((time.sec % NUM_SEC_PER_HOUR) % NUM_SECONDS);
         absTime->Frames  = (unsigned short) (time.frames);
      }//else nothing- error sent out by CHECK
   }//else nothing- error handled in if statement
}
////////////////////////////////////////////////////////////////////////////////
//! Function: RunPpsPbit
//!
//! Description:  This method will send the command to run PBit pps checking in
//!               the FPGA_IO_Device.
//!
//! Parameters:
//!  cmd - command to send FPGA_IO_DEVICE
//!
//! Notes:
//!  None
//!
////////////////////////////////////////////////////////////////////////////////
void CTimeLoad::RunPpsPbit(TimeLoadCmd cmd)
{
   CHECK(WriteIODeviceStatus(FpgaIoDeviceObject_MGR, IODEV_FPGA_PPS_TEST,
       &cmd, sizeof(TimeLoadCmd)), __FILE__, __FUNCTION__, __LINE__);
}
CTimeLoad* CTimeLoad::mInstance = NULL;

////////////////////////////////////////////////////////////////////////////////
//! Function: setTimeOfDayVar
//!
//! Description:  This method will set the date time received by the Time at The
//!                Tone message.
//!
//! Parameters:
//!  Date_Time_Type - timeOfDay - time of day structure
//!
//! Notes:
//!  None
//!
////////////////////////////////////////////////////////////////////////////////
void CTimeLoad::setTimeOfDayVar(Date_Time_Type timeOfDay)
{
   mTimeOfDay = timeOfDay;
}

////////////////////////////////////////////////////////////////////////////////
//! Function: setTimeOfDayVar
//!
//! Description:  This method will set the date time received
//!
//! Parameters:
//!  LoadType timeLoadStyle - type of load auto = STOD
//!                                        manual = TATT Ethernet
//!
//! Notes:
//!  None
//!
////////////////////////////////////////////////////////////////////////////////
void CTimeLoad::setLoadType(Load_Type timeLoadStyle)
{
   mStyleOfTimeLoad = timeLoadStyle;
}

////////////////////////////////////////////////////////////////////////////////
//! Function: COVTimeAtTheToneMsg::SetSystemClock
//!
//! Description: This method handles the loading the of the HighResTimer Clock
//!  driven by the processor.  The .int file creates a clock that will
//!  allow the kernel to set the system time.
//!
//!  This uses the number of seconds in the day based on VLF time loading.  It
//!   should be noted that the system clock will continue to tick by.  It is NOT
//!   loaded with time since 1970 but a start point of seconds in the day.
//!   Further noted that the alarm clock used by keyeffectivity uses absolute
//!   time and will not move once it is set without clearing and resetting the
//!   alarm after the new system time has been set.
//!
//!   It might be needed that the seconds since time load be added to the vlfTime
//!   when performing a time update based on STOD accuracy.
//!
//! Parameters: none
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void CTimeLoad::SetSystemClock()
{
   Time getPriTime = {0,0};         // get time
   VlfTime vlfTime = GetVlfTime();  // VLF time
   GetClockTime(SystemClock, &getPriTime);

   if ( NO_LOAD != mStyleOfTimeLoad )
   {
      mStyleOfTimeLoad = NO_LOAD;

      //update current time load variable
      CVlf::Instance()->mRcvrStatus.TimeLoaded = true;

      // update rcvr and channel state machine
      CVlf::Instance()->setTimeLoadedStatus();

      // send DSP2 the updated status of the time load
      CVlf::Instance()->UpdateRcvrStatus();

      // Restart each Channel as Necessary
      for(int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
      {
         RestartChannelAfterTimeLoad(chanNum);
      }

      // Adjust system clock to TATT 1PPS signal
      // Delta Adjustment is accurate to the seconds
      Time newTime = {vlfTime.sec - (getPriTime.Seconds%NUM_SEC_PER_DAY),
                      ( vlfTime.frames * ONE_FRAME_MSEC ) -
                      getPriTime.Fraction}; //Delta Time

      // Check to see if VLF time is different than system time
      // then change system clock
      if ((newTime.Seconds > MAX_TIME_DIFF) ||
          (newTime.Seconds < MIN_TIME_DIFF))
      {
         CHECK(AdjustClockTime(SystemClock, &newTime),
          __FILE__, __FUNCTION__, __LINE__);

         // set key effectivity/ key rollover timer
         CKeyEffectData::Instance()->createKeyEffectAlarmTimer();
      }//else do nothing, system clock does not need to be adjusted
   }
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification:  UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
