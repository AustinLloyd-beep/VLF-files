///////////////////////////////////////////////////////////////////////////////
//
// File Name: CChannelState.h
//
// Description: This file contains the definition for the CVLFState Interface
//               class.  This class contains the state pattern of the
//               VLF receiver.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCHANNELSTATE_H
#define CCHANNELSTATE_H

#include "msg_defs.h"

///////////////////////////////////////////////////////////////////////////////
//
// Pre-declaration of classes included in this file
//
///////////////////////////////////////////////////////////////////////////////
class CChannel;                 //context of state class
class CChOperationalState;      // Channel State
class CChDegradedState;         // Channel State
class CChOfflineState;          // Channel State
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//! Class: IChannelState
//!
//!
//! Description: This is an interface/abstract class used to derive the specific
//!              state classes as part of the VLF channel state pattern.
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////////////////
class IChannelState
{
public:
   // Channel State Events
   virtual VLF_Channel_State_Type getChannelState() = 0;
   virtual void StartChannel(CChannel*) {};
   virtual void StopChannel(CChannel*);
   virtual void LoadTime(CChannel*) {};
   virtual void ChangeCpChanOpStatus(CChannel*) {};
   virtual void CryptoStatus(CChannel*) {};
   virtual void CryptoChannelUpdate(CChannel*) {};
   virtual void CryptoBIT(CChannel*) {};

public:
   // Singleton Classes
   static CChOperationalState theChOperationalState;
   static CChDegradedState theChDegradedState;
   static CChOfflineState theChOfflineState;
private:
   VLF_Channel_State_Type chstate;
};
///////////////////////////////////////////////////////////////////////////////
//! Class: COperationalState
//!
//!
//! Description: This class contains the class methods for the COperationalState
//!              class.  This class contains a state transition of the
//!              VLF channels
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////////////////
class CChOperationalState : public IChannelState
{
public:
   CChOperationalState();    // constructors
   ~CChOperationalState ();  // destructor

   // Channel State Events
   VLF_Channel_State_Type getChannelState();
   void LoadTime(CChannel*);
   void ChangeCpChanOpStatus(CChannel*);
   void CryptoStatus(CChannel*);
   void CryptoChannelUpdate(CChannel*);
   void CryptoBIT(CChannel*);

private:
   CChOperationalState(const CChOperationalState&);
   CChOperationalState& operator=(const CChOperationalState&);
   // Used throughout CChannelState
   VLF_Channel_State_Type chstate;
};
///////////////////////////////////////////////////////////////////////////////
//! Class: CChDegradedState
//!
//!
//! Description: This class contains the class methods for the CDegradedState
//!              class.  This class contains a state transition of the
//!              VLF channels
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////////////////
class CChDegradedState : public IChannelState
{
public:
   CChDegradedState();    // constructors
   ~CChDegradedState ();  // destructor

   // Channel State Events
   VLF_Channel_State_Type getChannelState();
   void LoadTime(CChannel*);
   void ChangeCpChanOpStatus(CChannel*);
   void CryptoStatus(CChannel*);
   void CryptoChannelUpdate(CChannel*);
   void CryptoBIT(CChannel*);

private:
   CChDegradedState(const CChDegradedState&);
   CChDegradedState& operator=(const CChDegradedState&);
   VLF_Channel_State_Type chstate;
   bool CheckStatusEvents(CChannel*);
   void CommonUpdate(CChannel*);
};
///////////////////////////////////////////////////////////////////////////////
//! Class: CChOfflinelState
//!
//!
//! Description: This class contains the class methods for the COfflineState
//!              class.  This class contains a state transition of the
//!              VLF channels
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////////////////
class CChOfflineState : public IChannelState
{
public:
   CChOfflineState();    // constructors
   ~CChOfflineState ();  // destructor

   // Channel State Events
   VLF_Channel_State_Type getChannelState();
   void StartChannel(CChannel*);

private:
   CChOfflineState(const CChOfflineState&);
   CChOfflineState& operator=(const CChOfflineState&);
   VLF_Channel_State_Type chstate;
};
#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification:  UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
