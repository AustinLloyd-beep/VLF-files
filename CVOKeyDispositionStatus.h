
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CVOKeyDispositionStatus.h
//
// Description:
//    This file contains the class definition for the CVOKeyDispositionStatus
//      Message.
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CVOKEY_DISPOSITION_MSG_H
#define CVOKEY_DISPOSITION_MSG_H

#include "CMessage.h"

class CVOKeyDispositionStatus
{

public:
   CVOKeyDispositionStatus(){};   // constructors
   ~CVOKeyDispositionStatus (){}; // destructor

   CMessage* BuildDispMsg (Key_Disposition_Status_Msg_Type& KeyDispMsgData);

private:
   CMessage snd_msg; // snd_msg is initialized in the constructor
   CVOKeyDispositionStatus(const CVOKeyDispositionStatus&); // copy operators
   CVOKeyDispositionStatus& operator=(const CVOKeyDispositionStatus&); // copy operators
};

#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
