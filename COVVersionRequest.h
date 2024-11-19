
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVVersionRequest.h
//
// Description:
//    This file contains the class definition for the COVVersionRequest Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CVERSION_REQUEST_MSG_H
#define CVERSION_REQUEST_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVVersionRequest
//
// Description:This class handles version request message
//              received from OES.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVVersionRequest : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVVersionRequest() {}; //constructor
   virtual ~COVVersionRequest() {}; //destructor
private:
   COVVersionRequest(const COVVersionRequest&);
   COVVersionRequest& operator=(const COVVersionRequest&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
