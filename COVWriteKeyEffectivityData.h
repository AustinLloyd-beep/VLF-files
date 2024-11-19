
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVWriteKeyEffectivityData.h
//
// Description:
//    This file contains the class definition for the COVWriteKeyEffectivityData Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CWRITE_KEY_EFFECT_MSG_H
#define CWRITE_KEY_EFFECT_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVWriteKeyEffectivityData
//
// Description: This class is used to support the retrieval of keys currently
//              loaded into the PEIP II+
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVWriteKeyEffectivityData  : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVWriteKeyEffectivityData() {}; //constructor
   virtual ~COVWriteKeyEffectivityData() {}; //destructor
private:
   COVWriteKeyEffectivityData(const COVWriteKeyEffectivityData&);
   COVWriteKeyEffectivityData& operator=(const COVWriteKeyEffectivityData&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
