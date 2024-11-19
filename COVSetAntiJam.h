
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVSetAntiJam.h
//
// Description:
//    This file contains the class definition for the COVSetAntiJam Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CSET_ANTI_JAM_MSG_H
#define CSET_ANTI_JAM_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVSetAntiJam
//
// Description: This class handles the set anti Jam parameter message
//              received from OES.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVSetAntiJam : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVSetAntiJam() {}; //constructor
   virtual ~COVSetAntiJam() {}; //destructor
private:
   COVSetAntiJam(const COVSetAntiJam&);
   COVSetAntiJam& operator=(const COVSetAntiJam&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
