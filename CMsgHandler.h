///////////////////////////////////////////////////////////////////////////////
// Class: CMsgHandler
//
// File Name: CMsgHandler.h
//
// Description: This file contains the Message Handler Class definition. This
//              class is used to register, send message and
//              invoke message handlers for an incoming message
//
// Notes: This class is implemented as singleton to prevent more than one
//        instantiation of the CMsgHandler object. To obtain a reference to
//        an instance of the CMsgHandler object, the user calls the
//        public Instance() member function.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CMSGHANDLER_H
#define CMSGHANDLER_H

#include "InterfaceHandler.h"
#include "CMessage.h"
#include <INTEGRITY.h>

class CMsgHandler
{
public:
   static CMsgHandler *Instance();
   InterfaceHandler *RegisterMsg(int msgNo, InterfaceHandler* ih);
   static void InvokeHandler(CMessage* msg);
   void SendMsg(CMessage* msg);
   void SendAckNak(Subsystem_Type dest, Message_ID_Type toMsgId,
               int actionId, Response_Status_Type status,
               Msg_Error_Codes_Type error, short channelID = 0);

   // Priority Message handling
   void SendPriMsg(CMessage* msg);
   void SendPriAckNak(Subsystem_Type dest, Message_ID_Type toMsgId,
               int actionId, Response_Status_Type status,
               Msg_Error_Codes_Type error, short channelID = 0);
private:
   CMsgHandler();   // constructors
   ~CMsgHandler (); // destructor
   CMsgHandler(const CMsgHandler&);
   CMsgHandler& operator=(const CMsgHandler&);

   void SendMsgHelper(CMessage* msg, MessageQueue queue);

   // data members
   static InterfaceHandler* mMsgHandlers[MAX_MSG_ID_MSGTYPE];   // msg handlers
   static CMsgHandler* mInstance;                               // object instance
};
#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////

