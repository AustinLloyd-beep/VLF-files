
///////////////////////////////////////////////////////////////////////////////
//
// File Name: COVFPGAOutputSampleDataEnable.cpp
//
// Description:
//    This file contains the class definition for the COVFPGAOutputSampleDataEnable
//     Message.
//
// Notes: To create a message handler for a message,
//        a user implements the InterfaceHandler and overrides the
//        ValidateMsgParam() and HandleMsg() methods.
//
///////////////////////////////////////////////////////////////////////////////

#include "COVFPGAOutputSampleDataEnable.h"
#include "CVlf.h"
#include "CMsgHandler.h"
#include "FpgaDeviceSingleton.h"
#include "FpgaIoDevice.h"

////////////////////////////////////////////////////////////////////////////////
//! Function: COVFPGAOutputSampleDataEnable::ValidateMsgParam
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
Msg_Error_Codes_Type COVFPGAOutputSampleDataEnable::ValidateMsgParam(const CMessage& msg)
{
   Msg_Error_Codes_Type error = UNKNOWN_ERROR;      // error

   Sample_Output_Test_Enable_Msg_Type* msg_data =
      (Sample_Output_Test_Enable_Msg_Type*)&msg.GetMsgData()->theData;  // msg data

   // Check message data parameters, the header is checked when the
   // message is received
   if ( ((msg_data->channelID < 1) ||
         (msg_data->channelID > MAX_VLF_CHANNEL)) ||
        ((msg_data->count > MAX_16BIT_NUM) ||
         (msg_data->count == 0)) ||
        (msg_data->frequency > MAX_TESTING_FREQ) ||
        (msg_data->sampleAddr >= MAX_FPGA_ADDR)
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
//! Function: COVFPGAOutputSampleDataEnable::HandleMsg
//!
//! Description: This method handles the COVFPGAOutputSampleDataEnable message
//!              received from OES.
//!
//! Parameters:
//!    msg - Message class pointer
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void COVFPGAOutputSampleDataEnable::HandleMsg(CMessage* msg)
{
   if ( check4Null(msg, __FILE__, __LINE__) )
   {
      return;// All errors handled within check4Null
   }//else nothing- input parameter check ok

   Msg_Error_Codes_Type error = ValidateMsgParam (*msg); // error
   Response_Status_Type status = NAK;               // status

   // fill response data
   Sample_Output_Test_Enable_Msg_Type*  msg_data = // msg data
      (Sample_Output_Test_Enable_Msg_Type*)msg->GetMsgData()->theData;

   // validate params then use the message if all in range
   if (VLF_NO_ERROR == error)
   {
      status = ACK;

      //set test enable
      CVlf::Instance()->chan[msg_data->channelID-1]->mSampleOutputEnabled = true;

      // get latest FpgaDeviceSingleton info
      FpgaDeviceSingleton* fpgaDevice = FpgaDeviceSingleton::instance();

      // set the frequency in the fpga, range checked already
      if (msg_data->frequency != 0)
      {
         CVlf::Instance()->chan[msg_data->channelID-1]->SetChFreq(msg_data->frequency);
      } // else - no action required

      //set test duration option
      CVlf::Instance()->chan[msg_data->channelID-1]->mNum20msecs2send =
            msg_data->count;

      //
      // Load the Register Address in the FPGA to the Kernel FpgaIoDevice.
      //  This is done so that if the address of the FPGA memory map changes,
      //  There are no hard coded values to change in the Kernel driver
      switch (static_cast<FPGA_Sample_Address_Type>(msg_data->sampleAddr))
      {
         case ANTENNA1:
            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan1Address,
                  Value(fpgaDevice->RFA1_GetOutputSample1Address())),
               __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan2Address,
                  Value(fpgaDevice->RFA1_GetOutputSample2Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan3Address,
                  Value(fpgaDevice->RFA1_GetOutputSample3Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan4Address,
                  Value(fpgaDevice->RFA1_GetOutputSample4Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan5Address,
                  Value(fpgaDevice->RFA1_GetOutputSample5Address())),
                  __FILE__, __FUNCTION__, __LINE__);
            break;

         case ANTENNA2:
            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan1Address,
                  Value(fpgaDevice->RFA2_GetOutputSample1Address())),
               __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan2Address,
                  Value(fpgaDevice->RFA2_GetOutputSample2Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan3Address,
                  Value(fpgaDevice->RFA2_GetOutputSample3Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan4Address,
                  Value(fpgaDevice->RFA2_GetOutputSample4Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan5Address,
                  Value(fpgaDevice->RFA2_GetOutputSample5Address())),
                  __FILE__, __FUNCTION__, __LINE__);
            break;

         case ANTENNA3:
            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan1Address,
                  Value(fpgaDevice->RFA3_GetOutputSample1Address())),
               __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan2Address,
                  Value(fpgaDevice->RFA3_GetOutputSample2Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan3Address,
                  Value(fpgaDevice->RFA3_GetOutputSample3Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan4Address,
                  Value(fpgaDevice->RFA3_GetOutputSample4Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan5Address,
                  Value(fpgaDevice->RFA3_GetOutputSample5Address())),
                  __FILE__, __FUNCTION__, __LINE__);
            break;

         // set the address back to the default setting OMNI
         default:
            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan1Address,
               Value(fpgaDevice->GetOutputSample1Address())),
               __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan2Address,
                  Value(fpgaDevice->GetOutputSample2Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan3Address,
                  Value(fpgaDevice->GetOutputSample3Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan4Address,
                  Value(fpgaDevice->GetOutputSample4Address())),
                  __FILE__, __FUNCTION__, __LINE__);

            CHECK(WriteIODeviceRegister(FpgaIoDeviceObject_MGR, FpgaRegChan5Address,
                  Value(fpgaDevice->GetOutputSample5Address())),
                  __FILE__, __FUNCTION__, __LINE__);
            break;
      }

   }//else nothing- parameters out of range

   // send Ack/Nak Message to OES
   CMsgHandler::Instance()->SendAckNak(msg->GetSrc(), msg->GetMsgId(),
                            msg->GetActionId(), status, error);
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
