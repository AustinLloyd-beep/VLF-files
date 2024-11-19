///////////////////////////////////////////////////////////////////////////////
//
// Class: Timeload
//
// File Name: TimeLoad.h
//
// Description: This file is an include file that contains the class prototypes
//              of the TimeLoad Class and inline TimeLoad methods. This
//              class is used by the user to load time into the VLF receiver.
//
// Notes: The GEMS STM modules broadcast time at the tone (TATT) message
//        and a 1PPS signal to the OES every second.  The TATT message is an
//        incoming UDP message that is converted to a TCP message and sent to
//        the VLF receiver.
//
//        The TATT message includes the following information:
//            1. UTC time and offset to the next 1PPS mark
//            2. Time source (BBC, GPS, IRIG-B, MILSTAR/AEHF, Operator)
//            3. Estimate time accuracy
//            4. Indicator of a narrow or wide 1PPS mark
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CTIMELOAD_H
#define CTIMELOAD_H

#include "FpgaIoDevice.h"
#include "chan_struct.h"

class CTimeLoad
{
public:
   static CTimeLoad* Instance();

   TimeLoadState mState;       // Time load states
   TimeLoadError mErr;         // Time load errors
   TimeLoadError mPpsErr;      // Time pps errors
   TimeLoadError mStodErr;     // Time stod errors

   void GetTimeStatus();       // get FPGA IO device time status
   VlfTime GetVlfTime();       // get the vlf internal clock
   void GetAbsTime(Absolute_Time_Type* absTime);  // get the vlf internal clock
   void RunPpsPbit(TimeLoadCmd cmd); // send Pbit command to FPGA IODevice

   // time handling
   void SetSystemClock();
   void setTimeOfDayVar(Date_Time_Type timeOfDay);
   void LoadTime(TimeLoadCmd cmd, Load_Type timeLoadStyle);

   ////////////////
   // constants
   ////////////////
   static const int NUM_SECONDS = 60;                                 // 60 seconds
   static const int NUM_MINUTES = 60;                                 // 60 minutes
   static const int NUM_SEC_PER_HOUR = (NUM_SECONDS * NUM_MINUTES);   // seconds per hour

private:
   static CTimeLoad* mInstance;

   CTimeLoad();   // constructors
   ~CTimeLoad (); // destructor
   CTimeLoad(const CTimeLoad&);
   CTimeLoad& operator=(const CTimeLoad&);

   void setLoadType(Load_Type timeLoadStyle);
   void SendTimeLoadCmd(TimeLoadCmd cmd);// send time load command to FPGA IO object
   void RestartChannelAfterTimeLoad(int& chanNum);

   // time loading variables
   Date_Time_Type mTimeOfDay;    // time of day
   Load_Type mStyleOfTimeLoad;   // load type
};
#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification:  UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
