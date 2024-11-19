///////////////////////////////////////////////////////////////////////////////
//
// File Name: CMode.h
//
// Description:
//    This file contain the class definition for the base Mode class
//    and the derived mode classes (CMode15, CMode9, and CModeHIDAR)
//
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CMODE_H
#define CMODE_H

#include "chan_struct.h"
#include "msg_defs.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: CMode
//
// Description:
//    This is base class used to derive specific mode
//    class (M15, M9, and HIDAR)
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
class CMode
{
public:
   Mode_Command_Type mCommand;
   Mode_Command_Type mPrevCommand;

   //ModeStatusDataType received from the CH address Space.
   Mode_Signal_Status_Type mChanModeStatus;
   Mode_Signal_Status_Type mPrevChanModeStatus;

   long mCnt20ms;
   static const unsigned char NUM_20MSEC_FOR_INIT = 2;
   static const unsigned char NUM_20MSEC_FOR_DATA_VALID = 8;

   // constructor
   CMode();
   // destructor
   ~CMode(){};

   void HandleMgrCmd(ChannelCmdStruct *mgrCmd);
   
   Channel_Mode_Processing_Status_Type GetStatus();
   Mode_Command_Type GetNextCmd();

   // CMode15 will need to override HandleStatus().
   // The other derived classes can use this function from the base class.
   virtual void HandleStatus(ChanStatusQueueStruct *chstatus);

protected:
   unsigned int mChanMode;
   
   //Status to be reported to OES by the channel
   Channel_Mode_Processing_Status_Type mModeStatus;

   // All derived classes must override GetModeSignalStatusType()
   virtual Mode_Signal_Status_Type GetModeSignalStatusType(ChanStatusQueueStruct *chstatus) = 0;
};
///////////////////////////////////////////////////////////////////////////////
//
// Class: CMode15
//
// Description:
//    This this class is used to handles the command and status for Mode 15
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class CMode15 : public CMode
{
public:
   // constructor
   CMode15();
   // destructor
   ~CMode15(){};

   // We'll need to override the default status handling for Mode 15.
   void HandleStatus(ChanStatusQueueStruct *chstatus);

protected:
   Mode_Signal_Status_Type GetModeSignalStatusType(ChanStatusQueueStruct *chstatus);
};
///////////////////////////////////////////////////////////////////////////////
//
// Class: CMode9
//
// Description:
//    This this class is used to handles the command and status for Mode 9
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class CMode9 : public CMode
{
public:
   // constructor
   CMode9();
   // destructor
   ~CMode9(){};

protected:
   Mode_Signal_Status_Type GetModeSignalStatusType(ChanStatusQueueStruct *chstatus);
};
///////////////////////////////////////////////////////////////////////////////
//
// Class: CModeHIDAR
//
// Description:
//    This this class is used to handles the command and status for mode HIDAR
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class CModeHidar : public CMode
{
public:
   // constructor
   CModeHidar();
   // destructor
   ~CModeHidar(){};

protected:
   Mode_Signal_Status_Type GetModeSignalStatusType(ChanStatusQueueStruct *chstatus);
};
///////////////////////////////////////////////////////////////////////////////
//
// Class: CMode23
//
// Description:
//    This this class is used to handles the command and status for Mode 23
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class CMode23 : public CMode
{
public:
   // constructor
   CMode23();
   // destructor
   ~CMode23(){};

protected:
   Mode_Signal_Status_Type GetModeSignalStatusType(ChanStatusQueueStruct *chstatus);
};
///////////////////////////////////////////////////////////////////////////////
//
// Class: CModeSMA
//
// Description:
//    This this class is used to handles the command and status for SMA (UMM)
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class CModeSMA : public CMode
{
public:
   // constructor
   CModeSMA();
   // destructor
   ~CModeSMA(){};

protected:
   Mode_Signal_Status_Type GetModeSignalStatusType(ChanStatusQueueStruct *chstatus);
};
#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
