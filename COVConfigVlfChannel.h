
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVConfigVlfChannel.h
//
// Description:
//    This file contains the class definition for the COVConfigVlfChannel Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCONFIG_CHAN_MSG_H
#define CCONFIG_CHAN_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVConfigVlfChannel
//
// Description: This class handles the write communication plan message
//              received from OES when the message includes Mode 23.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVConfigVlfChannel : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVConfigVlfChannel() {}; //constructor
   virtual ~COVConfigVlfChannel() {}; //destructor
private:
   COVConfigVlfChannel(const COVConfigVlfChannel&);
   COVConfigVlfChannel& operator=(const COVConfigVlfChannel&);
   bool OnlyShortTitleChanged(const CMessage& msg);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
