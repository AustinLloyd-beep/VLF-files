
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVReadVlfChannel.h
//
// Description:
//    This file contains the class definition for the COVConfigVlfChannel Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CREAD_COMMPLAN_MSG_H
#define CREAD_COMMPLAN_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVReadVlfChannel
//
// Description: This class handles the read communication plan message
//              received from OES.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVReadVlfChannel : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVReadVlfChannel() {}; //constructor
   virtual ~COVReadVlfChannel() {}; //destructor
private:
   COVReadVlfChannel(const COVReadVlfChannel&);
   COVReadVlfChannel& operator=(const COVReadVlfChannel&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
