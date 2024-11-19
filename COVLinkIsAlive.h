
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVLinkIsAlive.h
//
// Description:
//    This file contains the class definition for the COVLinkIsAlive Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CLINK_IS_ALIVE_MSG_H
#define CLINK_IS_ALIVE_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVLinkIsAlive
//
// Description: This class handles the link is alive message
//              received from OES.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVLinkIsAlive : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVLinkIsAlive() {}; //constructor
   virtual ~COVLinkIsAlive() {}; //destructor
private:
   COVLinkIsAlive(const COVLinkIsAlive&);
   COVLinkIsAlive& operator=(const COVLinkIsAlive&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
