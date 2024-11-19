
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CCVCryptoSystemStatusMsg.cpp
//
// Description:
//    This file contains the class definition for the CCVCryptoSystemStatusMsg
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "CCVCryptoSystemStatusMsg.h"
#include "CVlf.h"
#include "CMsgHandler.h"
#include "CControlVars.h"
#include "ZeroizeIODevice.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: CCVCryptoSystemStatusMsg::ValidateMsgParam
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
Msg_Error_Codes_Type CCVCryptoSystemStatusMsg::ValidateMsgParam(const CMessage& msg)
{
   // No parameters to check so just pass no error
   return (VLF_NO_ERROR);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CCVCryptoSystemStatusMsg::HandleMsg
//!
//! Description:
//!   This method handles the CCVCryptoSystemStatusMsg message
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes:
//!    None
//!
////////////////////////////////////////////////////////////////////////////////
void CCVCryptoSystemStatusMsg::HandleMsg(CMessage* msg)
{
   bool RestartChannel = false;   // restart channel

   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   if ((ValidateMsgParam (*msg)) == VLF_NO_ERROR)
   {
      // set results into receiver system status
      Crypto_System_Status_Msg_Type* msgData =
           (Crypto_System_Status_Msg_Type*)msg->GetMsgData()->theData;   // get msg data

      if ( check4Null(msgData, __FILE__, __LINE__) )
      {
         return;// All errors handled within check4Null
      }//else nothing- input parameter check ok

      // if the current state is initialing and the new state is operational
      if ( ECU_OPERATIONAL == msgData->CMState.ECUState )
      {
         if ((ECU_INITIALIZATION == CVlf::Instance()->mRcvrStatus.CMState.ECUState) ||
             (ECU_ALARM == CVlf::Instance()->mRcvrStatus.CMState.ECUState))
         {
            // if this is the first time full op flag it
            if ( !CVlf::Instance()->mDidCpFullOpOccur )
            {
               CVlf::Instance()->mDidCpFullOpOccur = true;
            }
            // try to restart the channels as the CP might now be up after a restart
            else
            {
               RestartChannel = true;
            }
         } // else - no action required
      }//else nothing ECU not operational

      CVlf::Instance()->mRcvrStatus.CMState = msgData->CMState;

      for(int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
      {
         // only change state if different
         if (CVlf::Instance()->mRcvrStatus.chanStatus[chanNum].cryptoChanState !=
               msgData->cryptoChanState[chanNum])
         {
            // if the channel is active and the new status is idle halt channel
            // if the channel is in alarm halt the channel
            if ( ((CVlf::Instance()->mRcvrStatus.chanStatus[chanNum].cryptoChanState == CH_ACTIVE) &&
                  (msgData->cryptoChanState[chanNum] == CH_IDLE )) ||
                 ( msgData->cryptoChanState[chanNum] == CH_ALARM ))
            {
               // set channel status data store
               CVlf::Instance()->mRcvrStatus.chanStatus[chanNum].cryptoChanState =
                 msgData->cryptoChanState[chanNum];

               // send request to halt channel
               HaltChannelAfterCPChanChng(chanNum);
            }
            else
            {
               // set channel status data store
               CVlf::Instance()->mRcvrStatus.chanStatus[chanNum].cryptoChanState =
                 msgData->cryptoChanState[chanNum];
            }
         } // else - no action required

         // this might be another instance of the CP going FULL OP
         if ( RestartChannel )
         {
            CVlf::Instance()->RestartChannelsAfterEventChg(chanNum);
         }
         //else nothing- do not change state


      }//end for loop

      // Call State Transition Event
      CVlf::Instance()->CryptoStatusChange();

      // handle substate operations
      performECUSubstateOps(msgData->CMState.ECUSubstate);

   }
   else
   {
      // Send software anamoly message to the OES
      // errStr is initialized in the constructor
      std::ostringstream errStr ( "" );  // error string
      errStr << "Invalid Msg Param, Msgid: "
             << msg->GetMsgId() << "ActionId: "
             << msg->GetActionId() << " ("
             << __FILE__ << " Line: " << __LINE__<< ")" << std::ends;
      send_sa_msg ( errStr.str().c_str() );
   }
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CCVCryptoSystemStatusMsg::performECUSubstateOps
//!
//! Description:
//!   This method perfroms operations based on specific ECU Substates.
//!   Current Substates:
//!           ECU_ZEROIZE_DETECTED
//!           ECU_ZEROIZE_PASSED
//!           ECU_ZEROIZE_FAILED
//!           ECU_INTERLOCK_DETECTED
//!
//!
//! Parameters:
//!    substate - ECU substate
//!
//! Return:
//!    Msg_Error_Codes_Type
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void CCVCryptoSystemStatusMsg::performECUSubstateOps(const unsigned int& substate)
{
   // Handle Condition Variable for clear memory functions
   if ( ( substate == ECU_ZEROIZE_PASSED ) ||
        ( substate == ECU_ZEROIZE_FAILED ) ||
        ( substate == ECU_INTERLOCK_DETECTED ) )
   {
      if (Success != ReleaseSemaphore( CControlVars::Instance()->sClearMemAction ))
      {
         // Work with IODevice to clear memory
         CHECK(WriteIODeviceRegister(ZeroizeIODeviceObject, Value(ZEROIZE_REG),
                 Value(ZEROIZE_VALUE)), __FILE__, __FUNCTION__, __LINE__);
      }//else nothing- IODevice will handle the zeroization
   }
   //else nothing- no processing of substate required
}
////////////////////////////////////////////////////////////////////////////////
//! Function: CCVCryptoSystemStatusMsg::HaltChannelAfterCPChanChng
//!
//! Description:
//!   This method handles the abililty to halt each channel after a Crypto
//!   Channel state change has been detected.  This will prevent the Special
//!   Modes from sending mode data to the Crypto every 20msecs.
//!
//! Parameters:
//!    int - channel number
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void CCVCryptoSystemStatusMsg::HaltChannelAfterCPChanChng(const int& chanNum)
{
   Error condError = Failure;    // error condition

   //only halt the channel if it is active in SModes
   if (( CVlf::Instance()->chan[chanNum]->mMode9->
            mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) ||
       ( CVlf::Instance()->chan[chanNum]->mModeHidar->
            mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) ||
       ( CVlf::Instance()->chan[chanNum]->mMode23->
            mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) ||
       ( CVlf::Instance()->chan[chanNum]->mModeSMA->
            mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) )
   {

      condError = TryToObtainSemaphore(CControlVars::Instance()->
         sec_msg_proc_struct[chanNum].sMsgAction);

      if (Success == condError)
      {
         //pass in msg info to the secondary processing variable
         //we are within a semaphore, data ok to modify
         CControlVars::Instance()->sec_msg_proc_struct[chanNum].
            secProcMsg.msgActionID = UNSOLICIT_ACTION_ID;

         CControlVars::Instance()->sec_msg_proc_struct[chanNum].
            secProcMsg.msgAction = CP_CHAN_ALARM_HALT;

         //send Condition and Release Semaphore
         SignalCondition(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].conAction);

         ReleaseSemaphore(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].sMsgAction);
      }
      else
      {
         // str is initialized in the constructor
         std::ostringstream str ( "" ); // string stream
         str << "VLF/LF RELIABILITY ERROR: "
             << __FILE__ << " Line: " << __LINE__ << " "
             << "Channel " << chanNum+1
             << " could not be Halted after CP Channel State Change." << std::ends;
         send_sa_msg ( str.str().c_str()  );
      }
   }
   //else nothing- do not halt the channel
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
