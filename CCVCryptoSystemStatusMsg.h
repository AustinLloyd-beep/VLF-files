
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CCVCryptoSystemStatusMsg.h
//
// Description:
//    This file contains the class definition for the CCVCryptoSystemStatusMsg Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCRYPTO_SYS_STAT_MSG_H
#define CCRYPTO_SYS_STAT_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: CCVCryptoSystemStatusMsg
//
// Description:  This class handles the system status reported by CP.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class CCVCryptoSystemStatusMsg : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   CCVCryptoSystemStatusMsg() {}; //constructor
   virtual ~CCVCryptoSystemStatusMsg() {}; //destructor
private:
   CCVCryptoSystemStatusMsg(const CCVCryptoSystemStatusMsg&);
   CCVCryptoSystemStatusMsg& operator=(const CCVCryptoSystemStatusMsg&);
   void HaltChannelAfterCPChanChng(const int& chanNum);
   void performECUSubstateOps(const unsigned int& substate);
   void ActivateRolloverAfterCPChanChng(const int& chanNum);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
