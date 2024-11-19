///////////////////////////////////////////////////////////////////////////////
// Class: CKeyEffectData
//
// File Name: CKeyEffectData.h
//
// Description: This file contains the definition for the CKeyEffectData
//              class.
//              This class contains the table, and function to operate on the
//              table, that holds the Key Effective Date and Data Assoc with Key
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CKEYEFFECTDATA_H
#define CKEYEFFECTDATA_H

#include <string>

#include "msg_defs.h"
#include "CMessage.h"
#include "CCVLoadedKeyInfoMsg.h"
#include "COVWriteKeyEffectivityData.h"
#include "CVOKeyDispositionStatus.h"
#include "CVCRunupChannel.h"
#include "CVCZeroizeCryptoChannel.h"
#include "CVCConfigureChannel.h"

class CKeyEffectData
{
////////////////////////////////////////////////////////////////////////////////
//
// Local data structures
//
////////////////////////////////////////////////////////////////////////////////
private:

   typedef struct Key_Table_Data_Type
   {
      unsigned           valid         : 8;  //bool, validate entry
      unsigned           keyPresent    : 8;  //bool, key loaded in unit
      unsigned           keyEffectDay  : 16; // day of year key is effective
      Date_Type          keyEffectDate;      //date key is effective; 4 bytes
      std::string        keyShortTitle;      //24 bytes
   } Key_Table_Data_Type; // 34 bytes

////////////////////////////////////////////////////////////////////////////////
//
// Class Methods and Variables
//
////////////////////////////////////////////////////////////////////////////////
public:
   // static variables
   static CKeyEffectData *Instance();

   // key management methods
   void setData( Write_Key_Effectivity_Data_Msg_Type& mData );
   void deleteData( Selective_Zeroize_Keys_Msg_Type& mData );
   void setKeyPresent( Loaded_Key_Info_Msg_Type& mData);
   void rolloverEffectivity( unsigned int chanNum );
   bool searchEffectDate( Vlf_Channel_Type& cpData );
   void createKeyEffectAlarmTimer();
   bool get_mTEKRollover( unsigned int chanNum );
   void set_mTEKRollover( unsigned int chanNum, bool valid );
   void clear_mSearchKeyEffectArray( unsigned int chanID );
   int findCurrentYear();
   void triggerMainKeyRolloverTask();

   // function for key disposition
   void sendKeyDispMsg();
   void setKeyDispData( unsigned int keyBankLoc,
                        unsigned int keyBankSegLoc,
                        Key_Disp_Status_Type status );
   void setKeyDispStatus( Key_Disp_Status_Type status );

   // messages to CP for key management
   void selectiveZeroizeCryptoKey( Zeroize_Keys_Action_Type action,
                                   unsigned int keyBank,
                                   unsigned int segLoc );

   void configureCryptoChannel( Channel_ID_Type chanID );
   void runupCryptoChannel( Channel_ID_Type chanID );
   void zeroizeCryptoChannel( Channel_ID_Type chanID );

   // used by main_key_rollover_task
   Key_Table_Data_Type mKeyEffArray[MAX_NUM_KEY_BANKS][MAX_TEKS_PER_BANK];
   void checkLineItemInKeyTable( unsigned int keyBank, unsigned int segLoc );

   // used to set data values
   UINT2 getDayOfYear( Date_Type date );

   // used to check if a bank is empty
   bool bankContainsKey( unsigned int bankIndex );

private:
   CKeyEffectData();   // constructors
   ~CKeyEffectData (); // destructor
   CKeyEffectData(const CKeyEffectData&);
   CKeyEffectData& operator=(const CKeyEffectData&);

   // class variables
   static CKeyEffectData* mInstance;
   bool mTEKRollover[MAX_VLF_CHANNEL]; // For TEKS that have passed crypto period.
   bool filledKeyBanks[MAX_NUM_KEY_BANKS];
   const std::string whitespace_chars;       // white space char

   Key_Bank_Info_Type mSearchKeyEffectArray[MAX_VLF_CHANNEL];
   // Local buffer for key disposition message
   Key_Disposition_Status_Msg_Type mKeyDispMsgData;

   CVOKeyDispositionStatus VOKeyDispositionStatus; // VO_KEY_DISPOSITION_STATUS
   CVCRunupChannel VCRunupChannel; // VC_RUNUP_CHANNEL_MSGTYPE
   CVCZeroizeCryptoChannel VCZeroizeCryptoChannel; // VC_ZEROIZE_CHANNEL_MSGTYPE
   CVCConfigureChannel VCConfigureChannel; // VC_CONFIGURE_CHANNEL_MSGTYPE

   // class methods
   Key_Disposition_Status_Msg_Type& getKeyDispData();
   void performChannelSetup( unsigned int chanNum );
   void initKeyEffectTable();
   bool searchKeyBankLoc(Vlf_Channel_Type& cpData);
   bool searchKeyBankSegLoc(Vlf_Channel_Type& cpData, unsigned int kBankLoc);
   void checkForRollover(Write_Key_Effectivity_Data_Msg_Type& mData);
   void buildFilledBankMap();
   Key_Bank_Info_Type getData( Channel_ID_Type chanID );
   void clear_mKeyEffArrayElement( unsigned int keyBank, unsigned int segLoc );
};
#endif
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
