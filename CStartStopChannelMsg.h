
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CStartStopChannelMsg.h
//
// Description:
//    This file contains the class definition for the CStartStopChannelMsg Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CSTART_STOP_CHAN_MSG_H
#define CSTART_STOP_CHAN_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: CStartStopChannelMsg
//
// Description: This class handles the start/stop channel message
//              received from OES.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class CStartStopChannelMsg : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   CStartStopChannelMsg() {}; //constructor
   virtual ~CStartStopChannelMsg() {}; //destructor
private:
   CStartStopChannelMsg(const CStartStopChannelMsg&);
   CStartStopChannelMsg& operator=(const CStartStopChannelMsg&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
