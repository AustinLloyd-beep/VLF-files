///////////////////////////////////////////////////////////////////////////////
// Class: CVlf
//
// File Name: CVlf.h
//
// Description: This file contains the definition for the vlf class
//              this class contains the state and status of the VLF receiver
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CVLF_H
#define CVLF_H

#include <INTEGRITY.h>
#include "CChannel.h"
#include "msg_defs.h"
#include "CVLFState.h"
#include "CMessage.h"
#include "CDspBIT.h"
#include "CDspConfig.h"

class CVlf
{
public:
   static CVlf                         *Instance();
   Subsystem_Type                      mId;
   CChannel*                           chan[MAX_VLF_CHANNEL];
   VLF_Receiver_System_Status_Msg_Type mRcvrStatus;
   Configuration_Params_Msg_Type       mConfigParms;
   Subsystem_Type                      mActiveOES;
   BIT_Result_Type                     mDspPBit;
   BIT_Result_Type                     mDspCBit;
   bool                                mCPLinkUp;
   bool                                mDSP2LinkUp;
   bool                                mMemoryClearRcvd;
   bool                                mDidCpFullOpOccur;
   CDspConfig                          mDspIOConfig;

public:
   // report overall status change of VLF Receiver
   void UpdateRcvrStatus();

   //version info methods
   void SendDSP2VersionData();
   void setFpgaVersion(const char* version);

   // State Events that cause transitions
   void setState(IVLFState* newState);
   void DSPCommunications();
   void ContBITUpdate();
   void ChannelStateChange();
   void setTimeLoadedStatus();
   void setKeyTblLoadedStatus(bool status);
   bool getKeyTblLoadedStatus() const;
   void CryptoStatusChange();
   void CryptoChannelChange(Channel_ID_Type chanNum);
   void RestartChannelsAfterEventChg(int& chanNum);

private:
   // Misc initialization functions.
   void   GetProdVersionData();
   void   SetConfigData();

   //variables for version construction
   static const unsigned short MAX_NUMBER_VERSIONS = 4;
   int versionEnum[MAX_NUMBER_VERSIONS];
   char* versionTitleString[MAX_NUMBER_VERSIONS];
   char* configString[CDspConfig::MAX_CONFIG_ITEMS + 1];

private:
   CVlf();   // constructors
   ~CVlf (); // destructor
   CVlf(const CVlf&);
   CVlf& operator=(const CVlf&);
   static CVlf* mInstance;

   Version_Data_Msg_Type mVersion;

   // VLF State
   IVLFState* mState;
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
