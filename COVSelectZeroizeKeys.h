
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVSelectZeroizeKeys.h
//
// Description:
//    This file contains the class definition for the COVSelectZeroizeKeys Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CSELECTIVE_ZEROIZE_MSG_H
#define CSELECTIVE_ZEROIZE_MSG_H

#include <INTEGRITY.h>
#include "InterfaceHandler.h"
#include "CMessage.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVSelectZeroizeKeys
//
// Description: This class is used to support the zerioze request from OES.
//              This message can be used to zerioze a single TEK, all TEKs
//              associated with an algorithm or all TEKs for Medley.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVSelectZeroizeKeys : public InterfaceHandler
{
public:
   static AlarmTimer HaltChanTimer;
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVSelectZeroizeKeys(); //constructor
   virtual ~COVSelectZeroizeKeys() {}; //destructor
   static void clearCommPlans();
   static void haltChannels();
   static void clearCommPlanTimeOutHandler(CMessage* msg);
private:
   static const int TIMER_RETRY = 2;
   CMessage rcv_msg; // Timer variarable used to hold incoming msg
   COVSelectZeroizeKeys(const COVSelectZeroizeKeys&);
   COVSelectZeroizeKeys& operator=(const COVSelectZeroizeKeys&);
   static const int HALT_TIMEOUT = 1;
};


#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
