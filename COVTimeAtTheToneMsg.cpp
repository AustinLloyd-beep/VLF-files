
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVTimeAtTheToneMsg.cpp
//
// Description:
//    This file contains the class definition for the COVTimeAtTheToneMsg
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVTimeAtTheToneMsg.h"
#include "CMsgHandler.h"
#include "TMemStrUtility.h"
#include "CKeyEffectData.h"
#include "rc_bsp_defs.h"
#include "Utility.h"
#include "CVlf.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVTimeAtTheToneMsg::Constructor
//!
//! Description:
//!   This is the class constructor, it initializes variables
//!
//! Parameters:
//!   None
//!
//! Return:
//!    None
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
COVTimeAtTheToneMsg::COVTimeAtTheToneMsg()
{
   mTimerFlagSet = false;

   // Create timer finish time load after IODevice is done
   Time LoadTimeTimeOut = {LOADTIME_TIMEOUT, 0};
   CHECK ( CreateAlarmTimer((Address)LoadTimeTimeOutHandler,
          (Address)&rcv_msg, &LoadTimeTimeOut, true, false, &LoadTimeTimer),
           __FILE__, __FUNCTION__, __LINE__);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVTimeAtTheToneMsg::ValidateMsgParam
//!
//! Description:
//!   This method validates the message parameters.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return:
//!    Msg_Error_Codes_Type
//!
//! Notes: Input parameters checked by calling function.
//!
////////////////////////////////////////////////////////////////////////////////
Msg_Error_Codes_Type COVTimeAtTheToneMsg::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;   // error

   Time_At_The_Tone_Msg_Type* tatt_msg =
      (Time_At_The_Tone_Msg_Type *)&msg.GetMsgData()->theData;  // msg

   // Check message data parameters, the header is checked when the
   // message is received

   // Check the Time source
   if ( (tatt_msg->timeSrc != BBC) &&
        (tatt_msg->timeSrc != GPS)  &&
        (tatt_msg->timeSrc != MILSTAR)  &&
        (tatt_msg->timeSrc != OPER)  &&
        (tatt_msg->timeSrc != IRIG_B)  &&
        (tatt_msg->timeSrc != NONE))
   {
      error = PARAM_OUT_OF_RANGE;
   }
   else if ( (tatt_msg->utcTime.Year > MAX_YEAR_VALUE) ||
        ((tatt_msg->utcTime.Month < MIN_MONTH_VALUE)  ||
         (tatt_msg->utcTime.Month > MAX_MONTH_VALUE)) ||
        ((tatt_msg->utcTime.Day < MIN_DAY_VALUE) ||
         (tatt_msg->utcTime.Day > MAX_CAL_DAY_VALUE)) ||
        (tatt_msg->utcTime.Hour > MAX_HOURS) ||
        (tatt_msg->utcTime.Minute > MAX_MINUTES) ||
        (tatt_msg->utcTime.Second > MAX_SECONDS) ||
        (tatt_msg->utcTime.reserved != UNUSED_VARIABLE_VAL))
   {
      error = PARAM_OUT_OF_RANGE;
   }
   // Check Offset
   else if (tatt_msg->offset > MAX_TATT_OFFSET)
   {
      error = PARAM_OUT_OF_RANGE;
   }
   // Check Pulse Width
   else if ((tatt_msg->loadType != NO_LOAD) &&
            (tatt_msg->loadType != AUTO_LOAD) &&
            (tatt_msg->loadType != MANUAL_LOAD))
   {
      error = PARAM_OUT_OF_RANGE;
   }
   // Check Estimate Accuracy field
   else if ((tatt_msg->timeAccy != NANO_SEC_1) &&
            (tatt_msg->timeAccy != NANO_SEC_10) &&
            (tatt_msg->timeAccy != NANO_SEC_100) &&
            (tatt_msg->timeAccy != MICRO_SEC_1) &&
            (tatt_msg->timeAccy != MICRO_SEC_10) &&
            (tatt_msg->timeAccy != MICRO_SEC_100) &&
            (tatt_msg->timeAccy != MILLI_SEC_1) &&
            (tatt_msg->timeAccy != MILLI_SEC_10) &&
            (tatt_msg->timeAccy != MILLI_SEC_100) &&
            (tatt_msg->timeAccy != SEC_1) &&
            (tatt_msg->timeAccy != SEC_10) &&
            (tatt_msg->timeAccy != SEC_100) &&
            (tatt_msg->timeAccy != UNK))
   {
      error = PARAM_OUT_OF_RANGE;
   }
   else if (mTimerFlagSet)
   {
      error = OPERATION_IN_PROGRESS;
   }
   else
   {
      // Send error if modes SM9 or HIDAR on channels (1-5) are in sync.
      // Time Load is not allowed if any SMode of the channels are in sync
      for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++) // loop thru channels
      {
         if ((CVlf::Instance()->chan[chanNum]->mMode9->
               mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
             (CVlf::Instance()->chan[chanNum]->mModeHidar->
               mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
             (CVlf::Instance()->chan[chanNum]->mMode23->
               mChanModeStatus.modeScanState == MODE_IN_SYNC) ||
             (CVlf::Instance()->chan[chanNum]->mModeSMA->
               mChanModeStatus.modeScanState == MODE_IN_SYNC) )
         {
            error = CHANNEL_IN_SYNC;
            break;
         }
         else
         {
            error = VLF_NO_ERROR;
         }
      }//end for loop
   }

   return (error);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVTimeAtTheToneMsg::HandleMsg
//!
//! Description: This method handles the CTimeAtTheToneMsg message.
//!              This message contains the GPS time of day from the
//!              STM use for loading time and calculating time
//!              accuracy.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVTimeAtTheToneMsg::HandleMsg( CMessage *msg )
{
   if ( check4Null( msg, __FILE__, __LINE__ ) )
   {
      return;// All errors handled within check4Null
   }//else nothing

   Msg_Error_Codes_Type msgError = ValidateMsgParam( *msg );           // message error
   Time_At_The_Tone_Msg_Type *msgData =
      (Time_At_The_Tone_Msg_Type*)msg->GetMsgData()->theData;              // msg pointer
   Response_Status_Type msgStatus = NAK;                    // message status
   Value timeLoadTATTData[NUM_TATT_STATUS_ELEMENTS] = {0};  // time load data
   unsigned int totalSec = 0;                               // total sec
   float offSetCnt1 = 0.0;                                  // floating point offset count
   unsigned int offSetCnt = 0;                              // offset count
   Error err = Failure;                                     // error
   Date_Type date = {0};                                    // date

   // Parameters out of range or time load is not in progress
   if ( ( msgError != VLF_NO_ERROR ) &&
        ( msgError != OPERATION_IN_PROGRESS ) )
   {
      // Change status based on error code
      if ( msgError == CHANNEL_IN_SYNC )
      {
         msgStatus = ACK;
      } // else nothing - other error already set

      // send Ack/Nak Message to VCI
      CMsgHandler::Instance()->SendAckNak( msg->GetSrc(),
                                           msg->GetMsgId(),
                                           msg->GetActionId(),
                                           msgStatus,
                                           msgError );
   }
   // First receipt, or time load is in progress
   else
   {
      msgStatus = ACK;
      CTimeLoad::Instance()->LoadTime( CmdLoadTime, (Load_Type)msgData->loadType );

      // Save a copy of the message for the alarm timer
      rcv_msg = * msg;

      // Set alarm timer to return and check time load status
      if ( !mTimerFlagSet )
      {
         CHECK( err = SetAlarmTimer( LoadTimeTimer ),
                __FILE__, __FUNCTION__, __LINE__ );

         if ( err != Success )
         {
            msgError = TIME_NOT_LOADED;
         }
         else
         {
            mTimerFlagSet = true;
         }
      } // else - no action required

      // Verify that the timer flag was set
      if ( !mTimerFlagSet )
      {
         // Send Ack/Nak Message to VCI
         CMsgHandler::Instance()->SendAckNak( msg->GetSrc(),
                                              msg->GetMsgId(),
                                              msg->GetActionId(),
                                              msgStatus,
                                              msgError );
      }
      else
      {
         // set up DoY
         date.Day = msgData->utcTime.Day;
         date.Month = msgData->utcTime.Month;
         date.Year = msgData->utcTime.Year;

         // Convert offset from STM format (0 -10000000) in 100 nanoseconds
         // to 0..3200 FPGA offset format
         offSetCnt1 = msgData->offset;
         offSetCnt = (unsigned int)( ( offSetCnt1 / MAX_TATT_OFFSET ) * MAX_FPGA_OFFSET );

         // Convert Time (hh:mm:ss) to total seconds
         totalSec = ( ( ( msgData->utcTime.Hour * (unsigned int)TOTAL_SECONDS ) +
                        msgData->utcTime.Minute ) * (unsigned int)TOTAL_SECONDS ) +
                      msgData->utcTime.Second;

         // [0]- Total GPS seconds, [1]- 1pps offset, [2] - GPS DoY[3]- PulseType
         timeLoadTATTData[0] = totalSec;  // GPS seconds
         timeLoadTATTData[1] = offSetCnt;
         timeLoadTATTData[2] = CKeyEffectData::Instance()->getDayOfYear( date );
         timeLoadTATTData[3] = (Load_Type)msgData->loadType;

         // Write the data to the FPGA IO device object
         CHECK( WriteIODeviceStatus( FpgaIoDeviceObject_MGR,
                                     IODEV_FPGA_TATT_TIMELOAD,
                                     timeLoadTATTData,
                                     sizeof( timeLoadTATTData ) ),
                __FILE__, __FUNCTION__, __LINE__ );

         // Save time of day data
         CTimeLoad::Instance()->setTimeOfDayVar( msgData->utcTime );

         if ( CTimeLoad::Instance()->mState == TimeLoaded )
         {
            // Update current time load variable
            CVlf::Instance()->mRcvrStatus.TimeLoaded = false;

            // Update rcvr and channel state machine
            CVlf::Instance()->setTimeLoadedStatus();

            // Send DSP2 the updated status of the time load
            CVlf::Instance()->UpdateRcvrStatus();
         }// else nothing- time not loaded do not change status
      }
   }
}

AlarmTimer COVTimeAtTheToneMsg::LoadTimeTimer;     // alarm timer
bool COVTimeAtTheToneMsg::mTimerFlagSet = false;   // time set flag
////////////////////////////////////////////////////////////////////////////////
//! Function: COVTimeAtTheToneMsg::LoadTimeTimeOutHandler
//!
//! Description:
//!   This method handles the load time timeout. Purpose is to wait for success
//!    since it takes 2-offset sec to load time
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes:
//!        This handler will set the alarm timer in the kernal that will
//!        control the key management automatic rollover when a timeloaded status
//!        is returned.  This implementation allows for more control over the
//!        alarm instead of the user defined alarm timer.
//!
////////////////////////////////////////////////////////////////////////////////
void COVTimeAtTheToneMsg::LoadTimeTimeOutHandler(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type error = UNKNOWN_ERROR;   // error code
   Response_Status_Type status = ACK;     // valid msg params
   static int counter = LOADTIME_COUNTER; // this counter will allow us to check
                                          // the status of the timeLoad every
                                          // 5 seconds

   CTimeLoad::Instance()->GetTimeStatus();
   if (CTimeLoad::Instance()->mState != TimeLoaded)
   {
      if (counter == 0)
      {
         //free alarm timer resources
         CancelAlarmTimer(LoadTimeTimer);

         error = TIME_NOT_LOADED;
         mTimerFlagSet = false;  //reset timer flag
         counter = LOADTIME_COUNTER;  // reset counter

         //update current time load variable
         CVlf::Instance()->mRcvrStatus.TimeLoaded = false;

         // update rcvr and channel state machine
         CVlf::Instance()->setTimeLoadedStatus();

         // send DSP2 the updated status of the time load
         CVlf::Instance()->UpdateRcvrStatus();

         // send Ack/Nak Message to VCI
         CMsgHandler::Instance()->SendAckNak(msg->GetSrc(), msg->GetMsgId(),
                            msg->GetActionId(), status, error);

         //reset counter
         counter = LOADTIME_COUNTER;
      }
      else
      {
         counter--; //decrement counter
      }
   }
   // Send TimeLoaded Event and Restart the Channels that are active
   else
   {
      error = VLF_NO_ERROR;
      status = ACK;
      mTimerFlagSet = false; //reset timer flag
      counter = LOADTIME_COUNTER;  // reset counter

      //free alarm timer resources
      CancelAlarmTimer(LoadTimeTimer);

      //update current time load variable
      CVlf::Instance()->mRcvrStatus.TimeLoaded = true;

      // update rcvr and channel state machine
      CVlf::Instance()->setTimeLoadedStatus();

      // send DSP2 the updated status of the time load
      CVlf::Instance()->UpdateRcvrStatus();

      // Restart each Channel as Necessary
      for(int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
      {
         CVlf::Instance()->RestartChannelsAfterEventChg(chanNum);
      }

      // Clear out Effectivity Table of Outdated Entries.
      CKeyEffectData::Instance()->triggerMainKeyRolloverTask();

      // send Ack/Nak Message to VCI
      CMsgHandler::Instance()->SendAckNak(msg->GetSrc(), msg->GetMsgId(),
                            msg->GetActionId(), status, error);
   }
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
