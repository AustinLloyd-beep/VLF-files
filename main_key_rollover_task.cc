///////////////////////////////////////////////////////////////////////////////
// TASK: Key Rollover Task (main_key_rollover_Task)
//
// File Name: main_key_rollover_Task.cc
//
// Description: The task handles the Continuous BIT testing that is activated
//              with a semiphore. This task will wait forever until it receives
//              the notification.  When the task receives the release it will
//              perform BIT tests as required.
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#include <INTEGRITY.h>
#include "KgrVpApp_integrate.h"
#include "CControlVars.h"
#include "CKeyEffectData.h"
#include "CTimeLoad.h"
#include "utility.h"
#include "CVlf.h"

void deleteDataBasedOnTime();
int findCurrentYear();

////////////////////////////////////////////////////////////////////////////////
//! Function: main_key_rollover_Task
//!
//! Description: This is the main body of the task.  It is called in the INT file
//!              as part of the OS startup.  This task is responsible for actions
//!              for deleting keys based on date from an ISR.
//!
//! Parameters:  None
//!
//! Return:  None
//!
//! Notes:
//!   This task performs the following functions:
//!
//!   1) This task will wait until the binary semiphore is released.
//!   2) It will perform all Key Disposition actions.
//!   3) repeat
//!
//!
////////////////////////////////////////////////////////////////////////////////
void main_key_rollover_Task ()
{
   Error condError = Failure;  // error code

   while ( true )
   {
      // set up the Condition Variable that will wait for trigger
      WaitForSemaphore(CControlVars::Instance()->sRolloverAction);
      {
         condError = WaitForCondition(CControlVars::Instance()->conRolloverAction,
                                  NULL, false);

         if ( Success == condError )
         {
            deleteDataBasedOnTime();
         }
         else
         {
            std::ostringstream str ( "" );  // string stream
            str << "VLF/LF RELIABILITY ERROR: "
                << __FILE__ << "Line: " << __LINE__
                << " Failure of WaitForCondition for Rollover Action." << std::ends;
            send_sa_msg ( str.str().c_str() );
         }
      }
      ReleaseSemaphore(CControlVars::Instance()->sRolloverAction);
   }//end task loop
}

////////////////////////////////////////////////////////////////////////////////
//! Function: findCurrentYear
//!
//! Description:
//!   Finds the current year by comparing each key bank and segment location's
//!   day of year with the current day of year.
//!
//! Parameters:  None
//!
//! Return: Current year
//!
//! Notes:
//!
////////////////////////////////////////////////////////////////////////////////
int findCurrentYear()
{
   VlfTime vlfTime = CTimeLoad::Instance()->GetVlfTime();  // VLF time
   bool found = false;  // found a year?
   int  temp = 0;       // holder for year search
   int  year = 0;       // return value

   // loop through effectivity table to find the current year
   for (int keyBank = 0; keyBank < MAX_NUM_KEY_BANKS; keyBank++)  // loop thru key banks
   {
      if (!found)
      {
         // If this bank does not contain a key, skip to the next bank
         if( (CKeyEffectData::Instance()->bankContainsKey(keyBank)) && (!found) )
         {
            for (int segLoc = 0; segLoc < MAX_TEKS_PER_BANK; segLoc++) // loop thru segments
            {
               if (CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].valid)
               {
                  // store the lowest year in any VALID key table entry
                  if ( ( (CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].keyEffectDate.Year > temp) && (0 == temp)) ||
                       (CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].keyEffectDate.Year < temp) )
                  {
                     temp = CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].keyEffectDate.Year;
                  }// else nothing -

                  if (CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].keyEffectDay == vlfTime.doy)
                  {
                     year = CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].keyEffectDate.Year;
                     found = true;
                     break;  //leave inner loop
                  }//else nothing-
               }//else nothing-
            }
         }// else nothing- bank does not have keys
      }
      else
      {
         break;  //leave outer loop
      }
   }

   if (!found)
   {
      year = temp;
   } // else - no action required


   return year;
}

////////////////////////////////////////////////////////////////////////////////
//! Function: deleteDataBasedOnTime
//!
//! Description:
//!   This method can be used to zeroize Effectivity Data based on date.
//!   This method is called at Crypto Period to clear out data previous to
//!   current system time.  This method loops through the keyEffectivity table
//!   to find the proper dates to delete.
//!
//! Parameters: none
//!
//! Return: none
//!
//! Notes: none
//!
////////////////////////////////////////////////////////////////////////////////
void deleteDataBasedOnTime()
{
   VlfTime vlfTime = CTimeLoad::Instance()->GetVlfTime();   // VLF time
   int year = findCurrentYear();  // year

   // loop through effectivity table and delete all entries with dates
   // previous to current system time.
   for ( unsigned int keyBank = 0; keyBank < MAX_NUM_KEY_BANKS; keyBank++ )  // loop thru key banks
   {
      // If this bank does not contain a key, skip to the next bank
      if ( CKeyEffectData::Instance()->bankContainsKey( keyBank ) )
      {
         for ( unsigned int segLoc = 0; segLoc < MAX_TEKS_PER_BANK; segLoc++ )  // loop thru segments
         {
            // check for valid key,
            // and that it has not already been marked for clear
            if (CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].valid)
            {
               // if the VLFTime.DOY is greater than the KeyEffetivityTable.DOY
               //  AND the year is equal between the two
               //  OR the year is 0 (meaning no current key element for today)
               if ( (CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].keyEffectDay < vlfTime.doy) &&
                    (CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].keyEffectDate.Year == year) )
               {
                  CKeyEffectData::Instance()->checkLineItemInKeyTable( keyBank, segLoc );
               }
               // if the DOY is greater than today AND the year is less than todays years
               // this case handles jan 1 and dec 31
               else
               {
                  if ((CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].keyEffectDay > vlfTime.doy) &&
                        (CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].keyEffectDate.Year < year))
                  {
                     CKeyEffectData::Instance()->checkLineItemInKeyTable( keyBank, segLoc );
                  }//else nothing-
               }
            }
            // key is marked invalid, but there is a key in the unit and the table is loaded,
            //  remove the key
            else
            {
               if ( ( CKeyEffectData::Instance()->mKeyEffArray[keyBank][segLoc].keyPresent) &&
                         ( CVlf::Instance()->getKeyTblLoadedStatus() ))
               {
                  CKeyEffectData::Instance()->checkLineItemInKeyTable( keyBank, segLoc );
               }
               //else do nothing, array element does not contain a valid key
            }
         }//end nested for loop
      }// else nothing bank does not have keys
   }//end for loop
}

//////////////////////////////////////////////////////////////////////////////
//
// Security classification:  UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////

