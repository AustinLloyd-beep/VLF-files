
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVSetConfigParam.cpp
//
// Description:
//    This file contains the class definition for the COVSetConfigParam
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVSetConfigParam.h"
#include "CVlf.h"
#include "CMsgHandler.h"
#include "FpgaDeviceSingleton.h"
#include "FpgaIoDevice.h"
#include "TMemStrUtility.h"

extern MessageQueue queueCmd; // Local Address Space Shared Queue

////////////////////////////////////////////////////////////////////////////////
//! Function: COVSetConfigParam::ValidateMsgParam
//!
//! Description:
//!   This method validates the message parameters.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return:
//!    Msg_Error_Codes_Type
//!
//! Notes: Input parameters checked by calling function.
//!
////////////////////////////////////////////////////////////////////////////////
Msg_Error_Codes_Type COVSetConfigParam::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;   // error code

      Configuration_Params_Msg_Type* msgData =
         (Configuration_Params_Msg_Type*)&msg.GetMsgData()->theData;  // msg data

   // Check message data parameters, the header is checked when the
   // message is received
   if (((msgData->SM_NONAP_Bypass !=0) &&
        (msgData->SM_NONAP_Bypass != 1)) ||
       ((msgData->M9_EDAC_Enabled != 0) &&
        (msgData->M9_EDAC_Enabled != 1)) ||
       ((msgData->Auto_TimeLoad_Enabled != 0) &&
        (msgData->Auto_TimeLoad_Enabled != 1)) ||
       ((msgData->CEP_Enabled != 0) &&
        (msgData->CEP_Enabled != 1)) ||
       ((msgData->WB_Noise_Reduction_Enabled != 0) &&
        (msgData->WB_Noise_Reduction_Enabled != 1)) ||
       ((msgData->NB_Noise_Reduction_Enabled != 0) &&
        (msgData->NB_Noise_Reduction_Enabled != 1))
      )
   {
      error = PARAM_OUT_OF_RANGE;
   }
   else if (((msgData->WB_Limiter_Enabled != 0) &&
             (msgData->WB_Limiter_Enabled != 1)) ||
            ((msgData->M15_Letters_Case_Enabled != 0) &&
             (msgData->M15_Letters_Case_Enabled != 1)) ||
            ((msgData->M15_Msg_Filter_Enabled != 0) &&
             (msgData->M15_Msg_Filter_Enabled != 1)) ||
            ((msgData->M9_Msg_Filter_Enabled != 0) &&
             (msgData->M9_Msg_Filter_Enabled != 1)) ||
            ((msgData->MMPM_Framing_Advis_Enabled != 0) &&
             (msgData->MMPM_Framing_Advis_Enabled != 1)) ||
            ((msgData->M15_Msg_Piecing_Enabled != 0) &&
             (msgData->M15_Msg_Piecing_Enabled != 1)) ||
            ((msgData->Sync_Status_Bypass != 0) &&
             (msgData->Sync_Status_Bypass != 1))
           )
   {
      error = PARAM_OUT_OF_RANGE;
   }
   else if (((msgData->Print_Control_Chars_Enabled != 0) &&
             (msgData->Print_Control_Chars_Enabled != 1)) ||
            ((msgData->Print_Hamming_M9_Enabled != 0) &&
             (msgData->Print_Hamming_M9_Enabled != 1)) ||
            ((msgData->Auto_Gain_Enabled != 0) &&
             (msgData->Auto_Gain_Enabled != 1)) ||
            (msgData->Manual_Gain_Digi > MAX_MAN_GAIN_SIN) ||
            (msgData->Manual_Gain_Deci > MAX_MAN_GAIN_TRI) ||
            ((msgData->Manual_Gain_Expo < MIN_MAN_GAIN_SIN) ||
             (msgData->Manual_Gain_Expo > MAX_MAN_GAIN_SIN)) ||
            ((msgData->Timing_Offset < MIN_MAN_GAIN_DBL) ||
             (msgData->Timing_Offset > MAX_MAN_GAIN_DBL))
           )
   {
      error = PARAM_OUT_OF_RANGE;
   }
   else if (((msgData->Dither_Enabled != 0) &&
             (msgData->Dither_Enabled != 1)) ||
            ((msgData->Ant1_Test_Enabled != 0) &&
             (msgData->Ant1_Test_Enabled != 1)) ||
            ((msgData->Ant2_Test_Enabled != 0) &&
             (msgData->Ant2_Test_Enabled != 1)) ||
            ((msgData->RFA_Test_Enabled != 0) &&
             (msgData->RFA_Test_Enabled != 1)) ||
            ((msgData->KG_Bypass_Enabled != 0) &&
             (msgData->KG_Bypass_Enabled != 1)) ||
            ((msgData->SPECTRAL_PEAKS_Bypass != 0) &&
             (msgData->SPECTRAL_PEAKS_Bypass != 1)) ||
            ((msgData->VM23_Msg_Filter_Enabled != 0) &&
             (msgData->VM23_Msg_Filter_Enabled != 1)) ||
            ((msgData->Reserved8 != 0) &&
             (msgData->Reserved8 != 1))
           )
   {
      error = PARAM_OUT_OF_RANGE;
   }
   else
   {
      error = VLF_NO_ERROR;
   }

   return (error);
}
////////////////////////////////////////////////////////////////////////////////
//! Function: COVSetConfigParam::HandleMsg
//!
//! Description: This method handles a command from the OES to config
//!              parameters for mode processing.  Once DSP2 receives
//!              this message, it will send it to DSP1 and than to mode
//!              address space via the command queue for processing.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVSetConfigParam::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   ChannelCmdStruct* cmdBuffer = NULL;            // cmd buffer
   void* buffer = NULL;                           // buffer
   Configuration_Params_Msg_Type* msgData =
      reinterpret_cast<Configuration_Params_Msg_Type*> (msg->GetMsgData()->theData); // msg data

   Msg_Error_Codes_Type error = ValidateMsgParam (*msg);    // error
   Response_Status_Type status = NAK;             // status
   FpgaDeviceSingleton* fpgaDevice = FpgaDeviceSingleton::instance();  // FPGA device object

   if (error == VLF_NO_ERROR)
   {
      status = ACK;

      // store config params in CVLF
      memcpy_safe (&CVlf::Instance()->mConfigParms, msgData,
               sizeof(Configuration_Params_Msg_Type));

      if (msgData->WB_Noise_Reduction_Enabled)
      {
         fpgaDevice->SetUseAnbBit();
      }
      else
      {
          fpgaDevice->ClrUseAnbBit();
      }

      if (msgData->NB_Noise_Reduction_Enabled)
      {
         fpgaDevice->SetUseAnlBit();
      }
      else
      {
         fpgaDevice->ClrUseAnlBit();
      }

      if (msgData->WB_Limiter_Enabled)
      {
         fpgaDevice->SetLimitBit();
      }
      else
      {
         fpgaDevice->ClrLimitBit();
      }

      // dither
      if (msgData->Dither_Enabled)
      {
         fpgaDevice->SetRegDitherEn();
      }
      else
      {
         fpgaDevice->ClrRegDitherEn();
      }

      // ant 1 test
      if (msgData->Ant1_Test_Enabled)
      {
         fpgaDevice->SetRegAntTstEn1();
      }
      else
      {
         fpgaDevice->ClrRegAntTstEn1();
      }

      //ant 2 test
      if (msgData->Ant2_Test_Enabled)
      {
         fpgaDevice->SetRegAntTstEn2();
      }
      else
      {
          fpgaDevice->ClrRegAntTstEn2();
      }

      // rfa test
      if (msgData->RFA_Test_Enabled)
      {
         fpgaDevice->SetRegRfaTstEn();
      }
      else
      {
         fpgaDevice->ClrRegRfaTstEn();
      }

      //send out parameters to all channels
      for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
      {
         Error err = AllocateMessageQueueBuffer(queueCmd, (void**)&buffer);  // alloc buffer
         if (err == Success)
         {
            cmdBuffer = (ChannelCmdStruct*)buffer;
            cmdBuffer->channel = chanNum+1; //add for 1-5 channel
            cmdBuffer->cmd = CONFIG_PARAM_CMD;

            memcpy_safe (&cmdBuffer->cmdData.configParams, msgData,
               sizeof(Configuration_Params_Msg_Type));

            CHECK(SendOnMessageQueue (queueCmd, buffer),
               __FILE__, __FUNCTION__, __LINE__);
         }
         else
         {
            CHECK(err, __FILE__, __FUNCTION__, __LINE__);
            error = INT_COMM_ERROR;
            break;
         }
         CVlf::Instance()->chan[chanNum]->mCEPEnabled = msgData->CEP_Enabled;
      }// end for loop

   }// else nothing- parameters out of range

   // send ACK/Nak Message to OES
   CMsgHandler::Instance()->SendAckNak(msg->GetSrc(), msg->GetMsgId(),
                               msg->GetActionId(), status, error);
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
