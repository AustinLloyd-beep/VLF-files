
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVRunIBIT.h
//
// Description:
//    This file contains the class definition for the COVConfigVlfChannel Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CRUN_IBIT_MSG_H
#define CRUN_IBIT_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVRunIBIT
//
// Description:This class handles Run IBIT message
//              received from OES.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVRunIBIT : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVRunIBIT() {}; //constructor
   virtual ~COVRunIBIT() {}; //destructor
private:
   COVRunIBIT(const COVRunIBIT&);
   COVRunIBIT& operator=(const COVRunIBIT&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
