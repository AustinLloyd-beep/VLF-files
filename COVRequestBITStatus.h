
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVRequestBITStatus.h
//
// Description:
//    This file contains the class definition for the COVRequestBITStatus Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CREQUEST_BIT_STATUS_MSG_H
#define CREQUEST_BIT_STATUS_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVRequestBITStatus
//
// Description: This class is used to support BIT request from
//    the OES.  Once this message is received, VLF will provide PBIT and CBIT status.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////

class COVRequestBITStatus : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVRequestBITStatus() {}; //constructor
   virtual ~COVRequestBITStatus() {}; //destructor
private:
   COVRequestBITStatus(const COVRequestBITStatus&);
   COVRequestBITStatus& operator=(const COVRequestBITStatus&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
