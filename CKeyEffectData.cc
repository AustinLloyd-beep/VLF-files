///////////////////////////////////////////////////////////////////////////////
// Class: CKeyEffectData
//
// File Name: CKeyEffectData.cc
//
// Description: This file contains the class methods for the CKeyEffectData
//              class.
//              This class contains the table, and functions to operate on the
//              table, that holds the Key Effective Date and Data Assoc with Key.
//
//              This file also includes functions used for operation of key
//              managment.
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include <sstream>
#include "CKeyEffectData.h"
#include "CVlf.h"
#include "CMsgHandler.h"
#include "CTimeLoad.h"
#include "TMemStrUtility.h"
#include "CControlVars.h"
#include "msg_defs.h"

extern MessageQueue queueKeyMgr;
////////////////////////////////////////////////////////////////////////////////
//! Function: Constructor
//!
//! Description: This method constructs the base mode object and initialize
//!              the class data
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
CKeyEffectData::CKeyEffectData(): whitespace_chars(" ")
{
   memset_safe (&mTEKRollover, false , sizeof(mTEKRollover));

   memset_safe(&mKeyDispMsgData, 0x00, sizeof(Key_Disposition_Status_Msg_Type));

   //set all values in table to zero
   initKeyEffectTable();
}

////////////////////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//!   This destructor method is used to cleanup the CKeyEffectData object
//!   once it is deleted.
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
CKeyEffectData::~CKeyEffectData()
{
   // if mInstance still exists, delete it
   if (mInstance != NULL)
   {
       delete mInstance;
       mInstance = NULL;
   }//else NULL - No action necessary
}
////////////////////////////////////////////////////////////////////////////////
//! Function: Instance
//!
//! Description:
//!   This method is used to obtain an instance of the CKeyEffectData
//!   class
//!
//! Parameters:
//!
//! Return:
//!   Pointer to CKeyEffectData object
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
CKeyEffectData* CKeyEffectData::Instance()
{
   if (mInstance == NULL)
   {
      mInstance = new CKeyEffectData;

      // Check to see of mInstance is NULL
      (void) check4Null(mInstance, __FILE__, __LINE__);
   } // else - no action required

   return mInstance;
}
CKeyEffectData* CKeyEffectData::mInstance = NULL;

////////////////////////////////////////////////////////////////////////////////
//! Function: initKeyEffectTable
//!
//! Description:
//!   This method is used to set the multi-dimentional array
//!   values to zero
//!
//! Parameters:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::initKeyEffectTable()
{
   // Clear out Effectivity Table contents
   for (int keyBank = 0; keyBank < MAX_NUM_KEY_BANKS; keyBank++)
   {
      for (int segLoc = 0; segLoc < MAX_TEKS_PER_BANK; segLoc++)
      {
         mKeyEffArray[keyBank][segLoc].valid = false;
         mKeyEffArray[keyBank][segLoc].keyPresent = false;
         mKeyEffArray[keyBank][segLoc].keyEffectDate.Year = 0;
         mKeyEffArray[keyBank][segLoc].keyEffectDate.Month = 0;
         mKeyEffArray[keyBank][segLoc].keyEffectDate.Day = 0;
         mKeyEffArray[keyBank][segLoc].keyEffectDay = 0;
         mKeyEffArray[keyBank][segLoc].keyShortTitle.clear();  //clear string
      }
   }

   // clears out search results
   memset_safe (&mSearchKeyEffectArray, 0, sizeof(mSearchKeyEffectArray));

   // create the filled bank array
   memset_safe (&filledKeyBanks, false, sizeof(filledKeyBanks));
}

////////////////////////////////////////////////////////////////////////////////
//! Function: searchKeyBankLoc
//!
//! Description:
//!   This is a helper method is used to obtain the key data info for a channel.
//!
//!
//! Parameters: Vlf_Channel_Type& cmpData
//!
//! Return: bool true/false
//!
//! Notes:
//!   In coming pointer checked by calling method
//!          searchEffectDate(Vlf_Channel_Type& cmpData
//!
////////////////////////////////////////////////////////////////////////////////
bool CKeyEffectData::searchKeyBankLoc( Vlf_Channel_Type& cmpData )
{
   bool found = false;   // return

   for ( unsigned int kBankLoc = 0; kBankLoc < MAX_NUM_KEY_BANKS; kBankLoc++ )  // loop thru banks
   {
      // If this bank does not contain a valid key, continue to the next bank
      if( !bankContainsKey( kBankLoc ) )
      {
         continue;
      } // else - no action required

      if ( searchKeyBankSegLoc( cmpData, kBankLoc ) )
      {
         found = true;
         break;
      }//else nothing- search not found
   }

   // clear out the search when no search found,
   if (!found)
   {
      mSearchKeyEffectArray[cmpData.channelID-1].keyBankLoc = 0;
      mSearchKeyEffectArray[cmpData.channelID-1].keyBankSegLoc = 0;
   }//else nothing- found item

   return found;
}

////////////////////////////////////////////////////////////////////////////////
//! Function: searchKeyBankSegLoc
//!
//! Description:
//!   This is a helper method is used to obtain the key data info for a channel.
//!   The commPlan contains both the short title and the channel number which are
//!   needed to search for the correct keybank/segment location and store the
//!   result for use by other functions.
//!
//! Parameters: Vlf_Channel_Type& - cmpData,
//!             unsigned int - kBankLoc
//!
//! Return: bool true/false
//!
//!   In coming pointer checked by original calling method
//!          searchEffectDate(Vlf_Channel_Type& cmpData
//!
////////////////////////////////////////////////////////////////////////////////
bool CKeyEffectData::searchKeyBankSegLoc( Vlf_Channel_Type& cmpData,
                                          unsigned int kBankLoc )
{
   bool found = false;  // return
   VlfTime vlfTime = CTimeLoad::Instance()->GetVlfTime();

   //perform string operations on the short title in cmpData
   std::string commStr(cmpData.keyShortTitle);
   commStr.erase(commStr.find_last_not_of(whitespace_chars)+1);

   for ( unsigned int segLoc = 0; segLoc < MAX_TEKS_PER_BANK; segLoc++ )  // loop thru segments
   {
      if ((mKeyEffArray[kBankLoc][segLoc].valid) &&
         (commStr.compare(mKeyEffArray[kBankLoc][segLoc].keyShortTitle) == 0) &&
         (mKeyEffArray[kBankLoc][segLoc].keyEffectDay == vlfTime.doy))
         {
            // Offset from the indices of keyBankLoc and keyBankSegLoc to align to real locations
            mSearchKeyEffectArray[cmpData.channelID-1].keyBankLoc = ( kBankLoc + KEY_BANK_IDX_FIRST );
            mSearchKeyEffectArray[cmpData.channelID-1].keyBankSegLoc = ( segLoc + MIN_KEY_BANK_SEG_LOC );
            found = true;
            break;
         }//else nothing- no match
   }
   return found;
}

////////////////////////////////////////////////////////////////////////////////
//! Function: searchEffectDate
//!
//! Description:
//!   This method is used to search through the array using Date,(mm/dd/yyyy) and
//!   CommPlan(channel number and short title). The methods called by this function
//!   are divided to search by keybank, then segment location.
//!
//!
//! Parameters: Vlf_Channel_Type& - cmpData,
//!
//! Return:
//!   bool true/false - based on valid search found
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
bool CKeyEffectData::searchEffectDate(Vlf_Channel_Type& cmpData)
{
   return searchKeyBankLoc(cmpData);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: checkForRollover
//!
//! Description:
//!   This method is used to check for a manual rollover event.  This is done by
//!   checking if a commPlan has been loaded, then checking the incoming data
//!   with the current TEK configuration, if there is a change,
//!   mark mTEKRollover.
//!
//! Parameters: Write_Key_Effectivity_Data_Msg_Type& - mData
//!
//! Return:
//!   None
//!
//! Notes:
//!   NONE
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::checkForRollover(Write_Key_Effectivity_Data_Msg_Type& mData)
{
   VlfTime vlfTime = CTimeLoad::Instance()->GetVlfTime();   // VLF time

   for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
   {
      if ((CVlf::Instance()->chan[chanNum]->mCommPlan.mode9 == true) ||
           (CVlf::Instance()->chan[chanNum]->mCommPlan.modeHIDAR == true) ||
           (CVlf::Instance()->chan[chanNum]->mCommPlan.mode23 == true) ||
           (CVlf::Instance()->chan[chanNum]->mCommPlan.modeSMA == true) )
      {
         for (int keyNum = 0; keyNum < mData.numKeys; keyNum++)  // loop thru keys
         {
            // If the incoming key is the one in use and has a new date
            // then manual rollover event has occured
            if ((((mSearchKeyEffectArray[chanNum].keyBankLoc) ==
                    (mData.KeyEffectData[keyNum].keyBankLoc)) &&
                 ((mSearchKeyEffectArray[chanNum].keyBankSegLoc) ==
                        (mData.KeyEffectData[keyNum].keyBankSegLoc))) &&
                  // check day of year
                  ((vlfTime.doy > getDayOfYear(mData.KeyEffectData[keyNum].keyEffectDate)) ||
                  (!mData.KeyEffectData[keyNum].keyValid)) )
            {
               mTEKRollover[chanNum] = true;
            }
            //else
            //   do nothing, key not in use
            //   do nothing, not time for rollover.
         }
      }
      //else
      //   do nothing, channel is not setup for special mode.
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: getDayOfYear
//!
//! Description:
//!   This method is used to convert the date format DD/MM/YYYY into Day Of Year
//!
//! Parameters: Date_Type date
//!
//! Return:
//!   UINT2 dayOfYear
//!
//! Notes:
//!   C/C++ tm structure uses 0-365, or  "days since January 1st" which means
//!    January 1st is day 0.  Need to add 1 to align with STOD
//!
//!   Ensure that all methods that need day of year uses this function to ensure
//!   consistency.
//!
////////////////////////////////////////////////////////////////////////////////
UINT2 CKeyEffectData::getDayOfYear (Date_Type date)
{
   UINT2 dayOfYear = 0;   // set to invalid day
   tm mLocTime = {0};     //time structure

   // Convert the stored tatt_msg to a time format
   // day of the month [1,31]
   mLocTime.tm_mday = date.Day;

   // months since Jan [0,11] subtract 1 from month
   mLocTime.tm_mon = date.Month - 1;

   // years since 1900
   mLocTime.tm_year = (date.Year - EPOCH_YEAR_VALUE);

   // adjust tm structure to get day of year
   if ( ((time_t)-1) != mktime(&mLocTime))
   {
      // add one to align "day of year" with "days sinse january 1st"
      dayOfYear = mLocTime.tm_yday + 1;
   }// else nothing- value already set

   return dayOfYear;
}

////////////////////////////////////////////////////////////////////////////////
//! Function: bankContainsKey
//!
//! Description:
//!   This method is used to check if a bank is empty
//!
//! Parameters: unsigned int bankIndex
//!
//! Return:
//!   bool containsKey
//!
//! Notes:
//!
////////////////////////////////////////////////////////////////////////////////
bool CKeyEffectData::bankContainsKey( unsigned int bankIndex )
{
   // Check the parameter before use
   return( ( bankIndex < MAX_NUM_KEY_BANKS ) && filledKeyBanks[bankIndex] );
}

////////////////////////////////////////////////////////////////////////////////
//! Function: setData
//!
//! Description:
//!   This method is used to store the key effectivity information sent in by the
//!   Write_Key_Effectivity_Data_Msg.  This method first checks to see if the
//!   new data contains changes to the currently in-use key entry
//!   (checkForRollover).  All data is then written to the table.
//!   All entries that are set to a date prior to the current system time
//!   will be discarded.  Then each channel will be checked to determine if a
//!   manual rollover event occured with the loading of the new table data.
//!
//! Parameters: Write_Key_Effectivity_Data_Msg_Type& - mData
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::setData(Write_Key_Effectivity_Data_Msg_Type& mData)
{
   checkForRollover(mData);

   // Process msg and load short title and date in Table
   for (int keyNum = 0; keyNum < mData.numKeys; keyNum++)  // loop thru keys
   {
      // set valid elements
      if ( mData.KeyEffectData[keyNum].keyValid )
      {
         // lower keyBankLoc and keyBankSegLoc to align with 0 array elements
         mKeyEffArray[(mData.KeyEffectData[keyNum].keyBankLoc - KEY_BANK_IDX_FIRST)]
                     [(mData.KeyEffectData[keyNum].keyBankSegLoc - MIN_KEY_BANK_SEG_LOC)].valid =
            mData.KeyEffectData[keyNum].keyValid;

         mKeyEffArray[(mData.KeyEffectData[keyNum].keyBankLoc - KEY_BANK_IDX_FIRST)]
            [(mData.KeyEffectData[keyNum].keyBankSegLoc - MIN_KEY_BANK_SEG_LOC)].keyEffectDate =
            mData.KeyEffectData[keyNum].keyEffectDate;

         mKeyEffArray[(mData.KeyEffectData[keyNum].keyBankLoc - KEY_BANK_IDX_FIRST)]
            [(mData.KeyEffectData[keyNum].keyBankSegLoc - MIN_KEY_BANK_SEG_LOC)].keyEffectDay =
            getDayOfYear(mData.KeyEffectData[keyNum].keyEffectDate);

         //clean up incoming string short title
         //trim all whitespace from the short title
         std::string inStr(mData.KeyEffectData[keyNum].keyShortTitle);
         inStr.erase(inStr.find_last_not_of( whitespace_chars )+1);

         mKeyEffArray[(mData.KeyEffectData[keyNum].keyBankLoc - KEY_BANK_IDX_FIRST)]
            [(mData.KeyEffectData[keyNum].keyBankSegLoc - MIN_KEY_BANK_SEG_LOC)].keyShortTitle = inStr;
      }
      // the element is no longer valid handle it
      else
      {
         if (!(mKeyEffArray[(mData.KeyEffectData[keyNum].keyBankLoc - KEY_BANK_IDX_FIRST)]
                           [(mData.KeyEffectData[keyNum].keyBankSegLoc - MIN_KEY_BANK_SEG_LOC)].keyPresent) )
         {
            clear_mKeyEffArrayElement((mData.KeyEffectData[keyNum].keyBankLoc - KEY_BANK_IDX_FIRST),
                                      (mData.KeyEffectData[keyNum].keyBankSegLoc - MIN_KEY_BANK_SEG_LOC));
         }
         //else there is a key present and the rollover task will do the cleanup
         else
         {
            // mark the table entry invalid
            mKeyEffArray[(mData.KeyEffectData[keyNum].keyBankLoc - KEY_BANK_IDX_FIRST)]
                        [(mData.KeyEffectData[keyNum].keyBankSegLoc - MIN_KEY_BANK_SEG_LOC)].valid =
               mData.KeyEffectData[keyNum].keyValid;
         }
      }
   }

   buildFilledBankMap();

   // Only perform rollover if this was the last write keys message
   if(mData.lastMsg)
   {
      // Clear out Effectivity Table of Outdated Entries.
      triggerMainKeyRolloverTask();
   } // else - no action required

   // Process any rollover events that are set for each channel
   for (int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru channels
   {
      if (mTEKRollover[chanNum])
      {
         rolloverEffectivity(chanNum);
      }
      //else - do nothing, rollover not needed.
   }
}
////////////////////////////////////////////////////////////////////////////////
//! Function: buildFilledBankMap
//!
//! Description:
//!   This method is used to build the map of filled banks, which can be used
//!   to skip banks that do not contain any valid keys in further operations.
//!
//! Parameters: None
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::buildFilledBankMap()
{
   bool foundKey = false;   // found flag

   // Check each key bank for valid keys
   for (int keyBank = 0; keyBank < MAX_NUM_KEY_BANKS; keyBank++)   // loop thru key banks
   {
      foundKey = false;

      for (int segLoc = 0; segLoc < MAX_TEKS_PER_BANK; segLoc++)  // loop thru segments
      {
         if ( (mKeyEffArray[keyBank][segLoc].valid) ||
              (mKeyEffArray[keyBank][segLoc].keyPresent))
         {
            foundKey = true;
            break;
         } // else - no action required
      }

      // Set the bank to filled if it contains a valid key, otherwise set to false
      filledKeyBanks[keyBank] = foundKey;
   }
}
////////////////////////////////////////////////////////////////////////////////
//! Function: setKeyPresent
//!
//! Description:
//!   This method is used to set the key present flag.  The purpose is to set the
//!   flag so that any key loaded in the unit and not in the effectivity table can
//!   be deleted.
//!
//! Parameters: mData - Loaded_Keys_Data_Msg_Type class pointer
//!
//! Return: None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::setKeyPresent(Loaded_Key_Info_Msg_Type& mData)
{
   // Process msg and load short title and date in Table
   for (int keyNum = 0; keyNum < mData.numKeys; keyNum++) // loop thruTEK array
   {
      mKeyEffArray[(mData.TEKs[keyNum].keyBankLoc -1)]
                  [(mData.TEKs[keyNum].keyBankSegLoc -1)].keyPresent = true;
   }
   buildFilledBankMap();

   // Clear out Effectivity Table of Outdated Entries.
   triggerMainKeyRolloverTask();
}

////////////////////////////////////////////////////////////////////////////////
//! Function: getData
//!
//! Description:
//!   This method is used to obtain the key data stored for each channel in a
//!   private variable located in the header file.  The data stored is a result
//!   to the searchEffectDate() method.
//!
//! Parameters: Channel_ID_Type chanID - [0-4]
//!
//! Return: Key_Bank_Info_Type - structure that holds keybank and segment loc
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
Key_Bank_Info_Type CKeyEffectData::getData( Channel_ID_Type chanID )
{
   // Initialize a "bad" return value
   Key_Bank_Info_Type lRetVal = { 0, 0, 0 };

   if ( ( chanID < 0 ) || ( chanID >= MAX_VLF_CHANNEL ) )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanID=" << chanID+1 << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   // Load the requested information
   else
   {
      lRetVal = mSearchKeyEffectArray[chanID];
   }

   return( lRetVal );
}

////////////////////////////////////////////////////////////////////////////////
//! Function: deleteData
//!
//! Description:
//!   This method is used when a selective zeroize ALL_TEKS action is
//!   sent by the HMI or CDE action from CDE_DATA_ERASURE message handling.
//!
//! Parameters: Selective_Zeroize_Keys_Msg_Type& - mData
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::deleteData( Selective_Zeroize_Keys_Msg_Type& mData )
{
   if ( ( mData.action == ALL_TEKS ) || ( mData.action == CDE ) )
   {
      //clear out Key Effectivity Table
      initKeyEffectTable();
   }
   //else nothing- do not update table
}

////////////////////////////////////////////////////////////////////////////////
//! Function: selectiveZeroizeCryptoKey
//!
//! Description:
//!   This method places the key bank and segment location on a buffer, and then
//!   the key_Mgr_Proc_Task will send the info on to the crypto.
//!
//! Parameters:
//!   Zeroize_Keys_Action_Type action - (SPECIFIC_TEK or CDE)
//!   unsigned int keyBank- the key bank index of the TEK [0,1, 3,4,5,6]
//!   unsigned int segLoc- the segment index of the TEK [0-99]
//!
//! Return:
//!   None
//!
//! Notes:
//!   None:
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::selectiveZeroizeCryptoKey( Zeroize_Keys_Action_Type action,
                                                unsigned int keyBank,
                                                unsigned int segLoc )
{
   Error error = Failure;             // error code
   Key_Bank_Info_Type *buffer = NULL; // message queue buffer

   // Input is an array index, 0-99
   if ( segLoc >= MAX_TEKS_PER_BANK )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (segLoc=" << segLoc << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   // KeyBank is an array index
   else if ( keyBank >= MAX_NUM_KEY_BANKS )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (keyBank=" << keyBank << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else
   {
      // create varaible and fill with data to be sent to crypto
      // if for deleting specific TEK add 1 to each item to remove array indexing
      Key_Bank_Info_Type keyInfo = {0};
      if ( SPECIFIC_TEK == action )
      {
         keyInfo.keyBankLoc = keyBank + KEY_BANK_IDX_FIRST;     // Offset from index to value
         keyInfo.keyBankSegLoc = segLoc + MIN_KEY_BANK_SEG_LOC; // Offset from index to value
      }
      // else action is CDE, keyInfo is already set to 0.

      CHECK (error = AllocateMessageQueueBuffer(queueKeyMgr,
        (void **)&buffer), __FILE__, __FUNCTION__, __LINE__);

      if (error == Success)
      {
         memcpy_safe (buffer, &keyInfo, sizeof(Key_Bank_Info_Type));
         CHECK( error = SendOnMessageQueue(queueKeyMgr, buffer)
            ,__FILE__, __FUNCTION__, __LINE__);
      }
      //else nothing- could not allocate buffer

      // if unable to send message to queue alert operator
      if ( error != Success )
      {
         // create disposition message and output to operator
         Key_Disposition_Status_Msg_Type KeyDispMsgData;     // status msg
         KeyDispMsgData.keyBankLoc = keyInfo.keyBankLoc;
         KeyDispMsgData.keyBankSegLoc = keyInfo.keyBankSegLoc;
         KeyDispMsgData.status = 0; // failure

         CMsgHandler::Instance()->SendPriMsg(VOKeyDispositionStatus.BuildDispMsg(KeyDispMsgData));
      }
      //else nothing- message sent on queue
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: clear_mKeyEffArrayElement
//!
//! Description:
//!   This method is used to clear the information out of the mKeyEffArray
//!   element.
//!
//! Parameters:
//!   unsigned int keyBank - the key bank index of the TEK [0,1,3,4,5,6]
//!   unsigned int segLoc - the segment index of the TEK [0-99]
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::clear_mKeyEffArrayElement( unsigned int keyBank,
                                                unsigned int segLoc )
{
   if ( keyBank >= MAX_NUM_KEY_BANKS )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (keyBank=" << keyBank << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else if ( segLoc >= MAX_TEKS_PER_BANK )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (segLoc=" << segLoc << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else
   {
      // Delete item from table
      mKeyEffArray[keyBank][segLoc].valid = false;
      mKeyEffArray[keyBank][segLoc].keyPresent = false;
      mKeyEffArray[keyBank][segLoc].keyEffectDate.Year = 0;
      mKeyEffArray[keyBank][segLoc].keyEffectDate.Month = 0;
      mKeyEffArray[keyBank][segLoc].keyEffectDate.Day = 0;
      mKeyEffArray[keyBank][segLoc].keyEffectDay = 0;
      mKeyEffArray[keyBank][segLoc].keyShortTitle.clear();  //clear string
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: configureCryptoChannel
//!
//! Description:
//!   This method is used to send configuration information to crypto
//!
//! Parameters: Channel_ID_Type - chanID [0-4]
//!
//! Return:
//!   None
//!
//! Notes:
//!   Requires a call to - searchEffectDate(Vlf_Channel_Type&)
//!   This method uses the last searchEffectDate() call that populated
//!   the mSearchKeyEffectArray[] for the chanID.
//!
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::configureCryptoChannel( Channel_ID_Type chanID )
{
   if ( ( chanID < 0 ) || ( chanID >= MAX_VLF_CHANNEL ) )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanID=" << chanID+1 << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else
   {
      CMsgHandler::Instance()->SendMsg( VCConfigureChannel.BuildConfigChanMsg( chanID, getData( chanID ) ) );
   }
}
////////////////////////////////////////////////////////////////////////////////
//! Function: runupCryptoChannel
//!
//! Description:
//!   This method is used to tell the crypto to runup channel
//!
//! Parameters: Channel_ID_Type - chanID [0-4]
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::runupCryptoChannel( Channel_ID_Type chanID )
{
   if ( ( chanID < 0 ) || ( chanID >= MAX_VLF_CHANNEL ) )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanID=" << chanID << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else
   {
      CMsgHandler::Instance()->SendMsg( VCRunupChannel.BuildRunupMsg( chanID ) );
   }
}
////////////////////////////////////////////////////////////////////////////////
//! Function: zeroizeCryptoChannel
//!
//! Description:
//!   This method is used to tell the crypto to zeroize channel data
//!
//! Parameters:  Channel_ID_Type - chanID [0-4]
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::zeroizeCryptoChannel( Channel_ID_Type chanID )
{
   if ( ( chanID < 0 ) || ( chanID >= MAX_VLF_CHANNEL ) )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanID=" << chanID+1 << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else
   {
      CMsgHandler::Instance()->SendMsg(VCZeroizeCryptoChannel.BuildZeroizeChanMsg( chanID ));
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: clear_mSearchKeyEffectArray
//!
//! Description:
//!   This method is used to clear out the current key bank and segment location
//!   for a channel.  Under normal conditions this is updated with new locations
//!   each start channel, and cleared when a channel is halted and the crypto has
//!   responded with a zeroize channel.
//!
//! Parameters:  unsigned int - chanID (0-4)
//!
//! Return:
//!   None
//!
//! Notes:
//!   This function is to be called only after the Crypto no longer needs key
//!   bank and segment location.  This will avoid a start channel setting the
//!   value while a halt channel clears out the value.
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::clear_mSearchKeyEffectArray( unsigned int chanID )
{
   if ( chanID >= MAX_VLF_CHANNEL )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanID=" << chanID+1 << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else
   {
      mSearchKeyEffectArray[chanID].keyBankLoc = 0;
      mSearchKeyEffectArray[chanID].keyBankSegLoc = 0;
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: createKeyEffectAlarmTimer
//!
//! Description:
//!   This method is used to create the alarm in the system clock.  This alarm
//!   will be an absolute timer that will repeat every day. Subsequent calls to
//!   this function will clear previous alarms.
//!
//! Parameters: None
//!
//! Return:
//!   None
//!
//! Notes:
//!   None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::createKeyEffectAlarmTimer()
{
   Time sysTime = {0,0};                     // system time
   const Time intTime = {NUM_SEC_PER_DAY,0}; // alarm interval
   time_t secTime = 0;                       // time in sec

   // Get System Clock Time and Format it for hours/minutes only
   GetClockTime(SystemClock, &sysTime);

   // Format System Time to remove all other seconds except those
   // used for hours, minutes, and seconds of current time
   // set absolute time that alarm will go off then add 2 seconds to ensure that
   //  the alarm will go off after time rollover
   secTime = (sysTime.Seconds +
             (NUM_SEC_PER_DAY - (sysTime.Seconds % NUM_SEC_PER_DAY)) + 1);

   // Create the time from now till the end of the day,
   // this assumes that crypto period is referenced in when the clock was set
   Time RolloverTimeOut = {secTime, 0};

   // create system alarm on system clock
   // the alarm will be set a repeating alarm indicated by the 'true' value
   CHECK(SetClockAlarm(SystemClock, true, &RolloverTimeOut, &intTime),
          __FILE__, __FUNCTION__, __LINE__);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: rolloverEffectivity
//!
//! Description:
//!   This method will determine if a channel is in-sync or active for SModes,
//!   For active channels the crypto will be sent a message to tear-down the
//!   channel, and then rebuild with the new key effectivity data, followed by
//!   a runup channel command. For those channels that are not active they will
//!   be sent only the zeorize and configure channel messages.  Mode15 in either
//!   state (active/halted) will not be effected by the changes.
//!
//! Parameters:
//!    chanNum - unsigned int to channel ID (0-4)
//!
//! Return: none
//!
//! Notes: All Start/Halt/Forced Halt channel operations are handled by
//!        sec_msg_proc_task, which is protected by a Semaphore.
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::rolloverEffectivity( unsigned int chanNum )
{
   if ( chanNum >= MAX_VLF_CHANNEL )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanNum: " << chanNum << " >= MAX_VLF_CHANNEL)."
          << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   // Process rollover event if Special Modes are not in_sync
   // Special note: SMA allows for bypass and forced rollover even if MODE_IN_SYNC with config params message
   else if ( ( CVlf::Instance()->chan[chanNum]->mMode9->mChanModeStatus.modeScanState != MODE_IN_SYNC ) &&
             ( CVlf::Instance()->chan[chanNum]->mModeHidar->mChanModeStatus.modeScanState != MODE_IN_SYNC ) &&
             ( CVlf::Instance()->chan[chanNum]->mMode23->mChanModeStatus.modeScanState != MODE_IN_SYNC ) &&
            (( CVlf::Instance()->chan[chanNum]->mModeSMA->mChanModeStatus.modeScanState != MODE_IN_SYNC ) ||
             ( CVlf::Instance()->mConfigParms.Sync_Status_Bypass ))
           )
   {
      // if SMA is MODE_IN_SYNC and Sync_Status_Bypass enabled send out info log
      if ( CVlf::Instance()->mConfigParms.Sync_Status_Bypass &&
           CVlf::Instance()->chan[chanNum]->mModeSMA->mChanModeStatus.modeScanState == MODE_IN_SYNC)
      {
         std::ostringstream str ( "" );  // string stream
         str << "VLF/LF INFORMATION LOG: "
             << "Sync_Status_Bypass Enabled (CH:" << chanNum+1 << " SMA MODE_IN_SYNC Status Bypassed "
             << "for Rollover)."
             << std::ends;
         send_sa_msg( str.str().c_str() );
      }//else nothing- do not log

      // If Channel is not halted, halt, zeroize crypto channel, configure
      // channel with new key bank and segment location, and then runup channel.
      if ( ( CVlf::Instance()->chan[chanNum]->mMode9->mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) ||
           ( CVlf::Instance()->chan[chanNum]->mModeHidar->mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) ||
           ( CVlf::Instance()->chan[chanNum]->mMode23->mChanModeStatus.modeScanState != MODE_SEARCH_HALTED ) ||
           ( CVlf::Instance()->chan[chanNum]->mModeSMA->mChanModeStatus.modeScanState != MODE_SEARCH_HALTED )
         )
      {
         performChannelSetup( chanNum );
      }
      // the channel is already halted, check now for key disposition options
      else
      {
         // Clear out Effectivity Table of Outdated Entries.
         triggerMainKeyRolloverTask();
      }
   }
   // SMode is In-Sync, so mark that it needs to be deleted later
   else
   {
      mTEKRollover[chanNum] = true;
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: performChannelSetup
//!
//! Description:
//!   This method will perfrom the operations required to setup a channel
//!   after a rollover event.  If no is TEK available, then the channel will
//!   remain in the halted state.  This only effects Special Modes.
//!
//! Parameters:
//!    chanNum - unsigned int to channel ID (0-4)
//!
//! Return: none
//!
//! Notes: All Start/Halt/Forced Halt channel operations are handled by
//!        sec_msg_proc_task, which is protected by a Semaphore.
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::performChannelSetup( unsigned int chanNum )
{
   Error condError = Failure;  // error code

   if ( chanNum >= MAX_VLF_CHANNEL )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanID=" << chanNum+1 << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   // Only restart the channel if it is active in SModes
   else if ( ( CVlf::Instance()->chan[chanNum]->mMode9->mChanModeStatus.modeScanState !=
               MODE_SEARCH_HALTED ) ||
             ( CVlf::Instance()->chan[chanNum]->mModeHidar->mChanModeStatus.modeScanState !=
               MODE_SEARCH_HALTED ) ||
             ( CVlf::Instance()->chan[chanNum]->mMode23->mChanModeStatus.modeScanState !=
               MODE_SEARCH_HALTED ) ||
             ( CVlf::Instance()->chan[chanNum]->mModeSMA->mChanModeStatus.modeScanState !=
               MODE_SEARCH_HALTED ) )
   {
      condError = TryToObtainSemaphore(CControlVars::Instance()->
         sec_msg_proc_struct[chanNum].sMsgAction);

      if ( Success == condError )
      {
         //pass in msg info to the secondary processing variable
         //we are within a semaphore, data ok to modify
         CControlVars::Instance()->sec_msg_proc_struct[chanNum].
            secProcMsg.msgActionID = UNSOLICIT_ACTION_ID;

         CControlVars::Instance()->sec_msg_proc_struct[chanNum].
            secProcMsg.msgAction = ACTIVATE_ROLLOVER;

         //send Condition and Release Semahpore
         SignalCondition(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].conAction);

         ReleaseSemaphore(CControlVars::Instance()->
            sec_msg_proc_struct[chanNum].sMsgAction);
      }
      else
      {
         // str is initialized in the constructor
         std::ostringstream str ( "" );  // string stream
         str << "VLF/LF RELIABILITY ERROR: "
             << __FILE__ << " Line: " << __LINE__ << " "
             << "Channel " << chanNum+1
             << " could not be restarted after Key Rollover." << std::ends;
         send_sa_msg ( str.str().c_str() );
      }
   }
   //else nothing- do not restart the channel
}

////////////////////////////////////////////////////////////////////////////////
//! Function: get_mTEKRollover
//!
//! Description:
//!   This is a get method for a private variable mTEKRollover.
//!
//! Parameters:
//!    chanNum - unsigned int reference to channel ID (0-4)
//!
//! Return: bool - true or false based on array
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
bool CKeyEffectData::get_mTEKRollover( unsigned int chanNum )
{
   bool rtnValue = false;   // return value

   if ( chanNum >= MAX_VLF_CHANNEL )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanNum=" << chanNum+1 << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else
   {
      rtnValue = mTEKRollover[chanNum];
   }

   return( rtnValue );
}

////////////////////////////////////////////////////////////////////////////////
//! Function: set_mTEKRollover
//!
//! Description:
//!   This is a set method for a private variable mTEKRollover.
//!
//! Parameters:
//!    chanNum - unsigned int reference to channel ID (0-4)
//!    valid - value to set mTEKRollover [true/false]
//!
//! Return:
//!   None
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::set_mTEKRollover( unsigned int chanNum,
                                       bool valid )
{
   if ( chanNum >= MAX_VLF_CHANNEL )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (chanNum=" << chanNum+1 << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else if ( ( false != valid ) && ( true != valid ) )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (valid=" << valid << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else
   {
      mTEKRollover[chanNum] = valid;
   }
}

////////////////////////////////////////////////////////////////////////////////
//! Function: checkLineItemInKeyTable
//!
//! Description:
//!   This method is used to check the line item in the Key Table to see if the
//!   key is active in any channel.  If no channel is using the key, the process
//!   of key disposition starts.
//!
//! Parameters:
//!    unsigned int keyBank - ref to the keybank location [0,1 & 3,4,5,6] array bounds
//!    unsigned int segLoc - ref to the segment location  [0-99] array bounds
//!
//! Return:
//!   None
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::checkLineItemInKeyTable( unsigned int keyBank,
                                              unsigned int segLoc )
{
   bool keyInUse = false;   // key in use flag

   if ( keyBank >= MAX_NUM_KEY_BANKS )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (keyBank=" << keyBank << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }
   else if ( segLoc >= MAX_TEKS_PER_BANK )
   {
      std::ostringstream str ( "" );  // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__ << " "
          << "Parameter out-of-range (segLoc=" << segLoc << ")." << std::ends;
      send_sa_msg( str.str().c_str() );
   }

   // search mSearchKeyEffectArray table for all channels to
   //  see if any channel is using the key.
   //  When a channel is started the table is filled in, when
   //  a channel is halted the table entry is deleted.
   for ( int chanNum = 0; chanNum < MAX_VLF_CHANNEL; chanNum++)  // loop thru key array
   {
      // Convert from array index
      if ( ( mSearchKeyEffectArray[chanNum].keyBankLoc == ( keyBank + KEY_BANK_IDX_FIRST ) ) &&
           ( mSearchKeyEffectArray[chanNum].keyBankSegLoc == ( segLoc + MIN_KEY_BANK_SEG_LOC ) ) )
      {
         keyInUse = true;
         break;
      }
      //else nothing- key does not match
   }

   // if the key is not in use AND
   // key is present
   if ( ( !keyInUse ) && ( mKeyEffArray[keyBank][segLoc].keyPresent ) )
   {
      // delete the table entry,
      // this will ensure that the message to delete the key is sent once
      // all errors in sending key will be sent to the operator and
      // a manual zeroization of the TEK will need to be performed.
      clear_mKeyEffArrayElement( keyBank, segLoc );

      //send Crypto Selective Zeroize TEK msg
      selectiveZeroizeCryptoKey( SPECIFIC_TEK, keyBank, segLoc );

   }//else nothing- do not delete key while in use
}

////////////////////////////////////////////////////////////////////////////////
//! Function: sendKeyDispMsg
//!
//! Description: The purpose of this function is to send the
//!              VO_KEY_DISPOSITION_STATUS message to the OES.
//!
//! Parameters:  None
//!
//! Return:  None
//!
//! Notes: This message is used to send the current key disposition status
//!        of the variable stored in this class.  It is used after the data to
//!        delete has been sent to the crypto.
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::sendKeyDispMsg()
{
   // fill message and send
   CMsgHandler::Instance()->SendPriMsg(VOKeyDispositionStatus.BuildDispMsg(getKeyDispData()));
}

////////////////////////////////////////////////////////////////////////////////
//! Function: setKeyDispData
//!
//! Description: The purpose of this function is to set the
//!              mKeyDispMsgData variable.
//!
//! Parameters:  unsigned int keyBankLoc
//!              unsigned int keyBankSegLoc
//!              Key_Disp_Status_Type status
//!
//! Return:  None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::setKeyDispData( unsigned int keyBankLoc,
                                     unsigned int keyBankSegLoc,
                                     Key_Disp_Status_Type status )
{
   mKeyDispMsgData.keyBankLoc = keyBankLoc;
   mKeyDispMsgData.keyBankSegLoc = keyBankSegLoc;
   mKeyDispMsgData.status = status;
}

////////////////////////////////////////////////////////////////////////////////
//! Function: setKeyDispData
//!
//! Description: The purpose of this function is to set the
//!              mKeyDispMsgData.status variable to PASS or FAILURE
//!
//! Parameters:  const Key_Disp_Status_Type& status
//!
//! Return:  None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::setKeyDispStatus( Key_Disp_Status_Type status )
{
   mKeyDispMsgData.status = status;
}

////////////////////////////////////////////////////////////////////////////////
//! Function: getKeyDispData
//!
//! Description: The purpose of this function is to return a pointer to the
//!              mKeyDispMsgData.
//!
//! Parameters:  None
//!
//! Return:  Key_Disposition_Status_Msg_Type pointer
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
Key_Disposition_Status_Msg_Type& CKeyEffectData::getKeyDispData()
{
   return (mKeyDispMsgData);
}

////////////////////////////////////////////////////////////////////////////////
//! Function: triggerMainKeyRolloverTask
//!
//! Description: The purpose of this function is to trigger the main key rollover
//!                task to start the key disposition process.
//!
//! Parameters:  None
//!
//! Return:  None
//!
//! Notes: None
//!
////////////////////////////////////////////////////////////////////////////////
void CKeyEffectData::triggerMainKeyRolloverTask()
{
   if ( Success == TryToObtainSemaphore( CControlVars::Instance()->sRolloverAction ) )
   {
      //send Condition and Release Semaphore
      SignalCondition( CControlVars::Instance()->conRolloverAction );
      ReleaseSemaphore( CControlVars::Instance()->sRolloverAction );
   }
   else
   {
      std::ostringstream str ( "" ); // string stream
      str << "VLF/LF RELIABILITY ERROR: "
          << __FILE__ << " Line: " << __LINE__
          << " Failure to get semaphore for Rollover Activation." << std::ends;
      send_sa_msg ( str.str().c_str() );
   }
}

////////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
////////////////////////////////////////////////////////////////////////////////
