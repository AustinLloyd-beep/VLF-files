///////////////////////////////////////////////////////////////////////////////
// Class: CVlf
//
// File Name: CVlf.cc
//
// Description: This file contains the class methods for the CVlf class.
//              this class contains the state and status of the VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#include "rc_bsp_defs.h"
#include "CVlf.h"
#include "VersionIoDevice.h"
#include "CMsgHandler.h"
#include "TMemStrUtility.h"
#include "CTimeload.h"
#include "RcvrStatusIoDevice.h"
#include "CControlVars.h"

///////////////////////////////////////////////////////////////////
//! Function: Constructor
//!
//! Description: This method constructs the base mode object and initialize
//!              the class data
//!
//! Parameters:
//!  None
//!
//! Notes:
//!  None
//!
///////////////////////////////////////////////////////////////////
CVlf::CVlf()
{
   mId = DSP1;
   mActiveOES = OES1;
   mCPLinkUp = false;
   mDSP2LinkUp = false;
   mMemoryClearRcvd = false;
   mDidCpFullOpOccur = false;

   versionEnum[0] = IODEV_VERSION_PROD;
   versionEnum[1] = IODEV_VERSION_BOOT;
   versionEnum[2] = IODEV_VERSION_DEPOT;
   versionEnum[3] = IODEV_VERSION_HW_SER;

   versionTitleString[0] = "DSP1 App SW Version";
   versionTitleString[1] = "DSP1 Boot SW Version";
   versionTitleString[2] = "DSP1 Depot SW Version";
   versionTitleString[3] = "DSP1 Serial Number";

   configString[0] = "0";
   configString[1] = "1";
   configString[2] = "2";
   configString[3] = "3";
   configString[4] = "4";
   configString[5] = "5";
   configString[6] = "6";
   configString[7] = "7";
   configString[8] = "8";
   configString[9] = "9";
   configString[10] = "10";
   configString[11] = "11";
   configString[12] = "12";
   configString[13] = "13";
   configString[14] = "14";
   configString[15] = "15";
   configString[CDspConfig::MAX_CONFIG_ITEMS] = "RSVD-DEFAULT TO 0";

   memset_safe (&mVersion, 0, sizeof(Version_Data_Msg_Type));
   memset_safe (&mRcvrStatus, 0 , sizeof(VLF_Receiver_System_Status_Msg_Type));
   memset_safe (&mDspPBit, 0xff, sizeof(BIT_Result_Type));
   memset_safe (&mDspCBit, 0xff, sizeof(BIT_Result_Type));

   // Get PROD Version Data.
   GetProdVersionData();
   SetConfigData();

   //initialize default mConfigParms
   memset_safe(&mConfigParms, 0, sizeof(Configuration_Params_Msg_Type));
   mConfigParms.SM_NONAP_Bypass              = false; // No_Bypass
   mConfigParms.M9_EDAC_Enabled              = false; // M9_EDAC disabled
   mConfigParms.Auto_TimeLoad_Enabled        = true;  // Enable Auto Time Load
   mConfigParms.CEP_Enabled                  = true;  // CEP Enabled
   mConfigParms.WB_Noise_Reduction_Enabled   = true;  // WB_Noise_Reduct enabled
   mConfigParms.NB_Noise_Reduction_Enabled   = true;  // NB_Noise_Reduct enabled
   mConfigParms.WB_Limiter_Enabled           = false; // set limit[true]/blank[flase] for WB Reduct
   mConfigParms.M15_Letters_Case_Enabled     = true;  // M15_Letters_Case enabled
   mConfigParms.M15_Msg_Filter_Enabled       = true;  // M15_Msg_Filter enabled
   mConfigParms.M9_Msg_Filter_Enabled        = true;  // M9_Msg_Filter enabled
   mConfigParms.MMPM_Framing_Advis_Enabled   = false; // Framing_Advis enabled
   mConfigParms.M15_Msg_Piecing_Enabled      = true;  // M15 Msg peicing disabled
   mConfigParms.Sync_Status_Bypass           = false; // No_Bypass
   mConfigParms.Print_Control_Chars_Enabled  = false; // Control_Chars disabled
   mConfigParms.Print_Hamming_M9_Enabled     = false; // Print_Hamming_M9 disabled
   mConfigParms.Auto_Gain_Enabled            = true;  // Auto_Gain enabled
   mConfigParms.Manual_Gain_Digi             = 1;     // floating point broken into three parts
   mConfigParms.Manual_Gain_Deci             = 0;     // Floating Point Decimal Part Number
   mConfigParms.Manual_Gain_Expo             = 0;     // Floating Point Exponent Part Number
   mConfigParms.Timing_Offset                = 0;     // no_offset
   mConfigParms.Dither_Enabled               = false; // Dither Diabled
   mConfigParms.Ant1_Test_Enabled            = false; // Ant1 test disabled
   mConfigParms.Ant2_Test_Enabled            = false; // Ant 2 test disabled
   mConfigParms.RFA_Test_Enabled             = false; // rfa test disabled
   mConfigParms.KG_Bypass_Enabled            = false; // bypass key usage in VM23
   mConfigParms.SPECTRAL_PEAKS_Bypass        = false; // No_Bypass
   mConfigParms.VM23_Msg_Filter_Enabled      = true;  // enable VM23 Msg Filter [UNCLASS EAMs ONLY]
   mConfigParms.Reserved8                    = false; // place holder

   // set the current VLFSTATE to INIT for Startup
   setState(&IVLFState::theInitState);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: GetProdVersionData
//!
//! Description:
//!   This method is used to retrieve production version data.
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
//! Notes:  When the Version Information is retrieved from the VersionIODevice,
//!         the string is NULL terminated.
//!
////////////////////////////////////////////////////////////////////////////////
void CVlf::GetProdVersionData()
{
   char VersionString[MAX_VERSION_LENGTH]; //VersionIoDevice.h

   // loop through parallel arrays to create all the version informations
   for (int verNum = 0; verNum < MAX_NUMBER_VERSIONS; verNum++)  // loop thru version
   {
      // copy version label into array
      (void) strncpy(mVersion.VersionInfo[verNum].Version_Title,
            versionTitleString[verNum], MAX_VERSION_TITLE_LENGTH);

      if (Success == ReadIODeviceStatus(VersionIoDeviceObject,
            versionEnum[verNum], VersionString, MAX_VERSION_LENGTH))
      {
         // see note in method description
         // copy version info into array
         (void) strncpy(mVersion.VersionInfo[verNum].Version_Data,
                  VersionString, MAX_VERSION_LENGTH);
         mVersion.numVersions++; // increment the number of versions
      }
      else
      {
         // see note in method description
         // copy verion info into array
         (void) strncpy(mVersion.VersionInfo[verNum].Version_Data,
              "UNKNOWN", MAX_VERSION_LENGTH);
         mVersion.numVersions++; // increment the number of versions
      }
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: SetConfigData
//!
//! Description:
//!   This method is used to set the Configuration data in mVersion.
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CVlf::SetConfigData()
{
   const unsigned int verNum = mVersion.numVersions;  // version #

   //Get DSP configuration
   (void)strncpy(mVersion.VersionInfo[verNum].Version_Title,
           "DSP1 Configuration", MAX_VERSION_TITLE_LENGTH);

   (void)strncpy(mVersion.VersionInfo[verNum].Version_Data,
           configString[mDspIOConfig.getEquipSelectConfig()], MAX_VERSION_LENGTH);

   mVersion.numVersions++; // increment the number of versions
}
///////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//!   This destructor method is used to cleanup the CVlf object
//!   once it is deleted.
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CVlf::~CVlf()
{
   int chanNum;    // channel num

   // delete the channel objects
   for (chanNum=0; chanNum<MAX_VLF_CHANNEL; chanNum++)
   {
      if (chan[chanNum] != NULL)
      {
         delete chan[chanNum];
         chan[chanNum] = NULL;
      }
      //else do nothing, channel is  null
   }
   // if mInstance still exists, delete it.
   if (mInstance != NULL)
   {
      delete mInstance;
      mInstance = NULL;
   }
   //else
   // do nothing, mInstance already deleted

}

///////////////////////////////////////////////////////////////////
//! Function: Instance
//!
//! Description:
//!   This method is used to obtain an instance of the CVlf
//!   class
//!
//! Parameters:
//!   None
//!
//! Return:
//!   Pointer to CVlf object
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
CVlf* CVlf::Instance()
{
   if (mInstance == NULL)
   {
      mInstance = new CVlf;

      // Check to see of mInstance is NULL
      (void) check4Null(mInstance, __FILE__, __LINE__);
   }
   //else
   // do nothing, mInstance is already initialized

   return mInstance;
}
CVlf* CVlf::mInstance;

////////////////////////////////////////////////////////////////////////////////
//! Function: UpdateRcvrStatus
//!
//! Description:
//!   This method is used to send the updated receiver status, time load and
//!   comm plan status to dsp2.
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void CVlf::UpdateRcvrStatus()
{
   VLF_Receiver_State_Msg_Type snd_data;  // send data
   memset_safe (&snd_data, 0, sizeof(VLF_Receiver_State_Msg_Type));

   // load current info into data variable
   snd_data.TimeLoaded = mRcvrStatus.TimeLoaded;
   snd_data.receiverState = mRcvrStatus.receiverState;
   snd_data.CommPlanLoaded = mRcvrStatus.CommPlanLoaded;
   snd_data.KeyTblLoaded = mRcvrStatus.KeyTblLoaded;

   // create message and load data to be sent
   CMessage rsp_msg;   // rsp msg
   rsp_msg.SetMsgId(VV_VLF_RECEIVER_STATE_MSGTYPE);
   rsp_msg.SetSrc(mId);
   rsp_msg.SetDest(DSP2);
   rsp_msg.SetActionId(0);
   (void) rsp_msg.SetMsgData(&snd_data, sizeof(VLF_Receiver_State_Msg_Type));

   // send message to DSP2
   CMsgHandler::Instance()->SendMsg(&rsp_msg);
}

///////////////////////////////////////////////////////////////////
//
// State Machine: All state change events come through this context.
//
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//! Function: setState
//!
//! Description:
//!   This method is used to set the state of the VLF receiver.
//!   It will then send a message to the Active OES to update status
//!
//! Parameters:
//!   ptr to IVLFState* object
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CVlf::setState(IVLFState* newState)
{
   if ( !check4Null(newState, __FILE__, __LINE__) )
   {
      mState = newState;
      mRcvrStatus.receiverState = mState->getState();

      // send DSP2 the Receiver State Message
      // If state is not Init, report the new state to the OES
      if (mRcvrStatus.receiverState != VLF_INITIALIZATION)
      {
         UpdateRcvrStatus();
      }
      //else
      //   do nothing, still initializing we do not want to send msg
   }//else nothing- error handled in if statement
}

///////////////////////////////////////////////////////////////////
//! Function: DSPCommunications
//!
//! Description:
//!   This method is used to change the VLF State
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CVlf::DSPCommunications()
{
   mState->DSPCommunications(this);
}

///////////////////////////////////////////////////////////////////
//! Function: ContBITUpdate
//!
//! Description:
//!   This method is used to change the VLF State
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
//! Notes:
//!   This method is called from CDspBIT::isDSP2LinkUp()
//!
///////////////////////////////////////////////////////////////////
void CVlf::ContBITUpdate()
{
   mState->ContBITUpdate(this);
}

///////////////////////////////////////////////////////////////////
//! Function: ChannelStateChange
//!
//! Description:
//!   This method is used to change the VLF State
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CVlf::ChannelStateChange()
{
   mState->ChannelStateChange(this);
}

///////////////////////////////////////////////////////////////////
//! Function: setTimeLoadedStatus
//!
//! Description:
//!   This method is used to cycle a channel state event to process
//!   time loaded for each channel.
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CVlf::setTimeLoadedStatus()
{
   for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
   {
      chan[chanNum]->LoadTime();
   }
}

///////////////////////////////////////////////////////////////////
//! Function: setTimeLoadedStatus
//!
//! Description:
//!   This method is used to set the status of the processed,
//!    key effectivity table.
//!
//! Parameters:
//!   status - true if key table is loaded
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CVlf::setKeyTblLoadedStatus(bool status)
{
   mRcvrStatus.KeyTblLoaded = status;
}

///////////////////////////////////////////////////////////////////
//! Function: getTimeLoadedStatus
//!
//! Description:
//!   This method is used to get the status of the processed,
//!    key effectivity table.
//!
//! Parameters:
//!   None
//!
//! Return:
//!   bool - true if key table is loaded
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
bool CVlf::getKeyTblLoadedStatus() const
{
   return mRcvrStatus.KeyTblLoaded == 0 ? false : true;
}

///////////////////////////////////////////////////////////////////
//! Function: CryptoStatusChange
//!
//! Description:
//!   This method is used to cycle a channel state event to process
//!   crypto change for each channel.
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CVlf::CryptoStatusChange()
{
   for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
   {
      chan[chanNum]->CryptoStatus();
   }
}

///////////////////////////////////////////////////////////////////
//! Function: CryptoChannelChange
//!
//! Description:
//!   This method is used to cycle a channel state event to process
//!   crypto change for individual channel.
//!
//! Parameters:
//!   None
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
///////////////////////////////////////////////////////////////////
void CVlf::CryptoChannelChange(Channel_ID_Type chanNum)
{
   if ((chanNum >= 0) && (chanNum < MAX_VLF_CHANNEL))
   {
      chan[chanNum]->CryptoChannelUpdate();
   }
   else
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanNum=" << chanNum << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
}


////////////////////////////////////////////////////////////////////////////////
//! Function: SendDSP2VersionData
//!
//! Description:
//!   This is the method that will send DSP2 Version information upon connection
//!   so server.
//!
//! Parameters:
//!    None
//!
//! Return: none
//!
//! Notes: The message data has been created when this class (CVlf)
//!        was constructed.  Just pass this info.
//!
////////////////////////////////////////////////////////////////////////////////
void CVlf::SendDSP2VersionData()
{
   //create out going message - then send
   CMessage rsp_msg;     // rsp msg
   rsp_msg.SetMsgId(VV_DSP1_VERSION_DATA_MSGTYPE);
   rsp_msg.SetSrc(CVlf::Instance()->mId);
   rsp_msg.SetDest(DSP2);
   rsp_msg.SetActionId(UNSOLICIT_ACTION_ID);
   (void) rsp_msg.SetMsgData(&mVersion, sizeof(Version_Data_Msg_Type));
   CMsgHandler::Instance()->SendMsg(&rsp_msg);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: setFpgaVersion
//!
//! Description:
//!   This method will set the FGPA version information in mVersion
//!
//! Parameters:
//!    const char* version - version info
//!
//! Return: none
//!
//! Notes: NULL Version Info is allowed and handled with UNKNOWN output
//!
////////////////////////////////////////////////////////////////////////////////
void CVlf::setFpgaVersion( const char* version )
{
   const unsigned int verNum = mVersion.numVersions;   // version #

   // copy version labed into array
   (void) strncpy(mVersion.VersionInfo[verNum].Version_Title,
         "DSP1 FPGA SW Version", MAX_VERSION_TITLE_LENGTH);

   //set the version info into the array
   // if the pointer is null, then set UNKNOWN as version info
   if ( (NULL == version) || (0 == strlen(version)) )
   {
      // copy verion info into array
      (void) strncpy(mVersion.VersionInfo[verNum].Version_Data,
           "UNKNOWN", MAX_VERSION_LENGTH);
      mVersion.numVersions++; // increment the number of versions
   }
   else
   {
      // copy verion info into array
      (void) strncpy(mVersion.VersionInfo[verNum].Version_Data,
               version, MAX_VERSION_LENGTH);
      mVersion.numVersions++; // increment the number of versions
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: CVlf::RestartChannelsAfterEventChg
//!
//! Description:
//!   This method handles the abililty to restart each channel as necessary after
//!   an event.  Each channel is restarted based on current comm plan
//!   configuration.  This function sends the RESTART_CHANNEL action
//!   to the secondary message processing task for each channel.
//!
//! Parameters:
//!    int - channel number
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void CVlf::RestartChannelsAfterEventChg(int& chanNum)
{
   Error condError = Failure;  // error code

   if ((chanNum >= MAX_VLF_CHANNEL) || (chanNum < 0))
   {
      // str is initialized in the constructor
      std::ostringstream str ( "" );   // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanNum=" << chanNum << ")." << std::ends;
      send_sa_msg ( str.str().c_str() );
   }
   else
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
            secProcMsg.msgAction = CP_CHAN_RESTART;

         //send Condition and Release Semaphore
         SignalCondition(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].conAction);

         ReleaseSemaphore(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].sMsgAction);
      }
      else
      {
         // str is initialized in the constructor
         std::ostringstream str ( "" );   // string stream
         str << "VLF/LF RELIABILITY ERROR: "
             << __FILE__ << " Line: " << __LINE__ << " "
             << "Channel " << chanNum+1
             << " could not be restarted after Time Load." << std::ends;
         send_sa_msg ( str.str().c_str() );
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
