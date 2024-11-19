////////////////////////////////////////////////////////////////////////////////
// Class: CChannelState
//
// File Name: CChannelState.cc
//
// Description: This file contains the class methods for the CVLFState class.
//              this class contains the state pattern of the VLF receiver
//
// Notes: None
//
////////////////////////////////////////////////////////////////////////////////

#include "CVlf.h"
#include "CChannelState.h"
#include "CTimeLoad.h"
#include "CChannel.h"


////////////////////////////////////////////////////////////////////////////////
// Static Variable
////////////////////////////////////////////////////////////////////////////////
// The Following are classes and initialized in their respective constructors
CChOperationalState IChannelState::theChOperationalState;   // channel operational state
CChDegradedState IChannelState::theChDegradedState;         // channel degraded state
CChOfflineState IChannelState::theChOfflineState;           // channel offline state

////////////////////////////////////////////////////////////////////////////////
//! Function: StopChannel
//!
//! Description:
//!   This method is used to transition the channel state to Offline State.
//!
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: NONE
//!
//! Notes:
//!   This base class handler can be overridden, if needed.
//!
////////////////////////////////////////////////////////////////////////////////
void IChannelState::StopChannel(CChannel* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      // check to ensure all modes have stopped or were never started
      if((instance->mMode15->mChanModeStatus.modeScanState == MODE_SEARCH_HALTED) &&
         (instance->mMode9->mChanModeStatus.modeScanState == MODE_SEARCH_HALTED) &&
         (instance->mModeHidar->mChanModeStatus.modeScanState == MODE_SEARCH_HALTED) &&
         (instance->mMode23->mChanModeStatus.modeScanState == MODE_SEARCH_HALTED) &&
         (instance->mModeSMA->mChanModeStatus.modeScanState == MODE_SEARCH_HALTED) )
      {
         instance->setState(&theChOfflineState);
      }//else nothing- all modes halted
   }//else nothing- error handled in if statement
}

////////////////////////////////////////////////////////////////////////////////
// Class: CChOperationalState
//
//
// Description: This class contains the class methods for the COperationalState
//              class.  This class contains a state transition of the
//              VLF channels
//
// Notes: None
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//! Function: CChOperationalState
//!
//! Description:
//!   This is the class default constructor method
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
CChOperationalState::CChOperationalState()
{
   //set Channel State Variable
   chstate = CH_OPERATIONAL;
}
////////////////////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//!   This destructor method is used to cleanup the COperationalState object
//!   once it is deleted.
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
CChOperationalState::~CChOperationalState()
{
}
////////////////////////////////////////////////////////////////////////////////
//! Function: getChannelState
//!
//! Description:
//!   This method is used to get the state variable of the class. This will
//!    allow for the state variable to be sent in messages to the OES.
//!
//! Parameters: None
//!
//! Return:  VLF_Channel_State_Type
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
VLF_Channel_State_Type CChOperationalState::getChannelState()
{
   return chstate;
}
////////////////////////////////////////////////////////////////////////////////
//! Function: LoadTime
//!
//! Description:
//!   This method is used to transition the channel state to Degraded State,
//!    based on conditional criteria. If Timeload Message is sent,
//!    and current time check fails and channels are running, transition to
//!    Degraded State.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChOperationalState::LoadTime(CChannel* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      // Check commPlan for SM_Modes
      if ((instance->mCommPlan.mode9 == (unsigned)true) ||
           (instance->mCommPlan.modeHIDAR == (unsigned)true) ||
           (instance->mCommPlan.mode23 == (unsigned)true) ||
           (instance->mCommPlan.modeSMA == (unsigned)true))
      {
         // Check Time
         if (CTimeLoad::Instance()->mState != TimeLoaded)
         {
           instance->setState(&theChDegradedState);
         }//else nothing- time not loaded
      }//else nothing- no SModes in comm plan
   }//else nothing- error handled in if statement
}

////////////////////////////////////////////////////////////////////////////////
//! Function: ChangeCpChanOpStatus
//!
//! Description:
//!   This method is used to transition the VLF state to Degraded State,
//!    based on conditional criteria.
//!    The flag value: mCpChanOpStatValid, can be set if the following
//!    Crypto conditions occur
//!    1. TEK valid/invalid
//!    2. CP Chan Configure Pass/Fail
//!    3. CP Chan Runup Pass/Fail
//!    4. CP Chan Zeroize Pass/Fail
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChOperationalState::ChangeCpChanOpStatus(CChannel* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      // Check commPlan for SM_Modes
      if ((instance->mCommPlan.mode9 == (unsigned)true) ||
          (instance->mCommPlan.modeHIDAR == (unsigned)true) ||
          (instance->mCommPlan.mode23 == (unsigned)true)||
          (instance->mCommPlan.modeSMA == (unsigned)true))
      {
         // Check TEK
         if (instance->mCpChanOpStatValid == false)
         {
           instance->setState(&theChDegradedState);
         }//else nothing- tek not loaded
      }//else nothing- SModes not in comm plan
   }//else nothing- error handled in if statement
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoStatus
//!
//! Description:
//!   This method is used to transition the VLF state to Degraded State,
//!    based on conditional criteria.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChOperationalState::CryptoStatus(CChannel* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      // Check commPlan for SM_Modes
      if ((instance->mCommPlan.mode9 == (unsigned)true) ||
          (instance->mCommPlan.modeHIDAR == (unsigned)true) ||
          (instance->mCommPlan.mode23 == (unsigned)true) ||
          (instance->mCommPlan.modeSMA == (unsigned)true))
      {
         // Check Crypto
         if ((CVlf::Instance()->mRcvrStatus.CMState.ECUState == (unsigned)ECU_ALARM) ||
            (CVlf::Instance()->mRcvrStatus.CMState.ECUSubstate != (unsigned)NO_SUBSTATE)||
            (CVlf::Instance()->mRcvrStatus.chanStatus
               [(instance->mCommPlan.channelID - 1)].cryptoChanState == (unsigned)CH_ALARM))
         {
           instance->setState(&theChDegradedState);
         }//else nothing- crypto states valid
      }//else nothing- SModes not in comm plan
   }//else nothing- error handled in if statement
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoChannelUpdate
//!
//! Description:
//!   This method is used to transition the VLF state to Degraded State,
//!    based on conditional criteria.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChOperationalState::CryptoChannelUpdate(CChannel* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      // Check commPlan for SM_Modes
      if ((instance->mCommPlan.mode9 == (unsigned)true) ||
          (instance->mCommPlan.modeHIDAR == (unsigned)true) ||
          (instance->mCommPlan.mode23 == (unsigned)true) ||
          (instance->mCommPlan.modeSMA == (unsigned)true))
      {
         if (CVlf::Instance()->mRcvrStatus.chanStatus
            [(instance->mCommPlan.channelID - 1)].cryptoChanState == (unsigned)CH_ALARM)
         {
            instance->setState(&theChDegradedState);
         }//else nothing- channel not in alarm
      }//else nothing- SModes not in comm plan
   }//else nothing- error handled in if statement
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoBIT
//!
//! Description:
//!   This method is used to transition the VLF state to Degraded State,
//!    based on conditional criteria.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChOperationalState::CryptoBIT(CChannel* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      // Check commPlan for SM_Modes
      if ((instance->mCommPlan.mode9 == (unsigned)true) ||
          (instance->mCommPlan.modeHIDAR == (unsigned)true) ||
          (instance->mCommPlan.mode23 == (unsigned)true) ||
          (instance->mCommPlan.modeSMA == (unsigned)true))
      {
         // Check BIT status
         if (!CVlf::Instance()->mCPLinkUp)
         {
            instance->setState(&theChDegradedState);
         }
         //else do nothing, still connected to the Crypto
      }
      //else
      //do nothing, the channel is not setup for special mode.
   }//else nothing- error handled in if statement
}



////////////////////////////////////////////////////////////////////////////////
// Class: CChDegradedState
//
//
// Description: This class contains the class methods for the CDegradedState
//              class.  This class contains a state transition of the
//              VLF receiver
//
// Notes: None
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//! Function: CChDegradedState
//!
//! Description:
//!   This is the class default constructor method
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
CChDegradedState::CChDegradedState()
{
   //set VLF channel Variable
   chstate = CH_DEGRADED;
}
////////////////////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//!   This destructor method is used to cleanup the CDegradedState object
//!   once it is deleted.
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
CChDegradedState::~CChDegradedState()
{
}
////////////////////////////////////////////////////////////////////////////////
//! Function: getChannelState
//!
//! Description:
//!   This method is used to get the state variable of the class. This will
//!    allow for the state variable to be sent in messages to the OES.
//!
//! Parameters: None
//!
//! Return:  VLF_Channel_State_Type - state variable for class
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
VLF_Channel_State_Type CChDegradedState::getChannelState()
{
   return chstate;
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CommonUpdate
//!
//! Description:
//!   This method is used to consolidate the common function processing of
//!    the CChDegradedState class.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   This helper method was created to eliminate the detection of duplicate
//!   algorithms in the code as reported by the customer's analysis tool
//!
////////////////////////////////////////////////////////////////////////////////
void CChDegradedState::CommonUpdate(CChannel* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      // Check CommPlan, Time, TEK, and Crypto
      if(CheckStatusEvents(instance))
      {
         instance->setState(&theChOperationalState);
      }//else nothing- all values do not pass
   }//else nothing- error handled in if statement
}

////////////////////////////////////////////////////////////////////////////////
//! Function: LoadTime
//!
//! Description:
//!   This method is used to transition the VLF state to Operational State,
//!    based on conditional criteria. If Timeload Message is sent,
//!    and current time check passes, TEK loaded, and channels are running,
//!    transition to Operational State.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChDegradedState::LoadTime(CChannel* instance)
{
   // Invoke the helper method to eliminate duplicate algorithm detected
   // by customer's analysis tool.
   CommonUpdate(instance);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: ChangeCpChanOpStatus
//!
//! Description:
//!   This method is used to transition the VLF state to Operational State,
//!    based on conditional criteria.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChDegradedState::ChangeCpChanOpStatus(CChannel* instance)
{
   // Invoke the helper method to eliminate duplicate algorithm detected
   // by customer's analysis tool.
   CommonUpdate(instance);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoStatus
//!
//! Description:
//!   This method is used to transition the channel state to Operational State
//!   based on conditional criteria.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChDegradedState::CryptoStatus(CChannel* instance)
{
   // Invoke the helper method to eliminate duplicate algorithm detected
   // by customer's analysis tool.
   CommonUpdate(instance);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoChannelUpdate
//!
//! Description:
//!   This method is used to transition the VLF state to Degraded State,
//!    based on conditional criteria.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChDegradedState::CryptoChannelUpdate(CChannel* instance)
{
   // Invoke the helper method to eliminate duplicate algorithm detected
   // by customer's analysis tool.
   CommonUpdate(instance);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoBIT
//!
//! Description:
//!   This method is used to transition the VLF state to Operational State,
//!    based on conditional criteria.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChDegradedState::CryptoBIT(CChannel* instance)
{
   // Check BIT status
   if ((CVlf::Instance()->mCPLinkUp) &&
       ( !check4Null(instance, __FILE__, __LINE__)))
   {
      // Check CommPlan, Time, TEK, and Crypto
      if(CheckStatusEvents(instance))
      {
         instance->setState(&theChOperationalState);
      }//else nothing- all values do not pass
   }//else nothing- link not up
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CheckStatusEvents
//!
//! Description:
//!   This method is used to check the status TEK, Time, and Crypto
//!     for the events.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: bool valid - true/false
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
bool CChDegradedState::CheckStatusEvents(CChannel* instance)
{
   bool valid = false; // Flag for Degraded

   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      // Check commPlan for SM_Modes
      if ((instance->mCommPlan.mode9 == (unsigned)true) ||
          (instance->mCommPlan.modeHIDAR == (unsigned)true) ||
          (instance->mCommPlan.mode23 == (unsigned)true) ||
          (instance->mCommPlan.modeSMA == (unsigned)true))
      {
         // Check Crypto Status, Time and TEK
         if ((CTimeLoad::Instance()->mState == TimeLoaded) &&
            (CVlf::Instance()->mRcvrStatus.CMState.ECUState != (unsigned)ECU_ALARM) &&
            (CVlf::Instance()->mRcvrStatus.CMState.ECUSubstate == (unsigned)NO_SUBSTATE)&&
            (CVlf::Instance()->mRcvrStatus.chanStatus
               [(instance->mCommPlan.channelID - 1)].cryptoChanState != (unsigned)CH_ALARM)
             && (instance->mCpChanOpStatValid == true))
         {
           valid = true;
         }//else nothing- values not correct
      }
      // Mode15 only
      else
      {
         valid = true;
      }
   }//else nothing- error handled in if statement

   return valid;
}



////////////////////////////////////////////////////////////////////////////////
// Class: CChOfflineState
//
//
// Description: This class contains the class methods for the COfflineState
//              class.  This class contains a state transition of the
//              VLF channels
//
// Notes: None
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//! Function: CChOfflineState
//!
//! Description:
//!   This is the class default constructor method
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
CChOfflineState::CChOfflineState()
{
   //set VLF State Variable
   chstate = CH_OFFLINE;
}
////////////////////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//!   This destructor method is used to cleanup the COfflineState object
//!   once it is deleted.
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
CChOfflineState::~CChOfflineState()
{
}
////////////////////////////////////////////////////////////////////////////////
//! Function: getChannelState
//!
//! Description:
//!   This method is used to get the state variable of the class. This will
//!    allow for the state variable to be sent in messages to the OES.
//!
//! Parameters: None
//!
//! Return:  VLF_Channel_State_Type
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
VLF_Channel_State_Type CChOfflineState::getChannelState()
{
   return chstate;
}
////////////////////////////////////////////////////////////////////////////////
//! Function: StartChannel
//!
//! Description:
//!   This method is used to transition the channel state to Operational State,
//!    or Degraded State based on conditional criteria.
//!    Check for valid Time, TEK, CommPlan, SModes, and CryptoStatus.
//!    If all pass transition state to Operational else Degraded.
//!    Channel Start Event can only happen when channel is offline.
//!
//! Parameters:
//!     CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CChOfflineState::StartChannel(CChannel* instance)
{
   if ( check4Null(instance, __FILE__, __LINE__) )
   {
      return; //error handle in check4Null function
   }//else nothing- no error continue

   // check for valid commPlan
   if (instance->mCommPlanValid == true )
   {
      // Check commPlan for SM_Modes
      if ((instance->mCommPlan.mode9 == (unsigned)true) ||
          (instance->mCommPlan.modeHIDAR == (unsigned)true) ||
          (instance->mCommPlan.mode23 == (unsigned)true) ||
          (instance->mCommPlan.modeSMA == (unsigned)true))
      {
         // Check Crypto Status, Time and TEK
         if ((CTimeLoad::Instance()->mState == TimeLoaded) &&
            (CVlf::Instance()->mRcvrStatus.CMState.ECUState != (unsigned)ECU_ALARM) &&
            (CVlf::Instance()->mRcvrStatus.CMState.ECUSubstate == (unsigned)NO_SUBSTATE)&&
            (CVlf::Instance()->mRcvrStatus.chanStatus
               [(instance->mCommPlan.channelID - 1)].cryptoChanState != (unsigned)CH_ALARM)&&
            (instance->mCpChanOpStatValid == true))
         {
            instance->setState(&theChOperationalState);
         }
         //
         // Else we are invalid and change channel state to Degraded
         else
         {
            instance->setState(&theChDegradedState);
         }
      }
      // else channel is only configured for mode15
      else
      {
         instance->setState(&theChOperationalState);
      }
   }//else nothing- no comm plan loaded
}
////////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
////////////////////////////////////////////////////////////////////////////////
