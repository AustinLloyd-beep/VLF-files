
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVFPGAOutputSampleDataEnable.h
//
// Description:
//    This file contains the class definition for the COVFPGAOutputSampleDataEnable Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CFPGA_OUT_SAMPLE_MSG_H
#define CFPGA_OUT_SAMPLE_MSG_H

#include "InterfaceHandler.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: COVFPGAOutputSampleDataEnable
//
// Description: This class handles the OUTPUT_SAMPLE_TEST_ENABLE_MSGTYPE
//              message received from OES.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class COVFPGAOutputSampleDataEnable : public InterfaceHandler
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   COVFPGAOutputSampleDataEnable() {}; //constructor
   virtual ~COVFPGAOutputSampleDataEnable() {}; //destructor
private:
   COVFPGAOutputSampleDataEnable(const COVFPGAOutputSampleDataEnable&);
   COVFPGAOutputSampleDataEnable& operator=(const COVFPGAOutputSampleDataEnable&);
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
