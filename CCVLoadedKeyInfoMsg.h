
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CCVLoadedKeyInfoMsg.h
//
// Description:
//    This file contains the class definition for the CCVLoadedKeyInfoMsg Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CLOADED_KEY_INFO_MSG_H
#define CLOADED_KEY_INFO_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: CCVLoadedKeyInfoMsg
//
// Description: This class handles the loaded key data results received from
//              CP.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class CCVLoadedKeyInfoMsg : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   CCVLoadedKeyInfoMsg() {}; //constructor
   virtual ~CCVLoadedKeyInfoMsg() {}; //destructor
private:
   CCVLoadedKeyInfoMsg(const CCVLoadedKeyInfoMsg&);
   CCVLoadedKeyInfoMsg& operator=(const CCVLoadedKeyInfoMsg&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
