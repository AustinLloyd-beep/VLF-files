
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVRequestSystemStatus.h
//
// Description:
//    This file contains the class definition for the COVRequestSystemStatus Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CREQUEST_SYSTEM_STATUS_MSG_H
#define CREQUEST_SYSTEM_STATUS_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVRequestSystemStatus
//
// Description:This class handles system status request message
//              received from VLF Control Interface.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVRequestSystemStatus : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVRequestSystemStatus() {}; //constructor
   virtual ~COVRequestSystemStatus() {}; //destructor
private:
   COVRequestSystemStatus(const COVRequestSystemStatus&);
   COVRequestSystemStatus& operator=(const COVRequestSystemStatus&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
