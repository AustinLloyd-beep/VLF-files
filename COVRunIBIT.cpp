
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVRunIBIT.cpp
//
// Description:
//    This file contains the class definition for the COVRunIBIT
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVRunIBIT.h"
#include "CVlf.h"
#include "CMsgHandler.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVRunIBIT::ValidateMsgParam
//!
//! Description:
//!   This method validates the message parameters.
//!   No parameters so return VLF_NO_ERROR
//!
//! Parameters:
//!    msg - Message class pointer - NOT USED
//!
//! Return:
//!    Msg_Error_Codes_Type
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
Msg_Error_Codes_Type COVRunIBIT::ValidateMsgParam(const CMessage& msg)
{
   // There are parameters to validate so just return no error
   return (VLF_NO_ERROR);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVRunIBIT::HandleMsg
//!
//! Description:
//!   This method handles the COVRunOfflineBIT message received from
//!   DSP2.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVRunIBIT::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   if ( ValidateMsgParam (*msg) == VLF_NO_ERROR )
   {
      // Send error if any of the channels (1-5) modes are active, not halted.
      // IBIT is not allowed if any of the channels are active.
      for (int chanNum=0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
      {
         if ((CVlf::Instance()->chan[chanNum]->mMode15->
               mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
             (CVlf::Instance()->chan[chanNum]->mMode9->
               mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
             (CVlf::Instance()->chan[chanNum]->mModeHidar->
               mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
             (CVlf::Instance()->chan[chanNum]->mMode23->
               mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) ||
             (CVlf::Instance()->chan[chanNum]->mModeSMA->
               mChanModeStatus.modeScanState != MODE_SEARCH_HALTED) )
         {
            // send message to DSP2 that we have a Mode In-Sync.
            // rsp_msg is initialized in the constructor
            CMessage rsp_msg;  // rsp msg
            rsp_msg.SetMsgId(VV_RUN_IBIT_REQUEST);
            rsp_msg.SetSrc(CVlf::Instance()->mId);
            rsp_msg.SetDest(DSP2);
            rsp_msg.SetActionId(msg->GetActionId());
            rsp_msg.SetDataLen(0);
            CMsgHandler::Instance()->SendMsg(&rsp_msg);

            // exit loop
            break;
         }//else nothing- do not send a message to DSP2
      }// end for loop
   }
   else
   {
      // Send software anamoly message to the OES
      // errStr is initialized in the constructor
      std::ostringstream errStr ( "" );  // error string
      errStr << "Invalid Msg Param, Msgid: "
             << msg->GetMsgId() << "ActionId: "
             << msg->GetActionId()
             << " (" << __FILE__ << " Line: " << __LINE__<< ")" << std::ends;
      send_sa_msg ( errStr.str().c_str() );
   }
}


//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
