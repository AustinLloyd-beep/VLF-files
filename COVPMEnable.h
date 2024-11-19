
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVPMEnable.h
//
// Description:
//    This file contains the class definition for the COVPMEnable Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CPM_ENABLE_MSG_H
#define CPM_ENABLE_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVPMEnable
//
// Description: This class handles the PM enable message
//              received from OES.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVPMEnable : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVPMEnable() {}; //constructor
   virtual ~COVPMEnable() {}; //destructor
private:
   COVPMEnable(const COVPMEnable&);
   COVPMEnable& operator=(const COVPMEnable&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
