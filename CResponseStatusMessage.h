
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CResponseStatusMessage.h
//
// Description:
//    This file contains the class definition for the Response Status Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CRESP_STAT_MSG_H
#define CRESP_STAT_MSG_H

#include "InterfaceHandler.h"
#include "CResponseStatusMessageCommon.h"

///////////////////////////////////////////////////////////////////////////////
//
// Class: CResponceStatusMessage
//
// Description: This class handles the message status responses received
//              by DSP1
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
class CResponseStatusMessage : public InterfaceHandler, protected CResponseStatusMessageCommon
{
public:
   Msg_Error_Codes_Type ValidateMsgParam(const CMessage& msg);
   void HandleMsg(CMessage* msg);
   CResponseStatusMessage() {}; //constructor
   virtual ~CResponseStatusMessage() {}; //destructor
private:
   enum Hndl_Ch_Resp_Type {
      HNDL_CONFIG_CH_RESP,
      HNDL_RUNUP_CH_RESP,
      HNDL_ZEROIZE_CH_RESP
   };
   CResponseStatusMessage(const CResponseStatusMessage&);
   CResponseStatusMessage& operator=(const CResponseStatusMessage&);
   void HandleCpResponses(CMessage* msg);
   void HandleSelectiveZeroizeResponse (Response_Status_Msg_Type* msgData);
   void HandleConfigureChannelResponse (Response_Status_Msg_Type* msgData,
                                        const unsigned int& actionID);
   void HandleRunupChannelResponse (Response_Status_Msg_Type* msgData,
                                    const unsigned int& actionID);
   void HandleZeroizeChannelResponse (Response_Status_Msg_Type* msgData,
                                      const unsigned int& actionID);

   void HandleCommonChannelResponse (Response_Status_Msg_Type* msgData,
                                     const unsigned int& actionID,
                                     Hndl_Ch_Resp_Type hndlType);
   void GetHandlerChanData (const Hndl_Ch_Resp_Type hndlType,
                            const unsigned int chanNum,
                            Semaphore** hndlrSem,
                            Condition** hndlrCon,
                            Msg_Error_Codes_Type& hndlrErr );
   void DisplayUnsolicitActionIdMsg ( const Hndl_Ch_Resp_Type hndlType,
                                      const unsigned int chanNum );
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
