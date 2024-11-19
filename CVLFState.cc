
///////////////////////////////////////////////////////////////////////////////
// Class: CVLFState
//
// File Name: CVLFState.cc
//
// Description: This file contains the class methods for the CVLFState class.
//              this class contains the state pattern of the VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include "KgrVpApp_integrate.h"
#include "CVlf.h"
#include "CVLFState.h"

///////////////////////////////////////////////////////////////////////////////
// Static Variable
///////////////////////////////////////////////////////////////////////////////
CInitState IVLFState::theInitState;
CStandbyState IVLFState::theStandbyState;
CDegradedState IVLFState::theDegradedState;
COperationalState IVLFState::theOperationalState;
COfflineState IVLFState::theOfflineState;

///////////////////////////////////////////////////////////////////////////////
// Class: IVLFState
//
//
// Description: This class contains the base class methods for the other
//              classes in this file.
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//! Function: ContBITUpdate
//!
//! Description:
//!   This method is used to transition the VLF state to Offline State
//!    based on conditional criteria.
//!
//! Parameters:
//!   CVlf* instance- pointer to CVlf object
//!
//! Return:
//!
//! Notes:
//!   This common base class method may be overridden for derived classes
//!   that require more specific processing.
//!
///////////////////////////////////////////////////////////////////////////////
void IVLFState::ContBITUpdate(CVlf* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      if (!instance->mDSP2LinkUp)
      {
         instance->setState(&theOfflineState);
      }
      //else - no change in state
   }//else nothing- error handled in if statement
}

///////////////////////////////////////////////////////////////////////////////
// Class: CInitState
//
//
// Description: This class contains the class methods for the CInitState class.
//              this class contains a state transition of the VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//! Function: CInitState
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
///////////////////////////////////////////////////////////////////////////////
CInitState::CInitState()
{
   //set VLF State Variable
   state = VLF_INITIALIZATION;
}
///////////////////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//!   This destructor method is used to cleanup the CInitState object
//!   once it is deleted.
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
CInitState::~CInitState()
{
}
///////////////////////////////////////////////////////////////////////////////
//! Function: getState
//!
//! Description:
//!   This method is used to get the state variable of the class. This will
//!    allow for the state variable to be sent in messages to the OES.
//!
//! Parameters:
//!
//! Return:  VLF_Receiver_State_Type
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
VLF_Receiver_State_Type CInitState::getState()
{
   return state;
}
///////////////////////////////////////////////////////////////////////////////
//! Function: DSPCommunications
//!
//! Description:
//!   This method is used to transition the VLF state to standby
//!    when communcations have been established between DSP1 and DSP2.
//!
//! Parameters:
//!   CVlf* instance- pointer to CVlf object
//!
//! Return:
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
void CInitState::DSPCommunications(CVlf* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      instance->setState(&theStandbyState);
   }//else nothing- error handled in if statement
}




///////////////////////////////////////////////////////////////////////////////
// Class: COperationalState
//
//
// Description: This class contains the class methods for the COperationalState
//              class.  This class contains a state transition of the
//              VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//! Function: COperationalState
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
///////////////////////////////////////////////////////////////////////////////
COperationalState::COperationalState()
{
   //set VLF State Variable
   state = VLF_OPERATIONAL;
}
///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
COperationalState::~COperationalState()
{
}
///////////////////////////////////////////////////////////////////////////////
//! Function: getState
//!
//! Description:
//!   This method is used to get the state variable of the class. This will
//!    allow for the state variable to be sent in messages to the OES.
//!
//! Parameters:
//!
//! Return:  VLF_Receiver_State_Type
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
VLF_Receiver_State_Type COperationalState::getState()
{
   return state;
}
///////////////////////////////////////////////////////////////////////////////
//! Function: ChannelStateChange
//!
//! Description:
//!   This method is used to transition the VLF state based on the Channel
//!   state change due to conditional criteria.
//!
//! Parameters:
//!   CVlf* instance- pointer to CVlf object
//!
//! Return:
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
void COperationalState::ChannelStateChange(CVlf* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      bool offline = false;        // offline flag
      bool degraded = false;       // degraded flag
      bool operational = false;    // operational flag

      for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
      {
         // Check for valid Comm Plan
         if (instance->chan[chanNum]->mCommPlanValid == true)
         {
            // Check if any channel is Offline, Degraded or Operational
            if (instance->chan[chanNum]->GetChState() == CH_OFFLINE)
            {
               offline = true;
            }
            else if (instance->chan[chanNum]->GetChState() == CH_DEGRADED)
            {
               degraded = true;
            }
            else
            {
	            if (instance->chan[chanNum]->GetChState() == CH_OPERATIONAL)
	            {
	               operational = true;
	            }
	            //else nothing- not reachable
            }
         }//else nothing- comm plan not valid
      }

      // if min one channel operational and none degraded
      // change VLF State
      if (degraded == true)
      {
         instance->setState(&theDegradedState);
      }
      // if all channel in offline change state
      else
      {
	      if ((offline == true) && ((operational == false) &&
	               ( degraded == false)))
	      {
	         instance->setState(&theStandbyState);
	      }
	      //else nothing- not reachable
      }
   }//else nothing- error handled in if statement
}
///////////////////////////////////////////////////////////////////////////////
//! Function: ContBITUpdate
//!
//! Description:
//!   This method is used to transition the VLF state to Offline State,
//!    based on conditional criteria.
//!
//! Parameters:
//!   CVlf* instance- pointer to CVlf object
//!
//! Return:
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
void COperationalState::ContBITUpdate(CVlf* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      if (!instance->mDSP2LinkUp)
      {
         instance->setState(&theOfflineState);
      }
      else
      {
	      if (!instance->mCPLinkUp)
	      {
	         for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++) // loop thru channels
	         {
	            // Check for valid Comm Plan, AND Mode Active
                if (((instance->chan[chanNum]->mCommPlan.mode9 == true) ||
                     (instance->chan[chanNum]->mCommPlan.modeHIDAR == true) ||
                     (instance->chan[chanNum]->mCommPlan.mode23 == true) ||
                     (instance->chan[chanNum]->mCommPlan.modeSMA == true)) &&
	                 (instance->chan[chanNum]->GetChState() != CH_OFFLINE))
	            {
	               instance->setState(&theDegradedState);

	               // leave loop, any one channel in DegradedState sets all
	               break;
	            }
	            //else nothing- comm plan does not have special modes
	            // we stay in current state
	         }//end for loop
	      }
	      // else do nothing, still operational
      }
   }//else nothing- error handled in if statement
}



///////////////////////////////////////////////////////////////////////////////
// Class: CDegradedState
//
//
// Description: This class contains the class methods for the CDegradedState
//              class.  This class contains a state transition of the
//              VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//! Function: CDegradedState
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
///////////////////////////////////////////////////////////////////////////////
CDegradedState::CDegradedState()
{
   //set VLF State Variable
   state = VLF_DEGRADED;
}
///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
CDegradedState::~CDegradedState()
{
}
///////////////////////////////////////////////////////////////////////////////
//! Function: getState
//!
//! Description:
//!   This method is used to get the state variable of the class. This will
//!    allow for the state variable to be sent in messages to the OES.
//!
//! Parameters:
//!
//! Return:  VLF_Receiver_State_Type
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
VLF_Receiver_State_Type CDegradedState::getState()
{
   return state;
}
///////////////////////////////////////////////////////////////////////////////
//! Function: ChannelStateChange
//!
//! Description:
//!   This method is used to transition the VLF state to Operational or
//!    Standby when an OES Shutdown message is recieved.
//!
//! Parameters:
//!   CVlf* instance- pointer to CVlf object
//!
//! Return:
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
void CDegradedState::ChannelStateChange(CVlf* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      bool offline = false;
      bool degraded = false;
      bool operational = false;

      for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
      {
         // Check for valid Comm Plan
         if (instance->chan[chanNum]->mCommPlanValid == true)
         {
            // Check if any channel is Offline, Degraded or Operational
            if (instance->chan[chanNum]->GetChState() == CH_OFFLINE)
            {
               offline = true;
            }
            else if (instance->chan[chanNum]->GetChState() == CH_DEGRADED)
            {
               degraded = true;
            }
            else
            {
	            if (instance->chan[chanNum]->GetChState() == CH_OPERATIONAL)
	            {
	               operational = true;
	            }
               //else - no other variable to set.
            }
         }
         //else do nothing, stay degraded
      }

      // if min one channel operational and none degraded
      // change VLF State
      if ((operational == true) && ( degraded == false))
      {
         instance->setState(&theOperationalState);
      }
      // if all channel in offline change state to standby
      else
      {
	      if ((offline == true) && ((operational == false) &&
	               ( degraded == false)))
	      {
	         instance->setState(&theStandbyState);
	      }
	      //else - no change in state
      }
   }//else nothing- error handled in if statement
}


///////////////////////////////////////////////////////////////////////////////
// Class: CStandbyState
//
//
// Description: This class contains the class methods for the CStandbyState
//              class.  This class contains a state transition of the
//              VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//! Function: CStandbyState
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
///////////////////////////////////////////////////////////////////////////////
CStandbyState::CStandbyState()
{
   //set VLF State Variable
   state = VLF_STANDBY;
}

///////////////////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//!   This destructor method is used to cleanup the CStandbyState object
//!   once it is deleted.
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
CStandbyState::~CStandbyState()
{
}
///////////////////////////////////////////////////////////////////////////////
//! Function: getState
//!
//! Description:
//!   This method is used to get the state variable of the class. This will
//!    allow for the state variable to be sent in messages to the OES.
//!
//! Parameters:
//!
//! Return:  VLF_Receiver_State_Type
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
VLF_Receiver_State_Type CStandbyState::getState()
{
   return state;
}
///////////////////////////////////////////////////////////////////////////////
//! Function: ChannelStateChange
//!
//! Description:
//!   This method is used to transition the VLF state to Operational or
//!    Degraded when a channel state has changed.
//!
//! Parameters:
//!   CVlf* instance- pointer to CVlf object
//!
//! Return:
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
void CStandbyState::ChannelStateChange(CVlf* instance)
{
   if ( !check4Null(instance, __FILE__, __LINE__) )
   {
      bool degraded = false;
      bool operational = false;

      for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
      {
         // Check for valid Comm Plan
         if (instance->chan[chanNum]->mCommPlanValid == true)
         {
            // Check if any channel is Degraded or Operational
            if (instance->chan[chanNum]->GetChState() == CH_DEGRADED)
            {
               degraded = true;
            }
            else
            {
	            if (instance->chan[chanNum]->GetChState() == CH_OPERATIONAL)
	            {
	               operational = true;
	            }
               // else - no other variable to set
            }
         }//else nothing- comm plan not valid
      }

      if (degraded == true)
      {
         instance->setState(&theDegradedState);
      }
      else
      {
	      if (operational == true)
	      {
	         instance->setState(&theOperationalState);
	      }
         //else - no state change required
      }
   }//else nothing- error handled in if statement
}



///////////////////////////////////////////////////////////////////////////////
// Class: COfflineState
//
//
// Description: This class contains the class methods for the COfflineState
//              class.  This class contains a state transition of the
//              VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//! Function: COfflineState
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
///////////////////////////////////////////////////////////////////////////////
COfflineState::COfflineState()
{
   //set VLF State Variable
   state = VLF_OFFLINE;
}
///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
COfflineState::~COfflineState()
{
}
///////////////////////////////////////////////////////////////////////////////
//! Function: getState
//!
//! Description:
//!   This method is used to get the state variable of the class. This will
//!    allow for the state variable to be sent in messages to the OES.
//!
//! Parameters:
//!
//! Return:  VLF_Receiver_State_Type
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
VLF_Receiver_State_Type COfflineState::getState()
{
   return state;
}
///////////////////////////////////////////////////////////////////////////////
//! Function: ContBITUpdate
//!
//! Description:
//!   This method is used to transition the VLF state to Standby State.
//!    The channel states will determine overall receiver State, so if all
//!    Offline BITS are cleared set to standby and signal channels to determine
//!    states.
//!
//! Parameters:
//!   CVlf* instance- pointer to CVlf object
//!
//! Return:
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////////////////
void COfflineState::ContBITUpdate(CVlf* instance)
{
   if ( ( !check4Null(instance, __FILE__, __LINE__) ) &&
        (instance->mDSP2LinkUp) )
   {
      bool offline = false;     // offline
      bool degraded = false;    // degraded
      bool operational = false; // operational

      for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
      {
         // Check for valid Comm Plan
         if (instance->chan[chanNum]->mCommPlanValid == true)
         {
            // Check if any channel is Offline, Degraded or Operational
            if (instance->chan[chanNum]->GetChState() == CH_OFFLINE)
            {
               offline = true;
            }
            else if (instance->chan[chanNum]->GetChState() == CH_DEGRADED)
            {
               degraded = true;
            }
            else
            {
	            if (instance->chan[chanNum]->GetChState() == CH_OPERATIONAL)
	            {
	               operational = true;
	            }
               // else- no other variable to set
            }
         }
         // with no comm plan we are offline,
         // set offline flag to true
         else
         {
            offline = true;
         }
      }//end for loop

      // change VLF state based on channel states
      if(degraded == true)
      {
         instance->setState(&theDegradedState);
      }
      else if ((operational == true) && (degraded == false))
      {
         instance->setState(&theOperationalState);
      }
      // if all channel in offline change state to standby
      else
      {
	      if ((offline == true) && (operational == false) &&
	               (degraded == false))
	      {
	         instance->setState(&theStandbyState);
	      }
         //else - No state change required
      }
   }//else nothing- error handled in if statement or not dsp2 up
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
