
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVTimeAtTheToneMsg.h
//
// Description:
//    This file contains the class definition for the COVTimeAtTheToneMsg Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CTIME_AT_THE_TONE_MSG_H
#define CTIME_AT_THE_TONE_MSG_H

#include "InterfaceHandler.h"
#include "CTimeLoad.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVTimeAtTheToneMsg
//
// Description:
//    This class is used to handle time at the tone message from the VLF
//     Control Interface
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVTimeAtTheToneMsg : public InterfaceHandler
{
public:
   static AlarmTimer LoadTimeTimer;
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   static void LoadTimeTimeOutHandler(CMessage* msg);
   void HandleMsg(CMessage* msg);
   COVTimeAtTheToneMsg(); //constructor
   virtual ~COVTimeAtTheToneMsg() {}; //destructor
private:
   static bool mTimerFlagSet;
   CMessage rcv_msg; // Timer variarable used to hold incoming msg
   COVTimeAtTheToneMsg(const COVTimeAtTheToneMsg&);
   COVTimeAtTheToneMsg& operator=(const COVTimeAtTheToneMsg&);

   static const int LOADTIME_TIMEOUT = 5;
   static const int LOADTIME_COUNTER = 12;
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
