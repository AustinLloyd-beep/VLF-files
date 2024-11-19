
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CVLFState.h
//
// Description: This file contains the definition for the CVLFState Interface
//               class.  This class contains the state pattern of the
//               VLF receiver.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CVLFSTATE_H
#define CVLFSTATE_H

#include "msg_defs.h"

///////////////////////////////////////////////////////////////////////////////
//
// Pre-declaration of classes included in this file
//
///////////////////////////////////////////////////////////////////////////////
class CVlf;                   //context of state class
class CInitState;             // VLF State
class CStandbyState;          // VLF State
class COperationalState;      // VLF State
class CDegradedState;         // VLF State
class COfflineState;          // VLF State
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Class: IVLFState
//
//
// Description: This is an interface/abstract class used to derive the specific
//              state classes as part of the VLF state pattern.
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
class IVLFState
{
public:
   // VLF Receiver State Events
   virtual VLF_Receiver_State_Type getState() = 0;
   virtual void ChannelStateChange(CVlf*) {};
   virtual void DSPCommunications(CVlf*) {};
   virtual void ContBITUpdate(CVlf*);

public:
   // Singletons of each state
   static CInitState theInitState;               // init state
   static CStandbyState theStandbyState;         // standby state
   static COperationalState theOperationalState; // operational state
   static CDegradedState theDegradedState;       // degraded state
   static COfflineState theOfflineState;         // offline state
};
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
class CInitState : public IVLFState
{
public:
   CInitState();     // constructors
   ~CInitState ();   // destructor

   // VLF Receiver State Events
   VLF_Receiver_State_Type getState();
   void DSPCommunications(CVlf*);

private:
   CInitState(const CInitState&);
   CInitState& operator=(const CInitState&);
   VLF_Receiver_State_Type state;
};
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
class COperationalState : public IVLFState
{
public:
   COperationalState();    // constructors
   ~COperationalState ();  // destructor

   // VLF Receiver State Events
   VLF_Receiver_State_Type getState();
   void ChannelStateChange(CVlf*);
   void ContBITUpdate(CVlf*);

private:
   COperationalState(const COperationalState&);
   COperationalState& operator=(const COperationalState&);
   VLF_Receiver_State_Type state;
};
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
class CDegradedState : public IVLFState
{
public:
   CDegradedState();    // constructors
   ~CDegradedState ();  // destructor

   // VLF Receiver State Events
   VLF_Receiver_State_Type getState();
   void ChannelStateChange(CVlf*);

private:
   CDegradedState(const CDegradedState&);
   CDegradedState& operator=(const CDegradedState&);
   VLF_Receiver_State_Type state;
};
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
class CStandbyState : public IVLFState
{
public:
   CStandbyState();    // constructors
   ~CStandbyState ();  // destructor

   // VLF Receiver State Events
   VLF_Receiver_State_Type getState();
   void ChannelStateChange(CVlf*);

private:
   CStandbyState(const CStandbyState&);
   CStandbyState& operator=(const CStandbyState&);
   VLF_Receiver_State_Type state;
};
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
class COfflineState : public IVLFState
{
public:
   COfflineState();    // constructors
   ~COfflineState ();  // destructor

   // VLF Receiver State Events
   VLF_Receiver_State_Type getState();
   void ContBITUpdate(CVlf*);

private:
   COfflineState(const COfflineState&);
   COfflineState& operator=(const COfflineState&);
   VLF_Receiver_State_Type state;
};
#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification:  UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
