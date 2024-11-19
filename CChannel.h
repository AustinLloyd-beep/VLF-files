
///////////////////////////////////////////////////////////////////////////////
// Class: CChannel
//
// File Name: CChannel.h
//
// Description: This file contains the definition for the channel class
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCHANNEL_H
#define CCHANNEL_H

#include "CMode.h"
#include "msg_defs.h"
#include "utility.h"
#include "FpgaDevice.h"
#include "CChannelState.h"

typedef Value (FpgaDevice::*FpgaGETSampleAddrPFuncType)();
typedef FpgaDevice::ERROR (FpgaDevice::*FpgaSetFreqPFuncType)(const unsigned int);

class CChannel
{
public:
   Vlf_Channel_Type mCommPlan;   // comm plan
   MgrChCmdQueueStruct mChCmd;   // channel cmd
   CMode15 *mMode15;             // Mode 15
   CMode9  *mMode9;              // Mode 9
   CModeHidar  *mModeHidar;      // Mode HIDAR
   CMode23 *mMode23;             // Mode 23
   CModeSMA *mModeSMA;           // Mode SMA

   // flags
   bool mEnableHidarOpstat;      // HIDAR enable OP stat
   bool mEnableVlf_Pm;           // enable PM flag
   bool mCEPEnabled;             // CEP enable flag
   bool mAntiJamOnly;            // anti-jam flag
   bool mCommPlanValid;          // comm plan valiud flag
   bool mCpChanOpStatValid;      // valid channel OP stat flag
   bool mSampleOutputEnabled;    // FPGA Output Sample Test
   unsigned int mNum20msecs2send; //Number of samples to send
   Msg_Error_Codes_Type mChannelError; // channel err
   unsigned int mCurrentChanAction; // set current channel action by operator

   // constructors
   CChannel(Channel_ID_Type chan, unsigned short freq, Connection cmdConn,
            Value fpgaRegChAddr,
            FpgaSetFreqPFuncType chSetFreqFPtr,
            FpgaGETSampleAddrPFuncType chGetOutputSampleAddrFPtr);

   // destructor
   ~CChannel ();

   // methods
   void SendChCmd(ChannelCmdStruct *pCmdBuff);
   void HandleMgrCmd(ChannelCmdStruct* mgrCmd);
   void HandleChStatus(ChanStatusQueueStruct* chstatus);
   void SetChFreq();
   void SetChFreq(const unsigned int freq);
   void LoadChOutputSample();
   void ReportChStatus();

   // Channel State
   VLF_Channel_State_Type GetChState();
   void setState(IChannelState* newChannelState);
   void StartChannel();
   void StopChannel();
   void ChangeCpChanOpStatus();
   void LoadTime();
   void CryptoStatus();
   void CryptoChannelUpdate();
   void CryptoBIT();

private:
   Value mFpgaRegChanAddress;                     // FPGA register channel addr


   VLF_Receiver_Channel_Status_Type mStatus;      // channel status
   VLF_Receiver_Channel_Status_Type mPrevStatus;  // previous channel status

   VLF_Channel_State_Type mVlfChanState;          // channel state

   // channel specific function pointers
   FpgaGETSampleAddrPFuncType mChanGetOutputSampleAddrFPtr; // get channel output sample addr
   FpgaSetFreqPFuncType mChanSetFreqFPtr;        // set channel frequency

   // Channel State
   IChannelState* mChannelState;                 // channel state object

   void SetChState(VLF_Channel_State_Type chstate);
};
#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////


