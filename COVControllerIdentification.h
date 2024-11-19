
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVControllerIdentification.h
//
// Description:
//    This file contains the class definition for the COVControllerIdentification Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCONTROLL_ID_MSG_H
#define CCONTROLL_ID_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVControllerIdentification
//
// Description: This message class is used handle the OES switchover request
//
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVControllerIdentification : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVControllerIdentification() {}; //constructor
   virtual ~COVControllerIdentification() {}; //destructor
private:
   COVControllerIdentification(const COVControllerIdentification&);
   COVControllerIdentification& operator=(const COVControllerIdentification&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
