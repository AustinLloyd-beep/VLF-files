
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVConfigAllVlfChannels.h
//
// Description:
//    This file contains the class definition for the COVConfigAllVlfChannels
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCONFIG_ALL_CHAN_MSG_H
#define CCONFIG_ALL_CHAN_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVConfigAllVlfChannels
//
// Description: This class handles the write communication plans message
//              received from HMI when the message includes Mode 23.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVConfigAllVlfChannels : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVConfigAllVlfChannels() {}; //constructor
   virtual ~COVConfigAllVlfChannels() {}; //destructor
private:
   bool commPlanValid [MAX_VLF_CHANNEL];
   COVConfigAllVlfChannels(const COVConfigAllVlfChannels&);
   COVConfigAllVlfChannels& operator=(const COVConfigAllVlfChannels&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
