
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVSetConfigParam.h
//
// Description:
//    This file contains the class definition for the COVSetConfigParam Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CSET_CONFIG_PARAMS_MSG_H
#define CSET_CONFIG_PARAMS_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVSetConfigParam
//
// Description: This class handles setting the config parameter message
//              received from OES.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVSetConfigParam : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVSetConfigParam() {}; //constructor
   virtual ~COVSetConfigParam() {}; //destructor
private:
   COVSetConfigParam(const COVSetConfigParam&);
   COVSetConfigParam& operator=(const COVSetConfigParam&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
