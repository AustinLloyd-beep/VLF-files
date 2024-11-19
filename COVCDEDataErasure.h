
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVCDEDataErasure.h
//
// Description:
//    This file contains the class definition for the COVCDEDataErasure Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCDE_MSG_H
#define CCDE_MSG_H

#include "InterfaceHandler.h"
#include "CMessage.h"
#include "COVSelectZeroizeKeys.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVCDEDataErasure
//
// Description: This class is used to support the CDE Data Ereasure from HMI.
//              This message is used to halt all channels, clear the
//              Key Effectivity table and delete all mission TEKs and KEK.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVCDEDataErasure : public InterfaceHandler
{
   static const int CDE_TIMEOUT = 1;
public:
   static AlarmTimer CDETimer;
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVCDEDataErasure(); //constructor
   virtual ~COVCDEDataErasure() {}; //destructor
   static void haltChannels();
   static void zeroizeAllKeys();
   static void zeroizeAllKeysTimeOutHandler();
private:
   static const int TIMER_RETRY = 2;
   CMessage rcv_msg; // Timer variarable used to hold incoming msg
   COVCDEDataErasure(const COVSelectZeroizeKeys&);
   COVCDEDataErasure& operator=(const COVCDEDataErasure&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
