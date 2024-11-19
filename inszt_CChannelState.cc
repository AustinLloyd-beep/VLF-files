/*
C++ TESTBED VERSION  : 9.8.5
FILE UNDER TEST  : "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CChannelState.cc"
DATE OF ANALYSIS : Tue Apr 11 10:49:39 2023
*/

////////////////////////////////////////////////////////////////////////////////
// Class: CChannelState
//
// File Name: CChannelState.cc
//
// Description: This file contains the class methods for the CVLFState class.
// this class contains the state pattern of the VLF receiver
//
// Notes: None
//
////////////////////////////////////////////////////////////////////////////////
#define QQQdialect GREEN__C99                                                                                                                                                                                                        
#undef QQQ146
#define QQQ148
#undef QQQbndchk
#define QQQ294
#undef QQQEMBEDDEDICE
 /* Note: for BITMAP execution histories QQQthreaded is not defined */
#undef QQQthreaded 
#define QQQdo178b
#undef QQQfixbra
#define QQQswitch3
#define QQQternary
#undef QQQswitch
#undef QQQmacrof
#undef QQQMULTIPROCESSEXH
#undef QQFLUSH
#undef QQNEWBS
#define qqqMaxBranchDepth     20
#define QQQstructbitmap
 static int qqqqbmselwidth =           32 ;
 static int zzfileid =     11;
#undef QQQALGONE
#undef QQQVCLFLG
#undef QQQFORKFL
#undef QQQIADDRF
#undef QQQRTI
#undef QQQPERFA
#undef QQQADRMOD
#undef QQQDCAPFL
#undef QQQTEMPLATEONLY
#define QQQNOATEXIT
#define QQQUPLOADATEND
#define QQQNOSTDIO
#undef QQQASHLINGVITRA
#define QQQBITMAP 
 #define qqqbitmapint unsigned int
#define QQQBITMAPMCDC 
#undef QQQTIC2XSERIALIO
#undef QQQTIC2XFLASH
#undef QQQCOMPRESSED_EXH
#undef QQQMAINFL
#define QQQSINGLEFILE
#define QQQFILEID
#define QQQseparate
extern int QQQindicator;
static int QQQfirstmcdc=1;
#define CChannelState_11zzopen                                                                                zzopen
 extern int CChannelState_11zzopen                                                                              ;
#define CChannelState_11zqqzqz1                                                                               zqqzqz1
#define QQQLDRA_PORT 
                                                                                                                                                                                                                                                                    
/***************** BEGIN INSTRUMENTATION OPTIONS CHECKS ******************/                                                                                                                                                                                         
#if defined(QQQTEMPLATEONLY)                                                                                                                                                                                                                                        
#error "Instrumentation option: 'Use I/O Template (for embedded systems)' is not currently supported with this TLP."                                                                                                                                                
#endif                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                    
#if defined(QQQCOMPRESSED_EXH) && !defined(QQQFIXEDSIZE)                                                                                                                                                                                                            
#error "Instrumentation option: 'Compress Execution History: Hitmap (Dynamic Alloc)' is not currently supported with this TLP."                                                                                                                                     
#endif                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                    
#if defined(QQQCOMPRESSED_EXH) && defined(QQQFIXEDSIZE)                                                                                                                                                                                                             
#error "Instrumentation option: 'Compress Execution History: Hitmap (Fixed Alloc)' is not currently supported with this TLP."                                                                                                                                       
#endif                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                    
#if defined(QQQBITMAP) && defined(QQQBITMAPMCDC) && !defined(QQQstructbitmap)                                                                                                                                                                                       
#error "Instrumentation option: 'Compress Execution History: Bitmap (Bitmap MC/DC)' is not currently supported with this TLP."                                                                                                                                      
#endif                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                    
#ifndef QQQSINGLEFILE                                                                                                                                                                                                                                               
#error "cppvals.dat flag 143 must be selected."                                                                                                                                                                                                                     
#endif                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                    
#ifdef QQQACCBMAPEXH                                                                                                                                                                                                                                                
#error "Instrumentation option: 'Accumulate Bitmap Execution Histories (Host/Host)' is not currently supported with this TLP."                                                                                                                                      
#endif                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                    
#ifdef QQQthreaded                                                                                                                                                                                                                                                  
#error "Instrumentation option: 'Thread ID in Execution History' is not currently supported with this TLP."                                                                                                                                                         
#endif                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                    
#ifdef QQQIADDRF                                                                                                                                                                                                                                                    
#error "Instrumentation option: 'Execution History to Memory Address' is not currently supported with this TLP."                                                                                                                                                    
#endif                                                                                                                                                                                                                                                              
/****************** END INSTRUMENTATION OPTIONS CHECKS *******************/                                                                                                                                                                                         
                                                                                                                                                                                                                                                                    
#ifndef QQQLDRA_PORT                                                                                                                                                                                                                                                
#error "Only LDRA_PORT is supported with this TLP."                                                                                                                                                                                                                 
#define FILEPOINT FILE * f,                                                                                                                                                                                                                                         
#else /* QQQLDRA_PORT */                                                                                                                                                                                                                                            
#define FILEPOINT                                                                                                                                                                                                                                                   
                                                                                                                                                                                                                                                                    
/*************************** BEGIN LDRA_PORT *****************************/                                                                                                                                                                                         
#ifdef QQQ_SHLAYOUT                                                                                                                                                                                                                                                 
static int tbrun_mode=1;                                                                                                                                                                                                                                            
#else                                                                                                                                                                                                                                                               
static int tbrun_mode=0;                                                                                                                                                                                                                                            
#endif /* QQQ_SHLAYOUT */                                                                                                                                                                                                                                           
#include "C:\LDRA_Toolsuite\Compiler_spec\Greenhills\Integrity_ppc\ldra_port.h"                                                                                                                                                                                     
#include "C:\LDRA_Toolsuite\Compiler_spec\Greenhills\Integrity_ppc\ldra_port_common.h"                                                                                                                                                                              
#ifndef QQQ_SHLAYOUT                                                                                                                                                                                                                                                
#ifdef QQQMAINFL                                                                                                                                                                                                                                                    
#include "C:\LDRA_Toolsuite\Compiler_spec\Greenhills\Integrity_ppc\ldra_port.c"                                                                                                                                                                                     
#include "C:\LDRA_Toolsuite\Compiler_spec\Greenhills\Integrity_ppc\ldra_port_common.c"                                                                                                                                                                              
#endif /* QQQMAINFL */                                                                                                                                                                                                                                              
#endif /* QQQ_SHLAYOUT */                                                                                                                                                                                                                                           
                                                                                                                                                                                                                                                                    
#if 0                                                                                                                                                                                                                                                               
#if defined(QQQstructbitmap)                                                                                                                                                                                                                                        
#error "Instrumentation option: 'Shared Memory' can currently only be used with Bitmap(Hitmap MC/DC) instrumentation."                                                                                                                                              
#endif                                                                                                                                                                                                                                                              
#define VAR_BITMAPARR static unsigned int* bitmaparr;                                                                                                                                                                                                               
#define VAR_AQQQMCDCSTORE static int* aqqqmcdcstore;                                                                                                                                                                                                                
#define VAR_AQQQMCDCSTR static int* aqqqmcdcstr;                                                                                                                                                                                                                    
#define VAR_AQQQSTR static int* aqqqstr;                                                                                                                                                                                                                            
#else                                                                                                                                                                                                                                                               
#define VAR_BITMAPARR static unsigned int bitmaparr[(qqqbranches/8)+1];                                                                                                                                                                                             
#define VAR_AQQQMCDCSTORE static int aqqqmcdcstore[QQQMAXMCDCSIZE];                                                                                                                                                                                                 
#define VAR_AQQQMCDCSTR static int aqqqmcdcstr[qqqbranches1];                                                                                                                                                                                                       
#define VAR_AQQQSTR static int aqqqstr[qqqbranches1];                                                                                                                                                                                                               
#endif /* 0 */                                                                                                                                                                                                                                                      
                                                                                                                                                                                                                                                                    
/* Forward Declaration */                                                                                                                                                                                                                                           
static void init_shared_memory(void);                                                                                                                                                                                                                               
/**************************** END LDRA_PORT *****************************/                                                                                                                                                                                          
#endif /* QQQLDRA_PORT */                                                                                                                                                                                                                                           
                                                                                                                                                                                                                                                                    
#ifndef QQQnumfil                                                                                                                                                                                                                                                   
#define QQQnumfil 40  /* default setting */                                                                                                                                                                                                                         
#endif /* QQQnumfil */                                                                                                                                                                                                                                              
#if defined(QQQstructbitmap) && defined(QQQSINGLEFILE)                                                                                                                                                                                                              
#ifndef LDRA_VOID_FUNC                                                                                                                                                                                                                                              
#define LDRA_VOID_FUNC                                                                                                                                                                                                                                              
  typedef void(*ldra_void_function)();                                                                                                                                                                                                                              
#endif                                                                                                                                                                                                                                                              
  extern "C" void qqpopulate_array_fcn_ptrQQ(int x, ldra_void_function y, ldra_void_function z);                                                                                                                                                                    
#if defined(QQQMAINFL)                                                                                                                                                                                                                                              
  int qqqshell_upload = 0;                                                                                                                                                                                                                                          
  int QQQfcn_ptr_num = 0;                                                                                                                                                                                                                                           
  static int qqqisinitialised = 0;                                                                                                                                                                                                                                  
  ldra_void_function qqqaccumupload[QQQnumfil];                                                                                                                                                                                                                     
  ldra_void_function qqqaccumreset[QQQnumfil];                                                                                                                                                                                                                      
  void qqqtotalupload(void);                                                                                                                                                                                                                                        
  void qqqtotalreset(void);                                                                                                                                                                                                                                         
  void qqpopulate_array_fcn_ptrQQ(int x, ldra_void_function y, ldra_void_function z) {                                                                                                                                                                              
    qqqaccumupload[x]=y;                                                                                                                                                                                                                                            
    qqqaccumreset[x]=z;                                                                                                                                                                                                                                             
    QQQfcn_ptr_num++;                                                                                                                                                                                                                                               
  }                                                                                                                                                                                                                                                                 
#else /* (QQQMAINFL) */                                                                                                                                                                                                                                             
  extern int QQQfcn_ptr_num;                                                                                                                                                                                                                                        
  extern ldra_void_function qqqaccumupload[QQQnumfil];                                                                                                                                                                                                              
  static int qqqstructzzopen = 0;                                                                                                                                                                                                                                   
#endif /* defined(QQQMAINFL) */                                                                                                                                                                                                                                     
#endif /* defined(QQQstructbitmap) && defined(QQQSINGLEFILE) */                                                                                                                                                                                                     
#if !defined(QQQSUPPRESS_UNDEF)                                                                                                                                                                                                                                     
#undef ldra_fprintf                                                                                                                                                                                                                                                 
#undef ldra_sscanf                                                                                                                                                                                                                                                  
#endif /* !defined(QQQSUPPRESS_UNDEF) */                                                                                                                                                                                                                            
#undef QQQHITMAP_STORAGE                                                                                                                                                                                                                                            
#undef qqnull_params                                                                                                                                                                                                                                                
#define qqnull_params void                                                                                                                                                                                                                                          
#define QQQ_PROTOTYPE_DEF                                                                                                                                                                                                                                           
  /* Conventional Instrumentation */                                                                                                                                                                                                                                
#undef QQ_ANSI_PROTOTYPE                                                                                                                                                                                                                                            
#define QQ_ANSI_PROTOTYPE 1                                                                                                                                                                                                                                         
#define QQQnumfil 40  /* default setting */                                                                                                                                                                                                                         
  static int qqxxswitch = 0;                                                                                                                                                                                                                                        
  static int qqyyswitch = 0;                                                                                                                                                                                                                                        
  static unsigned char qqqzzglobflag = 0;                                                                                                                                                                                                                           
  static struct bitmapstruct_t                                                                                                                                                                                                                                      
  {                                                                                                                                                                                                                                                                 
#define ELEMENT(N) qqqbitmapint element##N;                                                                                                                                                                                                                         
#define LASTELEMENT                                                                                                                                                                                                                                                 
#include "CChannelState_11zbelem.def"                                                                                                                                                                                                                               
#undef ELEMENT                                                                                                                                                                                                                                                      
#undef LASTELEMENT                                                                                                                                                                                                                                                  
  } bitmapstruct = {                                                                                                                                                                                                                                                
#define ELEMENT(N) 0,                                                                                                                                                                                                                                               
#undef LASTELEMENT                                                                                                                                                                                                                                                  
#include "CChannelState_11zbelem.def"                                                                                                                                                                                                                               
#undef ELEMENT                                                                                                                                                                                                                                                      
  0};                                                                                                                                                                                                                                                               
  static void qqoutput(FILEPOINT char* s,int i);                                                                                                                                                                                                                    
  static void qqoutput2(FILEPOINT char* s, int i, int j);                                                                                                                                                                                                           
  static void qqoutput3(FILEPOINT char* s, int i, int j, int k);                                                                                                                                                                                                    
  static void qqoutput4(FILEPOINT char* s, int i, int j, int k, int l);                                                                                                                                                                                             
  static void qqoutput0(FILEPOINT char* s);                                                                                                                                                                                                                         
  static int qqswitchxx(qqnull_params);                                                                                                                                                                                                                             
  static int qqswitchyy(qqnull_params);                                                                                                                                                                                                                             
  static int uuswitchqq(qqnull_params);                                                                                                                                                                                                                             
  static int CChannelState_11zqqzqz(qqnull_params);                                                                                                                                                                                                                 
  static int CChannelState_11zqqzqz1(qqnull_params);                                                                                                                                                                                                                
  static int CChannelState_11zqendz (int qqqi);                                                                                                                                                                                                                     
  static int CChannelState_11zqzqzq (int qqqi);                                                                                                                                                                                                                     
  static int CChannelState_11zzdo17 (int dummy, int a, int b);                                                                                                                                                                                                      
  static void qqqupload(qqnull_params);                                                                                                                                                                                                                             
  static void qqqbitmapreset(qqnull_params);                                                                                                                                                                                                                        
  static int CChannelState_11zscanf (char* qqscan_str);                                                                                                                                                                                                             
/* ------------------------------ END OF TESTBED PROTOTYPES -------------------------------- */                                                                                                                                                                     
                                                                                                                                                                                                                                                                    
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CVlf.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2020, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
// Class: CVlf
//
// File Name: CVlf.h
//
// Description: This file contains the definition for the vlf class
// this class contains the state and status of the VLF receiver
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CVLF_H
#define CVLF_H
#include <INTEGRITY.h>
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CChannel.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2019, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
// Class: CChannel
//
// File Name: CChannel.h
//
// Description: This file contains the definition for the channel class
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCHANNEL_H
#define CCHANNEL_H
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CMode.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2020, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CMode.h
//
// Description:
// This file contain the class definition for the base Mode class
// and the derived mode classes (CMode15, CMode9, and CModeHIDAR)
//
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CMODE_H
#define CMODE_H
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\VPCommon\chan_struct.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2020, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// File Name: chan_struct.h
//
// Description: This file contains the common data structures used to send
// command and status messages between the Manager and Channels
// AddressSpace.
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CHAN_STRUCT_H
#define CHAN_STRUCT_H
#include <INTEGRITY.H>
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpBsp\FpgaIoDevice.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2020, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//!
//! Class: FpgaIoDevice
//!
//! File Name: FpgaIoDevice.h
//!
//! Description: INTEGRITY IODevice Driver that is responsible for gathering
//! FPGA Output Sample Data when the IRQ2 Interrupt from the the
//! FPGA goes off. It is also responsible for loading and reporting
//! accurate time when commanded by the VLF Control. FPGA
//! initialization and control is done by the FpgaDevice companion
//! class located in the 'FpgaDevice.h' file.
//!
//! Notes: This IODevice is based on the information contained in the Document
//! "Rockwell Collins, Inc. Design Implmentation Guide for the VLF
//! Digital Tuner FPGA"
//!
//! This IODevice Driver assumes all the source addresses (FPGA Output
//! Samples) and all the destination addresses (shared MemoryRegions) are
//! loaded into the IODevice before this IODevice Driver begins to gather
//! data or initialize time load. The IODevice Driver will not work if one
//! or more of the source/destination address are not properly addressed.
//!
//! The task that is working with this IODevice driver, via a
//! INTERRUPT_IODeviceNotifyTask call, must wait at least 110 msec,
//! 55*20 msec, before it begins to process the Output Samples. This
//! will give the IODevice Driver time to fill all the destination
//! address with valid data.
//!
///////////////////////////////////////////////////////////////////////////////
//! The ANI buffers will be sized in units of OUT_SAMPLE_SIZE. A buffer
//! that is sized to hold 1 second of data would require 50 OUT_SAMPLE_SIZE.
//!
//! Each channel is buffered separately. Previously (MMRT and MRT) interleaved
//! the complex ANI samples (TE, TMFA, TMLR). This is no longer done since each
//! antenna channel (TE, TMFA, TMLR) will be divided up by FPGA.
//!
//! The number of bytes to store 1 OUT_SAMPLE_SIZE of complex samples from 1
//! channel from one of the FPGAs is:
//!
//! (3200 samp/sec) * 2 (complex) * 4 (bytes per word) / 50 = 512 bytes = 0x200
//! = 128 long words (or int)
///////////////////////////////////////////////////////////////////////////////
#ifndef FPGAIODEVICE_H
#define FPGAIODEVICE_H
#include "INTEGRITY_types.h"
#define OUT_SAMPLE_SIZE 128
//! GPIO MAX BIT
#define BIT00 0x80000000
//! Number of FPGA Channels.
#define NUM_CHANNELS 5
//! number of status elements that can be read
#define NUM_TIMELOAD_STATUS_ELEMENTS 4
#define NUM_TIME_STATUS_ELEMENTS 4
#define NUM_TATT_STATUS_ELEMENTS 4
 
enum Chan_ID_Type
{
  CH1 = 0 ,
  CH2 = 1 ,
  CH3 = 2 ,
  CH4 = 3 ,
  CH5 = 4
} ;
 
typedef
  enum
  {
    CmdLoadTime = 0 ,
                    // Load time command
    CmdReportAccy = 1 ,
                      // Report time accuracy
    CmdRunPpsBit = 2 ,
                     // Run Pps Pbit
    CmdStopPpsBit = 3 ,
                      // End Pps Pbit
    CmdLoadStodTime = 4// Load Time with STOD
  } TimeLoadCmd ;
              // Time load commands
 
typedef
  enum
  {
    TimeNotLoaded = 0 ,
    WaitingFor1PPS = 1 ,
    WaitingFor1Sec = 2 ,
    WaitingForStod = 3 ,
    WaitingForTATT = 4 ,
    WaitingForMPulse = 5 ,
    TimeLoaded = 6
  } TimeLoadState ;
                // time loading states
 
typedef
  enum
  {
    PpsNoState = 0 ,
    TestingFor1PPS = 1
  } PpsTestState ;
               // time loading states
 
typedef
  enum
  {
    ShortPulse = 1 ,
    ManualPulse = 2
  } PulseType ;
            // 1PPS pulse width
 
typedef
  enum
  {
    NoError = 0 ,
    ErrNoPPSInterrupt = 1 ,
    ErrNo1SecInterrupt = 2 ,
    Err20MsecInterruptFault = 3 ,
    Err1SecInterruptFault = 4 ,
    ErrWatchdogInterrupt = 5 ,
    ErrTimeLoadWarning = 6 ,
    ErrNoTATTMessageReceived = 7 ,
    ErrNoManualPulseReceived = 8 ,
    ErrNoStodReceived = 9 ,
    ErrTimeAccFault = 10 ,
    MaxErr
  } TimeLoadError ;
                // TimeLoad error
 
typedef
struct VlfTime
{
  unsigned int sec ;
  unsigned short frames ;
  unsigned short doy ;
  unsigned short offset ; // value cannot exceed 3200 decimal
} VlfTime ;
 
enum IO_Signal
{
  low = 0 ,
  high = 1
} ;
//! Pseudo FPGA Register used with IODevice ReadRegister/WriteRegister
 
enum FpgaRegister
{
  FpgaRegMemRegion1Address = 0 ,
  FpgaRegMemRegion2Address = 1 ,
  FpgaRegMemRegion3Address = 2 ,
  FpgaRegMemRegion4Address = 3 ,
  FpgaRegMemRegion5Address = 4 ,
  FpgaRegChan1NumOfSamples = 5 ,
  FpgaRegChan2NumOfSamples = 6 ,
  FpgaRegChan3NumOfSamples = 7 ,
  FpgaRegChan4NumOfSamples = 8 ,
  FpgaRegChan5NumOfSamples = 9 ,
  FpgaRegChan1Address = 10 ,
  FpgaRegChan2Address = 11 ,
  FpgaRegChan3Address = 12 ,
  FpgaRegChan4Address = 13 ,
  FpgaRegChan5Address = 14 ,
  FpgaRegIrqAddress = 15 ,
  FpgaRegTimePm = 16 ,
  FpgaRegoffSet1ppsAddress = 17 ,
  FpgaRegIrqCtrlAddress = 18 ,
  FpgaRegCntAt1PPSAddress = 19 ,
  FpgaRegRfaAdcStatusAddress = 20 ,
  FpgaRegTODMinSecAddress = 21 ,
  FpgaRegTODHrsAddress = 22 ,
  FpgaRegTODDoYAddress = 23 ,
  FpgaMaxReg
} ;
//! Structure used to determine where the FPGA data is
//! going from/to and how big the destination buffer is.
 
typedef
  struct
  {
    volatile int * src ;
    volatile int ( * dest ) [ 128 ] ;
    unsigned short int numOfSamples ;
    unsigned short int currentIndex ;
    unsigned short int nextIndex ;
  } OutputSampleAddressFrom ;
//! Structure used to gather performance monitoring
//! timing data that could be used to check the reliability
//! of the 20 msec interrupt by BIT.
#define NUM_IRQ2_READINGS 100
 
typedef
  struct
  {
    unsigned int count ;
    unsigned int index ;
    unsigned int readings [ 100 ] ;
    Boolean on ;
  } TimeDiagRecorderData ;
//
//! FPGA Time format
//!
//! these typedefs must be PACKED
#pragma pack (1)
 
typedef
struct bcdTimeStruct
{
  unsigned BCD_VALUE1 : 4 ; // (0:3)
  unsigned BCD_VALUE2 : 4 ; // (4:7)
  unsigned BCD_VALUE3 : 4 ; // (8:11)
  unsigned BCD_VALUE4 : 4 ; // (12:15)
} bcdTimeStruct ;
#pragma pack ()
// end PACKED
 
union bcdTimeUnion
{
  UINT2 regVal ;
  bcdTimeStruct bits ;
} ;
//! Structure that contains data about the FPGA IODevice.
 
typedef
  struct
  {
    OutputSampleAddressFrom channel [ 5 ] ;
    volatile unsigned short int * irqReg ;
    volatile unsigned short int * irqCtrlReg ;
    volatile unsigned short int * cntAt1PPSReg ;
    volatile unsigned short int * offSet1ppsReg ;
    volatile unsigned short int * rfaStatusReg ;
    volatile unsigned short int * todMinSecReg ;
    volatile unsigned short int * todHrsReg ;
    volatile unsigned short int * todDoYReg ;
    int reportCount ;
    TimeDiagRecorderData irq2Readings ;
  } FpgaIoDeviceDataForm ;
//! Structure that contains data for Time Load.
 
typedef
  struct
  {
    TimeLoadState state ;
                        // Time load states
    TimeLoadError err ;
                      // Time load errors
    TimeLoadError ppsErr ;
                         // pps errors
    PpsTestState ppsState ;
                          // pps state
    TimeLoadError stodErr ;
    int timeAdjust ;// used to adjust time from TOD message to what is
                            // loaded at the 1 sec interrupt
    VlfTime gpsTime ;
                    // From TOD message except frames
    VlfTime vlfTime ;
                    // locally maintained time
    VlfTime stodTime ;
                     // fpga stod maintained time
    VlfTime stodTimePrev ;
                         // fpga stod maintained time previous value
    int enable1SecIntCntDwn ;// count 20msec interrupts from 1PPS
                            // interrupt to enable 1 sec interrupt
    int enableTATTCntDwn ;// need a TATT msg before this counts down to 0 else
                            // a fault is declared
    int enableManPulseCntDwn ;// need a Manual Pulse for time load before this
                            // counts down to 0 else a fault is declared
    int enablePpsErrCntDwn ;// need a 3 PPScounts before this counts
                            // down to 0 else a fault is declared
    int enableSTODCntDwn ;// need STOD data before this counts
                            // down to 0 else a fault is declared
    unsigned int ctr20msec ;// counts 0 to 50 to detect problems with the 20
                            // msec or 1 sec interrupt
    unsigned int ctr1sec ;
                         // counts the number of 1 second interrupts
    unsigned int ctr1pps ;
                         // counts the number of 1PPS interrupts
    unsigned int ctrWatchDog ;
                            // counts the number of watchdog interrupts
    unsigned int num20MsecDiscarded ;
                                    // number of discarded 20 msec interrupts
    unsigned int old1SecTimeStamp ;// 32 bit lower timebase value from
                                  // previous 1 sec interrupt
    unsigned int new1SecTimeStamp ;// 32 bit lower timebase value from
                                  // current 1 sec interrupt
    unsigned int ppsTimeStamp ;// 32 bit lower timebase value when
                                  // 1pps interrupt occurred
    PulseType pulseLoadType ;
                            // 1PPS pulse type indicator
    unsigned int errPulseCntr ;
                              // Acc counts in error
  } TimeLoadDataForm ;
//! functions for working with GPIO
 
unsigned int
  inword (
  unsigned long addr ) ;
 
void
  outword (
  unsigned long addr ,
  unsigned int data ) ;
 
void
  set_GPIO (
  unsigned int GPIO_Number ,
  enum IO_Signal set_pin ) ;
 
void
  short_delay (
  unsigned int cpu_cycles ) ;
       //FPGAIODEVICE_H
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpBsp\FpgaIoDevice.h*/
/*   CLOSE_FILE Include File */
 
#include "KgrVpApp_integrate.h"
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\VPCommon\channel_defs.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2020, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// File Name: channel_defs.h
//
// Description: This file contains the common data structures used to send
// command and status messages between the Manager and Channels
// AddressSpace.
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CHAN_DEFS_H
#define CHAN_DEFS_H
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\mode_defs.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2022, Collins Aerospace, All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// File Name: mode_defs.h
//
// Description: Used with the mode code to move messages between
// the three processors.
//
// Notes: Notes this is a common file for all modes shared data items
//
///////////////////////////////////////////////////////////////////////////////
#ifndef MODE_DEFS_H
#define MODE_DEFS_H
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\SAMPLE_TYPE.h */
///////////////////////////////////////////////////////////////////////////////
//! Copyright 2020-2022, Collins Aerospace. All rights reserved.
//! Collins Aerospace Proprietary Information
//!
//! Security classification: UNCLASSIFIED//FOUO
//!
///////////////////////////////////////////////////////////////////////////////
//!
//! namespace: SAMPLE_TYPE
//!
//! File Name: SAMPLE_TYPE.h
//!
//! Description: Provide error handling functions for messaging over the ethernet.
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////////////////
#ifndef SAMPLE_TYPE_H
#define SAMPLE_TYPE_H
#include <complex>
namespace SAMPLE_TYPE {
 
static const unsigned int
  BUFFER_SAMPLE_SIZE = 512 ;
 
static const int
  HALF_COMPLEX_DATA_SIZE = 32 ;               // process half the samples
 
static const int
  COMPLEX_DATA_SIZE = 64 ;               // process 64 complex samples
 
typedef
std :: complex < int >
  FPGADataType ;                        // complex [real/imag] type
// this is used for union items. std::complex<> is not allowed in union
 
typedef
struct Complex
{
  float re ;
  float im ;
} Complex ;
}
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\SAMPLE_TYPE.h*/
/*   CLOSE_FILE Include File */
 
#include <complex>
#include <stdint.h>
//******************************************************************************
// Contants definitions
//******************************************************************************
 
static const unsigned int
  N_P1CP_DATA = 5 ;                        // P1CP data
 
static const unsigned int
  N_CPP2_DATA = 4 ;                        // CPP2 data
 
static const unsigned int
  N_CHIPS_32 = 32 ;                        // #of chips
 
static const unsigned int
  MAX_SYMS = 181 ;                        // max symbols
 
static const unsigned int
  DEFAULT_ZERO = 0 ;                        // default value
#define MAX_RADIO_FREQ_HZ 60000.0f
// Fine Sync Adjustment
 
static const int
  Decrease_Delay = - 1 ;              // decrement counter
 
static const int
  Delay_Unchanged = 0 ;               // level counter
 
static const int
  Increase_Delay = + 1 ;
                                      // increment counter
// 32 complex samples/20 msec * 50 20msec interval * 2 buffers = 3200 samples per second
// buffer length is 1 second
 
static const unsigned int
  SAMPLE_LENGTH_OF_SM_CHIP_FILTER_BUFFER = 3200 ;
 
static const int
  MS_PER_FRAME = 20 ;
                                    // 20msec value
//******************************************************************************
// System Delays
//******************************************************************************
 
static const unsigned int
  NONAP_PROCESSING_STARTUP_DELAY_IN_MS = 1000 ;
//Required separation between read & write pointers on any buffer for which
//Fine_Sync_Adjustments is performed. Requirements based on analysis of
//following situation: Rcvr acquires sync at a maximum range (6400 nautical
//miles) and flies toward xmtr (requires 3.3 hours at 1950 knots, 8 hours
//at 800 knots). A delay adjustment of +40ms would be required during trip
//to hold the the key delay position found at outset. Same is true for
//reverse situation with sync at min range and receiver moves away from
//transmitter
 
static const unsigned int
  FINE_SYNC_ADJ_READ_WRITE_PTR_COORDINATION_DELAY_IN_MS = 40 ;
//Total delay expected for NONAP Startup
 
static const unsigned int
  COMBINED_NONAP_STARTUP_DELAY_INTERVALS =
  (
  ( NONAP_PROCESSING_STARTUP_DELAY_IN_MS /
  MS_PER_FRAME ) + ( FINE_SYNC_ADJ_READ_WRITE_PTR_COORDINATION_DELAY_IN_MS /
  MS_PER_FRAME ) ) ;
//works out to 0..50+2 = 0..52 ---only 52 intervals used, zero is
// ---starting position only
//******************************************************************************
// Enumerations definitions
//******************************************************************************
 
enum P1CP_Cmd_Type
{
  P1CP_NONE = 0 ,
  TRANSFER_PARAMETERS1 = 1 ,
  KEYSTARTTIME_NODATA = 2 ,
  M9_CHIPSPRESENT = 3 ,
  M9_HALT_NODATA = 4 ,
  HIDAR_CHIPSPRESENT = 5 ,
  HIDAR_HALT_NODATA = 6 ,
  PM_ENABLE1 = 7 ,
  COMM_PLAN1 = 8 ,
  MODE_PARAMS_REQUEST = 9 ,
  VM_SAMPLESPRESENT = 10 ,
  VM_HALT_NODATA = 11 ,
  SMA_CHIPSPRESENT = 12 ,
  SMA_HALT_NODATA = 13
} ;
 
enum CPP2_Cmd_Type
{
  CPP2_NONE = 0 ,
  TRANSFER_PARAMETERS2 = 1 ,
  M9_INIT_WITHSYMBOLS = 2 ,
  M9_CONTINUE_WITHSYMBOLS = 3 ,
  M9_HALT_NOSYMBOLS = 4 ,
  HIDAR_INIT_WITHSYMBOLS = 5 ,
  HIDAR_CONTINUE_WITHSYMBOLS = 6 ,
  HIDAR_HALT_NOSYMBOLS = 7 ,
  PM_ENABLE2 = 8 ,
  COMM_PLAN2 = 9 ,
  RESERVED1 = 10 ,
  NONAP_PARAM_DATA = 11 ,
  OTHER_PARAM_DATA = 12 ,
  RESERVED2 = 13 ,
  VM_INIT_NOSAMPLES = 14 ,
  VM_CONTINUE_WITHSAMPLES = 15 ,
  VM_HALT_NOSAMPLES = 16 ,
  SMA_INIT_WITHSYMBOLS = 17 ,
  SMA_CONTINUE_WITHSYMBOLS = 18 ,
  SMA_HALT_NOSYMBOLS = 19
} ;
 
enum P2P1_Cmd_Type
{
  P2P1_None = 0 ,
  M9_FineSync = 1 ,
  M9_Sync_Status = 2 ,
  HIDAR_FineSync = 3 ,
  HIDAR_Sync_Status = 4 ,
  Set_Msg_Indicator = 5 ,
  NONAP_Parameters = 6 ,
  VM_Sync_Status = 7 ,
  SMA_Sync_Status = 8
} ;
 
enum Param_Cmd_Type
{
  PARAM_NONE = 0 ,
  HIDAR_ORI_PARAM = 1 ,
  HIDAR_ADD_1 = 2 ,
  HIDAR_ADD_2 = 3 ,
  HIDAR_ADD_3 = 4 ,
  MAX_HIDAR_CMD = 5 ,
  MMPM_ORI_PARAM = 6 ,
  MMPM_ADD_1 = 7 ,
  MMPM_ADD_2 = 8 ,
  MMPM_ADD_3 = 9 ,
  MAX_MMPM_CMD = 10
} ;
//Absolute_Time_Type to be sent each message
 
typedef
struct Absolute_Time_Type
{
  unsigned short Hours : 16 ; //0..23
  unsigned short Minutes : 16 ; //0..59
  unsigned short Seconds : 16 ; //0..59
  unsigned short Frames : 16 ; //0..49
} Absolute_Time_Type ;
///////////////////////////////////////////////////////////////////////////////
// CP Ethernet Message Structures for Correlation and Parameter Messages.
///////////////////////////////////////////////////////////////////////////////
// DSP1 to CP data type
 
typedef
struct P1CP_Data_Type
{
  float Power ;
  SAMPLE_TYPE :: Complex Chips32 [ N_CHIPS_32 ] ;
} P1CP_Data_Type ;
//CP to DSP2 data type
 
typedef
struct CPP2_Data_Type
{
  unsigned short int SM9_Corr_Sym_Index ;
  unsigned char HIDAR_Mark ;
  unsigned char HIDAR_Segment ;
  float Power ;
  SAMPLE_TYPE :: Complex Syms [ MAX_SYMS ] ;
} CPP2_Data_Type ;
// DSP1 to CP operational data type
 
typedef
struct P1CP_Operational_Data_Type
{
  Absolute_Time_Type TimeOfDay ;
  P1CP_Data_Type P1CP_Data [ N_P1CP_DATA ] ;
} P1CP_Operational_Data_Type ;
 
static const unsigned int
  N_PARAMETER_BYTES =
  (
  ( sizeof ( P1CP_Data_Type )
   ) * N_P1CP_DATA ) ;
 
typedef
unsigned char
  P1CP_Parameter_Data_Type [ N_PARAMETER_BYTES ] ;
 
static const unsigned int
  NONAP_PARAMETER_ELEMENTS = 23 ;                        // number of elements in crypto file
 
typedef
int
  NONAP_Parameter_Data_Type [ NONAP_PARAMETER_ELEMENTS ] ;
 
static const unsigned int
  CL_N_PARAMETER_BYTES = 92 ;                        // largest msg size in bytes from CP classified_params.h
 
typedef
unsigned char
  CPP2_Parameter_Data_Type [ CL_N_PARAMETER_BYTES ] ;
// data to be sent from DSP1 to CP
 
typedef
struct P1CP_Interface_Type
{
  P1CP_Cmd_Type Command ;
  union data
  {
    P1CP_Operational_Data_Type opData ;
    P1CP_Parameter_Data_Type paramData ;
  } data ;
} P1CP_Interface_Type ;
// CP to DSP2 operational data type
 
typedef
struct CPP2_Operational_Data_Type
{
  Absolute_Time_Type TimeOfDay ;
  CPP2_Data_Type CPP2_Data [ N_CPP2_DATA ] ;
} CPP2_Operational_Data_Type ;
// data to be sent from CP to DSP2
 
typedef
struct CPP2_Interface_Type
{
  CPP2_Cmd_Type Command ;
  union data
  {
    CPP2_Operational_Data_Type opData ;
    P1CP_Parameter_Data_Type paramData ;
  } data ;
} CPP2_Interface_Type ;
// data to be sent from DSP2 to DSP1
 
typedef
struct P2P1_Interface_Type
{
  P2P1_Cmd_Type Command : 32 ;
  int Data : 32 ;
} P2P1_Interface_Type ;
//////////////////////////////////////////////////////////////////////////////
//
// General Mode Types and Variables
//
//////////////////////////////////////////////////////////////////////////////
//! soft decision processing type
 
static const unsigned int
  Baudot_SD_Char_Size = 5 ;
 
typedef
float
  Baudot_SD_Char_Type [ Baudot_SD_Char_Size ] ;
//! type used for holding quality bit data
 
static const unsigned int
  NUM_QUALITY_BITS = 2 ;                        // Start and stop bits
 
typedef
float
  Quality_Bit_Type [ NUM_QUALITY_BITS ] ;
 
static const unsigned int
  FIGURE_SHIFT_VAL = 27 ;
 
static const unsigned int
  LETTER_SHIFT_VAL = 31 ;
// shift mode type
 
typedef
enum Shift_Mode_Type
{
  LETTER_SHIFT = 0 ,
  FIGURE_SHIFT = 1
} Shift_Mode_Type ;
////////////////////////////////////////////////////////////////////////////////
//
// Classified Parameter Structures and Variables
//
////////////////////////////////////////////////////////////////////////////////
// structure to interface with ada,
// this must match structure located in Mode_msgs.ads
 
typedef
struct Classified_Interface_Type
{
  CPP2_Cmd_Type Command : 32 ;
  CPP2_Parameter_Data_Type paramData ;
} Classified_Interface_Type ;
 
static const unsigned int
  ClassifiedInterfaceTypeHeaderSize = sizeof ( CPP2_Cmd_Type ) ;
//////////////////////////////////////////////////////////////////////////////
//
// VM Structures and Variables
//
//////////////////////////////////////////////////////////////////////////////
// VERDIN mode key constants
 
static const unsigned int
  VM_INTERVAL_SAMPLES = 8 ;                        // number of VM23 samples per 20 ms
 
static const unsigned int
  VM_SAMPLES = VM_INTERVAL_SAMPLES * N_P1CP_DATA ;
 
static const unsigned int
  NUM_VM_CHANNELS = 4 ;                        // number of VM23 channels
// VERDIN mode message data constants
 
static const unsigned int
  Max_Number_VM_Chars_Per_Transfer = 16 ;
 
typedef
struct VM_Data_Output_Type
{
  char vmData [ Max_Number_VM_Chars_Per_Transfer ] ;
  Baudot_SD_Char_Type sd_data [ Max_Number_VM_Chars_Per_Transfer ] ;
  Quality_Bit_Type quality_bits [ Max_Number_VM_Chars_Per_Transfer ] ;
} Verdin_Data_Buffer_Type ;
 
typedef
struct VM_CH_Key_Type
{
  float keySample [ NUM_VM_CHANNELS ] ;
} VM_CH_Key_Type ;
 
typedef
struct VM_Data_Type
{
  SAMPLE_TYPE :: Complex VM_FOB [ VM_INTERVAL_SAMPLES ] ;
} VM_Data_Type ;
 
typedef
struct VM_Key_Data_Type
{
  VM_CH_Key_Type VM_Key [ N_P1CP_DATA ] ;
} VM_Key_Data_Type ;
// data to be sent from DSP1 to CP
 
typedef
struct P1CP_VM_Interface_Type
{
  P1CP_Cmd_Type Command ;
  Absolute_Time_Type TimeOfDay ;
  VM_Data_Type Data [ N_P1CP_DATA ] ;
} P1CP_VM_Interface_Type ;
// data to be sent from CP to DSP2
 
typedef
struct CPP2_VM_Interface_Type
{
  CPP2_Cmd_Type Command ;
  Absolute_Time_Type TimeOfDay ;
  VM_Data_Type Data [ N_P1CP_DATA ] ;
  VM_Key_Data_Type New_Key ;
} CPP2_VM_Interface_Type ;
//////////////////////////////////////////////////////////////////////////////
//
// SMA Structures and Variables
//
//////////////////////////////////////////////////////////////////////////////
 
static const unsigned int
  N_SMA_CPP2_DATA = 1 ;                        // SMA CPP2 data
 
static const unsigned int
  N_CHIPS_64 = 64 ;                        // #of chips
 
typedef
enum TemporalOffsetsType
{
  RAW_OFFSET = 0 , // Must be 0 or 1
  NONAP_OFFSET = 1 , // Must be RAW_OFFSET ^ 1
  NUM_TEMPORAL_OFFSETS
} TemporalOffsetsType ;
 
typedef
enum DetectionType
{
  PRIMARY_DETECTION = 0 , // Must be 0 or 1
  SECONDARY_DETECTION = 1 , // Must be PRIMARY_DETECTION ^ 1
  FINAL_DETECTION ,
  NUM_DETECTION_TYPES
} DetectionType ;
 
static const int32_t
  MAX_DEMOD_OFFSETS = 4 ;                   // total number of demod offsets, 4 streams -> 4
 
static const int32_t
  MAX_CHIP_OFFSETS = 66 ;                   // number of samples per index
 
static const int32_t
  MAX_CHIP_DEMOD_OFFSETS = MAX_CHIP_OFFSETS * MAX_DEMOD_OFFSETS ;                   // const for 4 * 66 = 264
 
static const int32_t
  MAX_CHIP_TEMPORAL_OFFSETS = NUM_TEMPORAL_OFFSETS * MAX_CHIP_DEMOD_OFFSETS ;
 
typedef
struct DechipOutputBuffer
{
   /** The symbol index of this data, based on 0 start time. */
  int32_t symbolIndex ;
   /** The dechipped symbol values for the various chip offsets presented. */
  std :: complex < float > values [ NUM_TEMPORAL_OFFSETS ] [ MAX_CHIP_DEMOD_OFFSETS ] ;
} DechipOutputBuffer ;
// DSP1 to CP data type
 
typedef
struct P1CP_SMA_Data_Type
{
  SAMPLE_TYPE :: Complex Chips64 [ N_CHIPS_64 ] ;
} P1CP_SMA_Data_Type ;
 
typedef
struct P1CP_SMA_Operational_Data_Type
{
  Absolute_Time_Type TimeOfDay ;
  P1CP_SMA_Data_Type P1CP_Data [ NUM_TEMPORAL_OFFSETS ] [ N_P1CP_DATA ] ;
} P1CP_SMA_Operational_Data_Type ;
// data to be sent from DSP1 to CP
 
typedef
struct P1CP_SMA_Interface_Type
{
  P1CP_Cmd_Type Command ;
  P1CP_SMA_Operational_Data_Type opData ;
} P1CP_SMA_Interface_Type ;
//DSP2 to CP structs
//CP to DSP2 data type
 
typedef
struct CPP2_SMA_Data_Type
{
  unsigned int SMA_Corr_Sym_Index ;
  std :: complex < float > Syms [ NUM_TEMPORAL_OFFSETS ] [ MAX_CHIP_DEMOD_OFFSETS ] ;
} CPP2_SMA_Data_Type ;
// CP to DSP2 operational data type
 
typedef
struct CPP2_Operational_SMA_Data_Type
{
  Absolute_Time_Type TimeOfDay ;
  CPP2_SMA_Data_Type CPP2_SMA_Data [ N_SMA_CPP2_DATA ] ;
} CPP2_Operational_SMA_Data_Type ;
// data to be sent from CP to DSP2
 
typedef
struct CPP2_SMA_Interface_Type
{
  CPP2_Cmd_Type Command ;
  CPP2_Operational_SMA_Data_Type opData ;
} CPP2_SMA_Interface_Type ;
       //MODE_DEFS_H
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\mode_defs.h*/
/*   CLOSE_FILE Include File */
 
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg_defs.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2022, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// File Name: msg_defs.h
//
// Description: This file contains the message definitions and contants as
// defined in COMMON VLF RECEIVER, INC 1 SOFTWARE INTERFACE DESIGN DOCUMENT
// (IDD) FOR THE VERY LOW FREQUENCY (VLF) SUBSYSTEM (CVRi1_DAL-012)
//
//
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
#ifndef MSG_DEFS_H
#define MSG_DEFS_H
//******************************************************************************
// Contants definitions used to validate messages.
//******************************************************************************
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2019, Collins Aerospace All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// File Name: msg.h
//
// Description:
//
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
#ifndef MSG_H
#define MSG_H
//subsystems
 
enum Subsystem_Type
{
  OES1 = 0 ,  // system type OES1
  OES2 = 1 ,  // system type OES2
  CP = 2 ,  // system type CP
  DSP1 = 3 ,  // system type DSP1
  DSP2 = 4 ,  // system type DSP2
  CH1SYNC = 5 ,  // system type Channel 1 sync
  CH2SYNC = 6 ,  // system type Channel 2 sync
  CH3SYNC = 7 ,  // system type Channel 3 sync
  CH4SYNC = 8 ,  // system type Channel 4 sync
  CH5SYNC = 9 ,  // system type Channel 5 sync
  CPCUT = 10 ,  // system type CP Cut
  PTS = 11 ,  // system type PTS
  MAX_SUBSYSTEM_TYPE
} ;
//Classification:
// used by both CP and VP for Key and Msg Classifications
 
enum Class_Type
{
  CLASS_CONF = 0 , // Confidential
  CLASS_UNCLASS = 1 , // Unclassified
  CLASS_SEC = 2 , // Secret
  CLASS_TS = 3 , // Top Secret
  CLASS_UNKN = 4 , // UNKNOWN
  MAX_CLASS_TYPE
} ;
// Default Class_Type for VLF
 
static const Class_Type
  DEFAULT_CLASS_TYPE = CLASS_UNKN ;
//Protocol Version to be backward compatible with an older HMI
 
enum Protocol_Version_Type
{
  PROTOCOL_VERSION_LEGACY = 0 , // to be used with older version of HMI
  PROTOCOL_VERSION_VM23 = 1 , // compatible with VM23 updated HMIs
  MAX_PROTOCOL_VERSION
} ;
 
static const Protocol_Version_Type
  DEFAULT_PROTOCOL_VERSION = PROTOCOL_VERSION_VM23 ;
//Reseved Config used between HMIs only to indicate who is active
 
enum Reserved_Config_Type
{
  ACTIVE_HMI = 0 ,
  STANBY_HMI = 1 ,
  MAX_RESERVED_CONFIG
} ;
 
static const Reserved_Config_Type
  DEFAULT_RSVD_CONFIG = ACTIVE_HMI ;
//
// The DSP TCP/IP Server can only accept connection
// from a client on the following ports:
//
// OES1 40000
// OES2 40001
// CP 40002
// DSP1 40003
// CH1SYNC 40005
// CH2SYNC 40006
// CH3SYNC 40007
// CH4SYNC 40008
// CH5SYNC 40009
// CPCUT 40010
// PTS 40011
//
 
static const int
  CLIENT_PORT_BASE = 40000 ;               // client port base
 
static const int
  CLIENT_PORT_OFFSET_MIN = OES1 ;               // client port offset min
 
static const int
  CLIENT_PORT_OFFSET_MAX =
  ( MAX_SUBSYSTEM_TYPE - 1 ) ;
                                                                    // client port offset max
// Message IDs for messages between the OES and VLF and between
// VP CSCI and CP CSCI.
 
enum Message_ID_Type
{
   //Common message
  RESPONSE_STATUS_MSGTYPE = 0 ,
                                                 //Expected Response:
   //OES to VLF 1-50
  OV_CONFIG_VLF_CHANNEL_MSGTYPE = 1 , //RESPONSE_STATUS_MSGTYPE
  OV_START_DS101_FILL_MSGTYPE = 2 , //RESPONSE_STATUS_MSGTYPE
  OV_START_STOP_CHANNEL_MSGTYPE = 3 , //RESPONSE_STATUS_MSGTYPE
   // 4 not used for CVRi1
  OV_GET_LOADED_KEY_INFO_MSGTYPE = 5 , //VO_LOADED_KEYS_DATA_MSGTYPE
  OV_SELECTIVE_ZEROIZE_KEY_DATA_MSGTYPE = 6 , //RESPONSE_STATUS_MSGTYPE
  OV_RUN_IBIT_MSGTYPE = 7 , //RESPONSE_STATUS_MSGTYPE
  OV_KEY_FILL_COMPLETE_MSGTYPE = 8 , //RESPONSE_STATUS_MSGTYPE
  OV_SET_ANTI_JAM_MSGTYPE = 9 , //RESPONSE_STATUS_MSGTYPE
  OV_CONTROLLER_IDENTIFICATION_MSGTYPE = 10 ,//RESPONSE_STATUS_MSGTYPE
  OV_VERSION_REQUEST_MSGTYPE = 11 ,//VO_VLF_RECEIVER_VERSION_DATA_MSGTYPE
  OV_REQUEST_SYSTEM_STATUS_MSGTYPE = 12 ,//VO_CVR_SYSTEM_STATUS_MSGTYPE
                                                 //VO_VLF_RECEIVER_SYSTEM_STATUS_MSGTYPE
  OV_RESTART_RECEIVER_MSGTYPE = 13 ,//RESPONSE_STATUS_MSGTYPE
  OV_LINK_IS_LIVE_MSGTYPE = 14 ,//RESPONSE_STATUS_MSGTYPE
  OV_CONFIG_ALL_VLF_CHANNELS_MSGTYPE = 15 ,//RESPONSE_STATUS_MSGTYPE
  OV_SELECTIVE_ZEROIZE_SYSTEM_KEY_MSGTYPE = 16 ,//RESPONSE_STATUS_MSGTYPE
  OV_TIME_AT_THE_TONE_MSGTYPE = 17 ,//RESPONSE_STATUS_MSGTYPE
   //18 Not Used
  OV_REQUEST_BIT_STATUS_MSGTYPE = 19 ,//VO_VLF_RECEIVER_PBIT_RESULT_MSGTYPE
                                                 //VO_VLF_RECEIVER_CBIT_RESULT_MSGTYPE
  OV_CDE_DATA_ERASURE_MSGTYPE = 20 ,//RESPONSE_STATUS_MSGTYPE
  OV_START_SEQUENCE_NUMBER_MSGTYPE = 21 ,//RESPONSE_STATUS_MSGTYPE
  OV_WRITE_KEY_EFFECTIVITY_DATA_MSGTYPE = 22 ,//RESPONSE_STATUS_MSGTYPE
  OV_GET_LOADED_SYSTEM_KEY_INFO_MSGTYPE = 23 ,//VO_LOADED_SYSTEM_KEYS_DATA_MSGTYPE
  OV_READ_VLF_CHANNEL_MSGTYPE = 24 ,
                                    //VO_VLF_CHANNEL_DATA_MSGTYPE
   // 25-50 Not Used
   //VLF to OES 51-100
   //51 Not Used
  VO_LOADED_KEY_INFO_MSGTYPE = 52 ,//Response or Unsolicited
  VO_VLF_RECEIVER_PBIT_RESULT_MSGTYPE = 53 ,//Response or Unsolicited
  VO_VLF_CHANNEL_DATA_MSGTYPE = 54 ,//Response
  VO_KEY_DISPOSITION_STATUS = 55 ,//Unsolicited
  VO_VLF_LF_DATA_MSGTYPE = 56 ,//Unsolicited
  VO_VLF_RECEIVER_VERSION_DATA_MSGTYPE = 57 ,//Response or Unsolicited
  VO_ALARM_REPORT_MSGTYPE = 58 ,//Unsolicited
  VO_LEGACY_VLF_RECEIVER_SYSTEM_STATUS_MSGTYPE = 59 ,//Response or Unsolicited
  VO_CVR_SYSTEM_STATUS_MSGTYPE = 60 ,//Response or Unsolicited
   // 60-62 Not Used
  VO_KEY_FILL_SUCCESS_MSGTYPE = 63 ,//Unsolicited
  VO_VLF_STREAM_DATA_MSGTYPE = 64 ,//Unsolicited
  VO_SOFTWARE_ANOMALY_LOG_MSGTYPE = 65 ,//Unsolicited
  VO_VLF_RECEIVER_CBIT_RESULT_MSGTYPE = 66 ,//Unsolicited
  VO_LOADED_SYSTEM_KEY_INFO_MSGTYPE = 67 ,//Response or Unsolicited
  VO_CEP_DATA_MSGTYPE = 68 ,//RESPONSE_STATUS_MSGTYPE
   //VP CSCI to CP CSCI 101-150
  VC_CONFIGURE_CHANNEL_MSGTYPE = 101 ,//RESPONSE_STATUS_MSGTYPE
  VC_RUNUP_CHANNEL_MSGTYPE = 102 ,//RESPONSE_STATUS_MSGTYPE
  VC_ZEROIZE_CHANNEL_MSGTYPE = 103 ,//RESPONSE_STATUS_MSGTYPE
                                                  //CV_CRYPTO_CHANNEL_STATE_MSGTYPE
  VC_CORRELATOR_INPUT_MSGTYPE = 104 ,// Used between DSP1 and CP
   // 105 not used for CVRi1
  VC_GET_LOADED_KEY_INFO_MSGTYPE = 106 ,//CV_LOADED_KEYS_DATA_MSGTYPE
  VC_SELECTIVE_ZEROIZE_KEY_DATA_MSGTYPE = 107 ,//RESPONSE_STATUS_MSGTYPE
  VC_CRYPTO_VERSION_REQUEST_MSGTYPE = 108 ,//CV_CRYPTO_VERSION_DATA_MSGTYPE
  VC_REQUEST_CRYPTO_SYSTEM_STATUS_MSGTYPE = 109 ,//CV_CRYPTO_SYSTEM_STATUS_MSGTYPE
  VC_DSP1_LINK_IS_LIVE_MSGTYPE = 110 ,//RESPONSE_STATUS_MSGTYPE
   // 111-112 Not Used (112 not used for CVRi1)
  VC_GET_LOADED_SYSTEM_KEY_INFO_MSGTYPE = 113 ,//CV_LOADED_SYSTEM_KEYS_DATA_MSGTYPE
  VC_REQUEST_PBIT_STATUS_MSGTYPE = 114 ,//CV_CRYPTO_PBIT_RESULT_MSGTYPE
  VC_START_DS101_FILL_MSGTYPE = 115 ,//RESPONSE_STATUS_MSGTYPE
  VC_KEY_FILL_COMPLETE_MSGTYPE = 116 ,//RESPONSE_STATUS_MSGTYPE
  VC_SELECTIVE_ZEROIZE_SYSTEM_KEY_MSGTYPE = 117 ,//RESPONSE_STATUS_MSGTYPE
  VC_GET_MODE_CONFIG_PARAMS_MSGTYPE = 118 ,
                                           //CV_MODE_CONFIG_PARAMS_MSGTYPE
   //119-150 Not Used - (119 not used for CVRi1)
    //CP to VP 151-200
  CV_CORRELATOR_OUTPUT_MSGTYPE = 151 ,//Used between CP and DSP2
  CV_LOADED_KEY_INFO_MSGTYPE = 152 ,//Response or unsolicited
  CV_CRYPTO_PBIT_RESULT_MSGTYPE = 153 ,//Response or unsolicited
  CV_CRYPTO_VERSION_DATA_MSGTYPE = 154 ,//Response or unsolicited
   // 155 Not Used
  CV_CRYPTO_SYSTEM_STATUS_MSGTYPE = 156 ,//Crypto system & channel status
   // 157-160 not used
  CV_LOADED_SYSTEM_KEY_INFO_MSGTYPE = 161 ,//CV_LOADED_SYSTEM_KEYS_DATA_MSGTYPE
  CV_KEY_FILL_SUCCESS_MSGTYPE = 162 ,//Unsolicited
  CV_CP_LINK_IS_LIVE_MSGTYPE = 163 ,//Unsolicited
  CV_CRYPTO_CBIT_RESULT_MSGTYPE = 164 ,//Unsolicited
  CV_MODE_CONFIG_PARAMS_MSGTYPE = 165 ,//Used between DSP2 and DSP1
   //DSP to DSP 201-250
  VV_RUN_IBIT_REQUEST = 201 ,//Response
  VV_DSP1_CBIT_RESULT_MSGTYPE = 202 ,//Response or Unsolicited
  VV_DSP1_PBIT_RESULT_MSGTYPE = 203 ,//Response or Unsolicited
  VV_LINK_IS_LIVE_MSGTYPE = 204 ,//Unsolicited
  VV_DSP1_PM_DATA_MSGTYPE = 205 ,//Unsolicited
   // 206 Not Used
  VV_VLF_CHANNEL_STATE_MSGTYPE = 207 ,//Unsolicited
  VV_VLF_RECEIVER_STATE_MSGTYPE = 208 ,//Unsolicited
  VV_DSP1_VERSION_DATA_MSGTYPE = 209 ,//Response or Unsolicited
  VV_DSP1_EAM_VLF_OUT_MSGTYPE = 210 ,
                                     //Unsolicited
   // 211-250 Not Used
   //Messages used for Software Certification
   // OES to VP 251-275
   // 251 Not Used for CVRi1
  OV_GET_DSP1_STATUS_MSGTYPE = 252 ,//DSP1_STATUS_MSGTYPE
  OV_OUTPUT_SAMPLE_TEST_ENABLE_MSGTYPE = 253 ,//OUTPUT_SAMPLE_DATA_MSGTYPE
  OV_CONFIGURATION_PARAMS_MSGTYPE = 254 ,//RESPONSE_STATUS_MSGTYPE
  OV_PERFORMANCE_MONITORING_ENABLE_MSGTYPE = 255 ,
                                                  //RESPONSE_STATUS_MSGTYPE
                                                     //VO_HIDAR_OPSTAT_MSGTYPE
                                                     //VO_PM_DATA_MSGTYPE
   //Messages used for Software Certification
   // VP to OES 276-300
  VO_DSP1_STATUS_MSGTYPE = 276 ,//Response
  VO_OUTPUT_SAMPLE_DATA_MSGTYPE = 277 ,//Response
  VO_HIDAR_OPSTAT_MSGTYPE = 278 ,//Response
  VO_PM_DATA_MSGTYPE = 279 ,//Response
   //CPCUT to CP 351-375
  TC_DISPLAY_UPDATE_NOTICE_MSGTYPE = 351 ,//Unsolicited
   //CP to CPCUT 376-400
  CT_DISPLAY_UPDATE_MSGTYPE = 376 ,//Unsolicited
  MAX_MSG_ID_MSGTYPE
} ;
//
// Note:
// The following code and Msg_type.ads must match for mode processing messages
//
 
typedef
struct msg_header_type
{
  unsigned Checksum : 32 ;  // Message checksum
  unsigned MsgId : 16 ;  // Message_ID_Type, Unique message Id
  unsigned SrcSS : 8 ;  // Subsystem_Type, Source subsystem
  unsigned DestSS : 8 ;  // Subsystem_Type, Destination subsystem
  unsigned DataLen : 16 ;  // Message data length in bytes
  unsigned ProtocolVersion : 8 ;  // Protocol Version
  unsigned ReservedConfig : 8 ;  // Reserved Config
  unsigned timestamp : 32 ;  // HMI timestamp used for EAM time logging
  unsigned ActionId : 32 ;  // HMI transaction Id (HMI use only)
  unsigned SequenceNum : 32 ;  // HMI EAM Msg Tracking
} msg_header_type ;
                  //24 bytes=6words
 
static const int
  MAX_MSG_BODY_LENGTH = 6060 ;              // largest HIDAR Txt Msg data 1515words
 
typedef
struct Message_Type
{
  msg_header_type header ;
  unsigned char theData [ MAX_MSG_BODY_LENGTH ] ;
                                               //the message data
} Message_Type ;
// Size of header and message
 
static const int
  SIZE_OF_HEADER = sizeof ( msg_header_type ) ;
 
static const int
  SIZE_OF_CMESSAGE =
  ( SIZE_OF_HEADER + MAX_MSG_BODY_LENGTH ) ;
       //MSG_H
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg.h*/
/*   CLOSE_FILE Include File */
 
// Constant definitions used for message handling functions such as data
// validation and message processing.
 
static const unsigned short
  MIN_FREQUENCY_RANGE = 14000 ;
 
static const unsigned short
  MAX_FREQUENCY_RANGE = 60000 ;
 
static const unsigned int
  MAX_TESTING_FREQ = 81910 ;
 
static const unsigned short
  MAX_EAM_CHAR_COUNT = 6052 ;                          //make it 6052 for word alignment
 
static const unsigned short
  MAX_STREAM_CHAR_COUNT = 64 ;
 
static const unsigned short
  MAX_OPSTAT_PM_DATA_COUNT = 1440 ;
 
static const unsigned char
  UNSOLICIT_ACTION_ID = 0 ;
 
static const unsigned char
  UNUSED_VARIABLE_VAL = 0 ;
 
static const unsigned char
  MAX_SHORT_TITLE_LENGTH = 24 ;
 
static const unsigned char
  MAX_EDITION_LENGTH = 8 ;                         //padding for word alignemt
 
static const unsigned char
  MAX_VERSION_INFO_LENGTH = 64 ;
 
static const unsigned char
  MAX_VERSION_TITLE_LENGTH = 32 ;
 
static const unsigned char
  MAX_VERSION_ARRAY_LENGTH = 48 ;
 
static const unsigned char
  MAX_INT_VERSION_ARR_LEN = 16 ;
 
static const unsigned char
  MAX_TEKS_PER_BANK = 100 ;
 
static const unsigned char
  MAX_CRYPTO_APP_NUM = 20 ;
 
static const unsigned char
  MAX_CRYPTO_AEK_NUM = 10 ;
 
static const unsigned char
  MAX_SOFT_ANOM_LEN = 199 ;
 
static const unsigned char
  MAX_SOFT_ANOM_ARRAY_LEN =
  ( MAX_SOFT_ANOM_LEN + 1 ) ;
 
static const unsigned char
  RESET_GPIO = 51 ;                         //changed from 48
 
static const unsigned short
  MAX_WORDS_PER_SAMPLE = 128 ;
 
static const unsigned short
  MAX_NUM_SAMPLES_PER_MSG = 11 ;
 
static const unsigned short
  MAX_SAMPLE_WORDS_PER_MSG = MAX_WORDS_PER_SAMPLE * MAX_NUM_SAMPLES_PER_MSG ;
 
static const unsigned char
  MIN_KEY_SEGMENT_DAY = 1 ;
 
static const unsigned char
  MAX_KEY_SEGMENT_DAY = 255 ;
 
static const unsigned char
  MIN_KEY_BANK_SEG_LOC = 1 ;
 
static const unsigned char
  MAX_KEY_BANK_SEG_LOC = 100 ;
 
static const unsigned char
  JOSEKI_TEK_LOC = 3 ;
 
static const unsigned char
  MIN_TX_NUMBER = 0 ;
 
static const unsigned char
  MAX_TX_NUMBER = 9 ;
 
static const unsigned int
  MAX_TATT_OFFSET = 10000000 ;                        //number of 100 nano-secs
 
static const unsigned short
  MAX_FPGA_OFFSET = 3199 ;                          //used by TATT to load FPGA
 
static const unsigned short
  MAX_DELTA_OFFSET = 3200 ;                          //used by time acc msg
 
static const unsigned short
  DELTA_OFFSET_MASK = 1000 ;                          //used by time acc msg
 
static const unsigned char
  MAX_BAD_MILLI_TIME = 40 ;                         //used by time acc msg
 
static const unsigned short
  MIN_BAD_MILLI_TIME = 20 ;                          //used by time acc msg
 
static const unsigned short
  MAX_16BIT_NUM = 0xFFFF ;
 
static const unsigned long
  MAX_32BIT_NUM = 0xFFFFFFFF ;
 
static const unsigned int
  MAX_SEQUENCE_NUM = 0xFFFFFFFF ;
 
static const unsigned char
  MIN_NUM_KEYS = 1 ;
 
static const unsigned char
  MAX_NUM_KEYS = 100 ;
 
static const unsigned char
  MIN_DAY_VALUE = 1 ;
 
static const unsigned char
  MAX_DAY_VALUE = 35 ;
 
static const unsigned char
  MIN_MONTH_VALUE = 1 ;
 
static const unsigned char
  MAX_MONTH_VALUE = 12 ;
 
static const unsigned char
  MIN_YEAR_VALUE = 1 ;
 
static const unsigned short
  MAX_YEAR_VALUE = 9999 ;
 
static const unsigned short
  EPOCH_YEAR_VALUE = 1900 ;
 
static const unsigned char
  MAX_TIME_DIFF = 1 ;
 
static const signed char
  MIN_TIME_DIFF = - 1 ;
 
static const unsigned char
  MAX_TIME_DIFF_FOR_EAM = 3 ;
 
static const signed char
  MIN_TIME_DIFF_FOR_EAM = - 3 ;
 
static const unsigned int
  NUM_SEC_PER_DAY = 86400 ;
 
static const unsigned char
  MAX_FRAMES_IN_SEC = 50 ;                         // used in CP
 
static const unsigned char
  MAX_SECS_IN_MIN = 60 ;
 
static const unsigned char
  ONE_FRAME_MSEC = 20 ;
 
static const unsigned char
  MAX_HOURS = 23 ;
 
static const unsigned char
  MAX_MINUTES = 59 ;
 
static const unsigned char
  MAX_SECONDS = 59 ;
 
static const unsigned char
  MAX_FRAMES = 49 ;
 
static const unsigned char
  MAX_CAL_DAY_VALUE = 31 ;
 
static const unsigned char
  MAX_MAN_GAIN_SIN = 9 ;
 
static const signed char
  MIN_MAN_GAIN_SIN = - 9 ;
 
static const unsigned char
  MAX_MAN_GAIN_DBL = 99 ;
 
static const signed char
  MIN_MAN_GAIN_DBL = - 99 ;
 
static const unsigned short
  MAX_MAN_GAIN_TRI = 999 ;
 
static const unsigned char
  TOTAL_SECONDS = 60 ;
 
static const unsigned char
  MAX_ALARM_REGISTERS = 4 ;
 
static const unsigned char
  MAX_STATUS_REGISTERS = 2 ;
//******************************************************************************
// Enumerations definitions
//******************************************************************************
 
enum Response_Status_Type
{
  ACK = 0 ,
  NAK = 1 ,
  MAX_STATUS
} ;
 
enum Msg_Error_Codes_Type
{
  VLF_NO_ERROR = 0 , // General parsing error
  CMD_ID_ERROR = 1 , // Unable to identify command
  DATA_LENGTH_ERROR = 2 , // Data length disagrees with data received
  DATA_WORD_COUNT_ERROR = 3 , // Data received is not an integral of words
  CHECKSUM_ERROR = 4 , // Checksum error
  PARAM_OUT_OF_RANGE = 5 , // Data is not in the legal range
  MAX_PARSING_ERROR , // Used to show Highest General Error
   //Error specific to Channel
  INVALID_TEK_SPECIFIED = 20 ,
  CHANNEL_NOT_ZEROIZED = 21 ,
  CHANNEL_NOT_CONFIGURED = 22 ,
  CHANNEL_IN_ALARM = 23 ,
  CHANNEL_IN_SYNC = 24 ,
  CHANNEL_ACTIVE = 25 ,
  CP_CHANNEL_NOT_STARTED = 26 ,
  CP_CHANNEL_NOT_CONFIGURED = 27 ,
  INT_COMM_ERROR = 28 ,
  CHANNEL_ROLLOVER_FAILED = 29 ,
  MAX_CHANNEL_ERROR , //Used to show Highest Channel Error
   // Internal VLF errors
  TIME_NOT_LOADED = 40 ,
  NOT_ACTIVE_OES = 41 ,
  OPERATION_IN_PROGRESS = 42 ,
  CLEAR_COMM_PLNS_FAILED = 43 ,
  TIME_ACCURACY_UNAVAILABLE = 44 ,
  INVALID_KEY_SPECIFIED = 45 ,
  INVALID_ALG_SPECIFIED = 46 ,
  INVALID_KEY_TYPE = 47 ,
  CM_CMD_FAILED = 48 ,
  DS101_FILL_ALREADY_ACTIVE = 49 ,
  NO_FILL_OPERATION_ACTIVE = 51 ,
  OPERATION_NOT_ALLOWED = 52 ,
  STORE_ERROR = 53 ,
  DUPLICATE_CHAN_ID_USED_IN_COMMPLAN = 54 ,
  NO_VALID_COMMPLAN_FOUND = 55 ,
  SEQUENCE_NUMBER_NOT_UPDATED = 56 ,
  MAX_INTERNAL_VLF_ERROR , //Used to show Highest VLF Error
  UNKNOWN_ERROR = 0xFFFF
} ;
 
enum Tx_Mode_Type
{
  NO_MODE_SPECIFIED = 0 ,
  NORMAL_MODE_15 = 1 ,
  SPECIAL_MODE_9 = 2 ,
  SPECIAL_MODE_HIDAR = 3 ,
  VERDIN_MODE_23 = 4 ,
  SPECIAL_MODE_A = 5 ,
  TX_MODE_TYPE_MAX
} ;
 
enum VLF_Data_Segment_Type
{
  WHOLE_MSG = 0 ,
  PARTIAL_MSG = 1 ,
  SUPPRESS_MSG = 2 ,
  DUPLICATE_MSG = 3 ,
  VLF_DATA_SEGMENT_TYPE_MAX
} ;
 
enum VLF_Data_Msg_Type
{
  NORMAL_MSG = 0 ,
  FIRST_PIECED_MSG = 1 ,
  SECOND_PIECED_MSG = 2 ,
  VLF_DATA_MSG_TYPE_MAX
} ;
 
enum Channel_ID_Type
{
  CH_1 = 0 ,
  CH_2 = 1 ,
  CH_3 = 2 ,
  CH_4 = 3 ,
  CH_5 = 4 ,
  MAX_VLF_CHANNEL = 5
} ;
 
enum VM_Channel_Type
{
  VM_NO_CHANNEL = 0 ,
  VM_CH_1 = 1 ,
  VM_CH_2 = 2 ,
  VM_CH_3 = 3 ,
  VM_CH_4 = 4
} ;
 
enum Crypto_Algorithm_Type
{
  NA_ALG = 0 ,
  RESERVED_ALG1 = 1 ,
  RESERVED_ALG2 = 2 ,
  DECRYPTION_ALG = 3 ,
  MEDLEY_ALG = 4 ,
  RESERVED_ALG5 = 5 ,
  RESERVED_ALG6 = 6 ,
  RESERVED_ALG7 = 7 ,
  RESERVED_ALG8 = 8 ,
  RESERVED_ALG9 = 9 ,
  RESERVED_ALG10 = 10 ,
  RESERVED_ALG11 = 11 ,
  RESERVED_ALG12 = 12 ,
  RESERVED_ALG13 = 13 ,
  RESERVED_ALG14 = 14 ,
  RESERVED_ALG15 = 15 ,
  RESERVED_ALG16 = 16 ,
  RESERVED_ALG17 = 17 ,
  RESERVED_ALG18 = 18 ,
  RESERVED_ALG19 = 19 ,
  RESERVED_ALG20 = 20 ,
  CRYPTO_ALGORITHM_TYPE_MAX
} ;
 
enum Crypto_Alg_MSG_Type
{
  NO_ALG = 0 ,
  RESERVED_1 = 1 ,
  MEDLEY = 2
} ;
//Assumption: TEKs loaded Key Bank 1 & 2 are associated with algorithm
//loaded in location 1, and TEKs loaded in Key Banks 4-7 are associated
//with Medley algorithm loaded in location 2.
 
enum Keybank_Type
{
  NO_BANK = 0 ,
  RESERVED_BANK1 = 1 ,
  RESERVED_BANK2 = 2 ,
  DECRYPTION_BANK = 3 ,
  MEDLEY_BANK1 = 4 ,
  MEDLEY_BANK2 = 5 ,
  MEDLEY_BANK3 = 6 ,
  MEDLEY_BANK4 = 7 ,
  RESERVED_BANK8 = 8 ,
  RESERVED_BANK9 = 9 ,
  RESERVED_BANK10 = 10 ,
  KEYBANK_TYPE_MAX ,
  KEY_BANK_IDX_FIRST = NO_BANK + 1 ,
  KEY_BANK_IDX_LAST = KEYBANK_TYPE_MAX - 1 ,
  MAX_NUM_KEY_BANKS = KEY_BANK_IDX_LAST - KEY_BANK_IDX_FIRST + 1
} ;
//Used in OV_START_STOP_CHANNEL_MSGTYPE
 
enum Channel_Action_Type
{
  START_CHANNEL = 0 ,
  STOP_CHANNEL = 1 ,
  STOP_CHANNEL_FORCED = 2 ,
  OES_CHANNEL_ACTION_TYPE_MAX ,
  RESTART_CHANNEL = 10 ,
  ACTIVATE_ANTI_JAM = 11 ,
  DEACTIVATE_ANTI_JAM = 12 ,
  ACTIVATE_ROLLOVER = 13 ,
  CP_CHAN_ALARM_HALT = 14 ,
  CHANNEL_OFFLINE = 15 ,
  CP_CHAN_RESTART = 16 ,
  INTERNAL_CHANNEL_CMD_MAX
} ;
//Used in OV_SELECTIVE_ZEROIZE_KEYS_MSGTYPE
 
enum Zeroize_Keys_Action_Type
{
  SPECIFIC_TEK = 0 ,//a single TEK, must provide Key information
  ALG_SPECIFIC_TEKS = 1 ,//all keys associated with alg, must specify alg
  ALL_TEKS = 2 , //All TEKs in bank 1-4
  ALL_COMM_PLANS = 3 , // Zeoize all Comm Plans
  CDE = 4 , // used for CDE to delete all TEKs & KEK
  ZERIOZE_KEYS_ACTION_TYPE_MAX
} ;
//Used in OV_SELECTIVE_ZEROIZE_SYSTEM_KEY_MSGTYPE
 
enum Zeroize_System_Keys_Action_Type
{
  SPECIFIC_AEK = 0 , //a single AEK, must provide Key information
  ALL_AEKS = 1 , //All AEKs
  JOSEKI_TEK = 2 , // Joseki TEK in bank 3
  KEK = 3 , // KEK
  ALL_SYSTEM_KEYS = 4 , // All system keys
  ZERIOZE_SYSTEM_KEYS_ACTION_TYPE_MAX
} ;
 
enum BIT_Fault_Type
{
  NORMAL = 0 ,
  FAULTED = 1
} ;
 
enum Bit_Set_Type
{
  BIT_CLEAR = 0 ,
  BIT_SET = 1
} ;
//This type is used to report Continuous BIT for DSP1.
//MAX_DSP1_CBIT cannot exceed 31
 
enum DSP1_CBIT_Type
{
   //faults from DSP1
  DSP1_CPU_BOARD_FAULT = 0 ,
  DSP1_4V_PWR_CONVERTER_FAIL = 1 ,
  FPGA_INTERFACE_FAULT = 2 , //20 ms interrupt
  FPGA_CRC_ERROR = 3 , //IRQ5 in interrupt register
  PPS_FAULT = 4 ,
  TIME_ACCURACY_FAULT = 5 ,
  STOD_FAULT = 6 ,
  TIME_LOADED_STATUS = 7 ,
  RFA_DCXO_BIT_STATUS = 8 ,
  RFA_PS1_BIT_STATUS = 9 ,
  RFA_FCXO_LOCK_STATUS = 10 ,
   //status only
  DSP1_IIC1_TEMP_SENSOR_TEST = 11 ,
  EXT_SEL_STATUS = 12 ,
  DSP1_MEMORY_CLEAR = 13 ,
  DSP1_ECC_TEST_FAULT = 14 ,
  MAX_DSP1_CBIT_TYPE
} ;
//This type is used to report Continuous BIT for DSP2.
//MAX_DSP2_CBIT cannot exceed 31
 
enum DSP2_CBIT_Type
{
   //faults reported from DSP2
   //faults from DSP2
  DSP2_CPU_BOARD_FAULT = 0 ,
  DSP2_4V_PWR_CONVERTER_FAIL = 1 ,
  DSP2_MAIN_PSA_CARD_FAULT = 2 ,
   // Ethernet comm faults
  CRYPTO_ETHERNET_COMM_FAULT = 3 ,
  DSP1_ETHERNET_COMM_FAULT = 4 ,
  DSP2_ETHERNET_COMM_FAULT = 5 ,
  OES1_ETHERNET_COMM_FAULT = 6 ,
  OES2_ETHERNET_COMM_FAULT = 7 ,
   //status only
  DSP2_IIC1_TEMP_SENSOR_TEST = 8 ,
  CHASSIS_TEMPERATURE_ALARM = 9 ,
  DSP2_MEMORY_CLEAR = 10 ,
  PTS_ETHERNET_COMM_FAULT = 11 ,
  DSP2_ECC_TEST_FAULT = 12 ,
  MAX_DSP2_CBIT_TYPE
} ;
// These are bits in the 'cryptoBITResults word' of the
// PBIT (Receiver_PBIT_Result_Msg_Type) and
// and CBIT message (Receiver_PBIT_Result_Msg_Type).
//
 
enum Crypto_BIT_Type
{
  CRYPTO_ALARMED = 0 , // Least Sig Bit
  PEIP_BATTERY_FAULTED = 1 , // Next to Least Sig Bit
  MAX_CRYPTO_BIT_TYPE  // Only 2 bits are needed.
} ;
//Power-Up BIT for DSP1
//MAX_DSP1_PBIT_TYPE cannot exceed 31
 
enum DSP1_PBIT_Type
{
  DSP1_FLASH_TEST = 0 ,
  DSP1_SDRAM_TEST = 1 ,
  DSP1_PROCESSOR_TEST = 2 ,
  DSP1_25MHZ_CLOCK_TEST = 3 ,
  DSP1_ECC_TEST = 4 ,
  FPGA_CONFIG_LOAD_FAIL = 5 ,
  FPGA_TEST = 6 ,
  ANTENNA_CHANNEL_1_TEST = 7 ,
  ANTENNA_CHANNEL_2_TEST = 8 ,
  RFA_TEST = 9 ,
  DSP1_RFA_DCXO_BIT_STATUS = 10 ,
  DSP1_RFA_PS1_BIT_STATUS = 11 ,
  DSP1_RFA_FCXO_LOCK_STATUS = 12 ,
  DSP1_BOOT_EEPROM_TEST = 13 ,
  PULSE_PER_SECOND_FAULT = 14 ,
  DSP1_IIC1_TEMP_MONITOR_TEST = 15 ,
  MAX_DSP1_PBIT_TYPE
} ;
//Power-Up BIT for DSP2
//MAX_DSP2_PBIT_TYPE cannot exceed 31
 
enum DSP2_PBIT_Type
{
  DSP2_FLASH_TEST = 0 ,
  DSP2_SDRAM_TEST = 1 ,
  DSP2_PROCESSOR_TEST = 2 ,
  DSP2_25MHZ_CLOCK_TEST = 3 ,
  DSP2_ECC_TEST = 4 ,
  DSP2_BOOT_EEPROM_TEST = 5 ,
  DSP2_IIC1_TEMP_MONITOR_TEST = 6 ,
  MAX_DSP2_PBIT_TYPE
} ;
//32-bit, each bit represented a status or BIT result as specified in the
//in the enum for PBIT and CBIT and DSP Misc statuses.
 
typedef
struct BIT_Result_Type
{
  unsigned result : 32 ; // 1 bit field
} BIT_Result_Type ;
                 //4 bytes
 
enum VLF_Receiver_State_Type
{
  VLF_INITIALIZATION = 0 ,
  VLF_STANDBY = 1 ,
  VLF_OPERATIONAL = 2 ,
  VLF_DEGRADED = 3 ,
  VLF_OFFLINE = 4 ,
  VLF_RECEIVER_STATE_MAX
} ;
 
enum ECU_State_Type
{
  ECU_INITIALIZATION = 0 ,
  ECU_OPERATIONAL = 1 ,
  ECU_ALARM = 2 ,
  ECU_RECOVERY = 3 ,
  ECU_DEPOT = 4 ,
  ECU_STATE_TYPE_MAX
} ;
 
enum ECU_Substate_Type
{
  NO_SUBSTATE = 0 ,
  NO_JOSEKI_SPLIT = 1 ,
  ECU_ZEROIZE_DETECTED = 2 ,
  NO_CM_OS = 3 ,
  INVALID_CIK = 4 ,
  ECU_INTERLOCK_DETECTED = 5 ,
  NO_DECRYPT_ALG = 6 ,
  NO_DECRYPT_AEK = 7 ,
  NO_DECRYPT_TEK = 8 ,
  ECU_ZEROIZE_PASSED = 9 ,
  ECU_ZEROIZE_FAILED = 10 ,
  ECU_SUBSTATE_TYPE_MAX
} ;
 
enum VLF_Channel_State_Type
{
  CH_OFFLINE = 0 ,
  CH_OPERATIONAL = 1 ,
  CH_DEGRADED = 2 ,
  VLF_CHANNEL_STATE_TYPE_MAX
} ;
 
enum Crypto_Channel_State_Type
{
  CH_IDLE = 0 ,
  CH_ACTIVE = 1 ,
  CH_ALARM = 2 ,
  CRYPTO_CHANNEL_STATE_TYPE_MAX
} ;
 
enum Channel_Mode_Processing_Status_Type
{
  CH_NOT_SETUP_FOR_MODE = 0 ,
  SEARCHING = 1 ,
  IN_SYNC = 2 ,
  VLF_ERROR = 3 ,
  SEARCH_HALTED = 4 ,
  CHANNEL_MODE_PROCESSING_STATUS_TYPE_MAX
} ;
// Referenced in Alarm_Report_Msg_Type for VO_ALARM_REPORT_MSGTYPE,
// CV_ALARM_REPORT_MSGTYPE
 
enum VLF_Alarm_Type
{
  UNKNOWN_ALARM = 0 ,
  INTERLOCK = 1 ,
  ZEROIZE = 2 ,
  VP_SW_FAULTED = 3 ,
  CP_ALARMED = 4 ,
  VLF_DSP1_HW_FAULTED = 5 ,
  VLF_DSP2_HW_FAULTED = 6 ,
  ANTENNA_FAULTED = 7 ,
  RFA_FAULTED = 8 ,
  PSA_FAULTED = 9 ,
  CRYPTO_COMM_FAULTED = 10 ,
  DSP_COMM_FAULTED = 11 ,
  OES_COMM_FAULTED = 12 ,
  CHASSIS_TEMPERATURE_WARNING = 13 ,
  DSP1_IIC1_TEMPERATURE_ALARM = 14 ,
  DSP2_IIC1_TEMPERATURE_ALARM = 15 ,
  VLF_ALARM_TYPE_MAX
} ;
 
enum Alarm_Category_Type
{
  STATUS_ADVISORY = 0 ,
  ERROR_ADVISORY = 1 ,
  ALERT = 2 ,
  ALARM = 3 ,
  ALARM_CATEGORY_TYPE_MAX
} ;
 
enum Alarm_Source_Type
{
  RECEIVER = 0 ,
  CRYPTO = 1 ,
  VLF_ANTENNA = 2 ,
  OTHER = 3 ,
  ALARM_SOURCE_TYPE_MAX
} ;
// Referenced in Time_At_The_Tone_Msg_Type used for
// OV_TIME_AT_THE_TONE_MSGTYPE
 
enum Time_Source_Type
{
  BBC = 0 ,
  GPS = 1 ,
  MILSTAR = 2 ,
  OPER = 3 ,
  IRIG_B = 4 ,
  NONE = 255
} ;
 
enum Load_Type
{
  NO_LOAD = 0 ,
  AUTO_LOAD = 1 ,
  MANUAL_LOAD = 2
} ;
 
enum Time_Accy_Type
{
  NANO_SEC_1 = - 9 ,
  NANO_SEC_10 = - 8 ,
  NANO_SEC_100 = - 7 ,
  MICRO_SEC_1 = - 6 ,
  MICRO_SEC_10 = - 5 ,
  MICRO_SEC_100 = - 4 ,
  MILLI_SEC_1 = - 3 ,
  MILLI_SEC_10 = - 2 ,
  MILLI_SEC_100 = - 1 ,
  SEC_1 = 0 ,
  SEC_10 = 1 ,
  SEC_100 = 2 ,
  UNK = 255
} ;
 
typedef
struct Date_Time_Type
{
  unsigned Year : 16 ;//4 digits year
  unsigned Month : 8 ; //1..12
  unsigned Day : 8 ; //1..31
  unsigned Hour : 8 ; //0..23
  unsigned Minute : 8 ; //0..59
  unsigned Second : 8 ; //0..59
   // reserved is part of the data structure and is necessary for space
  unsigned reserved : 8 ;
} Date_Time_Type ;
                 //8 bytes
 
typedef
struct Hour_Minute_Type
{
  unsigned Hour : 8 ; //0..23
  unsigned Minute : 8 ; //0..59
   // reserved is part of the data structure and is necessary for space
  unsigned reserved : 16 ;
} Hour_Minute_Type ;
                   //4 bytes
 
typedef
struct Date_Type
{
  unsigned Year : 16 ;//4 digits year
  unsigned Month : 8 ; //1..12
  unsigned Day : 8 ; //1..31
} Date_Type ;
            //4 bytes
 
enum Time_Accy_Ind
{
  VLF_TIME_GOOD = 0 ,
  VLF_TIME_DEGRADED = 1 ,
  VLF_TIME_BAD = 2
} ;
 
enum Key_Disp_Status_Type
{
  FAILURE = 0 ,
  PASS = 1
} ;
 
enum Take_Cntrl_ID_Type
{
  TCN_NORMAL = 0 ,
  TCN_FORCED = 1
} ;
 
enum FPGA_Sample_Address_Type
{
  OMNI = 0 ,
  ANTENNA1 = 1 ,
  ANTENNA2 = 2 ,
  ANTENNA3 = 3 ,
  MAX_FPGA_ADDR
} ;
//******************************************************************************
// typedef definitions
//******************************************************************************
 
typedef
char
  Short_Title_Type [ MAX_SHORT_TITLE_LENGTH ] ;        //shortTitle 24 chars
 
typedef
char
  Edition_Type [ MAX_EDITION_LENGTH ] ;        //edition 8 chars
 
typedef
char
  Version_String_Type [ MAX_VERSION_INFO_LENGTH ] ;        //include the null terminated
 
typedef
char
  Version_Title_String_Type [ MAX_VERSION_TITLE_LENGTH ] ;        //include the null terminated
 
typedef
unsigned short
  Crypto_Alarm_Registers_Type [ MAX_ALARM_REGISTERS ] ;                  //2 words
 
typedef
unsigned short
  Crypto_Status_Registers_Type [ MAX_STATUS_REGISTERS ] ;
                                                                           //2 words
// Use in VO_VLF_CHANNEL_DATA_MSGTYPE, OV_CONFIG_VLF_CHANNEL_MSGTYPE,
// and OV_CONFIG_ALL_VLF_MSGTYPE messages
 
typedef
struct Vlf_Channel_Type
{
  unsigned channelID : 8 ; // 1-5 [0=NULL COMM/PLAN]
  unsigned mode15 : 8 ; // bool
  unsigned mode9 : 8 ; // bool
  unsigned modeHIDAR : 8 ; // bool
  unsigned frequency : 16 ; // ranges 14000..60000
  unsigned reserved : 16 ; // used for alignment
  unsigned mode23 : 8 ; // VM_Channel_Type
  unsigned modeSMA : 8 ; // UMM
  unsigned modeSMB : 8 ; // SFLEX
  unsigned reserved2 : 8 ; // used for alignment
  Short_Title_Type keyShortTitle ; // 24 bytes
} Vlf_Channel_Type ;
//Individual TEK information & storage in the PEIP
 
typedef
struct Key_Info_Type
{
  unsigned segmentDay : 8 ; //segment 1..35
  unsigned keyBankLoc : 8 ; //Keybank_Type
  unsigned keyBankSegLoc : 8 ; //1..100
  unsigned keyClassification : 8 ;
  Short_Title_Type keyShortTitle ; //24 chars
   // edition is part of the data structure and is necessary for space
  Edition_Type edition ; //8 chars
} Key_Info_Type ;
                //36 bytes
 
typedef
struct Key_Bank_Info_Type
{
  unsigned keyBankLoc : 8 ; //Keybank_Type
  unsigned keyBankSegLoc : 8 ; //1..100
   // reserved is part of the data structure and is necessary for space
  unsigned reserved : 16 ;
} Key_Bank_Info_Type ;
                     //4 bytes
 
typedef
struct Key_Effectivity_Data_Type
{
  unsigned keyBankLoc : 8 ; //Keybank_Type
  unsigned keyBankSegLoc : 8 ;
                               //1-100 for TEK, 1-20 for AEK
                                            //location within a Key bank
   // reserved is part of the data structure and is necessary for space
  unsigned keyValid : 8 ; // 0 = false, 1 = true
  unsigned reserved : 8 ;
  Date_Type keyEffectDate ; // 4-bytes
   // keyShortTitle is part of the data structure and is necessary for space
  Short_Title_Type keyShortTitle ; //24 chars
} Key_Effectivity_Data_Type ;
                            //32 bytes
 
typedef
struct Crypto_Sys_Key_Info_Type
{
  unsigned SystemKeyLoc : 16 ;
                               // 1..20 for Alg
                                            // 1..10 for AEK
   // reserved is part of the data structure and is necessary for space
  unsigned reserved : 16 ;
  Short_Title_Type SysKeyShortTitle ; // 24 bytes
} Crypto_Sys_Key_Info_Type ;
                           // 28 bytes
 
typedef
struct Component_Version_Type
{
  Version_Title_String_Type Version_Title ; //32
  Version_String_Type Version_Data ; //64
} Component_Version_Type ;
                         // 96 bytes
 
typedef
struct Legacy_VLF_Receiver_Channel_Status_Type
{
  unsigned VLFChanState : 8 ; //VLF_Channel_State_Type
  unsigned cryptoChanState : 8 ; //Crypto_Channel_State_Type
  unsigned mode15Status : 8 ; //Channel_Mode_Processing_Status_Type
  unsigned mode9Status : 8 ; //Channel_Mode_Processing_Status_Type
  unsigned modeHIDARStatus : 8 ; //Channel_Mode_Processing_Status_Type
  unsigned antiJamOnly : 8 ; //normal/anti-jam only
  unsigned chanError : 16 ;//Msg_Error_Codes_Type
} Legacy_VLF_Receiver_Channel_Status_Type ;
                                          //8 bytes
 
typedef
struct VLF_Receiver_Channel_Status_Type
{
  unsigned VLFChanState : 8 ; //VLF_Channel_State_Type
  unsigned cryptoChanState : 8 ; //Crypto_Channel_State_Type
  unsigned mode15Status : 8 ; //Channel_Mode_Processing_Status_Type
  unsigned mode9Status : 8 ; //Channel_Mode_Processing_Status_Type
  unsigned modeHIDARStatus : 8 ; //Channel_Mode_Processing_Status_Type
  unsigned modeVM23Status : 8 ; //Channel_Mode_Processing_Status_Type
  unsigned modeSMAStatus : 8 ; //Channel_Mode_Processing_Status_Type
  unsigned mode2ResvStatus : 8 ; //Channel_Mode_Processing_Status_Type
  unsigned mode3ResvStatus : 8 ; //Channel_Mode_Processing_Status_Type
  unsigned antiJamOnly : 8 ; //normal/anti-jam only
  unsigned chanError : 16 ;//Msg_Error_Codes_Type
} VLF_Receiver_Channel_Status_Type ;
                                   //12 bytes
 
typedef
struct Crypto_Module_State_Type
{
  unsigned ECUState : 16 ; //ECU_State_Type
  unsigned ECUSubstate : 16 ; //ECU_Substate_Type
} Crypto_Module_State_Type ;//4 bytes
//use for correlation
 
typedef
struct complex_float
{
  float Re ; // IEEE-754 single precision 32 bit float
  float Im ; // IEEE-754 single precision 32 bit float
} complex_float ;
//******************************************************************************
// Message definitions
//******************************************************************************
/////////////////// RESPONSE_STATUS_MSGTYPE ///////////////////
// Description: Use to response to any message requiring ACK/NAK
//
// Expected Response: None
///////////////////////////////////////////////////////////////
 
typedef
struct Response_Status_Msg_Type
{
  unsigned Status : 16 ;//Response_Status_Type Status, 16 bits storage
  unsigned respToMsgID : 16 ;//Message_ID_Type
  unsigned errorCode : 16 ;//Msg_Error_Codes_Type
  unsigned channelID : 16 ;//used internally 1-5
} Response_Status_Msg_Type ;
                            //2 words
/*************************************************************************/
/* Messages specific between VLF Control and VP */
/*************************************************************************/
/////////////////// OV_CONFIG_VLF_CHANNEL_MSGTYPE /////////////////////////
// Description: Command to write comm plan which contains Mode 23.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
//////////////////////////////////////////////////////////////////
 
typedef
struct Config_Vlf_Channel_Msg_Type
{
  Vlf_Channel_Type commPlan ; //36 bytes
} Config_Vlf_Channel_Msg_Type ;
                              // 10 words
/////////////////// OV_CONFIG_ALL_VLF_CHANNELS_MSGTYPE ////////////////////
// Description: Command to write comm plan which contains Mode 23.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
//////////////////////////////////////////////////////////////////
 
typedef
struct Config_All_Vlf_Channels_Msg_Type
{
  Vlf_Channel_Type commPlans [ MAX_VLF_CHANNEL ] ;
                                                //36 bytes x 5
} Config_All_Vlf_Channels_Msg_Type ;
                                   // 50 words
/////////////////// OV_READ_VLF_CHANNEL_MSGTYPE ///////////////////
// Description: Command to get the comm plan for the specified channel
// Expected Response: VO_VLF_CHANNEL_DATA_MSGTYPE
/////////////////////////////////////////////////////////////////
 
typedef
struct Read_Vlf_Channel_Msg_Type
{
  unsigned channelID : 8 ;//
   // reserved is needed to complete the data structure
  unsigned reserved : 24 ; //filler
} Read_Vlf_Channel_Msg_Type ;
                            //1 word
/////////////////// VO_VLF_CHANNEL_DATA_MSGTYPE ///////////////////
// Description: Comm Plan data in response to OV_READ_VLF_CHANNEL_MSGTYPE
// Message ID : VO_VLF_CHANNEL_DATA_MSGTYPE
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
/////////////////////////////////////////////////////////////////
 
typedef
struct Vlf_Channel_Data_Msg_Type
{
  unsigned validCommPlan : 8 ;
   // reserved is needed to complete the data structure
  unsigned reserved : 24 ;
  Vlf_Channel_Type commPlan ; //36 bytes
} Vlf_Channel_Data_Msg_Type ;
                            //10 words
/////////////////// OV_START_STOP_CHANNEL_MSGTYPE ///////////////////
// Description: Command to start or stop a channel
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
/////////////////////////////////////////////////////////////////
 
typedef
struct Start_Stop_Channel_Msg_Type
{
  unsigned channelID : 8 ;//1-5
  unsigned action : 8 ;//Channel_Action_Type
   // reserved is needed to complete the data structure
  unsigned reserved : 16 ;//filler
} Start_Stop_Channel_Msg_Type ;
                              // 1 word
/////////////////// OV_START_DS101_FILL_MSGTYPE ///////////////////
/////////////////// VC_START_DS101_FILL_MSGTYPE ///////////////////
// Description: Command to notify CP that we are starting a key
// fill using the DTD/SKL.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
/////////////////// OV_KEY_FILL_COMPLETE_MSGTYPE ///////////////////
/////////////////// VC_KEY_FILL_COMPLETE_MSGTYPE ///////////////////
// Description: Command to notify CP that we are done loading a key
// fill using the DTD/SKL.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////
/////////////////// OV_GET_LOADED_KEYS_MSGTYPE /////////////////////////////////
/////////////////// VC_GET_LOADED_KEYS_MSGTYPE /////////////////////////////////
// Description: Use to request all loaded keys in the PEIP II+.
// These messages only contain only the message header. When VP
// receives the OV_GET_LOADED_KEYS_MSGTYPE, VP routes to CP using
// message ID VC_GET_LOADED_KEYS_MSGTYPE. When VP receives the
// CV_LOADED_KEYS_DATA_MSGTYPE from CP, it routes to VLF Control using
// message ID VO_LOADED_KEYS_DATA_MSGTYPE.
//
// Expected Response: VO_LOADED_KEYS_DATA_MSGTYPE,
// CV_LOADED_KEYS_DATA_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
/////////////////// OV_GET_LOADED_KEY_INFO_MSGTYPE ////////////////////////////////
/////////////////// VO_LOADED_KEY_INFO_MSGTYPE ////////////////////////////////
// Description: Provides all loaded keys in the PEIP II+.
// These messages are in response to OV_GET_LOADED_KEY_INFO_MSGTYPE and
// VC_GET_LOADED_KEY_INFO_MSGTYPE or unsolicited when there are changes.
// When VP receives CV_LOADED_KEY_INFO_MSGTYPE from CP, VP routes
// the message to VLF Control using message ID VO_LOADED_KEY_INFO_MSGTYPE.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Loaded_Key_Info_Msg_Type
{
  unsigned numKeys : 16 ;
   // number of TEKs loaded in Keybank 0-10
// remainingVLFKeys is needed to complete the data structure
  unsigned remainingVLFKeys : 16 ;
   // number of loaded VLF Keys Remain
  Key_Info_Type TEKs [ MAX_TEKS_PER_BANK ] ;
                                          // 36*100 = 3600bytes
} Loaded_Key_Info_Msg_Type ;
                          // //901 words = 3604bytes
/////////////////// OV_GET_LOADED_SYSTEM_KEY_INFO_MSGTYPE //////////////////////////
/////////////////// VC_GET_LOADED_SYSTEM_KEY_INFO_MSGTYPE //////////////////////////
// Description: Use to request all loaded keys in the PEIP II+.
// These messages only contain only the message header. When VP
// receives the OV_GET_LOADED_SYSTEM_KEY_INFO_MSGTYPE, VP routes to CP using
// message ID VC_GET_LOADED_SYSTEM_KEY_INFO_MSGTYPE. When VP receives the
// CV_LOADED_SYSTEM_KEY_INFO_MSGTYPE from CP, it routes to VLF Control using
// message ID VO_LOADED_SYSTEM_KEY_INFO_MSGTYPE.
//
// Expected Response: VO_LOADED_SYSTEM_KEY_INFO_MSGTYPE,
// CV_LOADED_SYSTEM_KEY_INFO_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
/////////////////// VO_LOADED_SYSTEM_KEY_INFO_MSGTYPE /////////////////////////
/////////////////// CV_LOADED_SYSTEM_KEY_INFO_MSGTYPE /////////////////////////
// Description: Provides all loaded keys in the PEIP II+.
// These messages are in response to OV_GET_LOADED_SYSTEM_KEY_INFO_MSGTYPE and
// VC_GET_LOADED_SYSTEM_KEY_INFO_MSGTYPE or unsolicited when there are changes.
// When VP receives CV_LOADED_SYSTEM_KEY_INFO_MSGTYPE from CP, VP routes
// the message to VLF Control using message ID VO_LOADED_SYSTEM_KEY_INFO_MSGTYPE.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Loaded_System_Key_Info_Msg_Type
{
   // JOSEKIShortTitle is needed to complete the data structure
  Short_Title_Type JOSEKIShortTitle ; // 24bytes
  unsigned numCryptoApps : 16 ; // number of Crypto Apps
  unsigned numAEKs : 16 ; // number of AEKs
  Key_Info_Type JosekiTEK ; // 36 bytes
  Key_Info_Type KEK ; // 36 bytes
  Crypto_Sys_Key_Info_Type CryptoAppInfo [ MAX_CRYPTO_APP_NUM ] ;
                                                               // 28 bytes*20
  Crypto_Sys_Key_Info_Type CryptoAEKInfo [ MAX_CRYPTO_AEK_NUM ] ;
                                                               // 28 bytes*10
} Loaded_System_Key_Info_Msg_Type ;
                                  //940 bytes possible
/////////////////// OV_SELECTIVE_ZEROIZE_KEYS_MSGTYPE //////////////////////////
/////////////////// VC_SELECTIVE_ZEROIZE_KEYS_MSGTYPE //////////////////////////
// Description: command to zeroize a single TEK, all TEKs associated
// with an algorithms or all TEKs for Medley. When VP receives
// the OV_SELECTIVE_ZEROIZE_KEYS_MSGTYPE from VLF Control, VP routes it to CP
// using message ID VC_SELECTIVE_ZEROIZE_KEYS_MSGTYPE.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE followed by
// VO_LOADED_KEYS_DATA_MSGTYPE,
// CV_LOADED_KEYS_DATA_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Selective_Zeroize_Keys_Msg_Type
{
  unsigned action : 8 ;//Zeroize_Keys_Action_Type
  unsigned algorithm : 8 ; //Crypto_Alg_MSG_Type,
                                    // must specify for ALGORITHM_SPECIFIC
  unsigned keyBankLoc : 8 ; //Keybank_Type
  unsigned keyBankSegLoc : 8 ; //1..100
} Selective_Zeroize_Keys_Msg_Type ;
                                 //32 bytes = 7 words
/////////////////// OV_SELECTIVE_ZEROIZE_SYSTEM_KEY_DATA_MSGTYPE ///////////////
/////////////////// VC_SELECTIVE_ZEROIZE_SYSTEM_KEY_DATA_MSGTYPE ///////////////
// Description: command to zeroize the system AEKS ot the JOSEKI TEK. When VP
// receives the OV_SELECTIVE_ZEROIZE_SYSTEM_KEY_DATA_MSGTYPE from VLF Control, VP
// routes it to CP using message ID VC_SELECTIVE_ZEROIZE_SYSTEM_KEY_DATA_MSGTYPE
//
// Expected Response: RESPONSE_STATUS_MSGTYPE followed by
// VO_LOADED_SYSTEM_KEY_INFO_MSGTYPE,
// CV_LOADED_SYSTEM_KEY_INFO_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Selective_Zeroize_System_Keys_Msg_Type
{
  unsigned action : 8 ;//Zeroize_System_Keys_Action_Type
  unsigned keyLocation : 8 ;
   // reserved is needed to complete the data structure
  unsigned reserved : 16 ;
} Selective_Zeroize_System_Keys_Msg_Type ;
                                        //32 bytes = 7 words
/////////////////// OV_RUN_IBIT_MSGTYPE //////////////////////////////
// Description: All channels must be stopped prior to VLF Control requesting VLF BIT
// This message will command the VLF receiver to run IBIT. If channels
// are not stopped, a Channel In-Sync error will be returned in the
// Response Status message. To perform IBIT, VLF will perform a reset
// of the VLF receiver. This message only contains the header.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////
/////////////////// OV_REQUEST_PBIT_STATUS_MSGTYPE ///////////////////
// Description: command to run PBIT, this message
// only contains the message header.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE, if not rejected
// followed by VO_RECEIVER_PBIT_RESULT_MSGTYPE
////////////////////////////////////////////////////////////////////
/////////////////// VO_VLF_RECEIVER_PBIT_RESULT_MSGTYPE ///////////////////
// Description: response to the OV_REQUEST_PBIT_STATUS_MSGTYPE
//
// Expected Response: None
//////////////////////////////////////////////////////////////////////
 
typedef
struct Receiver_PBIT_Result_Msg_Type
{
  BIT_Result_Type DSP1BITResults ; //enum DSP1_PBIT_Type
  BIT_Result_Type DSP2BITResults ; //enum DSP2_PBIT_Type
  BIT_Result_Type cryptoBITResults ; //enum Crypto_BIT_Type
} Receiver_PBIT_Result_Msg_Type ;
                               //4 bytes
/////////////////// VO_RECEIVER_CBIT_RESULT_MSGTYPE /////////////////////
// Description: This is an unsolicited message from VLF to report changes
// to CBIT.
// Expected Response: None
////////////////////////////////////////////////////////////////////////
 
typedef
struct Receiver_CBIT_Result_Msg_Type
{
  BIT_Result_Type DSP1BITResults ; //enum DSP1_CBIT_Type
  BIT_Result_Type DSP2BITResults ; //enum DSP2_CBIT_Type
  BIT_Result_Type cryptoBITResults ; //enum Crypto_BIT_Type
} Receiver_CBIT_Result_Msg_Type ;
                               //4 bytes
/////////////////// OV_TIME_AT_THE_TONE_MSGTYPE //////////////////////
// Description: Multicast message containing UTC for the
// next 1PPS. This message is sent once every second
// to the VLF
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Time_At_The_Tone_Msg_Type
{
  Date_Time_Type utcTime ; // 8 bytes
  unsigned offset : 32 ; // Measured in 100ns, 0-10000000
  unsigned timeSrc : 8 ; // Time_Source_Type, Source of UTC message
  unsigned loadType : 8 ; // Load_Type, Load Style: NOT, Auto, Man
  signed timeAccy : 16 ; // Time_Accy_Type
} Time_At_The_Tone_Msg_Type ;
                            //16 bytes - 4 words
/////////////////// OV_SET_ANTI_JAM_MSGTYPE /////////////////////////////////
// Description: Command to toggle mode 15 on and off.
// Expected Response: RESPONSE_STATUS_MSGTYPE
///////////////////////////////////////////////////////////////////////
 
typedef
struct AJ_Cmd_Msg_Type
{
  unsigned channelID : 8 ;//1..5
  unsigned antiJamOnly : 8 ;//bool
   // reserved is needed to complete the data structure
  unsigned reserved : 16 ;
} AJ_Cmd_Msg_Type ;
                  //4 bytes=1 word
/////////////////// OV_VERSION_REQUEST_MSGTYPE /////////////////////////////////
// Description: request to send the version information of the VLF receiver.
// This message contains the message header only.
//
// Expected Response: VO_VLF_RECEIVER_VERSION_DATA_MSGTYPE
///////////////////////////////////////////////////////////////////////
/////////////////// VO_VLF_RECEIVER_VERSION_DATA_MSGTYPE ///////////////////////
// Description: report the version information of the VLF receiver to
// VLF Control in response to the OV_VERSION_REQUEST_MSGTYPE
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
///////////////////////////////////////////////////////////////////////
 
typedef
struct VLF_Receiver_Version_Data_Msg_Type
{
  unsigned numVersions : 32 ; // number of version elements
  Component_Version_Type VersionInfo [ MAX_VERSION_ARRAY_LENGTH ] ;
                                                                //4608
} VLF_Receiver_Version_Data_Msg_Type ;
                                    //4612
/////////////////// OV_REQUEST_SYSTEM_STATUS_MSGTYPE ///////////////////
// Description: request to send the sytem status of
// the VLF receiver. This message contains the message header only.
//
// Expected Response: VO_LEGACY_VLF_RECEIVER_SYSTEM_STATUS_MSGTYPE or
// VO_CVR_SYSTEM_STATUS_MSGTYPE
///////////////////////////////////////////////////////////////////////
/////////////////// VO_LEGACY_VLF_RECEIVER_SYSTEM_STATUS_MSGTYPE ///////////////////
// Description: report the system status for Legacy HMI
// in response to the OV_REQUEST_SYSTEM_STATUS_MSGTYPE
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Legacy_VLF_Receiver_System_Status_Msg_Type
{
  unsigned receiverState : 8 ; //VLF_Receiver_State_Type
  unsigned TimeLoaded : 8 ; //bool
  unsigned CommPlanLoaded : 8 ; //bool
  unsigned KeyTblLoaded : 8 ; //bool
  Crypto_Module_State_Type CMState ; // 4 bytes
  Legacy_VLF_Receiver_Channel_Status_Type chanStatus [ MAX_VLF_CHANNEL ] ;
                                                                        //40 bytes
} Legacy_VLF_Receiver_System_Status_Msg_Type ;
                                             //52 bytes=13word
/////////////////// VO_CVR_SYSTEM_STATUS_MSGTYPE ///////////////////
// Description: report the system status for protocol version=Standard HMI
// in response to the OV_REQUEST_SYSTEM_STATUS_MSGTYPE
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct VLF_Receiver_System_Status_Msg_Type
{
  unsigned receiverState : 8 ; //VLF_Receiver_State_Type
  unsigned TimeLoaded : 8 ; //bool
  unsigned CommPlanLoaded : 8 ; //bool
  unsigned KeyTblLoaded : 8 ; //bool
  Crypto_Module_State_Type CMState ; // 4 bytes
  VLF_Receiver_Channel_Status_Type chanStatus [ MAX_VLF_CHANNEL ] ;
                                                                 //40 bytes
} VLF_Receiver_System_Status_Msg_Type ;
                                      //52 bytes=13word
/////////////////// VV_VLF_CHANNEL_STATE_MSGTYPE //////////////////////////////
// Description: report the channel status. This message is sent when
// there is a change to the channel status.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct VLF_Channel_State_Msg_Type
{
  VLF_Receiver_Channel_Status_Type chanStatus [ MAX_VLF_CHANNEL ] ;
                                                                 //40 bytes
} VLF_Channel_State_Msg_Type ;
                             //40 bytes
/////////////////// VV_VLF_RECEIVER_STATE_MSGTYPE //////////////////////////////
// Description: report the overall Receiver state status. This message is sent
// when there is a change to the overall Receiver state.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct VLF_Receiver_State_Msg_Type
{
  unsigned receiverState : 8 ; //VLF_Receiver_State_Type
  unsigned TimeLoaded : 8 ; //bool
  unsigned CommPlanLoaded : 8 ; //bool
  unsigned KeyTblLoaded : 8 ; //bool
} VLF_Receiver_State_Msg_Type ;
                             //4 bytes
/////////////////// OV_RESTART_RECEIVER_MSGTYPE ///////////////////
// Description: Request from VLF Control to restart the Receiver.
// This message only contains the header. VP will sent a
// VC_RESET_CRYPTO_MSGTYPE to CP.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE, then power on sequence
////////////////////////////////////////////////////////////////////////////////
/////////////////// OV_LINK_IS_LIVE_MSGTYPE ///////////////////////////
// Description: Keep alive message sent from VLF Control periodically to check the
// link. This message only contains the header.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
/////////////////// OV_CONTROLLER_IDENTIFICATION_MSGTYPE ///////////////////
// Description: From VLF Control to VP to request VLF Control
// switch over between VLF Control.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
///////////////////////////////////////////////////////////////////////
 
typedef
struct Controller_Identification_Msg_Type
{
  unsigned mainOES : 8 ;
  unsigned forceCnrtl : 8 ;
   // reserved is needed to complete the data structure
  unsigned reserved : 16 ;
} Controller_Identification_Msg_Type ;
                                    //1 words
/////////////////// VO_ALARM_REPORT_MSGTYPE ////////////////////////////////////
// Description: To report alarm to VLF Control, this message is sent when an
// alarm is set.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Alarm_Report_Msg_Type
{
  unsigned alarm : 8 ;//VLF_Alarm_Type
  unsigned status : 8 ;//bool, false=clear, true=set
  unsigned category : 8 ;//Alarm_Category_Type
  unsigned source : 8 ;//Alarm_Source_Type
  Crypto_Alarm_Registers_Type cpAlarmRegs ; //4 registers, 2 words
  Crypto_Status_Registers_Type cpStatusRegs ; //2 registers, 1 word
} Alarm_Report_Msg_Type ;
                        //4 words
/////////////////// VO_VLF_LF_DATA_MSGTYPE /////////////////////////////////////
// Description: VP sends to VLF Control automatically when data available.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct VLF_LF_Data_Msg_Type
{
  unsigned channelID : 8 ;//1..5
  unsigned mode : 8 ;//Tx_Mode_Type
  unsigned dataSegment : 8 ;//VLF_Data_Segment_Type
  unsigned msgSegment : 8 ;//VLF_Data_Msg_Type
  unsigned charCount : 32 ; //0..6050
  char text [ MAX_EAM_CHAR_COUNT ] ;
} VLF_LF_Data_Msg_Type ;
                      //6060
/////////////////// VO_VLF_STREAM_DATA_MSGTYPE //////////////////////////////////
// Description: VP sends to VLF Control automatically when stream data available.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct VLF_Stream_Data_Msg_Type
{
  unsigned channelID : 8 ;//1..5
  unsigned mode : 8 ;//Tx_Mode_Type
  unsigned charCount : 16 ; //0..64
  char text [ MAX_STREAM_CHAR_COUNT ] ;
} VLF_Stream_Data_Msg_Type ;
                          //17 words
/////////////////// OV_WRITE_KEY_EFFECTIVITY_DATA_MSGTYPE //////////////////////////
// Description: This message is used to send the Effectivity date for each TEK
// loaded in a key bank. OV_GET_LOADED_KEYS_MSGTYPE must be send prior or, TEK
// valid flag needs to be set.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Write_Key_Effectivity_Data_Msg_Type
{
  unsigned numKeys : 8 ; // (0 - 100) number of TEKs loaded in the message
  unsigned lastMsg : 8 ; // (0 - 1) flag which indicates that this message is
                                     // the last message in the series of key messages
  unsigned reserved : 16 ; // (0) needed to complete data structure
  Key_Effectivity_Data_Type KeyEffectData [ MAX_TEKS_PER_BANK ] ;
} Write_Key_Effectivity_Data_Msg_Type ;
                                     //3204 bytes = 801 words
/////////////////// VO_SOFTWARE_ANOMALY_LOG_MSGTYPE ///////////////////////////
// Description: To report software errors to VLF Control.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
//////////////////////////////////////////////////////////////////////////////
 
typedef
struct Software_Anomaly_log_Msg_Type
{
  char errorString [ MAX_SOFT_ANOM_ARRAY_LEN ] ;
} Software_Anomaly_log_Msg_Type ;
/////////////////// VO_KEY_DISPOSITION_STATUS //////////////////////////
// Description: This message is used to send the Key Disposition Status
// for a key that has been autonomoulsy zeroized by the VLF Receiver,
// as part of the rollover process.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Key_Disposition_Status_Msg_Type
{
  unsigned keyBankLoc : 8 ; // bank loc 1, 2, 4, 5
  unsigned keyBankSegLoc : 8 ; // segment loc 1-100
  unsigned status : 8 ; // 0 = failure, 1 = pass
   // reserved is part of the data structure and is necessary for space
  unsigned reserved : 8 ;
} Key_Disposition_Status_Msg_Type ;
                                  //4 bytes = 1 word
///////////////////// OV_START_SEQUENCE_NUMBER_MSGTYPE ///////////////////////
// Description: The starting sequence number to be used for EAM messages.
//
//////////////////////////////////////////////////////////////////////////////
 
typedef
struct Start_Sequence_Number_Msg_Type
{
  unsigned Sequence_Number : 32 ; // Starting Sequence Number for EAMs
} Start_Sequence_Number_Msg_Type ;
                                 //4 bytes = 1 word
/*************************************************************************/
/* Messages specific between CP and VP */
/*************************************************************************/
/////////////////// VC_CONFIGURE_CHANNEL_MSGTYPE ///////////////////
// Description: Command to CP to command the PEIP to configure a
// channel for keystream generation.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE of FAILED or SUCCESS
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Configure_Channel_Msg_Type
{
  unsigned channelID : 32 ; //1..5, 4 bytes
  Key_Bank_Info_Type keyInfo ; //4 bytes
  unsigned transmitterNum : 32 ; //0..9, 4 bytes
} Configure_Channel_Msg_Type ;
                             //12 bytes
/////////////////// VC_RUNUP_CHANNEL_MSGTYPE ///////////////////////////////////
// Description: Command to CP to command the PEIP to do a runnup
// on a configured channel.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE of FAILED or SUCCESS
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Runup_Channel_Msg_Type
{
  unsigned channelID : 32 ; //1..5, 4 bytes
  unsigned seconds : 32 ; //to calculate #bits to
  unsigned frames : 32 ; //runup to
} Runup_Channel_Msg_Type ;
                         //12 bytes
/////////////////// VC_ZEROIZE_CHANNEL_MSGTYPE /////////////////////////////////
// Description: Command to CP to command the PEIP to zeroize
// a configured channel. Note: when a channel is zeroized, all
// key association with the channel will be zeroized also. In
// order to use the channel again, the channel must be re-configured.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE of FAILED or SUCCESS
// and followed by CV_CRYPTO_CHANNEL_STATE_MSGTYPE if the SUCCESS.
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Zeroize_Channel_Msg_Type
{
  unsigned channelID : 32 ; //1..5, 4 bytes
} Zeroize_Channel_Msg_Type ;
                           //4 bytes
/////////////////// CV_OES_STATE_REQUEST_MSGTYPE ///////////////////
// Description: To check if the OES is connected, this message
// only contains the message header.
//
// Expected Response: VC_OES_STATE_MSGTYPE
////////////////////////////////////////////////////////////////////
/////////////////// VC_CRYPTO_VERSION_REQUEST_MSGTYPE //////////////////////////
// Description: request to send the version information of crypto module of
// the VLF receiver. This message contains the message header only.
//
// Expected Response: CV_CRYPTO_VERSION_DATA_MSGTYPE
///////////////////////////////////////////////////////////////////////
/////////////////// CV_CRYPTO_VERSION_DATA_MSGTYPE ///////////////////
/////////////////// VV_DSP1_VERSION_DATA_MSGTYPE ///////////////////
// Description: internal message that reports the version information
// of DSP1 and the crypto processor to DSP2 for collection and
// output to the VLF Control.
//
// In response to the OV_VERSION_REQUEST in DSP1
// and VC_CRYPTO_VERSION_REQUEST_MSGTYPE
//
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Version_Data_Msg_Type
{
  unsigned numVersions : 32 ; // number of version elements
  Component_Version_Type VersionInfo [ MAX_INT_VERSION_ARR_LEN ] ;
                                                                // 96*16=1536
} Version_Data_Msg_Type ;
                        //1540 bytes
/////////////////// VC_REQUEST_CRYPTO_SYSTEM_STATUS_MSGTYPE ///////////////////
// Description: request to send the crypto sytem status of
// the VLF receiver. This message contains the message header only.
//
// Expected Response: CV_CRYPTO_SYSTEM_STATUS_MSGTYPE
///////////////////////////////////////////////////////////////////////
/////////////////// CV_CRYPTO_SYSTEM_STATUS_MSGTYPE ///////////////////
// Description: report the Crypto system status
// in response to the VC_REQUEST_CRYPTO_SYSTEM_STATUS_MSGTYPE
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
//
// This structure is shared (for efficiency) by the 'Crypto Status IO Device' ('CPStatusIOD')
//
 
typedef
struct Crypto_System_Status_Msg_Type
{
  Crypto_Module_State_Type CMState ;//32
  unsigned cryptoChanState [ MAX_VLF_CHANNEL ] ;
                                             //Crypto_Channel_State_Type
  unsigned peipBatteryFaultIndicator : 32 ;// Least sig bit is 1 for fault, otherwise zero.
} Crypto_System_Status_Msg_Type ;
/////////////////// CV_CRYPTO_CHANNEL_STATE_MSGTYPE ////////////////////////////
// Description: report the channel status. This message is sent when
// there is a change to the channel status.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
///////////////////////////////////////////////////////////////////////
 
typedef
struct Crypto_Channel_State_Msg_Type
{
  unsigned channelID : 8 ; //Channel_ID_Type
  unsigned cryptoChanState : 8 ;//Crypto_Channel_State_Type
   // reserved is needed to complete the data structure
  unsigned reserved : 16 ;
} Crypto_Channel_State_Msg_Type ;
                                //4 bytes
/////////////////// CV_CRYPTO_MODULE_STATE_MSGTYPE /////////////////////////////
// Description: report the overall crypto module status. This message is sent
// when there is a change to the overall Receiver status.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
///////////////////////////////////////////////////////////////////////
 
typedef
struct Crypto_Module_State_Msg_Type
{
  Crypto_Module_State_Type CMState ;//32
} Crypto_Module_State_Msg_Type ;
                              //4 bytes
/////////////////// VC_DSP1_LINK_IS_LIVE_MSGTYPE ///////////////////
// Description: Keep alive message sent from VP to CP periodically to check
// the link. This message only contains the header.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
///////////////////////////////////////////////////////////////////////
/////////////////// VC_REQUEST_PBIT_STATUS_MSGTYPE ///////////////////
// Description: command the Crypto to run PBIT, this message
// only contains the message header.
//
// Expected Response: CV_CRYPTO_PBIT_RESULT_MSGTYPE
//////////////////////////////////////////////////////////////////////
/////////////////// CV_CRYPTO_PBIT_RESULT_MSGTYPE ///////////////////
// Description: response to command VC_REQUEST_PBIT_STATUS_MSGTYPE
//
// Expected Response: None
////////////////////////////////////////////////////////////////////
/////////////////// CV_CRYPTO_CBIT_RESULT_MSGTYPE ///////////////////
// Description: Unsolicited Crypto CBIT status
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////
 
typedef
struct Crypto_BIT_Result_Msg_Type
{
  BIT_Result_Type cryptoBITResults ; //1 word
  Crypto_Alarm_Registers_Type cpAlarmRegs ; // 2 words
  Crypto_Status_Registers_Type cpStatusRegs ; // 1 word
} Crypto_BIT_Result_Msg_Type ;
                             //4 words
////////////////////////////////////////////////////////////////////////////////
//
// Software Certification Message Section
//
////////////////////////////////////////////////////////////////////////////////
/////////////////// OV_PERFORMANCE_MONITORING_ENABLE_MSGTYPE /////////
// Description: Command to enable performance monitoring.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE then
// VO_PM_DATA_MSGTYPE and VO_HIDAR_OP_STAT_MSGTYPE sent as needed.
//////////////////////////////////////////////////////////////////////
 
typedef
struct Performance_Monitoring_Enable_Msg_Type
{
  unsigned channelID : 8 ;//1..5
  unsigned enableHIDAROPSTAT : 8 ;//bool
  unsigned enableVLFPM : 8 ;//bool
  unsigned reserved : 8 ;
} Performance_Monitoring_Enable_Msg_Type ;
                                         //4bytes=1word
/////////////////// VO_HIDAR_OPSTAT_MSGTYPE ////////////////////////////////////
// Description: HIDAR Operational status to be sent to VLF Control if the
// performance monitoring was enabled for HIDAR_OPSTAT
// OV_PERFORMANCE_MONITORING_ENABLE_MSGTYPE. The MMRT ICD indicates
// that the data will not exceed 1440 bytes/sec.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
/////////////////// VO_PM_DATA_MSGTYPE /////////////////////////////////////////
// Description: Performance monitoring status to be sent to VLF Control if the
// performance monitoring was enabled for VLF PM in the
// OV_PERFORMANCE_MONITORING_ENABLE_MSGTYPE.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
////////////////////////// VO_CEP_DATA_MSGTYPE ////////////////////////
// Description: VLF Receiver data for the Continuing Evaluation Program (CEP)
// that contains the information provided by the HIDAR Opstat and PM Data
// operationally from the waveforms NM15, M9, and HIDAR
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
///////////////////////////////////////////////////////////////////////
 
typedef
struct Performance_Data_Msg_Type
{
  unsigned channelID : 8 ; //1..5
  unsigned cep_enabled : 8 ; // bool [true/false]
  unsigned reserved : 16 ;
  unsigned char performanceData [ MAX_OPSTAT_PM_DATA_COUNT ] ;
} Performance_Data_Msg_Type ;
                            // 1444 bytes = 361 words
/////////////////// OV_CONFIGURATION_PARAMS_MSGTYPE ////////////////////////////
// Description: From VLF Control to VLF to set the configuration parameters as
// part of power on sequence.
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
////////////////////////////////////////////////////////////////////////////////
 
typedef
struct Configuration_Params_Msg_Type
{
  unsigned SM_NONAP_Bypass : 8 ; // bool, false=No_Bypass, true=Bypass
  unsigned M9_EDAC_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned Auto_TimeLoad_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned CEP_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned WB_Noise_Reduction_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned NB_Noise_Reduction_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned WB_Limiter_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned M15_Letters_Case_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned M15_Msg_Filter_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned M9_Msg_Filter_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned MMPM_Framing_Advis_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned M15_Msg_Piecing_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned Sync_Status_Bypass : 8 ; // bool, false=Disabled, true=Enabled
  unsigned Print_Control_Chars_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned Print_Hamming_M9_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned Auto_Gain_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned Manual_Gain_Digi : 16 ; // Floating Point Number
  unsigned Manual_Gain_Deci : 16 ; // Floating Point Number
  signed Manual_Gain_Expo : 16 ; // Floating Point Number
  signed Timing_Offset : 16 ; // Frames +- adjustment
  unsigned Dither_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned Ant1_Test_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned Ant2_Test_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned RFA_Test_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned KG_Bypass_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned SPECTRAL_PEAKS_Bypass : 8 ; // bool, false=No_Bypass, true=Bypass
  unsigned VM23_Msg_Filter_Enabled : 8 ; // bool, false=Disabled, true=Enabled
  unsigned Reserved8 : 8 ; // Keeps the data word aligned
} Configuration_Params_Msg_Type ;
                                 //
/////////////////// ModeConfigParamsType ////////////////////////////
// Description: One enumeration value is defined for each
// value in Configuration_Params_Msg_Type
////////////////////////////////////////////////////////////////////////////////
 
typedef
enum ModeConfigParamsType
{
  SM_NONAP_BYPASS = 0 ,
  M9_EDAC_ENABLED ,
  AUTO_TIMELOAD_ENABLED ,
  CEP_ENABLED ,
  WB_NOISE_REDUCTION_ENABLED ,
  NB_NOISE_REDUCTION_ENABLED ,
  WB_LIMITER_ENABLED ,
  M15_LETTERS_CASE_ENABLED ,
  M15_MSG_FILTER_ENABLED ,
  M9_MSG_FILTER_ENABLED ,
  MMPM_FRAMING_ADVIS_ENABLED ,
  M15_MSG_PIECING_ENABLED ,
  SYNC_STATUS_BYPASS ,
  PRINT_CONTROL_CHARS_ENABLED ,
  PRINT_HAMMING_M9_ENABLED ,
  AUTO_GAIN_ENABLED ,
  MANUAL_GAIN_DIGI ,
  MANUAL_GAIN_DECI ,
  MANUAL_GAIN_EXPO ,
  TIMING_OFFSET ,
  DITHER_ENABLED ,
  ANT1_TEST_ENABLED ,
  ANT2_TEST_ENABLED ,
  RFA_TEST_ENABLED ,
  KG_BYPASS_ENABLED ,
  SPECTRAL_PEAKS_BYPASS ,
  VM23_MSG_FILTER_ENABLED ,
   // Place all entries above the param count
  NUM_MODE_CONFIG_PARAMS
} ModeConfigParamsType ;
// configuration parameter boolean status types
 
static const int
  PARAM_ENABLED = 1 ;
 
static const int
  PARAM_DISABLED = 0 ;
/////////////////// SAMPLE_OUTPUT_DATA_TEST_MSGTYPE ///////////////////
// Description: From VLF Control to VLF to enable or disable the ability to
// output the FPGA Sample Data to the VLF Control for Data Collection,
//
// Expected Response: RESPONSE_STATUS_MSGTYPE
///////////////////////////////////////////////////////////////////////
 
typedef
struct Sample_Output_Test_Enable_Msg_Type
{
  unsigned channelID : 8 ; // 1..5
  unsigned reserved : 8 ; // reserved
  unsigned count : 16 ; // num 20msecs of data to collect
  unsigned frequency : 32 ; // 0-MAX_TESTING_FREQ
  unsigned sampleAddr : 32 ; // FPGA_Sample_Address_Type [1,2,3,4]
} Sample_Output_Test_Enable_Msg_Type ;
                                      //
/////////////////// SAMPLE_OUTPUT_DATA_TEST_MSGTYPE ///////////////////
// Description: DSP1 Output Sample from FPGA to VLF Control in response to
// Sample_Output_Test_Enable_Msg_Type command.
//
///////////////////////////////////////////////////////////////////////
 
typedef
struct Sample_Output_Data_Msg_Type
{
  unsigned channelID : 8 ; //1..5
   // reserved is needed to complete the data structure
  unsigned reserved : 24 ; //reserved
  signed int fpgaData [ MAX_SAMPLE_WORDS_PER_MSG ] ;
                                                  //the message data
} Sample_Output_Data_Msg_Type ;
                               //
       //MSG_DEFS_H
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg_defs.h*/
/*   CLOSE_FILE Include File */
 
#define CH1_FREQ 28000
#define CH2_FREQ 28000
#define CH3_FREQ 28000
#define CH4_FREQ 28000
#define CH5_FREQ 28000
//////////////////////////////////////////////////////
//Messages definitions from MGR to CH address space //
//////////////////////////////////////////////////////
// Channel Identifier type
 
typedef
enum ChannelIdType
{
  NULL_CHANNEL = 0 ,
  CHANNEL_1 = 1 ,
  CHANNEL_2 = 2 ,
  CHANNEL_3 = 3 ,
  CHANNEL_4 = 4 ,
  CHANNEL_5 = 5
} ChannelIdType ;
//Command IDs from MGR to CH address space
 
typedef
enum ChanCmdType
{
  CHAN_INVALID_CMD = 0 ,
  CHAN_MODE_CMD = 1 ,//use the Mode_Command_Type for each of the mode
  COMM_PLAN_CMD = 2 ,//use to set comm plan to the channel
  CONFIG_PARAM_CMD = 3 ,//used to set configuration parameters
  PM_ENABLE_CMD = 4 ,//used to set Performance Monitoring(PM)
  CHAN_CMD_MAX
} ChanCmdType ;
//Message ID from CH to MGR address space
 
typedef
enum ChanStatusMsgType
{
  CHAN_STATUS_INVALID = 0 ,
  CHAN_MODE_STATUS = 1 ,
  CHAN_STATUS_ALIVE = 2 ,
  CHAN_STATUS_MAX = 3
} ChanStatusMsgType ;
//Command to control each mode converted to C from Mode_Command_Type
//in sp_ep_defs.ads
 
typedef
enum Mode_Command_Type
{
  UNDEFINED = 0 ,
  INIT_MODE_SEARCH = 1 ,
  DATA_VALID = 2 ,
  CONTINUE_IDLE_OPERATION = 3 ,
  HALT_SEARCH = 4 ,
  HALT_SEARCH_FRCD = 5
} Mode_Command_Type ;
//Converted from the Mode_Command_Error_Type defined in sp_ep_defs.ads
 
typedef
enum Mode_Command_Error_Type
{
  NO_ERROR_PRESENT = 0 ,
  NO_COMMAND_RECEIVED = 1 ,
  ILLEGAL_INIT_MODE_SEARCH_COMMAND = 2 ,
  ILLEGAL_DATA_VALID_COMMAND = 3 ,
  ILLEGAL_CONTINUE_OPERATION_COMMAND = 4 ,
  ILLEGAL_HALT_SEARCH_COMMAND = 5 ,
  EXCESSIVE_MODE_SEARCH_COMMAND = 14 ,
  UNKNOWN_COMMAND = 15
} Mode_Command_Error_Type ;
//converted Expanded_Mode_Scan_State_Type in sp_defs.ads will use for all mode
 
typedef
enum Expanded_Mode_Scan_State_Type
{
  MODE_NO_STATUS = 0 ,
  MODE_SEARCH_HALTED = 1 ,
  MODE_SEARCH_INITIALIZING = 2 ,
  MODE_SEARCHING = 3 ,
  MODE_IN_SYNC = 4 ,
  MODE_NO_SYNC = 5 ,
  MODE_SCAN_HOLD = 6 , // Used for M9/MMPM
  MODE_SYNC_HOLD = 7  // Used for SMA
} Expanded_Mode_Scan_State_Type ;
// converted from the Mode_Signal_Status_Type in sp_ep_defs.ads to be
// used for all modes.
// Note: M15 will not use the MODE_SCAN_HOLD for Mode_Command_Error_Type
//
 
typedef
struct Mode_Signal_Status_Type
{
  Mode_Command_Error_Type modeCmdError : 16 ;
  Expanded_Mode_Scan_State_Type modeScanState : 16 ;
} Mode_Signal_Status_Type ;
// Converted from the SP_Status_Section_Type in sp_ep_defs.ads
// The mode status is used to by the Channel Address space to
// keep track of the Mode status and report back to the MGR in
// response to the CHAN_MODE_CMD.
 
typedef
struct ModeStatusDataType
{
  Mode_Signal_Status_Type statusMode15 ;
  Mode_Signal_Status_Type statusMode9 ;
  Mode_Signal_Status_Type statusModeHIDAR ;
  Mode_Signal_Status_Type statusMode23 ;
  Mode_Signal_Status_Type statusModeSMA ;
} ModeStatusDataType ;
//Used when COMM_PLAN_CMD is set for ChanCmdType. This message can only
//be processed when the channel is stopped.
//The structure used some of the fields from SP_Parameterized_Data_Type and
//the SP_Data_Location_Type the shared RAM defined in sp_ep_defs.ads.
 
typedef
struct CommPlanStruct
{
  unsigned short transmitterNum ;
  unsigned short freqOfChannel ;//in DECAHERTZ 1400 - 6000 range
  bool mode15_enabled ;
  bool mode9_enabled ;
  bool modeHIDAR_enabled ;
  unsigned char mode23_enabled ;
  bool modeSMA_enabled ;
  bool reserved1 ;
  bool reserved2 ;
  bool reserved3 ;
} CommPlanStruct ;
 
typedef
struct PMEnableStruct
{
  bool enableHIDAROPSTAT ;
  bool enableVLFPM ;
} PMEnableStruct ;
// This struct must match the ada srtuct in sp_ep_defs.ads Configuration_Params_Type
// when DSP2 ada is gone use the mgs_defs.h Configuration_Params_Msg_Type
 
typedef
struct ConfigurationParamsType
{
  bool M9_EDAC_Enabled ;  // false=Disabled, true=Enabled
  bool CEP_Enabled ;  // false=Disabled, true=Enabled
  bool MMPM_Framing_Advis_Enabled ;  // false=Disabled, true=Enabled
  bool Print_Control_Chars_Enabled ; // false=Disabled, true=Enabled
  bool Print_Hamming_M9_Enabled ;  // false=Disabled, true=Enabled
  bool M9_Msg_Filter_Enabled ;  // false=Disabled, true=Enabled
  bool KG_Bypass_Enabled ;  // false=Disabled, true=Enabled
  bool VM23_Msg_Filter_Enabled ;  // false=Disabled, true=Enabled
} ConfigurationParamsType ;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\VPCommon\channel_defs.h*/
/*   CLOSE_FILE Include File */
 
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg_defs.h"
                                                                                                      // LDRA full path
//The ChanModeCmdStruct is used when CHAN_MODE_CMD is set for ChanCmdType.
// Commands - converted SP_Command_Section_Type
// Mode_Parameters - is Absolute_Time_Type converted from
// SP_Mode_Parameters_Section_Type this will be sent every 20ms
// interrupt for all commands from MGR to the CH.
// Status_Data are statuses that will be sent
// from CH to MGR address space or to the transmit Ethernet queue which
// will be discussed later.
//
// Mode_Command_Array Index:
// NO_MODE_SPECIFIED = 0,
// NORMAL_MODE_15 = 1,
// SPECIAL_MODE_9 = 2,
// SPECIAL_MODE_HIDAR = 3,
// VERDIN_MODE_23 = 4,
// SPECIAL_MODE_A = 5,
 
typedef
Mode_Command_Type
  Mode_Command_Array [ TX_MODE_TYPE_MAX ] ;
 
typedef
struct ChanModeStruct
{
  Mode_Command_Array commands ;
  Absolute_Time_Type absTime ;
} ChanModeStruct ;
////////////////////////////////////////////////////////////////////////////
// MGR TO CHANNEL STRUCTURE:
// This structure is used to talk with CHx's AddressSpace. It
// contains MGR commands and FPGA Output Sample index (latest one filled)
// for this channel. It is used with the MGR to CHx Queue. This queue will
// be filled once every 20 msec. This same structure is also used to get
// commands from the Message Processing Task to the Coord_SP_Task
////////////////////////////////////////////////////////////////////////////
 
typedef
struct ChannelCmdStruct
{
  int channel ;
  int index ;
  ChanCmdType cmd ;
  union
  {
    ChanModeStruct modeCmdData ;  //CHAN_MODE_CMD
    CommPlanStruct commPlanConfig ;  //COMM_PLAN_CMD
    PMEnableStruct pmEnableConfig ;  //PM_ENABLE_CMD
    Configuration_Params_Msg_Type configParams ;  //CONFIG_PARAM_CMD
  } cmdData ;
} ChannelCmdStruct ;
//////////////////////////////////////////////////////
//Messages definitions from CH to MRG address space //
//////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// CHANNEL TO MGR STRUCTURE:
// This structure is used to send the status to the MGR from the CHx's
// AddressSpace. This is used with the Channel status Queue. This queue will
// be filled once every 20 msec by the CHx's addressSpace.
////////////////////////////////////////////////////////////////////////////
 
typedef
struct ChannelStatusStruct
{
  int channel ;
  ChanStatusMsgType msg ;
  ModeStatusDataType modeStatus ;
} ChannelStatusStruct ;
 
typedef
struct ChanStatusMsgStruct
{
  MessageQueue queueChStatus ;
  ChannelStatusStruct * statusBuffer ;
} ChanStatusMsgStruct ;
 
typedef
struct ChanStatusQueueStruct
{
  Connection connection ;
  MessageQueue queueChStatus ;
  ChannelStatusStruct * statusBuffer ;
} ChanStatusQueueStruct ;
////////////////////////////////////////////////////////////////////////////
// CHANNEL STRUCTURE:
// This structure is used by the Manager AddressSpace channel object
// to manage the channel mode processing
////////////////////////////////////////////////////////////////////////////
 
typedef
struct MgrChCmdQueueStruct
{
  unsigned short freq ;
  Connection connection ;
  MessageQueue queueChCmd ;
  ChannelCmdStruct * cmdBuffer ;
} MgrChCmdQueueStruct ;
////////////////////////////////////////////////////////////////////////////
// Message Processing Structure:
// This structure is used by the Manager AddressSpace Secondary Message
// Processing Task. It allows for the group of Conditions, Semaphores,
// and Task Variables to be located under on structure.
////////////////////////////////////////////////////////////////////////////
 
typedef
struct Sec_Msg_Command_Type
{
  unsigned msgActionID : 32 ;
  unsigned msgAction : 16 ;
  unsigned msgError : 16 ;
} Sec_Msg_Command_Type ;
 
typedef
struct Secondary_Msg_Proc_Type
{
  Semaphore sMsgAction ;
  Semaphore sMsgConfig ;
  Semaphore sMsgRunup ;
  Semaphore sMsgZeroize ;
  Condition conAction ;
  Condition conConfig ;
  Condition conRunup ;
  Condition conZeroize ;
  Sec_Msg_Command_Type secProcMsg ;
} Secondary_Msg_Proc_Type ;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\VPCommon\chan_struct.h*/
/*   CLOSE_FILE Include File */
 
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg_defs.h"
                                                                                                      // LDRA full path
///////////////////////////////////////////////////////////////////////////////
//
// Class: CMode
//
// Description:
// This is base class used to derive specific mode
// class (M15, M9, and HIDAR)
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100036100{ public:  /* 76 */
 ldra_class_1100036100(){ };
 ldra_class_1100036100(int i){ };
};
class CMode
        :public ldra_class_1100036100 /* 75 */
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  Mode_Command_Type mCommand ;
  Mode_Command_Type mPrevCommand ;
   //ModeStatusDataType received from the CH address Space.
  Mode_Signal_Status_Type mChanModeStatus ;
  Mode_Signal_Status_Type mPrevChanModeStatus ;
  long mCnt20ms ;
  static const unsigned char NUM_20MSEC_FOR_INIT = 2 ;
  static const unsigned char NUM_20MSEC_FOR_DATA_VALID = 8 ;
   // constructor
  CMode () ;
   // destructor
 
  ~CMode ()
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_1)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 <<  0))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 <<  1))); /* 30 */
    CChannelState_11zqendz                                                                               (       2 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
  void HandleMgrCmd ( ChannelCmdStruct * mgrCmd ) ;
  Channel_Mode_Processing_Status_Type GetStatus () ;
  Mode_Command_Type GetNextCmd () ;
   // CMode15 will need to override HandleStatus().
   // The other derived classes can use this function from the base class.
  virtual void HandleStatus ( ChanStatusQueueStruct * chstatus ) ;
  protected :
  unsigned int mChanMode ;
   //Status to be reported to OES by the channel
  Channel_Mode_Processing_Status_Type mModeStatus ;
   // All derived classes must override GetModeSignalStatusType()
  virtual Mode_Signal_Status_Type GetModeSignalStatusType ( ChanStatusQueueStruct * chstatus ) = 0 ;
} ;
///////////////////////////////////////////////////////////////////////////////
//
// Class: CMode15
//
// Description:
// This this class is used to handles the command and status for Mode 15
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100046100{ public:  /* 76 */
 ldra_class_1100046100(){ };
 ldra_class_1100046100(int i){ };
};
class CMode15 :
        public ldra_class_1100046100, /* 69 */
public CMode
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
   // constructor
  CMode15 () ;
   // destructor
 
  ~CMode15 ()
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_2)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 <<  2))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 <<  3))); /* 30 */
    CChannelState_11zqendz                                                                               (       4 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
   // We'll need to override the default status handling for Mode 15.
  void HandleStatus ( ChanStatusQueueStruct * chstatus ) ;
  protected :
  Mode_Signal_Status_Type GetModeSignalStatusType ( ChanStatusQueueStruct * chstatus ) ;
} ;
///////////////////////////////////////////////////////////////////////////////
//
// Class: CMode9
//
// Description:
// This this class is used to handles the command and status for Mode 9
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100056100{ public:  /* 76 */
 ldra_class_1100056100(){ };
 ldra_class_1100056100(int i){ };
};
class CMode9 :
        public ldra_class_1100056100, /* 69 */
public CMode
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
   // constructor
  CMode9 () ;
   // destructor
 
  ~CMode9 ()
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_3)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 <<  4))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 <<  5))); /* 30 */
    CChannelState_11zqendz                                                                               (       6 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
  protected :
  Mode_Signal_Status_Type GetModeSignalStatusType ( ChanStatusQueueStruct * chstatus ) ;
} ;
///////////////////////////////////////////////////////////////////////////////
//
// Class: CModeHIDAR
//
// Description:
// This this class is used to handles the command and status for mode HIDAR
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100066100{ public:  /* 76 */
 ldra_class_1100066100(){ };
 ldra_class_1100066100(int i){ };
};
class CModeHidar :
        public ldra_class_1100066100, /* 69 */
public CMode
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
   // constructor
  CModeHidar () ;
   // destructor
 
  ~CModeHidar ()
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_4)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 <<  6))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 <<  7))); /* 30 */
    CChannelState_11zqendz                                                                               (       8 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
  protected :
  Mode_Signal_Status_Type GetModeSignalStatusType ( ChanStatusQueueStruct * chstatus ) ;
} ;
///////////////////////////////////////////////////////////////////////////////
//
// Class: CMode23
//
// Description:
// This this class is used to handles the command and status for Mode 23
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100076100{ public:  /* 76 */
 ldra_class_1100076100(){ };
 ldra_class_1100076100(int i){ };
};
class CMode23 :
        public ldra_class_1100076100, /* 69 */
public CMode
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
   // constructor
  CMode23 () ;
   // destructor
 
  ~CMode23 ()
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_5)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 <<  8))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 <<  9))); /* 30 */
    CChannelState_11zqendz                                                                               (      10 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
  protected :
  Mode_Signal_Status_Type GetModeSignalStatusType ( ChanStatusQueueStruct * chstatus ) ;
} ;
///////////////////////////////////////////////////////////////////////////////
//
// Class: CModeSMA
//
// Description:
// This this class is used to handles the command and status for SMA (UMM)
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100086100{ public:  /* 76 */
 ldra_class_1100086100(){ };
 ldra_class_1100086100(int i){ };
};
class CModeSMA :
        public ldra_class_1100086100, /* 69 */
public CMode
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
   // constructor
  CModeSMA () ;
   // destructor
 
  ~CModeSMA ()
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_6)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 10))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 11))); /* 30 */
    CChannelState_11zqendz                                                                               (      12 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
  protected :
  Mode_Signal_Status_Type GetModeSignalStatusType ( ChanStatusQueueStruct * chstatus ) ;
} ;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CMode.h*/
/*   CLOSE_FILE Include File */
 
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg_defs.h"
                                                                                                      // LDRA full path
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\VPCommon\utility.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2019, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// Function: Utility Functions
//
// File Name: utility.h
//
// Description: This include file contains prototype and constants associated
// with the general utility functions that are used within the
// Manager Virtual Address Space of the VpGemApp - VpGemsApp2
// programs.
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
#ifndef UTILITY_H
#define UTILITY_H
#include <INTEGRITY.h>
                       // needed for Error data type
#include <string>
#include <sstream>
//
// Function Proto-types
//
 
extern void
  CHECK (
  Error theError ,
  const char * file ,
  const char * function ,
  int line ,
  const int chanNum = 0 ) ;
// message to output to serial port for diagnotics
 
void
  serial_output_msg (
  const char * out_msg ) ;
// function for sending software anomaly message for failures
 
void
  send_sa_msg (
  const char * err_msg ) ;
 
void
  save_error (
  const char * err_msg ) ;
// functions for parameter checking
 
bool
  check4Null (
  void * pointer ,
  char * file ,
  int line ) ;
       //UTILITY_H
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\VPCommon\utility.h*/
/*   CLOSE_FILE Include File */
 
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\HwDevice\FpgaDevice.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2019, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// Class: FpgaDevice
//
// File Name: FpgaDevice.h
//
// Description: This file is an include file that contains the class prototypes
// of the FpgaDevice Class and inline FpgaDevice methods. This
// class is used to give the caller full access to the FPGA device,
// including reading data directly out of the FPGA, while hiding
// the FPGA's hardware implementation.
//
// Notes: This class is based on the information contained in the Document
// "Rockwell Collins, Inc. Design Implmentation Guide for the VLF
// Digital Tuner FPGA"
//
// The user may only set the frequency of the 5 channels to a value
// between 0 Hz and 81910 Hz (MAX_FREQ_HZ). Any other value will
// return an error 'FpgaRangeError'.
//
// The user may only set the 1PPS Time Offset calue to a value
// between 0 3199 (MAX_1PPS). Any other value will return an
// error 'FpgaRangeError'.
//
// The constuctor will try to configure the FPGA only once. If
// it fails, the FpgaDevice will record the failure which should
// be reported to the OES. If the constructor can not configure
// the FPGA, the only way the FPGA can configured again is to
// reboot the VLF Board because the ConfigureFpga() method is
// private.
//
// This class should only be used as a base class. To prevent
// someone from instanting multiple copies of this class, the
// constructor/destructor are defined as protected (See
// FpgaDeviceSingleton.h).
//
//
///////////////////////////////////////////////////////////////////////////////
#ifndef FPGADEVICE_H
#define FPGADEVICE_H
#include <INTEGRITY.h>
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpBsp\FpgaIoDevice.h"
                                                                                             // LDRA full path
#include <string>
#include <sstream>
 


class ldra_class_1100096100{ public:  /* 76 */
 ldra_class_1100096100(){ };
 ldra_class_1100096100(int i){ };
};
class FpgaDevice
        :public ldra_class_1100096100 /* 75 */
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
//********************************************************************
// Enums and Constants
//********************************************************************
  public :
    // Error Codes used to indicate the state of the FpgaDevice Object.
    // See xltError[] for its English translation.
  enum ERROR
  {
    FpgaFailed = 1 ,
    FpgaBadConfigCount = 2 ,
    FpgaStatusStuckLow = 3 ,
    FpgaStatusStuckHigh = 4 ,
    FpgaConfigDoneStuckLow = 5 ,
    FpgaConfigDoneStuckHigh = 6 ,
    FpgaConfigError = 7 ,
    FpgaGpioError = 8 ,
    FpgaRangeError = 9 ,
    FpgaSuccess = 10 ,
    FpgaMaxError
  } ;
  enum FREQ_CHAN
  {
    FreqChan1 = 0 ,                 // Legal Frequency Channels
    FreqChan2 = 1 ,
    FreqChan3 = 2 ,
    FreqChan4 = 3 ,
    FreqChan5 = 4
  } ;
    //
    // NOTE: These constants must be declared public since they are
    // used in various structure.
    // Fixed length of the Configuration Data (in bytes).
    // NOTE: The SHA-1 in front of the FLASH Loaded Image contains
    // a length field of the executable.
  static const int CFG_DATA_BYTE_LEN = 12858952 ;
    // Number of bytes reserved between output samples and tune frequency
  static const int BYTE_BETWEEN_OUT_SAMPLE = 1536 ;
        // Number of bytes reserved between output samples and tune frequency
  static const int BYTE_AT_END_OF_SAMPLES_RESERVED = 16384 ;
    // number of bytes in 16 bit word
  static const int NUM_BYTES = 2 ;
  private :
    // Bit definition of the Control/Status Register ('ControlStatus' field
    // of 'FpgaReg' structure)
    // Enables production of output samples and interupts.
  static const short int CNTRL_RUN = 0x0001 ;
    // Enables "offset_1PPS" to be loaded into Samp_Ctr at next 1PPS.
  static const short int CNTRL_USE_1PPS = 0x0002 ;
    // Enables ANB stage to either blank or limit samples.
  static const short int CNTRL_USE_ANB = 0x0004 ;
    // Enables ANB stage to limit (else blank if zero).
  static const short int CNTRL_LIMIT = 0x0008 ;
    // Enables ANL (atomospheric noise limiter).
  static const short int CNTRL_USE_ANL = 0x0010 ;
    // Sample data is internal (else ANI samples if zero).
  static const short int CNTRL_TEST_ENABLE = 0x0020 ;
    // Bit Definitions of the RFA-ADC Control Register('RfaAdcControl' field
    // of 'FpgaReg' structure)
    // Enable the RFA Test
  static const UINT2 RFA_TEST_EN = 0x0001 ;
    // Enable the Antenna Test 1
  static const UINT2 ANT_TEST_EN_1 = 0x0002 ;
    // Enable the Antenna Test 2
  static const UINT2 ANT_TEST_EN_2 = 0x0004 ;
    // Enable the Dither Enable
  static const UINT2 DITHER_EN = 0x0008 ;
    // Bit definition of the Interrupt Register ('Interrupt' field of 'FpgaReg'
    // structure)
    // 20 ms periodic interrupt (samples are ready).
  static const short int IRQ_20MS = 0x0001 ;
    // Samp_Ctr reached full count and wrapped to 0.
  static const short int IRQ_1SECOND = 0x0002 ;
    // An enabled 1PPS edge received which loaded offset_1PPS.
  static const short int IRQ_1PPS = 0x0004 ;
    // ANI hardware failure will produce 256 usec interrupt rate.
  static const short int IRQ_WATCHDOG = 0x0008 ;
    // Bit definition of the Internal FPGA Status Register ('IntStatusRegister'
    // field of 'FpgaReg' structure)
    // Error receiving ADC1 data
  static const UINT2 ADC1_ERR = 0x0001 ;
    // Error receiving ADC2 data
  static const UINT2 ADC2_ERR = 0x0002 ;
    // Error receiving ADC3 data
  static const UINT2 ADC3_ERR = 0x0004 ;
    // Error receiving TOD (Time of Day) data
  static const UINT2 TOD_ERR = 0x0008 ;
    //
    // Bit definition of the RFA-ADC Status Register ('RfaAdcStatus' field of
    // 'FpgaReg' structure)
    // FCXO_LOCK
  static const UINT2 RFA_FCXO_LOCK_BIT = 0x0001 ;
    // low = DXCO fault.
  static const UINT2 RFA_ADC_DCX0_BIT = 0x0002 ;
    // low = Voltage regulator fault.
  static const UINT2 RFA_ADC_EXT_SEL_BIT = 0x0004 ;
    // PS1_UV PS1 Under Voltage
  static const UINT2 PS1_UV_BIT = 0x0008 ;
    // PS1_OV PS1 Under Voltage
  static const UINT2 PS1_OV_BIT = 0x0010 ;
    // PS2_UV PS2 Under Voltage
  static const UINT2 PS2_UV_BIT = 0x0020 ;
    // PS2_OV PS2 Under Voltage
  static const UINT2 PS2_OV_BIT = 0x0040 ;
    // ADC_OTRA1 ADC1 Analog out of Range
  static const UINT2 ADC_OTRA1_BIT = 0x0080 ;
    // ADC_OTRD1 ADC1 Analog out of Range
  static const UINT2 ADC_OTRD1_BIT = 0x0100 ;
    // ADC_OTRA2 ADC2 Analog out of Range
  static const UINT2 ADC_OTRA2_BIT = 0x0200 ;
    // ADC_OTRD2 ADC2 Analog out of Range
  static const UINT2 ADC_OTRD2_BIT = 0x0400 ;
    // ADC_OTRA3 ADC3 Analog out of Range
  static const UINT2 ADC_OTRA3_BIT = 0x0800 ;
    // ADC_OTRD3 ADC3 Analog out of Range
  static const UINT2 ADC_OTRD3_BIT = 0x1000 ;
    // Possible GPIO states.
  enum GPIO_STATE
  {
    GpioLow = 0 ,
    GpioHigh = 1
  } ;
  enum GPIO_PINS
  {
    GpioConfig = 54 ,                 // GPIO number for the nCONFIG Line
    GpioReset = 53 ,                 // GPIO number for the RESET_F Line
    GpioConfigDone = 31 ,                 // GPIO number for the CONF_DONE Line
    GpioStatus = 33
  } ;                                 // GPIO number for the nSTATUS Line
  static const volatile char * DEVICE_BASE_ADDRESS ; // FPGA's Base Address
  static const int MAX_FREQ_HZ = 81910 ;  // Maximum Frequency in Hz
  static const short int MAX_1PPS = 3199 ;
                                            // Maximum 1PPS Time Offset
    //
    // This Constant is used to translate the "enum ERROR" mentioned
    // above to an ASCII string that can be printed out.
    //
  static const char * xltError [] ;
    // version string info
  std :: ostringstream str ;
                            // string stream
//********************************************************************
// Friend Functions
//********************************************************************
//********************************************************************
// Member Functions
//********************************************************************
//
// Since this class should only be used as a base class, we are going
// to prevent someone from instanting this class by setting the
// constructor/destructor to protected.
//
  protected :
  FpgaDevice ( const unsigned int ) ;
  virtual ~FpgaDevice () ;
  public :
   //
   // Methods used to get information about the FPGA's image.
   //
  unsigned int GetImageConfigSize () const ;
  std :: string GetImageConfigDoc () ;
   //
   // Methods used to access the frequencies of the FPGA's 5 channels.
   //
  FpgaDevice :: ERROR SetFreqChan1InHz ( const unsigned int ) ;
  FpgaDevice :: ERROR SetFreqChan2InHz ( const unsigned int ) ;
  FpgaDevice :: ERROR SetFreqChan3InHz ( const unsigned int ) ;
  FpgaDevice :: ERROR SetFreqChan4InHz ( const unsigned int ) ;
  FpgaDevice :: ERROR SetFreqChan5InHz ( const unsigned int ) ;
  FpgaDevice :: ERROR SetFreqChanInHz ( unsigned int freq , enum FREQ_CHAN freqChan ) ;
   //
   // Methods used to access the Control/Status Register.
   //
  void ClrRunBit () ;
  void ClrUseAnbBit () ;
  void ClrLimitBit () ;
  void ClrUseAnlBit () ;
  void ClrTestEnableBit () ;
  void SetRunBit () ;
  void SetUseAnbBit () ;
  void SetLimitBit () ;
  void SetUseAnlBit () ;
  void SetTestEnableBit () ;
   //
   // Methods used to access the RFA-ADC Status Register.
   //
  bool IsFx1LockBitSet () ;
  bool IsDcx01BitSet () ;
  bool IsExtSel1BitSet () ;
  bool IsPs1UVBitSet () ;
  bool IsPs1OVBitSet () ;
  bool IsPs2UVBitSet () ;
  bool IsPs2OVBitSet () ;
   //
   // Methods used to access the RFA-ADC Control Register.
   //
  void ClrRegRfaTstEn () ;
  void ClrRegAntTstEn1 () ;
  void ClrRegAntTstEn2 () ;
  void ClrRegDitherEn () ;
  void SetRegRfaTstEn () ;
  void SetRegAntTstEn1 () ;
  void SetRegAntTstEn2 () ;
  void SetRegDitherEn () ;
   //
   // Methods used to access the 1PPS Register.
   //
  unsigned int GetSecondCountAt1ppAddress () const ;
   //
   // Methods used to get the Output Samples from the FPGA's 5 channels.
   //
   // NOTE: The GetOutputSample[1-5]Address() and GetIrqRegAddress()
   // were created to give the FpgaIoDevice Driver the ability to
   // get the output samples directly from the FPGA device when
   // the 20 msec interrupt occurs. The GetIrqCtrlRegAddress()
   // and the GetOffSet1PpsRegAddress() are created to allow
   // FpgaIoDevice Driver to have access to time related registers
   //
  unsigned int GetIrqRegAddress () const ;
  unsigned int GetIrqCtrlRegAddress () const ;
  unsigned int GetOffSet1PpsRegAddress () const ;
  unsigned int GetRfaStatusRegAddress () const ;
  unsigned int GetOutputSample1Address () const ;
  unsigned int GetOutputSample2Address () const ;
  unsigned int GetOutputSample3Address () const ;
  unsigned int GetOutputSample4Address () const ;
  unsigned int GetOutputSample5Address () const ;
  unsigned int RFA1_GetOutputSample1Address () const ;
  unsigned int RFA1_GetOutputSample2Address () const ;
  unsigned int RFA1_GetOutputSample3Address () const ;
  unsigned int RFA1_GetOutputSample4Address () const ;
  unsigned int RFA1_GetOutputSample5Address () const ;
  unsigned int RFA2_GetOutputSample1Address () const ;
  unsigned int RFA2_GetOutputSample2Address () const ;
  unsigned int RFA2_GetOutputSample3Address () const ;
  unsigned int RFA2_GetOutputSample4Address () const ;
  unsigned int RFA2_GetOutputSample5Address () const ;
  unsigned int RFA3_GetOutputSample1Address () const ;
  unsigned int RFA3_GetOutputSample2Address () const ;
  unsigned int RFA3_GetOutputSample3Address () const ;
  unsigned int RFA3_GetOutputSample4Address () const ;
  unsigned int RFA3_GetOutputSample5Address () const ;
  unsigned int GetTODMinSecRegAddress () const ;
  unsigned int GetTODHrsRegAddress () const ;
  unsigned int GetTODDoYRegAddress () const ;
   //
   // General Purpose Methods.
   //
  FpgaDevice :: ERROR GetLastError () const ;
  bool IsConfigured () const ;
  FpgaDevice :: ERROR Reset () ;
  private :
  FpgaDevice :: ERROR ConfigureFpga () ;
  unsigned short GetImageConfigData ( const unsigned int ) const ;
  FpgaDevice :: ERROR PrepareFpga () ;
   //
   // The following methods are not supported.
   //
  FpgaDevice () ;
  FpgaDevice ( const FpgaDevice & ) ;
 
  FpgaDevice &
  operator = ( const FpgaDevice & ) ;
//********************************************************************
// Data Members
//********************************************************************
  private :
   //
   // FPGA Image Format.
   //
   // The FPGA configuration data is contained in a single binary
   // file. The address of this binary file will be passed into
   // the constructor method.
   //
   // The Configuration data is written to the FPGA as an
   // 16-bit piece of data on the FPGA 16-bit bus.
   //
  typedef struct
  {
    UINT2 ConfigData [ CFG_DATA_BYTE_LEN /
    2 ] ;
  } ImageFormat ;
   //
   // FPGA IO Register Format.
   //
   // The following structure contains the registers of the FPGA's. It is
   // based on Table 7-14 in Document 946-8290-001 Rev B 2015
   //
   //
  typedef struct
  {
      // RFA 1
    int RFA1_OutputSample1 [ 128 ] ;           // 0x0000 Offset
    int RFA1_OutputSample2 [ 128 ] ;           // 0x0200 Offset
    int RFA1_OutputSample3 [ 128 ] ;           // 0x0400 Offset
    int RFA1_OutputSample4 [ 128 ] ;           // 0x0600 Offset
    int RFA1_OutputSample5 [ 128 ] ;           // 0x0800 Offset
    unsigned char Reserved_1 [ BYTE_BETWEEN_OUT_SAMPLE ] ;// 0x0a00 Offset
      // RFA 2
    int RFA2_OutputSample1 [ 128 ] ;           // 0x1000 Offset
    int RFA2_OutputSample2 [ 128 ] ;           // 0x1200 Offset
    int RFA2_OutputSample3 [ 128 ] ;           // 0x1400 Offset
    int RFA2_OutputSample4 [ 128 ] ;           // 0x1600 Offset
    int RFA2_OutputSample5 [ 128 ] ;           // 0x1800 Offset
    unsigned char Reserved_2 [ BYTE_BETWEEN_OUT_SAMPLE ] ;// 0x1a00 Offset
      // RFA 3
    int RFA3_OutputSample1 [ 128 ] ;           // 0x2000 Offset
    int RFA3_OutputSample2 [ 128 ] ;           // 0x2200 Offset
    int RFA3_OutputSample3 [ 128 ] ;           // 0x2400 Offset
    int RFA3_OutputSample4 [ 128 ] ;           // 0x2600 Offset
    int RFA3_OutputSample5 [ 128 ] ;           // 0x2800 Offset
    unsigned char Reserved_3 [ BYTE_BETWEEN_OUT_SAMPLE ] ;// 0x2a00 Offset
      // Omni
    int OutputSample1 [ 128 ] ;           // 0x3000 Offset
    int OutputSample2 [ 128 ] ;           // 0x3200 Offset
    int OutputSample3 [ 128 ] ;           // 0x3400 Offset
    int OutputSample4 [ 128 ] ;           // 0x3600 Offset
    int OutputSample5 [ 128 ] ;           // 0x3800 Offset
    unsigned char Reserved_4 [ BYTE_BETWEEN_OUT_SAMPLE ] ;
                                                         // 0x3a00 Offset
    unsigned char Reserved_5 [ BYTE_AT_END_OF_SAMPLES_RESERVED ] ;
    UINT2 TuningFrequency [ 5 ] ;// 0x8000-0x8008 Offset
                                           // Frequencies for channel 1-5
    UINT2 IntStatusRegister ;  // 0x800A Offset
                                           // Various Internal FPGA status bits
    UINT2 ControlStatus ;  // 0x800C Offset
                                           // Control Register/status reg.
    UINT2 Interrupt ;  // 0x800E Offset
                                           // Interrupt Register
    UINT2 RfaAdcStatus ;  // 0x8010 Offset
                                           // RFA-ADSC Status
    UINT2 RfaAdcControl ;  // 0x8012 Offset
                                           // RFA-ADSC Control
    UINT2 Offset1pps ;  // 0x8014 Offset
                                           // 1PPS time offset
    UINT2 CountAt1pps ;  // 0x8016 Offset
                                           // Second count at 1PPS
    bcdTimeStruct TodHours ;  // 0x8018 Offset
                                           // Time of Day Hours
    bcdTimeStruct TodMinSec ;  // 0x801A Offset
                                           // Time of Day Minutes/Seconds
    bcdTimeStruct TodDayOfYear ;  // 0x801C Offset
                                           // Time of Day Day of Year
    bcdTimeStruct TodFigOfMerit ;  // 0x801E Offset
                                           // Time of Day Hours
    UINT2 NameRegister1 ;  // 0x8020 Offset
                                           // First two characters of name
    UINT2 NameRegister2 ;  // 0x8022 Offset
                                           // Second two characters of name
    UINT2 BuildYear ;  // 0x8024 Offset
                                           // Build year as Hexadecimal number
    UINT2 BuildMonDay ;  // 0x8026 Offset
                                           // Build Month/Day as Hexadecimal number
  } FpgaReg ;
  bool mConfigured ; // config'ed flag
  volatile FpgaReg * mDeviceAddress ;// device addr
  volatile ImageFormat * mImageAddress ;// image addr
  FpgaDevice :: ERROR mLastError ;
                                 // last err
  IODevice mGPIODevice ;
                         // I/O device
//********************************************************************
// Static Functions
//********************************************************************
  public :
  static const char * XltLastError ( const FpgaDevice :: ERROR ) ;
} ;
///////////////////////////////////////////////////////////////////
//! Function: GetImageConfigData
//!
//! Description:
//! This is a PRIVATE inline method used to get a byte of
//! Configuration data from the flash image associated with the
//! FpgaDevice Object.
//!
//! Parameters:
//! index - The index into the Configuration Data array.
//! Return Value – Specified byte of Configuration Data.
//!
//! Notes:
//! To make this call as quick as possible, there is no range
//! checking to make sure the index is actually in ConfigData[].
//! This is not a problem since this is a private method and the
//! FpgaDevice Object will never ask for data that is out of range.
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_7)
 
inline unsigned short
  FpgaDevice :: GetImageConfigData (
  const unsigned int index ) const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 12))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 13))); /* 30 */
    CChannelState_11zqendz                                                                               (      14 ) ; /* 30 */  
    return
    ( mImageAddress -> ConfigData [ index ] ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: GetImageConfigSize
//!
//! Description:
//! This is a PUBLIC inline method used to tell the size
//! (in bytes) of the Configuration data that will be loaded into
//! the FpgaDevice Object.
//!
//! Parameters:
//! Return Value – Number of shorts in the Configuration Data array.
//!
//! Notes:
//! None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_8)
 
inline unsigned int
  FpgaDevice :: GetImageConfigSize() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 14))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 15))); /* 30 */
    CChannelState_11zqendz                                                                               (      16 ) ; /* 30 */  
    return
    ( CFG_DATA_BYTE_LEN /
    2 ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: SetFreqChanInHz
//!
//! Description:
//! This is a PRIVATE inline method (called by the public methods
//! below) used to set the frequency (in Hz) of Channel [1-5] of the
//! FpgaDevice Object.
//!
//! Parameters:
//! freq - The frequency (in Hz) the channel should go to.
//! freqChan - The frequency channel being set.
//! Return Value – A 'enum Error' code that indicates how successful
//! the FPGA resetting went. GetLastError() method
//! will also be updated with the return value.
//!
//! Notes:
//! - Frequency must be between 0 Hz and MAX_FREQ_HZ otherwise the
//! method will return an FpgaRangeError.
//! - Although the method requires the frequency to be in Hz, the
//! FPGA requires the frequency to be in decahertz (daHz) and
//! will ignore the ones place of the frequency (ie 12345 -> 12340)
//! - Since the FPGA could be a dead bug (FPGA is not configured
//! and therefore the FPGA's register do not exist), this method
//! will not check to make sure the frequency has actually been
//! set to the frequency the caller requested. It is the job of
//! the caller to verify the frequency is correct via the
//! GetFreq[1-5]InHz() methods.
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_9)
 
inline FpgaDevice :: ERROR
  FpgaDevice :: SetFreqChanInHz (
  unsigned int freq ,
  enum FpgaDevice :: FREQ_CHAN freqChan )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 16))); /* 37 */
    FpgaDevice :: ERROR
      rtnValue = FpgaDevice :: FpgaSuccess ;             // return value
    if
      (
      freq <= FpgaDevice :: MAX_FREQ_HZ
      )
 {
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 17))); /* 1 */
      {
        mDeviceAddress -> TuningFrequency [ freqChan ] = ( freq /
        10 ) ;
      }
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 18))); /* 3 */
 }
    else
  { 
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 19))); /* 2 */
      {
        rtnValue = FpgaDevice :: FpgaRangeError ;
      }
 }
    mLastError = rtnValue ;
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 20))); /* 30 */
    CChannelState_11zqendz                                                                               (      21 ) ; /* 30 */  
    return
    ( rtnValue ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: SetFreqChan[1-5]InHz
//!
//! Description:
//! This is a PUBLIC inline method used to set the frequency
//! (in Hz) of Channel [1-5] of the FpgaDevice Object.
//!
//! Parameters:
//! freq - The frequency (in Hz) the channel should go to.
//! Return Value – A 'enum Error' code that indicates how successful
//! the FPGA resetting went. GetLastError() method
//! will also be updated with the return value.
//!
//! Notes:
//! - Frequency must be between 0 Hz and MAX_FREQ_HZ otherwise the
//! method will return an FpgaRangeError.
//! - Although the method requires the frequency to be in Hz, the
//! FPGA requires the frequency to be in decahertz (daHz) and
//! will ignore the ones place of the frequency (ie 12345 -> 12340)
//! - Since the FPGA could be a dead bug (FPGA is not configured
//! and therefore the FPGA's register do not exist), this method
//! will not check to make sure the frequency has actually been
//! set to the frequency the caller requested. It is the job of
//! the caller to verify the frequency is correct via the
//! GetFreq[1-5]InHz() methods.
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_10)
 
inline FpgaDevice :: ERROR
  FpgaDevice :: SetFreqChan1InHz (
  unsigned int freq )
  {
typedef FpgaDevice :: ERROR  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 21))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 22))); /* 23 */
   zzqtype  qqzzzi =
      SetFreqChanInHz (
      freq , FpgaDevice :: FreqChan1 ) ;
 
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 23))); /* 30 */
    CChannelState_11zqendz                                                                               (      24 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_11)
 
inline FpgaDevice :: ERROR
  FpgaDevice :: SetFreqChan2InHz (
  unsigned int freq )
  {
typedef FpgaDevice :: ERROR  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 24))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 25))); /* 23 */
   zzqtype  qqzzzi =
      SetFreqChanInHz (
      freq , FpgaDevice :: FreqChan2 ) ;
 
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 26))); /* 30 */
    CChannelState_11zqendz                                                                               (      27 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_12)
 
inline FpgaDevice :: ERROR
  FpgaDevice :: SetFreqChan3InHz (
  unsigned int freq )
  {
typedef FpgaDevice :: ERROR  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 27))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 28))); /* 23 */
   zzqtype  qqzzzi =
      SetFreqChanInHz (
      freq , FpgaDevice :: FreqChan3 ) ;
 
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 29))); /* 30 */
    CChannelState_11zqendz                                                                               (      30 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_13)
 
inline FpgaDevice :: ERROR
  FpgaDevice :: SetFreqChan4InHz (
  unsigned int freq )
  {
typedef FpgaDevice :: ERROR  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 30))); /* 37 */
  ((unsigned int)(bitmapstruct.element0 |= ((unsigned int)1 << 31))); /* 23 */
   zzqtype  qqzzzi =
      SetFreqChanInHz (
      freq , FpgaDevice :: FreqChan4 ) ;
 
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 <<  0))); /* 30 */
    CChannelState_11zqendz                                                                               (      33 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_14)
 
inline FpgaDevice :: ERROR
  FpgaDevice :: SetFreqChan5InHz (
  unsigned int freq )
  {
typedef FpgaDevice :: ERROR  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 <<  1))); /* 37 */
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 <<  2))); /* 23 */
   zzqtype  qqzzzi =
      SetFreqChanInHz (
      freq , FpgaDevice :: FreqChan5 ) ;
 
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 <<  3))); /* 30 */
    CChannelState_11zqendz                                                                               (      36 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: Clr[Run/Use1pps/UseAnb/Limit/UseAnl/TestEnable]Bit
//!
//! Description:
//! This is a PUBLIC inline method used to clear the corresponding
//! bit in the Control/Status Register of the FpgaDevice Object
//! is set. The bits that can be cleared are:
//!
//! - Run
//! - Use 1PPS
//! - Use ANB
//! - Limit
//! - Use ANL
//! - Test Enable
//!
//! Parameters:
//! Nothing
//!
//! Notes:
//! - The Test Enable bit should never be turned off when the Run bit
//! is set. First turn the Run bit off then clear the Test Enable Bit.
//!
//! If 1PPS is enabled continually, the last 20ms interval in each
//! second can be of varying length. Sample processing can exhibit
//! 1us jitter due to the different clock domains in the FPGA.
//! Use of 1PPS can cause data discontinuities even when perfectly
//! stable. Use 1PPS rarely and only when the source is known to
//! be valid and stable.
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_15)
 
inline void
  FpgaDevice :: ClrRunBit()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 <<  4))); /* 37 */
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus & ~ CNTRL_RUN ;
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 <<  5))); /* 30 */
    CChannelState_11zqendz                                                                               (      38 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_16)
 
inline void
  FpgaDevice :: ClrUseAnbBit()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 <<  6))); /* 37 */
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus & ~ CNTRL_USE_ANB ;
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 <<  7))); /* 30 */
    CChannelState_11zqendz                                                                               (      40 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_17)
 
inline void
  FpgaDevice :: ClrLimitBit()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 <<  8))); /* 37 */
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus & ~ CNTRL_LIMIT ;
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 <<  9))); /* 30 */
    CChannelState_11zqendz                                                                               (      42 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_18)
 
inline void
  FpgaDevice :: ClrUseAnlBit()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 10))); /* 37 */
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus & ~ CNTRL_USE_ANL ;
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 11))); /* 30 */
    CChannelState_11zqendz                                                                               (      44 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_19)
 
inline void
  FpgaDevice :: ClrTestEnableBit()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 12))); /* 37 */
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus & ~ CNTRL_RUN ;
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus & ~ CNTRL_TEST_ENABLE ;
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 13))); /* 30 */
    CChannelState_11zqendz                                                                               (      46 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: Set[Run/Use1pps/UseAnb/Limit/UseAnl/TestEnable]Bit
//!
//! Description:
//! This is a PUBLIC inline method used to set the corresponding
//! bit in the Control/Status Register of the FpgaDevice Object
//! is set. The bits that can be cleared are:
//!
//! - Run
//! - Use 1PPS
//! - Use ANB
//! - Limit
//! - Use ANL
//! - Test Enable
//!
//! Parameters:
//! Nothing
//!
//! Notes:
//! - The Test Enable bit should never be turned on when the Run bit
//! is set. First turn the Run bit off then set the Test Enable Bit.
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_20)
 
inline void
  FpgaDevice :: SetRunBit()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 14))); /* 37 */
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus | CNTRL_RUN ;
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 15))); /* 30 */
    CChannelState_11zqendz                                                                               (      48 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_21)
 
inline void
  FpgaDevice :: SetUseAnbBit()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 16))); /* 37 */
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus | CNTRL_USE_ANB ;
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 17))); /* 30 */
    CChannelState_11zqendz                                                                               (      50 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_22)
 
inline void
  FpgaDevice :: SetLimitBit()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 18))); /* 37 */
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus | CNTRL_LIMIT ;
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 19))); /* 30 */
    CChannelState_11zqendz                                                                               (      52 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_23)
 
inline void
  FpgaDevice :: SetUseAnlBit()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 20))); /* 37 */
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus | CNTRL_USE_ANL ;
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 21))); /* 30 */
    CChannelState_11zqendz                                                                               (      54 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_24)
 
inline void
  FpgaDevice :: SetTestEnableBit()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 22))); /* 37 */
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus & ~ CNTRL_RUN ;
    mDeviceAddress -> ControlStatus = mDeviceAddress -> ControlStatus | CNTRL_TEST_ENABLE ;
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 23))); /* 30 */
    CChannelState_11zqendz                                                                               (      56 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: Is[Dcx01/Ps1/ExtSel1/Fx1Lock/Dcx01Ok]BitSet
//!
//! Description:
//! This is a PUBLIC inline method used to tell if the corresponding
//! bit in the RFA-ADC Status Register of the FpgaDevice Object is set.
//! The bits that can be tested are:
//!
//! - FCXO_LOCK
//! - DCXO_BIT
//! - Ext Sel 1
//! - PS1_UV
//! - PS1_OV
//! - PS2_UV
//! - PS2_OV
//! - ADC_OTRA1
//! - ADC_OTRD1
//! - ADC_OTRA2
//! - ADC_OTRD2
//! - ADC_OTRA3
//! - ADC_OTRD3
//!
//! Parameters:
//! Return Value – TRUE if it is set/FALSE if it is not set
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_25)
 
inline bool
  FpgaDevice :: IsFx1LockBitSet()
  {
typedef bool  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 24))); /* 37 */
   zzqtype  qqzzzi =
    (
     
  ( (  /*  67 */ 
 
    ( mDeviceAddress -> RfaAdcStatus & RFA_FCXO_LOCK_BIT ) == 0
  ) ?(((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 25))),
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 27))),
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 28))),
 1)
 :( ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 26))),
 0)) /* 66 */
    ?
    false
    :
    true
      )
    ;
 
  ((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 29))); /* 30 */
    CChannelState_11zqendz                                                                               (      62 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_26)
 
inline bool
  FpgaDevice :: IsDcx01BitSet()
  {
typedef bool  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 30))); /* 37 */
   zzqtype  qqzzzi =
    (
     
  ( (  /*  67 */ 
 
    ( mDeviceAddress -> RfaAdcStatus & RFA_ADC_DCX0_BIT ) == 0
  ) ?(((unsigned int)(bitmapstruct.element1 |= ((unsigned int)1 << 31))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 <<  1))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 <<  2))),
 1)
 :( ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 <<  0))),
 0)) /* 66 */
    ?
    false
    :
    true
      )
    ;
 
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 <<  3))); /* 30 */
    CChannelState_11zqendz                                                                               (      68 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_27)
 
inline bool
  FpgaDevice :: IsExtSel1BitSet()
  {
typedef bool  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 <<  4))); /* 37 */
   zzqtype  qqzzzi =
    (
     
  ( (  /*  67 */ 
 
    ( mDeviceAddress -> RfaAdcStatus & RFA_ADC_EXT_SEL_BIT ) == 0
  ) ?(((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 <<  5))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 <<  7))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 <<  8))),
 1)
 :( ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 <<  6))),
 0)) /* 66 */
    ?
    false
    :
    true
      )
    ;
 
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 <<  9))); /* 30 */
    CChannelState_11zqendz                                                                               (      74 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_28)
 
inline bool
  FpgaDevice :: IsPs1UVBitSet()
  {
typedef bool  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 10))); /* 37 */
   zzqtype  qqzzzi =
    (
     
  ( (  /*  67 */ 
 
    ( mDeviceAddress -> RfaAdcStatus & PS1_UV_BIT ) == 0
  ) ?(((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 11))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 13))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 14))),
 1)
 :( ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 12))),
 0)) /* 66 */
    ?
    false
    :
    true
      )
    ;
 
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 15))); /* 30 */
    CChannelState_11zqendz                                                                               (      80 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_29)
 
inline bool
  FpgaDevice :: IsPs1OVBitSet()
  {
typedef bool  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 16))); /* 37 */
   zzqtype  qqzzzi =
    (
     
  ( (  /*  67 */ 
 
    ( mDeviceAddress -> RfaAdcStatus & PS1_OV_BIT ) == 0
  ) ?(((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 17))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 19))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 20))),
 1)
 :( ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 18))),
 0)) /* 66 */
    ?
    false
    :
    true
      )
    ;
 
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 21))); /* 30 */
    CChannelState_11zqendz                                                                               (      86 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_30)
 
inline bool
  FpgaDevice :: IsPs2UVBitSet()
  {
typedef bool  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 22))); /* 37 */
   zzqtype  qqzzzi =
    (
     
  ( (  /*  67 */ 
 
    ( mDeviceAddress -> RfaAdcStatus & PS2_UV_BIT ) == 0
  ) ?(((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 23))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 25))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 26))),
 1)
 :( ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 24))),
 0)) /* 66 */
    ?
    false
    :
    true
      )
    ;
 
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 27))); /* 30 */
    CChannelState_11zqendz                                                                               (      92 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_31)
 
inline bool
  FpgaDevice :: IsPs2OVBitSet()
  {
typedef bool  zzqtype;
 int izzqqzz=((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 28))); /* 37 */
   zzqtype  qqzzzi =
    (
     
  ( (  /*  67 */ 
 
    ( mDeviceAddress -> RfaAdcStatus & PS2_OV_BIT ) == 0
  ) ?(((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 29))),
  ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 31))),
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 <<  0))),
 1)
 :( ((unsigned int)(bitmapstruct.element2 |= ((unsigned int)1 << 30))),
 0)) /* 66 */
    ?
    false
    :
    true
      )
    ;
 
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 <<  1))); /* 30 */
    CChannelState_11zqendz                                                                               (      98 ) ; /* 30 */  
    ;
return ( qqzzzi );
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: Set[RfaTest/AnTest1/AnTest2/DitherEn
//!
//! Description:
//! This is a PUBLIC inline method used to tell if the corresponding
//! bit in the RFA-ADC Control Register of the FpgaDevice Object is set.
//! The bits that can be tested are:
//!
//! - RFA_TEST_EN
//! - ANT_TEST_EN_1
//! - ANT_TEST_EN_2
//! - DITHER_EN
//!
//! Parameters:
//! Return Value – none
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_32)
 
inline void
  FpgaDevice :: SetRegRfaTstEn()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 <<  2))); /* 37 */
    mDeviceAddress -> RfaAdcControl = mDeviceAddress -> RfaAdcControl | RFA_TEST_EN ;
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 <<  3))); /* 30 */
    CChannelState_11zqendz                                                                               (     100 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_33)
 
inline void
  FpgaDevice :: SetRegAntTstEn1()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 <<  4))); /* 37 */
    mDeviceAddress -> RfaAdcControl = mDeviceAddress -> RfaAdcControl | ANT_TEST_EN_1 ;
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 <<  5))); /* 30 */
    CChannelState_11zqendz                                                                               (     102 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_34)
 
inline void
  FpgaDevice :: SetRegAntTstEn2()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 <<  6))); /* 37 */
    mDeviceAddress -> RfaAdcControl = mDeviceAddress -> RfaAdcControl | ANT_TEST_EN_2 ;
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 <<  7))); /* 30 */
    CChannelState_11zqendz                                                                               (     104 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_35)
 
inline void
  FpgaDevice :: SetRegDitherEn()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 <<  8))); /* 37 */
    mDeviceAddress -> RfaAdcControl = mDeviceAddress -> RfaAdcControl | DITHER_EN ;
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 <<  9))); /* 30 */
    CChannelState_11zqendz                                                                               (     106 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: Clr[RfaTest/AnTest1/AnTest2/DitherEn
//!
//! Description:
//! This is a PUBLIC inline method used to tell if the corresponding
//! bit in the RFA-ADC Control Register of the FpgaDevice Object is set.
//! The bits that can be tested are:
//!
//! - RFA_TEST_EN
//! - ANT_TEST_EN_1
//! - ANT_TEST_EN_2
//! - DITHER_EN
//!
//! Parameters:
//! Return Value – none
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_36)
 
inline void
  FpgaDevice :: ClrRegRfaTstEn()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 10))); /* 37 */
    mDeviceAddress -> RfaAdcControl = mDeviceAddress -> RfaAdcControl & ~ RFA_TEST_EN ;
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 11))); /* 30 */
    CChannelState_11zqendz                                                                               (     108 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_37)
 
inline void
  FpgaDevice :: ClrRegAntTstEn1()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 12))); /* 37 */
    mDeviceAddress -> RfaAdcControl = mDeviceAddress -> RfaAdcControl & ~ ANT_TEST_EN_1 ;
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 13))); /* 30 */
    CChannelState_11zqendz                                                                               (     110 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_38)
 
inline void
  FpgaDevice :: ClrRegAntTstEn2()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 14))); /* 37 */
    mDeviceAddress -> RfaAdcControl = mDeviceAddress -> RfaAdcControl & ~ ANT_TEST_EN_2 ;
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 15))); /* 30 */
    CChannelState_11zqendz                                                                               (     112 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_39)
 
inline void
  FpgaDevice :: ClrRegDitherEn()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 16))); /* 37 */
    mDeviceAddress -> RfaAdcControl = mDeviceAddress -> RfaAdcControl & ~ DITHER_EN ;
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 17))); /* 30 */
    CChannelState_11zqendz                                                                               (     114 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: GetSecondCountAt1ppAddress
//!
//! Description:
//! This is a public inline method used to tell the memory
//! location of the Fpga's Second Count At 1pps for the FpgaDevice
//! Object.
//!
//! Parameters:
//! Return Value – Address where the FPGA's SecondCountAt1pp is
//! is located.
//!
//! Notes:
//! None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_40)
 
inline unsigned int
  FpgaDevice :: GetSecondCountAt1ppAddress() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 18))); /* 37 */
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 19))); /* 30 */
    CChannelState_11zqendz                                                                               (     116 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> CountAt1pps ) ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: GetIrqRegAddress
//!
//! Description:
//! This is a public inline method used to tell the memory
//! location of the Fpga's Interrupt Register for the FpgaDevice
//! Object.
//!
//! Parameters:
//! Return Value – Address where the FPGA's Interrupt Register is
//! is located.
//!
//! Notes:
//! None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_41)
 
inline unsigned int
  FpgaDevice :: GetIrqRegAddress() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 20))); /* 37 */
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 21))); /* 30 */
    CChannelState_11zqendz                                                                               (     118 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> Interrupt ) ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: GetIrqCtrlRegAddress
//!
//! Description:
//! This is a public inline method used to tell the memory
//! location of the Fpga's Interrupt Control Register for the
//! FpgaDevice Object.
//!
//! Parameters:
//! Return Value – Address where the FPGA's Interrupt control
//! Register is located.
//!
//! Notes:
//! None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_42)
 
inline unsigned int
  FpgaDevice :: GetIrqCtrlRegAddress() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 22))); /* 37 */
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 23))); /* 30 */
    CChannelState_11zqendz                                                                               (     120 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> ControlStatus ) ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: GetOffSet1PpsRegAddress
//!
//! Description:
//! This is a public inline method used to tell the memory
//! location of the Fpga's offset1pps Register for the
//! FpgaDevice Object.
//!
//! Parameters:
//! Return Value – Address where the FPGA'soffset1pps
//! Register is located.
//!
//! Notes:
//! None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_43)
 
inline unsigned int
  FpgaDevice :: GetOffSet1PpsRegAddress() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 24))); /* 37 */
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 25))); /* 30 */
    CChannelState_11zqendz                                                                               (     122 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> Offset1pps ) ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: GetRfaStatusRegAddress
//!
//! Description:
//! This is a public inline method used to tell the memory
//! location of the RFA status Register for the
//! FpgaDevice Object.
//!
//! Parameters:
//! Return Value – Address where the RFA Status
//! Register is located.
//!
//! Notes:
//! None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_44)
 
inline unsigned int
  FpgaDevice :: GetRfaStatusRegAddress() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 26))); /* 37 */
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 27))); /* 30 */
    CChannelState_11zqendz                                                                               (     124 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RfaAdcStatus ) ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: GetOutputSample[1-5]Address
//!
//! Description:
//! This is a public inline method used to tell the memory
//! location of the Output Sample for Channel [1-5] for the
//! FpgaDevice Object.
//!
//! Parameters:
//! Return Value – Address where the FPGA's Output Sample for
//! Channel [1-5] is located.
//!
//! Notes:
//! None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_45)
 
inline unsigned int
  FpgaDevice :: GetOutputSample1Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 28))); /* 37 */
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 29))); /* 30 */
    CChannelState_11zqendz                                                                               (     126 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> OutputSample1 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_46)
 
inline unsigned int
  FpgaDevice :: GetOutputSample2Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 30))); /* 37 */
  ((unsigned int)(bitmapstruct.element3 |= ((unsigned int)1 << 31))); /* 30 */
    CChannelState_11zqendz                                                                               (     128 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> OutputSample2 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_47)
 
inline unsigned int
  FpgaDevice :: GetOutputSample3Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 <<  0))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 <<  1))); /* 30 */
    CChannelState_11zqendz                                                                               (     130 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> OutputSample3 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_48)
 
inline unsigned int
  FpgaDevice :: GetOutputSample4Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 <<  2))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 <<  3))); /* 30 */
    CChannelState_11zqendz                                                                               (     132 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> OutputSample4 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_49)
 
inline unsigned int
  FpgaDevice :: GetOutputSample5Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 <<  4))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 <<  5))); /* 30 */
    CChannelState_11zqendz                                                                               (     134 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> OutputSample5 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: RFA#_GetOutputSample[1-5]Address
//!
//! Description:
//! This is a public inline method used to tell the memory
//! location of the Output Sample for Channel [1-5] on different
//! RFA input channels for the FpgaDevice Object.
//!
//! Parameters:
//! Return Value – Address where the FPGA's Output Sample for
//! Channel [1-5] is located.
//!
//! Notes:
//! None
//!
///////////////////////////////////////////////////////////////////
//RFA 1
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_50)
 
inline unsigned int
  FpgaDevice :: RFA1_GetOutputSample1Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 <<  6))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 <<  7))); /* 30 */
    CChannelState_11zqendz                                                                               (     136 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA1_OutputSample1 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_51)
 
inline unsigned int
  FpgaDevice :: RFA1_GetOutputSample2Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 <<  8))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 <<  9))); /* 30 */
    CChannelState_11zqendz                                                                               (     138 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA1_OutputSample2 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_52)
 
inline unsigned int
  FpgaDevice :: RFA1_GetOutputSample3Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 10))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 11))); /* 30 */
    CChannelState_11zqendz                                                                               (     140 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA1_OutputSample3 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_53)
 
inline unsigned int
  FpgaDevice :: RFA1_GetOutputSample4Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 12))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 13))); /* 30 */
    CChannelState_11zqendz                                                                               (     142 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA1_OutputSample4 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_54)
 
inline unsigned int
  FpgaDevice :: RFA1_GetOutputSample5Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 14))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 15))); /* 30 */
    CChannelState_11zqendz                                                                               (     144 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA1_OutputSample5 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
//RFA 2
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_55)
 
inline unsigned int
  FpgaDevice :: RFA2_GetOutputSample1Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 16))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 17))); /* 30 */
    CChannelState_11zqendz                                                                               (     146 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA2_OutputSample1 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_56)
 
inline unsigned int
  FpgaDevice :: RFA2_GetOutputSample2Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 18))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 19))); /* 30 */
    CChannelState_11zqendz                                                                               (     148 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA2_OutputSample2 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_57)
 
inline unsigned int
  FpgaDevice :: RFA2_GetOutputSample3Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 20))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 21))); /* 30 */
    CChannelState_11zqendz                                                                               (     150 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA2_OutputSample3 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_58)
 
inline unsigned int
  FpgaDevice :: RFA2_GetOutputSample4Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 22))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 23))); /* 30 */
    CChannelState_11zqendz                                                                               (     152 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA2_OutputSample4 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_59)
 
inline unsigned int
  FpgaDevice :: RFA2_GetOutputSample5Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 24))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 25))); /* 30 */
    CChannelState_11zqendz                                                                               (     154 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA2_OutputSample5 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
//RFA 3
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_60)
 
inline unsigned int
  FpgaDevice :: RFA3_GetOutputSample1Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 26))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 27))); /* 30 */
    CChannelState_11zqendz                                                                               (     156 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA3_OutputSample1 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_61)
 
inline unsigned int
  FpgaDevice :: RFA3_GetOutputSample2Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 28))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 29))); /* 30 */
    CChannelState_11zqendz                                                                               (     158 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA3_OutputSample2 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_62)
 
inline unsigned int
  FpgaDevice :: RFA3_GetOutputSample3Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 30))); /* 37 */
  ((unsigned int)(bitmapstruct.element4 |= ((unsigned int)1 << 31))); /* 30 */
    CChannelState_11zqendz                                                                               (     160 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA3_OutputSample3 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_63)
 
inline unsigned int
  FpgaDevice :: RFA3_GetOutputSample4Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 <<  0))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 <<  1))); /* 30 */
    CChannelState_11zqendz                                                                               (     162 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA3_OutputSample4 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_64)
 
inline unsigned int
  FpgaDevice :: RFA3_GetOutputSample5Address() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 <<  2))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 <<  3))); /* 30 */
    CChannelState_11zqendz                                                                               (     164 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> RFA3_OutputSample5 [ 0 ] ) ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: GetLastError
//!
//! Description:
//! This is a PUBLIC inline method used to tell what the result of
//! the last known error detected by the FpgaDevice Object.
//!
//! Parameters:
//! Return Value – Last known error.
//!
//! Notes:
//! The method XltLastError() can translate the error into an ASCII
//! English string.
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_65)
 
inline FpgaDevice :: ERROR
  FpgaDevice :: GetLastError() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 <<  4))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 <<  5))); /* 30 */
    CChannelState_11zqendz                                                                               (     166 ) ; /* 30 */  
    return
    ( mLastError ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: XltLastError
//!
//! Description:
//! This is an PUBLIC inline method is used to translate an
//! 'enum Error' to an ASCII string that can be printed out.
//!
//! Parameters:
//! errorNum - A 'enum Error' code
//! Return Value – Pointer to a constant ASCII string that describes
//! the 'enum Error' as a English string.
//!
//! Notes:
//! Illegal error number will be translated to "Illegal Error Code".
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_66)
 
inline const char *
  FpgaDevice :: XltLastError (
  const FpgaDevice :: ERROR errorNum )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 <<  6))); /* 37 */
    FpgaDevice :: ERROR
      index = errorNum ;               // error code
    if
      (
      index > FpgaDevice :: FpgaMaxError
      )
 {
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 <<  7))); /* 1 */
      {
        index = FpgaDevice :: FpgaMaxError ;
      }
  } else ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 <<  8))); /* 4 */
     // else - no action required
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 <<  9))); /* 30 */
    CChannelState_11zqendz                                                                               (     170 ) ; /* 30 */  
    return
    (
    ( const char * ) xltError [ index ] ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: IsConfigured
//!
//! Description:
//! This is a PUBLIC inline method used to tell if the FpgaDevice Object
//! is properly configured.
//!
//! Parameters:
//! Return Value – TRUE if it properly configured/FALSE if it is not.
//!
//! Notes:
//! None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_67)
 
inline bool
  FpgaDevice :: IsConfigured() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 10))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 11))); /* 30 */
    CChannelState_11zqendz                                                                               (     172 ) ; /* 30 */  
    return
    ( mConfigured ) ;
  }
#endif /* endof dummy_ */
///////////////////////////////////////////////////////////////////
//! Function: Get[TODMinSec/TODHrs/TODDoY]RegAddress
//!
//! Description:
//! This is a public inline method used to tell the memory
//! location of the TOD Registers for the
//! FpgaDevice Object.
//!
//! Parameters:
//! Return Value – Address where the TOD Registers are located.
//!
//! Notes:
//! None
//!
///////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_68)
 
inline unsigned int
  FpgaDevice :: GetTODMinSecRegAddress() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 12))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 13))); /* 30 */
    CChannelState_11zqendz                                                                               (     174 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> TodMinSec ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_69)
 
inline unsigned int
  FpgaDevice :: GetTODHrsRegAddress() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 14))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 15))); /* 30 */
    CChannelState_11zqendz                                                                               (     176 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> TodHours ) ) ;
  }
#endif /* endof dummy_ */
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_70)
 
inline unsigned int
  FpgaDevice :: GetTODDoYRegAddress() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 16))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 17))); /* 30 */
    CChannelState_11zqendz                                                                               (     178 ) ; /* 30 */  
    return
    (
    ( unsigned int ) & ( mDeviceAddress -> TodDayOfYear ) ) ;
  }
#endif /* endof dummy_ */
       //FPGADEVICE_H
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\HwDevice\FpgaDevice.h*/
/*   CLOSE_FILE Include File */
 
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CChannelState.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2008-2019, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CChannelState.h
//
// Description: This file contains the definition for the CVLFState Interface
// class. This class contains the state pattern of the
// VLF receiver.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCHANNELSTATE_H
#define CCHANNELSTATE_H
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg_defs.h"
                                                                                                      // LDRA full path
///////////////////////////////////////////////////////////////////////////////
//
// Pre-declaration of classes included in this file
//
///////////////////////////////////////////////////////////////////////////////
 
class
  CChannel ;    //context of state class
 
class
  CChOperationalState ;    // Channel State
 
class
  CChDegradedState ;    // Channel State
 
class
  CChOfflineState ;
                       // Channel State
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//! Class: IChannelState
//!
//!
//! Description: This is an interface/abstract class used to derive the specific
//! state classes as part of the VLF channel state pattern.
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100007100{ public:  /* 76 */
 ldra_class_1100007100(){ };
 ldra_class_1100007100(int i){ };
};
class IChannelState
        :public ldra_class_1100007100 /* 75 */
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
   // Channel State Events
  virtual VLF_Channel_State_Type getChannelState () = 0 ;
 
  virtual void
               StartChannel ( CChannel * )
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_71)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 18))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 19))); /* 30 */
    CChannelState_11zqendz                                                                               (     180 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
  virtual void StopChannel ( CChannel * ) ;
 
  virtual void
               LoadTime ( CChannel * )
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_72)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 20))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 21))); /* 30 */
    CChannelState_11zqendz                                                                               (     182 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
 
  virtual void
               ChangeCpChanOpStatus ( CChannel * )
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_73)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 22))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 23))); /* 30 */
    CChannelState_11zqendz                                                                               (     184 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
 
  virtual void
               CryptoStatus ( CChannel * )
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_74)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 24))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 25))); /* 30 */
    CChannelState_11zqendz                                                                               (     186 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
 
  virtual void
               CryptoChannelUpdate ( CChannel * )
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_75)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 26))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 27))); /* 30 */
    CChannelState_11zqendz                                                                               (     188 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
 
  virtual void
               CryptoBIT ( CChannel * )
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_76)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 28))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 29))); /* 30 */
    CChannelState_11zqendz                                                                               (     190 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
  public :
   // Singleton Classes
  static CChOperationalState theChOperationalState ;
  static CChDegradedState theChDegradedState ;
  static CChOfflineState theChOfflineState ;
  private :
  VLF_Channel_State_Type chstate ;
} ;
///////////////////////////////////////////////////////////////////////////////
//! Class: COperationalState
//!
//!
//! Description: This class contains the class methods for the COperationalState
//! class. This class contains a state transition of the
//! VLF channels
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100017100{ public:  /* 76 */
 ldra_class_1100017100(){ };
 ldra_class_1100017100(int i){ };
};
class CChOperationalState :
        public ldra_class_1100017100, /* 69 */
public IChannelState
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  CChOperationalState () ;// constructors
  ~CChOperationalState () ; // destructor
   // Channel State Events
  VLF_Channel_State_Type getChannelState () ;
  void LoadTime ( CChannel * ) ;
  void ChangeCpChanOpStatus ( CChannel * ) ;
  void CryptoStatus ( CChannel * ) ;
  void CryptoChannelUpdate ( CChannel * ) ;
  void CryptoBIT ( CChannel * ) ;
  private :
  CChOperationalState ( const CChOperationalState & ) ;
 
  CChOperationalState &
  operator = ( const CChOperationalState & ) ;
   // Used throughout CChannelState
  VLF_Channel_State_Type chstate ;
} ;
///////////////////////////////////////////////////////////////////////////////
//! Class: CChDegradedState
//!
//!
//! Description: This class contains the class methods for the CDegradedState
//! class. This class contains a state transition of the
//! VLF channels
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100027100{ public:  /* 76 */
 ldra_class_1100027100(){ };
 ldra_class_1100027100(int i){ };
};
class CChDegradedState :
        public ldra_class_1100027100, /* 69 */
public IChannelState
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  CChDegradedState () ;// constructors
  ~CChDegradedState () ; // destructor
   // Channel State Events
  VLF_Channel_State_Type getChannelState () ;
  void LoadTime ( CChannel * ) ;
  void ChangeCpChanOpStatus ( CChannel * ) ;
  void CryptoStatus ( CChannel * ) ;
  void CryptoChannelUpdate ( CChannel * ) ;
  void CryptoBIT ( CChannel * ) ;
  private :
  CChDegradedState ( const CChDegradedState & ) ;
 
  CChDegradedState &
  operator = ( const CChDegradedState & ) ;
  VLF_Channel_State_Type chstate ;
  bool CheckStatusEvents ( CChannel * ) ;
  void CommonUpdate ( CChannel * ) ;
} ;
///////////////////////////////////////////////////////////////////////////////
//! Class: CChOfflinelState
//!
//!
//! Description: This class contains the class methods for the COfflineState
//! class. This class contains a state transition of the
//! VLF channels
//!
//! Notes: None
//!
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100037100{ public:  /* 76 */
 ldra_class_1100037100(){ };
 ldra_class_1100037100(int i){ };
};
class CChOfflineState :
        public ldra_class_1100037100, /* 69 */
public IChannelState
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  CChOfflineState () ;// constructors
  ~CChOfflineState () ; // destructor
   // Channel State Events
  VLF_Channel_State_Type getChannelState () ;
  void StartChannel ( CChannel * ) ;
  private :
  CChOfflineState ( const CChOfflineState & ) ;
 
  CChOfflineState &
  operator = ( const CChOfflineState & ) ;
  VLF_Channel_State_Type chstate ;
} ;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CChannelState.h*/
/*   CLOSE_FILE Include File */
 
 
typedef
Value
( FpgaDevice :: * FpgaGETSampleAddrPFuncType )() ;
 
typedef
FpgaDevice ::
  ERROR ( FpgaDevice :: * FpgaSetFreqPFuncType ) ( const unsigned int ) ;
 


class ldra_class_1100047100{ public:  /* 76 */
 ldra_class_1100047100(){ };
 ldra_class_1100047100(int i){ };
};
class CChannel
        :public ldra_class_1100047100 /* 75 */
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  Vlf_Channel_Type mCommPlan ; // comm plan
  MgrChCmdQueueStruct mChCmd ; // channel cmd
  CMode15 * mMode15 ;// Mode 15
  CMode9 * mMode9 ;// Mode 9
  CModeHidar * mModeHidar ;// Mode HIDAR
  CMode23 * mMode23 ;// Mode 23
  CModeSMA * mModeSMA ;// Mode SMA
   // flags
  bool mEnableHidarOpstat ; // HIDAR enable OP stat
  bool mEnableVlf_Pm ; // enable PM flag
  bool mCEPEnabled ; // CEP enable flag
  bool mAntiJamOnly ; // anti-jam flag
  bool mCommPlanValid ; // comm plan valiud flag
  bool mCpChanOpStatValid ; // valid channel OP stat flag
  bool mSampleOutputEnabled ; // FPGA Output Sample Test
  unsigned int mNum20msecs2send ; //Number of samples to send
  Msg_Error_Codes_Type mChannelError ; // channel err
  unsigned int mCurrentChanAction ; // set current channel action by operator
   // constructors
  CChannel ( Channel_ID_Type chan , unsigned short freq , Connection cmdConn , Value fpgaRegChAddr , FpgaSetFreqPFuncType chSetFreqFPtr , FpgaGETSampleAddrPFuncType chGetOutputSampleAddrFPtr ) ;
   // destructor
  ~CChannel () ;
   // methods
  void SendChCmd ( ChannelCmdStruct * pCmdBuff ) ;
  void HandleMgrCmd ( ChannelCmdStruct * mgrCmd ) ;
  void HandleChStatus ( ChanStatusQueueStruct * chstatus ) ;
  void SetChFreq () ;
  void SetChFreq ( const unsigned int freq ) ;
  void LoadChOutputSample () ;
  void ReportChStatus () ;
   // Channel State
  VLF_Channel_State_Type GetChState () ;
  void setState ( IChannelState * newChannelState ) ;
  void StartChannel () ;
  void StopChannel () ;
  void ChangeCpChanOpStatus () ;
  void LoadTime () ;
  void CryptoStatus () ;
  void CryptoChannelUpdate () ;
  void CryptoBIT () ;
  private :
  Value mFpgaRegChanAddress ; // FPGA register channel addr
  VLF_Receiver_Channel_Status_Type mStatus ; // channel status
  VLF_Receiver_Channel_Status_Type mPrevStatus ; // previous channel status
  VLF_Channel_State_Type mVlfChanState ; // channel state
   // channel specific function pointers
  FpgaGETSampleAddrPFuncType mChanGetOutputSampleAddrFPtr ; // get channel output sample addr
  FpgaSetFreqPFuncType mChanSetFreqFPtr ; // set channel frequency
   // Channel State
  IChannelState * mChannelState ;// channel state object
  void SetChState ( VLF_Channel_State_Type chstate ) ;
} ;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CChannel.h*/
/*   CLOSE_FILE Include File */
 
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg_defs.h"
                                                                                                      // LDRA full path
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CVLFState.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2008-2019, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// File Name: CVLFState.h
//
// Description: This file contains the definition for the CVLFState Interface
// class. This class contains the state pattern of the
// VLF receiver.
//
// Notes: none
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CVLFSTATE_H
#define CVLFSTATE_H
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg_defs.h"
                                                                                                      // LDRA full path
///////////////////////////////////////////////////////////////////////////////
//
// Pre-declaration of classes included in this file
//
///////////////////////////////////////////////////////////////////////////////
 
class
  CVlf ;    //context of state class
 
class
  CInitState ;    // VLF State
 
class
  CStandbyState ;    // VLF State
 
class
  COperationalState ;    // VLF State
 
class
  CDegradedState ;    // VLF State
 
class
  COfflineState ;
                     // VLF State
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Class: IVLFState
//
//
// Description: This is an interface/abstract class used to derive the specific
// state classes as part of the VLF state pattern.
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100057100{ public:  /* 76 */
 ldra_class_1100057100(){ };
 ldra_class_1100057100(int i){ };
};
class IVLFState
        :public ldra_class_1100057100 /* 75 */
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
   // VLF Receiver State Events
  virtual VLF_Receiver_State_Type getState () = 0 ;
 
  virtual void
               ChannelStateChange ( CVlf * )
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_77)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 30))); /* 37 */
  ((unsigned int)(bitmapstruct.element5 |= ((unsigned int)1 << 31))); /* 30 */
    CChannelState_11zqendz                                                                               (     192 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
 
  virtual void
               DSPCommunications ( CVlf * )
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_78)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 <<  0))); /* 37 */
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 <<  1))); /* 30 */
    CChannelState_11zqendz                                                                               (     194 ) ; /* 30 */  
  } ;
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
  virtual void ContBITUpdate ( CVlf * ) ;
  public :
   // Singletons of each state
  static CInitState theInitState ; // init state
  static CStandbyState theStandbyState ; // standby state
  static COperationalState theOperationalState ; // operational state
  static CDegradedState theDegradedState ; // degraded state
  static COfflineState theOfflineState ; // offline state
} ;
///////////////////////////////////////////////////////////////////////////////
// Class: CInitState
//
//
// Description: This class contains the class methods for the CInitState class.
// this class contains a state transition of the VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100067100{ public:  /* 76 */
 ldra_class_1100067100(){ };
 ldra_class_1100067100(int i){ };
};
class CInitState :
        public ldra_class_1100067100, /* 69 */
public IVLFState
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  CInitState () ;// constructors
  ~CInitState () ; // destructor
   // VLF Receiver State Events
  VLF_Receiver_State_Type getState () ;
  void DSPCommunications ( CVlf * ) ;
  private :
  CInitState ( const CInitState & ) ;
 
  CInitState &
  operator = ( const CInitState & ) ;
  VLF_Receiver_State_Type state ;
} ;
///////////////////////////////////////////////////////////////////////////////
// Class: COperationalState
//
//
// Description: This class contains the class methods for the COperationalState
// class. This class contains a state transition of the
// VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100077100{ public:  /* 76 */
 ldra_class_1100077100(){ };
 ldra_class_1100077100(int i){ };
};
class COperationalState :
        public ldra_class_1100077100, /* 69 */
public IVLFState
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  COperationalState () ;// constructors
  ~COperationalState () ; // destructor
   // VLF Receiver State Events
  VLF_Receiver_State_Type getState () ;
  void ChannelStateChange ( CVlf * ) ;
  void ContBITUpdate ( CVlf * ) ;
  private :
  COperationalState ( const COperationalState & ) ;
 
  COperationalState &
  operator = ( const COperationalState & ) ;
  VLF_Receiver_State_Type state ;
} ;
///////////////////////////////////////////////////////////////////////////////
// Class: CDegradedState
//
//
// Description: This class contains the class methods for the CDegradedState
// class. This class contains a state transition of the
// VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100087100{ public:  /* 76 */
 ldra_class_1100087100(){ };
 ldra_class_1100087100(int i){ };
};
class CDegradedState :
        public ldra_class_1100087100, /* 69 */
public IVLFState
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  CDegradedState () ;// constructors
  ~CDegradedState () ; // destructor
   // VLF Receiver State Events
  VLF_Receiver_State_Type getState () ;
  void ChannelStateChange ( CVlf * ) ;
  private :
  CDegradedState ( const CDegradedState & ) ;
 
  CDegradedState &
  operator = ( const CDegradedState & ) ;
  VLF_Receiver_State_Type state ;
} ;
///////////////////////////////////////////////////////////////////////////////
// Class: CStandbyState
//
//
// Description: This class contains the class methods for the CStandbyState
// class. This class contains a state transition of the
// VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100097100{ public:  /* 76 */
 ldra_class_1100097100(){ };
 ldra_class_1100097100(int i){ };
};
class CStandbyState :
        public ldra_class_1100097100, /* 69 */
public IVLFState
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  CStandbyState () ;// constructors
  ~CStandbyState () ; // destructor
   // VLF Receiver State Events
  VLF_Receiver_State_Type getState () ;
  void ChannelStateChange ( CVlf * ) ;
  private :
  CStandbyState ( const CStandbyState & ) ;
 
  CStandbyState &
  operator = ( const CStandbyState & ) ;
  VLF_Receiver_State_Type state ;
} ;
///////////////////////////////////////////////////////////////////////////////
// Class: COfflineState
//
//
// Description: This class contains the class methods for the COfflineState
// class. This class contains a state transition of the
// VLF receiver
//
// Notes: None
//
///////////////////////////////////////////////////////////////////////////////
 


class ldra_class_1100008100{ public:  /* 76 */
 ldra_class_1100008100(){ };
 ldra_class_1100008100(int i){ };
};
class COfflineState :
        public ldra_class_1100008100, /* 69 */
public IVLFState
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  COfflineState () ;// constructors
  ~COfflineState () ; // destructor
   // VLF Receiver State Events
  VLF_Receiver_State_Type getState () ;
  void ContBITUpdate ( CVlf * ) ;
  private :
  COfflineState ( const COfflineState & ) ;
 
  COfflineState &
  operator = ( const COfflineState & ) ;
  VLF_Receiver_State_Type state ;
} ;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CVLFState.h*/
/*   CLOSE_FILE Include File */
 
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\CMessage.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2006-2021, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// Class: CMessage
//
// File Name: CMessage.h
//
// Description: This file contains the Message class definition used to send
// and receive messages via ethernet interface.
// Notes:
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CMESSAGE_H
#define CMESSAGE_H
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg_defs.h"
                                                                                                      // LDRA full path
 


class ldra_class_1100018100{ public:  /* 76 */
 ldra_class_1100018100(){ };
 ldra_class_1100018100(int i){ };
};
class CMessage
        :public ldra_class_1100018100 /* 75 */
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  static const int NO_TIMESTAMP = 0 ; // timestamp flag
  CMessage () ; // constructor
 
  ~CMessage ()
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_79)
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 <<  2))); /* 37 */
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 <<  3))); /* 30 */
    CChannelState_11zqendz                                                                               (     196 ) ; /* 30 */  
  } ;               // destructor
#else
 ; /* end of prototype alternative */
#endif /* endof dummy_ */
   // methods
  Subsystem_Type GetDest () const ;
  void SetDest ( const Subsystem_Type & subsystem ) ;
  Subsystem_Type GetSrc () const ;
  void SetSrc ( const Subsystem_Type & subsystem ) ;
  unsigned long GetTimestamp () const ;
  void SetTimestamp ( const unsigned long timestamp = NO_TIMESTAMP ) ;
  unsigned int GetActionId () const ;
  void SetActionId ( const unsigned int action ) ;
  unsigned int GetSequenceNum () const ;
  void SetSequenceNum ( const unsigned int sequence ) ;
  void SetProtocolVersion ( const Protocol_Version_Type & protocolVersion ) ;
  Protocol_Version_Type GetProtocolVersion () const ;
  void SetReservedConfig ( const Reserved_Config_Type & reservedConfig ) ;
  Reserved_Config_Type GetReservedConfig () const ;
  Message_ID_Type GetMsgId () const ;
  void SetMsgId ( const Message_ID_Type id ) ;
  Message_Type * GetMsgData () const ;
  void SetMsgData ( const void * data , const unsigned short len ) ;
  void SetDataLen ( const unsigned int len ) ;
  unsigned short GetMsgLen () const ;
  void SetMsgChecksum () ;
  Msg_Error_Codes_Type IsMsgHeaderValid () ;
  void SetMsgHeaderDefaults () ;
  private :
  Message_Type mMsgData ; // msg data
   // method
  unsigned int CalculateChecksum () ;
  bool IsCheckSumValid () ;
} ;
////////////////////////////////////////////////////////////////////////////////
// Function: GetDest
//
// Description:
// This method returns the message destination subsystem ID
//
// Parameters: None
//
// Return: The Destination subsystem ID (Subsystem_Type)
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_80)
 
inline Subsystem_Type
  CMessage :: GetDest() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 <<  4))); /* 37 */
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 <<  5))); /* 30 */
    CChannelState_11zqendz                                                                               (     198 ) ; /* 30 */  
    return
    ( Subsystem_Type ) mMsgData.header.DestSS ;
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: SetDest
//
// Description:
// This method set the message destination subsystem ID
//
// Parameters: The Destination subsystem ID (Subsystem_Type)
//
// Return: None
//
// Notes: None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_81)
 
inline void
  CMessage :: SetDest (
  const Subsystem_Type & subsystem )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 <<  6))); /* 37 */
    mMsgData.header.DestSS = subsystem ;
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 <<  7))); /* 30 */
    CChannelState_11zqendz                                                                               (     200 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: GetSrc
//
// Description:
// This method is used to get the message source subsystem ID
//
// Parameters: None
//
// Return: The source subsystem ID (Subsystem_Type)
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_82)
 
inline Subsystem_Type
  CMessage :: GetSrc() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 <<  8))); /* 37 */
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 <<  9))); /* 30 */
    CChannelState_11zqendz                                                                               (     202 ) ; /* 30 */  
    return
    ( Subsystem_Type ) mMsgData.header.SrcSS ;
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: SetSrc
//
// Description:
// This method is used set the message source subsystem ID
//
// Parameters: source subsystem ID (Subsystem_Type)
//
// Return: None
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_83)
 
inline void
  CMessage :: SetSrc (
  const Subsystem_Type & subsystem )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 10))); /* 37 */
    mMsgData.header.SrcSS = subsystem ;
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 11))); /* 30 */
    CChannelState_11zqendz                                                                               (     204 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: GetTimestamp
//
// Description:
// This method retuns the message timestamp
//
// Parameters: None
//
// Return: The timestamp (unsigned int)
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_84)
 
inline unsigned long
  CMessage :: GetTimestamp() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 12))); /* 37 */
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 13))); /* 30 */
    CChannelState_11zqendz                                                                               (     206 ) ; /* 30 */  
    return
    mMsgData.header.timestamp ;
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: SetTimestamp
//
// Description:
// This method set message timestamp
//
// Parameters: timestamp (unsigned int)
//
// Return: none
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_85)
 
inline void
  CMessage :: SetTimestamp (
  const unsigned long timestamp )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 14))); /* 37 */
    mMsgData.header.timestamp = timestamp ;
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 15))); /* 30 */
    CChannelState_11zqendz                                                                               (     208 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: GetActionId
//
// Description:
// This method returns the message action id
//
// Parameters: None
//
// Return: The action id (unsigned int)
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_86)
 
inline unsigned int
  CMessage :: GetActionId() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 16))); /* 37 */
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 17))); /* 30 */
    CChannelState_11zqendz                                                                               (     210 ) ; /* 30 */  
    return
    mMsgData.header.ActionId ;
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: SetActionId
//
// Description:
// This method set message action id
//
// Parameters: action id (unsigned int)
//
// Return: none
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_87)
 
inline void
  CMessage :: SetActionId (
  const unsigned int action )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 18))); /* 37 */
    mMsgData.header.ActionId = action ;
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 19))); /* 30 */
    CChannelState_11zqendz                                                                               (     212 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: GetSequenceNum
//
// Description:
// This method returns the sequence num
//
// Parameters: None
//
// Return: The action id (unsigned int)
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_88)
 
inline unsigned int
  CMessage :: GetSequenceNum() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 20))); /* 37 */
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 21))); /* 30 */
    CChannelState_11zqendz                                                                               (     214 ) ; /* 30 */  
    return
    mMsgData.header.SequenceNum ;
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: SetSequenceNum
//
// Description:
// This method set message sequence number
//
// Parameters: sequence number (unsigned int)
//
// Return: none
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_89)
 
inline void
  CMessage :: SetSequenceNum (
  const unsigned int sequence )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 22))); /* 37 */
    mMsgData.header.SequenceNum = sequence ;
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 23))); /* 30 */
    CChannelState_11zqendz                                                                               (     216 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: SetProtocolVersion
//
// Description:
// This method is used set the protocol version
//
// Parameters: protocolVersion (Protocol_Version_Type)
//
// Return: None
//
// Notes:
// This method is called in the CMessage constructor
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_90)
 
inline void
  CMessage :: SetProtocolVersion (
  const Protocol_Version_Type & protocolVersion )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 24))); /* 37 */
    mMsgData.header.ProtocolVersion = protocolVersion ;
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 25))); /* 30 */
    CChannelState_11zqendz                                                                               (     218 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: GetProtocolVersion
//
// Description:
// This method is used get the message protocol version
//
// Parameters: None
//
// Return: Protocol_Version_Type
//
// Notes:
// This method is called in VP and CP as required
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_91)
 
inline Protocol_Version_Type
  CMessage :: GetProtocolVersion() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 26))); /* 37 */
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 27))); /* 30 */
    CChannelState_11zqendz                                                                               (     220 ) ; /* 30 */  
    return
    ( Protocol_Version_Type ) mMsgData.header.ProtocolVersion ;
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: SetReservedConfig
//
// Description:
// This method is used set the Reserved Config
//
// Parameters: reservedConfig (Reserved_Config_Type)
//
// Return: None
//
// Notes:
// This method is called in the CMessage constructor
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_92)
 
inline void
  CMessage :: SetReservedConfig (
  const Reserved_Config_Type & reservedConfig )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 28))); /* 37 */
    mMsgData.header.ReservedConfig = reservedConfig ;
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 29))); /* 30 */
    CChannelState_11zqendz                                                                               (     222 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: GetProtocolVersion
//
// Description:
// This method is used get the message protocol version
//
// Parameters: None
//
// Return: Protocol_Version_Type
//
// Notes:
// This method is called in VP and CP as required
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_93)
 
inline Reserved_Config_Type
  CMessage :: GetReservedConfig() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 30))); /* 37 */
  ((unsigned int)(bitmapstruct.element6 |= ((unsigned int)1 << 31))); /* 30 */
    CChannelState_11zqendz                                                                               (     224 ) ; /* 30 */  
    return
    ( Reserved_Config_Type ) mMsgData.header.ReservedConfig ;
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: GetMsgId
//
// Description:
// This method returns the message ID
//
// Parameters: None
//
// Return: The message ID (Message_ID_Type)
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_94)
 
inline Message_ID_Type
  CMessage :: GetMsgId() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 <<  0))); /* 37 */
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 <<  1))); /* 30 */
    CChannelState_11zqendz                                                                               (     226 ) ; /* 30 */  
    return
    ( Message_ID_Type ) mMsgData.header.MsgId ;
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: SetMsgId
//
// Description:
// This method sets the message ID
//
// Parameters: message ID (Message_ID_Type)
//
// Return: none
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_95)
 
inline void
  CMessage :: SetMsgId (
  const Message_ID_Type id )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 <<  2))); /* 37 */
    mMsgData.header.MsgId = id ;
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 <<  3))); /* 30 */
    CChannelState_11zqendz                                                                               (     228 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: GetMsgData
//
// Description:
// This method returns the message class data
//
// Parameters: None
//
// Return: pointer to message class data (Message_Type *)
//
// Notes: None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_96)
 
inline Message_Type *
CMessage :: GetMsgData() const
{
 int izzqqzz=((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 <<  4))); /* 37 */
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 <<  5))); /* 30 */
    CChannelState_11zqendz                                                                               (     230 ) ; /* 30 */  
  return
  ( Message_Type * ) & mMsgData ;
}
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: GetMsgLen
//
// Description:
// This method returns the message length
//
// Parameters: None
//
// Return: message length (unsigned short)
//
// Notes: none
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_97)
 
inline unsigned short
  CMessage :: GetMsgLen() const
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 <<  6))); /* 37 */
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 <<  7))); /* 30 */
    CChannelState_11zqendz                                                                               (     232 ) ; /* 30 */  
    return
    mMsgData.header.DataLen + sizeof ( mMsgData.header ) ;
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Function: SetDataLen
//
// Description:
// This method sets the lenth of the data field
//
// Parameters: length of data (unsigned int)
//
// Return: none
//
// Notes:
// None
//
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_98)
 
inline void
  CMessage :: SetDataLen (
  const unsigned int len )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 <<  8))); /* 37 */
    mMsgData.header.DataLen = len ;
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 <<  9))); /* 30 */
    CChannelState_11zqendz                                                                               (     234 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\CMessage.h*/
/*   CLOSE_FILE Include File */
 
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\BIT\CDspBIT.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2008-2019, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
// Class: CDspBIT
//
// File Name: CDspBIT.h
//
// Description: This file contains the DSP Built-In-Test (BIT) Class
// definition for power-up and continuous BIT.
//
//
// Notes: This class is implemented as singleton to prevent more than one
// instantiation of the CDspBIT object. To obtain a reference to
// an instance of the CDspBIT object, the user calls the
// public Instance() member function.
//
// The Instance() and CBITTimeOutHandler() methods are in
// the CDspBIT_Common.cc file in the KgrVpAppCommon\BIT folder
// so they can be shared by the CDspBIT classes of both DSP1 and DSP2.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CDSPBIT_H
#define CDSPBIT_H
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\Common\msg_defs.h"  // LDRA full path
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpBsp\FpgaIoDevice.h"
                                                                                             // LDRA full path
 


class ldra_class_1100028100{ public:  /* 76 */
 ldra_class_1100028100(){ };
 ldra_class_1100028100(int i){ };
};
class CDspBIT
        :public ldra_class_1100028100 /* 75 */
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
//////////////////////////////////////////////////////////////////////////////
//
// class structures and defs
//
//////////////////////////////////////////////////////////////////////////////
  public :
  enum Ethernet_Comm_Type
  {
    CP_TO_DSP1_COMM = 0 ,
    DSP2_TO_DSP1_COMM = 1
  } ;
//////////////////////////////////////////////////////////////////////////////
//
// class methods and variables
//
//////////////////////////////////////////////////////////////////////////////
  public :
  static CDspBIT * Instance () ;
  void updateLinkAliveCount ( const Ethernet_Comm_Type ethComm ) ;
  BIT_Result_Type runDspPBIT () ;
  BIT_Result_Type runDspCBIT () ;
  bool isCPLinkUp () ;
  bool isDSP2LinkUp () ;
  void toggleSwStatusLED () ;
  bool PBitCompleted ;
  private :
  enum GPIO_DSP1_PINS
  {
    GpioSwStatusLED = 26 ,
    GpioFpgaConfigFault = 31 ,
    GpioInterlockRcv = 32
  } ;
  enum FPGA_STATUS_TYPE
  {
    DCXO_STATUS = 1 ,
    FCXO_LOCK_STATUS = 2
  } ;
  Bit_Set_Type mSwStatusLED ; // status LED
  IODevice mFpgaCrcIODevice ; // FPGA CRC I/O device
  IODevice mGPIODevice ; // GPIO device
  unsigned long mCPEthCnt ; // link alive count from CP
  unsigned long mDSP2EthCnt ; // link alive count from DSP2
  unsigned long mPrevCPEthCnt ; // link alive count from CP
  unsigned long mPrevDSP2EthCnt ; // link alive count from DSP1
  unsigned int mCPConnCntr ; // cntr to check num of misses for CP Link Dn
  static const int CP_LINK_MISS_LIMIT = 5 ; // link miss limit
   // CBIT Timer
  static const unsigned char CBIT_TIMER = 5 ; // 5 seconds
  static const unsigned long SW_LED_TIMER = 0x40000000 ; // 1/4 seconds
  static AlarmTimer mCBITTimer ; // CBIT timer
  static void CBITTimeOutHandler () ;
  static AlarmTimer mSWLEDTimer ; // LED timer
  static void SWLEDTimeOutHandler () ;
  bool mCBITActive ; // CBIT active flag
  int mDspConfig ; // DSP config
  bool mAntTestDisabled ; // Antenna test diasbled flag
  private :
  CDspBIT () ;// constructor
  ~CDspBIT () ;// destructor
  static CDspBIT * mInstance ;
  BIT_Result_Type initPBITResults () ;
  BIT_Result_Type initCBITResults () ;
   //Individual BIT tests.
  enum BIT_Fault_Type getFpgaConfigFault () ;
  enum BIT_Fault_Type getInterlockStatus () ;
  enum BIT_Fault_Type runFpgaIFTest () ;
  enum BIT_Fault_Type runFpgaCRCTest () ;
  enum BIT_Fault_Type getDCXOStatus () ;
  enum BIT_Fault_Type getRfaPsStatus () ;
  enum BIT_Fault_Type getFCXOLockStatus () ;
  enum BIT_Fault_Type runTimeAccuracyTest () ;
  enum Bit_Set_Type getExtSelStatus () ;
  enum BIT_Fault_Type getPpsStatus () ;
  void runPPSTest ( TimeLoadCmd cmd ) ;
  enum BIT_Fault_Type getTimeLoadedStatus () ;
  enum BIT_Fault_Type getFpgaStatusHelper ( FPGA_STATUS_TYPE statusType ) ;
   //Update individual PBIT status
  void updateFlashStatus ( BIT_Result_Type & results ) ;
  void updateSdramStatus ( BIT_Result_Type & results ) ;
  void updateProcessorStatus ( BIT_Result_Type & results ) ;
  void update25MhzClockStatus ( BIT_Result_Type & results ) ;
  void updateEccStatus ( BIT_Result_Type & results ) ;
  void updateFpgaStatus ( BIT_Result_Type & results ) ;
  void updateRfaStatus ( BIT_Result_Type & results ) ;
  void updateAntChan1Status ( BIT_Result_Type & results ) ;
  void updateAntChan2Status ( BIT_Result_Type & results ) ;
  void updatePBITDcxoBitStatus ( BIT_Result_Type & results ) ;
  void updatePBITRfaPsBitStatus ( BIT_Result_Type & results ) ;
  void updatePBITfcxoStatus ( BIT_Result_Type & results ) ;
  void updateEepromStatus ( BIT_Result_Type & results ) ;
  void updateAntChanStatus ( BIT_Result_Type & results , DSP1_PBIT_Type antChan ) ;
   //Update individual CBIT status
  void updateCpuBoardStatus ( BIT_Result_Type & results ) ;
  void updateOvervoltageStatus ( BIT_Result_Type & results ) ;
  void updateFpgaIfStatus ( BIT_Result_Type & results ) ;
  void updateFpgaCrcStatus ( BIT_Result_Type & results ) ;
  void updatePpsStatus ( BIT_Result_Type & results , const unsigned int & bitNum ) ;
  void updateTimeAccuracyStatus ( BIT_Result_Type & results ) ;
  void updateTimeofDayStatus ( BIT_Result_Type & results ) ;
  void updateTimeLoadedStatus ( BIT_Result_Type & results ) ;
  void updateDcxoBitStatus ( BIT_Result_Type & results ) ;
  void updatePs1BitStatus ( BIT_Result_Type & results ) ;
  void updatefcxoStatus ( BIT_Result_Type & results ) ;
  void updateIic1Status ( BIT_Result_Type & results , const unsigned int & bitNum ) ;
  void updateExtSelStatus ( BIT_Result_Type & results ) ;
  void updateInterlockRcvStatus ( BIT_Result_Type & results ) ;
  void updateSystemTimeStatus () ;
  void updateEccErrorStatus ( BIT_Result_Type & results ) ;
} ;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\BIT\CDspBIT.h*/
/*   CLOSE_FILE Include File */
 
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\VPCommon\CDspConfig.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2019 Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
// Class: CDspConfig
//
// File Name: CDspConfig.h
//
// Description: This file contains the CDspConfig Class
// definition to read DSP1 & DSP2 Strap configurations from
// Equipment_Select pinout J3 B1-B4 and D1-D4.
//
//
// Notes: This class is implemented as singleton to prevent more than one
// instantiation of the CDspConfig object. To obtain a reference to
// an instance of the CDspConfig object, the user calls the
// public Instance() member function.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CDSPCONFIG_H
#define CDSPCONFIG_H
#include <INTEGRITY.h>
 


class ldra_class_1100038100{ public:  /* 76 */
 ldra_class_1100038100(){ };
 ldra_class_1100038100(int i){ };
};
class CDspConfig
        :public ldra_class_1100038100 /* 75 */
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
//////////////////////////////////////////////////////////////////////////////
//
// class structures and defs
//
//////////////////////////////////////////////////////////////////////////////
  public :
  static const int MAX_CONFIG_ITEMS = 16 ;
                                           // max config items 0-15 = 16 items
   // DSP1 Strap configurations from Equipment_Select pinout J3 B1-B4
   // 0: default - 2 ants,2 inputs B2-(Omni)
   // 1: 1 antenna,1 input, no antenna test for E6B (Ant 1)
   // 2: 1 antenna,2 inputs,no antenna test-future E6B(Omni)
   // 3: 1 antennae, 2 inputs B52 - Omni
   // 4: 2 antennae, 3 inputs-future B52
   // 5-15 - reserved
  enum DSP1_Equip_Sel_Strap_Config_Type
  {  //Antenna Type
    TWO_ANTENNA_TWO_INPUTS = 0 ,   //AS-3857
    ONE_ANT_1_INP_TEST_DISABLED = 1 ,   //NONE
    ONE_ANT_2_INPS_TEST_DISABLED = 2 ,
    ONE_ANTENNA_TWO_INPUTS = 3 ,   //AS-3858
    TWO_ANTENNAE_THREE_INPUTS = 4 ,
    MAX_DSP1_STRAP_CONFIG
  } ;
   // DSP2 Strap configurations from Equipment_Select pinout J3 D1-D4
   // 0 - default for one receiver with a PTS
   // 1 - RCVR 1 in 2 receivers config without a PTS, VM23 Msg Filter disabled
   // 2 - RCVR 2 in 2 receivers config without a PTS, VM23 Msg Filter disabled
   // 3-15 Reserved
  enum DSP2_Equip_Sel_Strap_Config_Type
  {
    RVCR_DEFAULT = 0 ,   // default IP 10.1.5.16
    RVCR1_NO_PTS_VM23_MSG_FLTR_DIS = 1 ,   // ip 10.1.5.15
    RVCR2_NO_PTS_VM23_MSG_FLTR_DIS = 2 ,   // ip 10.1.5.16
    MAX_DSP2_STRAP_CONFIG
  } ;
//////////////////////////////////////////////////////////////////////////////
//
// class methods and variables
//
//////////////////////////////////////////////////////////////////////////////
  public :
  CDspConfig () ;// constructor
  CDspConfig ( int inDspConfigIO ) ;
                                  // alt constructor
  ~CDspConfig () ;// destructor
  int getEquipSelectConfig () ;
  private :
  CDspConfig ( const CDspConfig & ) ;
 
  CDspConfig &
  operator = ( const CDspConfig & ) ;
  int mDspConfig ; // 0..15
} ;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\VPCommon\CDspConfig.h*/
/*   CLOSE_FILE Include File */
 
 


class ldra_class_1100048100{ public:  /* 76 */
 ldra_class_1100048100(){ };
 ldra_class_1100048100(int i){ };
};
class CVlf
        :public ldra_class_1100048100 /* 75 */
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  static CVlf * Instance () ;
  Subsystem_Type mId ;
  CChannel * chan [ MAX_VLF_CHANNEL ] ;
  VLF_Receiver_System_Status_Msg_Type mRcvrStatus ;
  Configuration_Params_Msg_Type mConfigParms ;
  Subsystem_Type mActiveOES ;
  BIT_Result_Type mDspPBit ;
  BIT_Result_Type mDspCBit ;
  bool mCPLinkUp ;
  bool mDSP2LinkUp ;
  bool mMemoryClearRcvd ;
  bool mDidCpFullOpOccur ;
  CDspConfig mDspIOConfig ;
  public :
   // report overall status change of VLF Receiver
  void UpdateRcvrStatus () ;
   //version info methods
  void SendDSP2VersionData () ;
  void setFpgaVersion ( const char * version ) ;
   // State Events that cause transitions
  void setState ( IVLFState * newState ) ;
  void DSPCommunications () ;
  void ContBITUpdate () ;
  void ChannelStateChange () ;
  void setTimeLoadedStatus () ;
  void setKeyTblLoadedStatus ( bool status ) ;
  bool getKeyTblLoadedStatus () const ;
  void CryptoStatusChange () ;
  void CryptoChannelChange ( Channel_ID_Type chanNum ) ;
  void RestartChannelsAfterEventChg ( int & chanNum ) ;
  private :
   // Misc initialization functions.
  void GetProdVersionData () ;
  void SetConfigData () ;
   //variables for version construction
  static const unsigned short MAX_NUMBER_VERSIONS = 4 ;
  int versionEnum [ MAX_NUMBER_VERSIONS ] ;
  char * versionTitleString [ MAX_NUMBER_VERSIONS ] ;
  char * configString [ CDspConfig :: MAX_CONFIG_ITEMS + 1 ] ;
  private :
  CVlf () ;// constructors
  ~CVlf () ; // destructor
  CVlf ( const CVlf & ) ;
 
  CVlf &
  operator = ( const CVlf & ) ;
  static CVlf * mInstance ;
  Version_Data_Msg_Type mVersion ;
   // VLF State
  IVLFState * mState ;
} ;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CVlf.h*/
/*   CLOSE_FILE Include File */
 
#include "CChannelState.h"
/* OPEN FILE E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CTimeLoad.h */
///////////////////////////////////////////////////////////////////////////////
// Copyright 2007-2020, Collins Aerospace. All rights reserved.
// Collins Aerospace Proprietary Information
//
// Security classification: UNCLASSIFIED//FOUO
//
///////////////////////////////////////////////////////////////////////////////
//
// Class: Timeload
//
// File Name: TimeLoad.h
//
// Description: This file is an include file that contains the class prototypes
// of the TimeLoad Class and inline TimeLoad methods. This
// class is used by the user to load time into the VLF receiver.
//
// Notes: The GEMS STM modules broadcast time at the tone (TATT) message
// and a 1PPS signal to the OES every second. The TATT message is an
// incoming UDP message that is converted to a TCP message and sent to
// the VLF receiver.
//
// The TATT message includes the following information:
// 1. UTC time and offset to the next 1PPS mark
// 2. Time source (BBC, GPS, IRIG-B, MILSTAR/AEHF, Operator)
// 3. Estimate time accuracy
// 4. Indicator of a narrow or wide 1PPS mark
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CTIMELOAD_H
#define CTIMELOAD_H
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpBsp\FpgaIoDevice.h"  // LDRA full path
#include "E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpAppCommon\VPCommon\chan_struct.h"
                                                                                                           // LDRA full path
 


class ldra_class_1100058100{ public:  /* 76 */
 ldra_class_1100058100(){ };
 ldra_class_1100058100(int i){ };
};
class CTimeLoad
        :public ldra_class_1100058100 /* 75 */
{
#if defined(ldra_qq_tbrun)
 friend class ldra_driver_11;
#endif
  public :
  static CTimeLoad * Instance () ;
  TimeLoadState mState ; // Time load states
  TimeLoadError mErr ; // Time load errors
  TimeLoadError mPpsErr ; // Time pps errors
  TimeLoadError mStodErr ; // Time stod errors
  void GetTimeStatus () ;// get FPGA IO device time status
  VlfTime GetVlfTime () ;// get the vlf internal clock
  void GetAbsTime ( Absolute_Time_Type * absTime ) ;
                                                 // get the vlf internal clock
  void RunPpsPbit ( TimeLoadCmd cmd ) ;// send Pbit command to FPGA IODevice
   // time handling
  void SetSystemClock () ;
  void setTimeOfDayVar ( Date_Time_Type timeOfDay ) ;
  void LoadTime ( TimeLoadCmd cmd , Load_Type timeLoadStyle ) ;
   ////////////////
   // constants
   ////////////////
  static const int NUM_SECONDS = 60 ; // 60 seconds
  static const int NUM_MINUTES = 60 ; // 60 minutes
  static const int NUM_SEC_PER_HOUR = ( NUM_SECONDS * NUM_MINUTES ) ;
                                                                    // seconds per hour
  private :
  static CTimeLoad * mInstance ;
  CTimeLoad () ;// constructors
  ~CTimeLoad () ; // destructor
  CTimeLoad ( const CTimeLoad & ) ;
 
  CTimeLoad &
  operator = ( const CTimeLoad & ) ;
  void setLoadType ( Load_Type timeLoadStyle ) ;
  void SendTimeLoadCmd ( TimeLoadCmd cmd ) ;
                                         // send time load command to FPGA IO object
  void RestartChannelAfterTimeLoad ( int & chanNum ) ;
   // time loading variables
  Date_Time_Type mTimeOfDay ; // time of day
  Load_Type mStyleOfTimeLoad ; // load type
} ;
//////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
//////////////////////////////////////////////////////////////////////////////
#endif /*00 E:\CVRi1\CVRi1\SD&D\Software\VLF_Software\Source\Projects\KgrVpApp\src\MGR\CTimeLoad.h*/
/*   CLOSE_FILE Include File */
 
#include "CChannel.h"
////////////////////////////////////////////////////////////////////////////////
// Static Variable
////////////////////////////////////////////////////////////////////////////////
// The Following are classes and initialized in their respective constructors
 
 int                                                                                                  ZZ11106326 = (
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 10))) * /* 26 + 23 */
  1 ) ; /* 26 */
CChOperationalState
IChannelState::theChOperationalState ;                    // channel operational state
 
 int                                                                                                  ZZ11106329 = (
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 11))) * /* 26 + 23 */
  1 ) ; /* 26 */
CChDegradedState
IChannelState::theChDegradedState ;                 // channel degraded state
 
 int                                                                                                  ZZ11106332 = (
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 12))) * /* 26 + 23 */
  1 ) ; /* 26 */
CChOfflineState
IChannelState::theChOfflineState ;
                                                  // channel offline state
////////////////////////////////////////////////////////////////////////////////
//! Function: StopChannel
//!
//! Description:
//! This method is used to transition the channel state to Offline State.
//!
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: NONE
//!
//! Notes:
//! This base class handler can be overridden, if needed.
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_99)
 
void
  IChannelState :: StopChannel (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 13))); /* 37 */
    if
      (
      !
        check4Null (
        instance , __FILE__ , __LINE__ )
      )
 {
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 14))); /* 1 */
      {
      // check to ensure all modes have stopped or were never started
        if
 (  /* 50 */
          (
          
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
          
  (     /*  52 */ 
          (
          instance -> mMode15 -> mChanModeStatus.modeScanState == MODE_SEARCH_HALTED
          )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,           1 ),
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 15))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,           1 ),
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 16))),0) ) /* 54 */
          &&
          
  (     /*  52 */ 
          (
          instance -> mMode9 -> mChanModeStatus.modeScanState == MODE_SEARCH_HALTED
          )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,           1 ),
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 19))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,           1 ),
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 20))),0) ) /* 54 */
          &&
          
  (     /*  52 */ 
          (
          instance -> mModeHidar -> mChanModeStatus.modeScanState == MODE_SEARCH_HALTED
          )
 ? (CChannelState_11zzdo17                                                                              
 (           3 ,1,           1 ),
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 23))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           3 ,0,           1 ),
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 24))),0) ) /* 54 */
          &&
          
  (     /*  52 */ 
          (
          instance -> mMode23 -> mChanModeStatus.modeScanState == MODE_SEARCH_HALTED
          )
 ? (CChannelState_11zzdo17                                                                              
 (           4 ,1,           1 ),
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 27))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           4 ,0,           1 ),
  ((unsigned int)(bitmapstruct.element7 |= ((unsigned int)1 << 28))),0) ) /* 54 */
          &&
          
  CChannelState_11zzdo17                                                                               (    5, /*  72 */ 
          ( instance -> mModeSMA -> mChanModeStatus.modeScanState == MODE_SEARCH_HALTED
          )
  ? 1 : 0  ,       1  )  /*  73 */
  ? 1 : 0  ,       1  )  /*  82 */
          )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 <<  3))); /* 1 */
          {
            instance ->
                        setState (
            & theChOfflineState ) ;
          }
  } else ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 <<  4))); /* 4 */
       //else nothing- all modes halted
      }
  } else ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 <<  5))); /* 4 */
    //else nothing- error handled in if statement
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 <<  6))); /* 30 */
    CChannelState_11zqendz                                                                               (     263 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Class: CChOperationalState
//
//
// Description: This class contains the class methods for the COperationalState
// class. This class contains a state transition of the
// VLF channels
//
// Notes: None
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//! Function: CChOperationalState
//!
//! Description:
//! This is the class default constructor method
//!
//! Parameters:
//! None
//!
//! Return:
//! None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_100)
 
  CChOperationalState :: CChOperationalState() :
    ldra_class_1100017100(),  /* 71 c1*/
  IChannelState ( )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 <<  7))); /* 37 */
   //set Channel State Variable
    chstate = CH_OPERATIONAL ;
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 <<  8))); /* 30 */
    CChannelState_11zqendz                                                                               (     265 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//! This destructor method is used to cleanup the COperationalState object
//! once it is deleted.
//!
//! Parameters:
//! None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_101)
 
  CChOperationalState :: ~CChOperationalState()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 <<  9))); /* 37 */
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 10))); /* 30 */
    CChannelState_11zqendz                                                                               (     267 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: getChannelState
//!
//! Description:
//! This method is used to get the state variable of the class. This will
//! allow for the state variable to be sent in messages to the OES.
//!
//! Parameters: None
//!
//! Return: VLF_Channel_State_Type
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_102)
 
VLF_Channel_State_Type
CChOperationalState :: getChannelState()
{
 int izzqqzz=((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 11))); /* 37 */
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 12))); /* 30 */
    CChannelState_11zqendz                                                                               (     269 ) ; /* 30 */  
  return
  chstate ;
}
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: LoadTime
//!
//! Description:
//! This method is used to transition the channel state to Degraded State,
//! based on conditional criteria. If Timeload Message is sent,
//! and current time check fails and channels are running, transition to
//! Degraded State.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_103)
 
void
  CChOperationalState :: LoadTime (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 13))); /* 37 */
    if
      (
      !
        check4Null (
        instance , __FILE__ , __LINE__ )
      )
 {
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 14))); /* 1 */
      {
      // Check commPlan for SM_Modes
        if
 (  /* 50 */
          (
          
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode9 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,           9 ),
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 16))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,           9 ),
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 15))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.modeHIDAR == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,           9 ),
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 20))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,           9 ),
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 19))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode23 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           3 ,1,           9 ),
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 24))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           3 ,0,           9 ),
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 23))),0) ) /* 54 */
          ||
          
  CChannelState_11zzdo17                                                                               (    4, /*  72 */ 
          ( instance -> mCommPlan.modeSMA == ( unsigned ) true
          )
  ? 1 : 0  ,       9  )  /*  73 */
  ? 1 : 0  ,       9  )  /*  82 */
          )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element8 |= ((unsigned int)1 << 31))); /* 1 */
          {
         // Check Time
            if
              (
              CTimeLoad :: Instance () -> mState != TimeLoaded
              )
 {
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 <<  0))); /* 1 */
              {
                instance ->
                            setState (
                & theChDegradedState ) ;
              }
  } else ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 <<  1))); /* 4 */
          //else nothing- time not loaded
          }
  } else ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 <<  2))); /* 4 */
       //else nothing- no SModes in comm plan
      }
  } else ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 <<  3))); /* 4 */
    //else nothing- error handled in if statement
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 <<  4))); /* 30 */
    CChannelState_11zqendz                                                                               (     293 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: ChangeCpChanOpStatus
//!
//! Description:
//! This method is used to transition the VLF state to Degraded State,
//! based on conditional criteria.
//! The flag value: mCpChanOpStatValid, can be set if the following
//! Crypto conditions occur
//! 1. TEK valid/invalid
//! 2. CP Chan Configure Pass/Fail
//! 3. CP Chan Runup Pass/Fail
//! 4. CP Chan Zeroize Pass/Fail
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_104)
 
void
  CChOperationalState :: ChangeCpChanOpStatus (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 <<  5))); /* 37 */
    if
      (
      !
        check4Null (
        instance , __FILE__ , __LINE__ )
      )
 {
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 <<  6))); /* 1 */
      {
      // Check commPlan for SM_Modes
        if
 (  /* 50 */
          (
          
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode9 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,          16 ),
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 <<  8))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,          16 ),
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 <<  7))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.modeHIDAR == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,          16 ),
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 12))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,          16 ),
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 11))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode23 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           3 ,1,          16 ),
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 16))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           3 ,0,          16 ),
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 15))),0) ) /* 54 */
          ||
          
  CChannelState_11zzdo17                                                                               (    4, /*  72 */ 
          ( instance -> mCommPlan.modeSMA == ( unsigned ) true
          )
  ? 1 : 0  ,      16  )  /*  73 */
  ? 1 : 0  ,      16  )  /*  82 */
          )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 23))); /* 1 */
          {
         // Check TEK
            if
              (
              instance -> mCpChanOpStatValid == false
              )
 {
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 24))); /* 1 */
              {
                instance ->
                            setState (
                & theChDegradedState ) ;
              }
  } else ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 25))); /* 4 */
          //else nothing- tek not loaded
          }
  } else ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 26))); /* 4 */
       //else nothing- SModes not in comm plan
      }
  } else ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 27))); /* 4 */
    //else nothing- error handled in if statement
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 28))); /* 30 */
    CChannelState_11zqendz                                                                               (     317 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoStatus
//!
//! Description:
//! This method is used to transition the VLF state to Degraded State,
//! based on conditional criteria.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_105)
 
void
  CChOperationalState :: CryptoStatus (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 29))); /* 37 */
    if
      (
      !
        check4Null (
        instance , __FILE__ , __LINE__ )
      )
 {
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 30))); /* 1 */
      {
      // Check commPlan for SM_Modes
        if
 (  /* 50 */
          (
          
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode9 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,          23 ),
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 <<  0))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,          23 ),
  ((unsigned int)(bitmapstruct.element9 |= ((unsigned int)1 << 31))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.modeHIDAR == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,          23 ),
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 <<  4))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,          23 ),
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 <<  3))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode23 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           3 ,1,          23 ),
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 <<  8))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           3 ,0,          23 ),
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 <<  7))),0) ) /* 54 */
          ||
          
  CChannelState_11zzdo17                                                                               (    4, /*  72 */ 
          ( instance -> mCommPlan.modeSMA == ( unsigned ) true
          )
  ? 1 : 0  ,      23  )  /*  73 */
  ? 1 : 0  ,      23  )  /*  82 */
          )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 << 15))); /* 1 */
          {
         // Check Crypto
            if
 (  /* 50 */
              (
              
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
              
  (     /*  51 */ 
              (
              CVlf :: Instance () -> mRcvrStatus.CMState.ECUState == ( unsigned ) ECU_ALARM
              )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,          30 ),
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 << 17))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,          30 ),
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 << 16))),0) ) /* 54 */
              ||
              
  (     /*  51 */ 
              (
              CVlf :: Instance (
              ) -> mRcvrStatus.CMState.ECUSubstate != ( unsigned ) NO_SUBSTATE
              )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,          30 ),
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 << 21))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,          30 ),
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 << 20))),0) ) /* 54 */
              ||
              
  CChannelState_11zzdo17                                                                               (    3, /*  72 */ 
              (
              CVlf :: Instance (
              ) -> mRcvrStatus.chanStatus [
              ( instance -> mCommPlan.channelID - 1 ) ].cryptoChanState == ( unsigned ) CH_ALARM
              )
  ? 1 : 0  ,      30  )  /*  73 */
  ? 1 : 0  ,      30  )  /*  82 */
              )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 << 28))); /* 1 */
              {
                instance ->
                            setState (
                & theChDegradedState ) ;
              }
  } else ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 << 29))); /* 4 */
          //else nothing- crypto states valid
          }
  } else ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 << 30))); /* 4 */
       //else nothing- SModes not in comm plan
      }
  } else ((unsigned int)(bitmapstruct.element10 |= ((unsigned int)1 << 31))); /* 4 */
    //else nothing- error handled in if statement
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 <<  0))); /* 30 */
    CChannelState_11zqendz                                                                               (     353 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoChannelUpdate
//!
//! Description:
//! This method is used to transition the VLF state to Degraded State,
//! based on conditional criteria.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_106)
 
void
  CChOperationalState :: CryptoChannelUpdate (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 <<  1))); /* 37 */
    if
      (
      !
        check4Null (
        instance , __FILE__ , __LINE__ )
      )
 {
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 <<  2))); /* 1 */
      {
      // Check commPlan for SM_Modes
        if
 (  /* 50 */
          (
          
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode9 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,          36 ),
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 <<  4))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,          36 ),
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 <<  3))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.modeHIDAR == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,          36 ),
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 <<  8))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,          36 ),
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 <<  7))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode23 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           3 ,1,          36 ),
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 12))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           3 ,0,          36 ),
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 11))),0) ) /* 54 */
          ||
          
  CChannelState_11zzdo17                                                                               (    4, /*  72 */ 
          ( instance -> mCommPlan.modeSMA == ( unsigned ) true
          )
  ? 1 : 0  ,      36  )  /*  73 */
  ? 1 : 0  ,      36  )  /*  82 */
          )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 19))); /* 1 */
          {
            if
              (
              CVlf :: Instance () -> mRcvrStatus.chanStatus [
              ( instance -> mCommPlan.channelID - 1 ) ].cryptoChanState == ( unsigned ) CH_ALARM
              )
 {
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 20))); /* 1 */
              {
                instance ->
                            setState (
                & theChDegradedState ) ;
              }
  } else ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 21))); /* 4 */
          //else nothing- channel not in alarm
          }
  } else ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 22))); /* 4 */
       //else nothing- SModes not in comm plan
      }
  } else ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 23))); /* 4 */
    //else nothing- error handled in if statement
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 24))); /* 30 */
    CChannelState_11zqendz                                                                               (     377 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoBIT
//!
//! Description:
//! This method is used to transition the VLF state to Degraded State,
//! based on conditional criteria.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_107)
 
void
  CChOperationalState :: CryptoBIT (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 25))); /* 37 */
    if
      (
      !
        check4Null (
        instance , __FILE__ , __LINE__ )
      )
 {
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 26))); /* 1 */
      {
      // Check commPlan for SM_Modes
        if
 (  /* 50 */
          (
          
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode9 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,          43 ),
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 28))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,          43 ),
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 27))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.modeHIDAR == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,          43 ),
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 <<  0))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,          43 ),
  ((unsigned int)(bitmapstruct.element11 |= ((unsigned int)1 << 31))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode23 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           3 ,1,          43 ),
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 <<  4))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           3 ,0,          43 ),
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 <<  3))),0) ) /* 54 */
          ||
          
  CChannelState_11zzdo17                                                                               (    4, /*  72 */ 
          ( instance -> mCommPlan.modeSMA == ( unsigned ) true
          )
  ? 1 : 0  ,      43  )  /*  73 */
  ? 1 : 0  ,      43  )  /*  82 */
          )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 11))); /* 1 */
          {
         // Check BIT status
            if
              (
              ! CVlf :: Instance () -> mCPLinkUp
              )
 {
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 12))); /* 1 */
              {
                instance ->
                            setState (
                & theChDegradedState ) ;
              }
  } else ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 13))); /* 4 */
         //else do nothing, still connected to the Crypto
          }
  } else ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 14))); /* 4 */
          //else
          //do nothing, the channel is not setup for special mode.
      }
  } else ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 15))); /* 4 */
    //else nothing- error handled in if statement
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 16))); /* 30 */
    CChannelState_11zqendz                                                                               (     401 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Class: CChDegradedState
//
//
// Description: This class contains the class methods for the CDegradedState
// class. This class contains a state transition of the
// VLF receiver
//
// Notes: None
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//! Function: CChDegradedState
//!
//! Description:
//! This is the class default constructor method
//!
//! Parameters:
//! None
//!
//! Return:
//! None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_108)
 
  CChDegradedState :: CChDegradedState() :
    ldra_class_1100027100(),  /* 71 c1*/
  IChannelState ( )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 17))); /* 37 */
   //set VLF channel Variable
    chstate = CH_DEGRADED ;
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 18))); /* 30 */
    CChannelState_11zqendz                                                                               (     403 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//! This destructor method is used to cleanup the CDegradedState object
//! once it is deleted.
//!
//! Parameters:
//! None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_109)
 
  CChDegradedState :: ~CChDegradedState()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 19))); /* 37 */
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 20))); /* 30 */
    CChannelState_11zqendz                                                                               (     405 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: getChannelState
//!
//! Description:
//! This method is used to get the state variable of the class. This will
//! allow for the state variable to be sent in messages to the OES.
//!
//! Parameters: None
//!
//! Return: VLF_Channel_State_Type - state variable for class
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_110)
 
VLF_Channel_State_Type
CChDegradedState :: getChannelState()
{
 int izzqqzz=((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 21))); /* 37 */
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 22))); /* 30 */
    CChannelState_11zqendz                                                                               (     407 ) ; /* 30 */  
  return
  chstate ;
}
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: CommonUpdate
//!
//! Description:
//! This method is used to consolidate the common function processing of
//! the CChDegradedState class.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! This helper method was created to eliminate the detection of duplicate
//! algorithms in the code as reported by the customer's analysis tool
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_111)
 
void
  CChDegradedState :: CommonUpdate (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 23))); /* 37 */
    if
      (
      !
        check4Null (
        instance , __FILE__ , __LINE__ )
      )
 {
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 24))); /* 1 */
      {
      // Check CommPlan, Time, TEK, and Crypto
        if
 (  /* 50 */
          (
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 25))) , /* 23e */
            CheckStatusEvents (
            instance )
          )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 26))); /* 1 */
          {
            instance ->
                        setState (
            & theChOperationalState ) ;
          }
  } else ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 27))); /* 4 */
       //else nothing- all values do not pass
      }
  } else ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 28))); /* 4 */
    //else nothing- error handled in if statement
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 29))); /* 30 */
    CChannelState_11zqendz                                                                               (     414 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: LoadTime
//!
//! Description:
//! This method is used to transition the VLF state to Operational State,
//! based on conditional criteria. If Timeload Message is sent,
//! and current time check passes, TEK loaded, and channels are running,
//! transition to Operational State.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_112)
 
void
  CChDegradedState :: LoadTime (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 30))); /* 37 */
   // Invoke the helper method to eliminate duplicate algorithm detected
   // by customer's analysis tool.
  ((unsigned int)(bitmapstruct.element12 |= ((unsigned int)1 << 31))); /* 23 */
 
    CommonUpdate (
    instance ) ;
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 <<  0))); /* 30 */
    CChannelState_11zqendz                                                                               (     417 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: ChangeCpChanOpStatus
//!
//! Description:
//! This method is used to transition the VLF state to Operational State,
//! based on conditional criteria.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_113)
 
void
  CChDegradedState :: ChangeCpChanOpStatus (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 <<  1))); /* 37 */
   // Invoke the helper method to eliminate duplicate algorithm detected
   // by customer's analysis tool.
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 <<  2))); /* 23 */
 
    CommonUpdate (
    instance ) ;
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 <<  3))); /* 30 */
    CChannelState_11zqendz                                                                               (     420 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoStatus
//!
//! Description:
//! This method is used to transition the channel state to Operational State
//! based on conditional criteria.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_114)
 
void
  CChDegradedState :: CryptoStatus (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 <<  4))); /* 37 */
   // Invoke the helper method to eliminate duplicate algorithm detected
   // by customer's analysis tool.
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 <<  5))); /* 23 */
 
    CommonUpdate (
    instance ) ;
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 <<  6))); /* 30 */
    CChannelState_11zqendz                                                                               (     423 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoChannelUpdate
//!
//! Description:
//! This method is used to transition the VLF state to Degraded State,
//! based on conditional criteria.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_115)
 
void
  CChDegradedState :: CryptoChannelUpdate (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 <<  7))); /* 37 */
   // Invoke the helper method to eliminate duplicate algorithm detected
   // by customer's analysis tool.
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 <<  8))); /* 23 */
 
    CommonUpdate (
    instance ) ;
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 <<  9))); /* 30 */
    CChannelState_11zqendz                                                                               (     426 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: CryptoBIT
//!
//! Description:
//! This method is used to transition the VLF state to Operational State,
//! based on conditional criteria.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_116)
 
void
  CChDegradedState :: CryptoBIT (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 10))); /* 37 */
   // Check BIT status
    if
 (  /* 50 */
      (
      
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
      
  (     /*  52 */ 
      (
      CVlf :: Instance () -> mCPLinkUp
      )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,          50 ),
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 11))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,          50 ),
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 12))),0) ) /* 54 */
      &&
      
 (   /*  55 */
      
  CChannelState_11zzdo17                                                                               (    2, /*  72 */ 
      (
 (   /*  55 */
 
      !
          check4Null (
          instance , __FILE__ , __LINE__ )
      
 )  /*  56 */
      )
  ? 1 : 0  ,      50  )  /*  73 */
      
 )  /*  56 */
  ? 1 : 0  ,      50  )  /*  82 */
      )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 19))); /* 1 */
      {
      // Check CommPlan, Time, TEK, and Crypto
        if
 (  /* 50 */
          (
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 20))) , /* 23e */
            CheckStatusEvents (
            instance )
          )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 21))); /* 1 */
          {
            instance ->
                        setState (
            & theChOperationalState ) ;
          }
  } else ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 22))); /* 4 */
       //else nothing- all values do not pass
      }
  } else ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 23))); /* 4 */
    //else nothing- link not up
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 24))); /* 30 */
    CChannelState_11zqendz                                                                               (     441 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: CheckStatusEvents
//!
//! Description:
//! This method is used to check the status TEK, Time, and Crypto
//! for the events.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: bool valid - true/false
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_117)
 
bool
  CChDegradedState :: CheckStatusEvents (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 25))); /* 37 */
    bool
      valid = false ;  // Flag for Degraded
    if
      (
      !
        check4Null (
        instance , __FILE__ , __LINE__ )
      )
 {
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 26))); /* 1 */
      {
      // Check commPlan for SM_Modes
        if
 (  /* 50 */
          (
          
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode9 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,          55 ),
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 28))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,          55 ),
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 27))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.modeHIDAR == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,          55 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 <<  0))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,          55 ),
  ((unsigned int)(bitmapstruct.element13 |= ((unsigned int)1 << 31))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode23 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           3 ,1,          55 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 <<  4))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           3 ,0,          55 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 <<  3))),0) ) /* 54 */
          ||
          
  CChannelState_11zzdo17                                                                               (    4, /*  72 */ 
          ( instance -> mCommPlan.modeSMA == ( unsigned ) true
          )
  ? 1 : 0  ,      55  )  /*  73 */
  ? 1 : 0  ,      55  )  /*  82 */
          )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 << 11))); /* 1 */
          {
         // Check Crypto Status, Time and TEK
            if
 (  /* 50 */
              (
              
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
              
  (     /*  52 */ 
              (
              CTimeLoad :: Instance () -> mState == TimeLoaded
              )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,          62 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 << 12))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,          62 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 << 13))),0) ) /* 54 */
              &&
              
  (     /*  52 */ 
              (
              CVlf :: Instance (
              ) -> mRcvrStatus.CMState.ECUState != ( unsigned ) ECU_ALARM
              )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,          62 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 << 16))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,          62 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 << 17))),0) ) /* 54 */
              &&
              
  (     /*  52 */ 
              (
              CVlf :: Instance (
              ) -> mRcvrStatus.CMState.ECUSubstate == ( unsigned ) NO_SUBSTATE
              )
 ? (CChannelState_11zzdo17                                                                              
 (           3 ,1,          62 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 << 20))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           3 ,0,          62 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 << 21))),0) ) /* 54 */
              &&
              
  (     /*  52 */ 
              (
              CVlf :: Instance (
              ) -> mRcvrStatus.chanStatus [
              ( instance -> mCommPlan.channelID - 1 ) ].cryptoChanState != ( unsigned ) CH_ALARM
              )
 ? (CChannelState_11zzdo17                                                                              
 (           4 ,1,          62 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 << 24))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           4 ,0,          62 ),
  ((unsigned int)(bitmapstruct.element14 |= ((unsigned int)1 << 25))),0) ) /* 54 */
              &&
              
  CChannelState_11zzdo17                                                                               (    5, /*  72 */ 
              ( instance -> mCpChanOpStatValid == true
              )
  ? 1 : 0  ,      62  )  /*  73 */
  ? 1 : 0  ,      62  )  /*  82 */
              )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 <<  0))); /* 1 */
              {
                valid = true ;
              }
  } else ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 <<  1))); /* 4 */
          //else nothing- values not correct
          }
      // Mode15 only
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 <<  2))); /* 3 */
 }
        else
  { 
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 <<  3))); /* 2 */
          {
            valid = true ;
          }
 }
      }
  } else ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 <<  4))); /* 4 */
    //else nothing- error handled in if statement
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 <<  5))); /* 30 */
    CChannelState_11zqendz                                                                               (     486 ) ; /* 30 */  
    return
    valid ;
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
// Class: CChOfflineState
//
//
// Description: This class contains the class methods for the COfflineState
// class. This class contains a state transition of the
// VLF channels
//
// Notes: None
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//! Function: CChOfflineState
//!
//! Description:
//! This is the class default constructor method
//!
//! Parameters:
//! None
//!
//! Return:
//! None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_118)
 
  CChOfflineState :: CChOfflineState() :
    ldra_class_1100037100(),  /* 71 c1*/
  IChannelState ( )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 <<  6))); /* 37 */
   //set VLF State Variable
    chstate = CH_OFFLINE ;
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 <<  7))); /* 30 */
    CChannelState_11zqendz                                                                               (     488 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: Destructor
//!
//! Description:
//! This destructor method is used to cleanup the COfflineState object
//! once it is deleted.
//!
//! Parameters:
//! None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_119)
 
  CChOfflineState :: ~CChOfflineState()
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 <<  8))); /* 37 */
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 <<  9))); /* 30 */
    CChannelState_11zqendz                                                                               (     490 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: getChannelState
//!
//! Description:
//! This method is used to get the state variable of the class. This will
//! allow for the state variable to be sent in messages to the OES.
//!
//! Parameters: None
//!
//! Return: VLF_Channel_State_Type
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_120)
 
VLF_Channel_State_Type
CChOfflineState :: getChannelState()
{
 int izzqqzz=((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 10))); /* 37 */
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 11))); /* 30 */
    CChannelState_11zqendz                                                                               (     492 ) ; /* 30 */  
  return
  chstate ;
}
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//! Function: StartChannel
//!
//! Description:
//! This method is used to transition the channel state to Operational State,
//! or Degraded State based on conditional criteria.
//! Check for valid Time, TEK, CommPlan, SModes, and CryptoStatus.
//! If all pass transition state to Operational else Degraded.
//! Channel Start Event can only happen when channel is offline.
//!
//! Parameters:
//! CChannel* instance- a pointer to the instance of the CChannel class
//!
//! Return: None
//!
//! Notes:
//! None
//!
////////////////////////////////////////////////////////////////////////////////
#if defined(LDRA_dummy_global) || defined(LDRA_dummy_11_121)
 
void
  CChOfflineState :: StartChannel (
  CChannel * instance )
  {
 int izzqqzz=((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 12))); /* 37 */
    if
      (
        check4Null (
        instance , __FILE__ , __LINE__ )
      )
 {
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 13))); /* 1 */
      {
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 14))); /* 30 */
    CChannelState_11zqendz                                                                               (     495 ) ; /* 30 */  
        return
        ;     //error handle in check4Null function
      }
  } else ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 15))); /* 4 */
      //else nothing- no error continue
      // check for valid commPlan
    if
      (
      instance -> mCommPlanValid == true
      )
 {
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 16))); /* 1 */
      {
      // Check commPlan for SM_Modes
        if
 (  /* 50 */
          (
          
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode9 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,          70 ),
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 18))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,          70 ),
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 17))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.modeHIDAR == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,          70 ),
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 22))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,          70 ),
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 21))),0) ) /* 54 */
          ||
          
  (     /*  51 */ 
          (
          instance -> mCommPlan.mode23 == ( unsigned ) true
          )
 ? (CChannelState_11zzdo17                                                                              
 (           3 ,1,          70 ),
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 26))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           3 ,0,          70 ),
  ((unsigned int)(bitmapstruct.element15 |= ((unsigned int)1 << 25))),0) ) /* 54 */
          ||
          
  CChannelState_11zzdo17                                                                               (    4, /*  72 */ 
          ( instance -> mCommPlan.modeSMA == ( unsigned ) true
          )
  ? 1 : 0  ,      70  )  /*  73 */
  ? 1 : 0  ,      70  )  /*  82 */
          )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 <<  1))); /* 1 */
          {
         // Check Crypto Status, Time and TEK
            if
 (  /* 50 */
              (
              
  CChannelState_11zzdo17                                                                               (    0,  /*  81 */ 
              
  (     /*  52 */ 
              (
              CTimeLoad :: Instance () -> mState == TimeLoaded
              )
 ? (CChannelState_11zzdo17                                                                              
 (           1 ,1,          77 ),
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 <<  2))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           1 ,0,          77 ),
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 <<  3))),0) ) /* 54 */
              &&
              
  (     /*  52 */ 
              (
              CVlf :: Instance (
              ) -> mRcvrStatus.CMState.ECUState != ( unsigned ) ECU_ALARM
              )
 ? (CChannelState_11zzdo17                                                                              
 (           2 ,1,          77 ),
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 <<  6))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           2 ,0,          77 ),
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 <<  7))),0) ) /* 54 */
              &&
              
  (     /*  52 */ 
              (
              CVlf :: Instance (
              ) -> mRcvrStatus.CMState.ECUSubstate == ( unsigned ) NO_SUBSTATE
              )
 ? (CChannelState_11zzdo17                                                                              
 (           3 ,1,          77 ),
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 10))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           3 ,0,          77 ),
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 11))),0) ) /* 54 */
              &&
              
  (     /*  52 */ 
              (
              CVlf :: Instance (
              ) -> mRcvrStatus.chanStatus [
              ( instance -> mCommPlan.channelID - 1 ) ].cryptoChanState != ( unsigned ) CH_ALARM
              )
 ? (CChannelState_11zzdo17                                                                              
 (           4 ,1,          77 ),
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 14))),1)           
 : (CChannelState_11zzdo17                                                                              
 (           4 ,0,          77 ),
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 15))),0) ) /* 54 */
              &&
              
  CChannelState_11zzdo17                                                                               (    5, /*  72 */ 
              ( instance -> mCpChanOpStatValid == true
              )
  ? 1 : 0  ,      77  )  /*  73 */
  ? 1 : 0  ,      77  )  /*  82 */
              )
  ) /* 1 */
 {
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 22))); /* 1 */
              {
                instance ->
                            setState (
                & theChOperationalState ) ;
              }
              //
              // Else we are invalid and change channel state to Degraded
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 23))); /* 3 */
 }
            else
  { 
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 24))); /* 2 */
              {
                instance ->
                            setState (
                & theChDegradedState ) ;
              }
 }
          }
      // else channel is only configured for mode15
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 25))); /* 3 */
 }
        else
  { 
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 26))); /* 2 */
          {
            instance ->
                        setState (
            & theChOperationalState ) ;
          }
 }
      }
  } else ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 27))); /* 4 */
    //else nothing- no comm plan loaded
  ((unsigned int)(bitmapstruct.element16 |= ((unsigned int)1 << 28))); /* 30 */
    CChannelState_11zqendz                                                                               (     541 ) ; /* 30 */  
  }
#endif /* endof dummy_ */
////////////////////////////////////////////////////////////////////////////////
//
// Security classification: UNCLASSIFIED//FOUO
//
////////////////////////////////////////////////////////////////////////////////
#define qqqbranches    541
#define QQQMAXMCDCSIZE     86
#define QQQMAXMCDCNEST     30
#define QQQBMAPMCDCFWDTH  8
#define QQQBMAPMCDCFORMAT  "%8d"
  static int aqqqmcdcstore[QQQMAXMCDCSIZE] =                     
    { 0,
      6,   4,   0,   0,   0,   0,   0,   0, 
      5,   4,   0,   0,   0,   0,   0, 
      5,   4,   0,   0,   0,   0,   0, 
      5,   4,   0,   0,   0,   0,   0, 
      4,   4,   0,   0,   0,   0, 
      5,   4,   0,   0,   0,   0,   0, 
      5,   4,   0,   0,   0,   0,   0, 
      3,   4,   0,   0,   0, 
      5,   4,   0,   0,   0,   0,   0, 
      6,   4,   0,   0,   0,   0,   0,   0, 
      5,   4,   0,   0,   0,   0,   0, 
      6,   4,   0,   0,   0,   0,   0,   0, 
      0 };
/********************** LDRA_PORT INSTRUMENTATION **********************/                                                                                                                                                                                           
                                                                                                                                                                                                                                                                    
/******************* END OF LDRA_PORT INSTRUMENTATION ******************/                                                                                                                                                                                           
#define ldra_sscanf                                                                                                                                                                                                                                                 
  /* put in undefs to protect our parameter names from macros */                                                                                                                                                                                                    
#undef f                                                                                                                                                                                                                                                            
#undef i                                                                                                                                                                                                                                                            
#undef j                                                                                                                                                                                                                                                            
#undef k                                                                                                                                                                                                                                                            
#undef s                                                                                                                                                                                                                                                            
#undef l                                                                                                                                                                                                                                                            
#undef ii                                                                                                                                                                                                                                                           
#undef some                                                                                                                                                                                                                                                         
#undef none                                                                                                                                                                                                                                                         
#undef from                                                                                                                                                                                                                                                         
#undef a                                                                                                                                                                                                                                                            
#undef b                                                                                                                                                                                                                                                            
#undef iz                                                                                                                                                                                                                                                           
#undef jz                                                                                                                                                                                                                                                           
#undef qqnull_params                                                                                                                                                                                                                                                
#define qqnull_params void                                                                                                                                                                                                                                          
  /* Conventional Instrumentation */                                                                                                                                                                                                                                
#define qqzzidfield 1                                                                                                                                                                                                                                               
  /* single file or fileid */                                                                                                                                                                                                                                       
  /* these have an extra field for the fileid */                                                                                                                                                                                                                    
  static char qqqqone[] = "%6d\n";           /* single point */                                                                                                                                                                                                     
  static int qqqmcdcnest = 0;                                                                                                                                                                                                                                       
  /* Bitmap MC/DC variables */                                                                                                                                                                                                                                      
  static int qqqmcdcval[QQQMAXMCDCNEST + 1];                                                                                                                                                                                                                        
  static int qqqmcdcoffset[QQQMAXMCDCNEST + 1];                                                                                                                                                                                                                     
  /* uncompressed data structures */                                                                                                                                                                                                                                
  /* uncompressed  bitmap */                                                                                                                                                                                                                                        
#define QQQFIXEDSIZE                                                                                                                                                                                                                                                
  static int qqqlast = 0;                                                                                                                                                                                                                                           
  static int qqqlastmcdc = 0;                                                                                                                                                                                                                                       
  static int qqqstoreused = -1;                                                                                                                                                                                                                                     
  static int paqqqmcdcstr;                                                                                                                                                                                                                                          
#define qqqbranches1   (qqqbranches+1)                                                                                                                                                                                                                              
  extern int qqupload_registered;                                                                                                                                                                                                                                   
                                                                                                                                                                                                                                                                    
  /* ----------- zscanf ---------------------------------------------------* 201 *                                                                                                                                                                                  
   *        Returns an integer extracted from a string                                                                                                                                                                                                              
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int CChannelState_11zscanf(char* qqscan_str)                                                                                                                                                                                                               
  {                                                                                                                                                                                                                                                                 
    int qqvalue;                                                                                                                                                                                                                                                    
    int qqisign;                                                                                                                                                                                                                                                    
    char* qqcptr;                                                                                                                                                                                                                                                   
    qqvalue = 0;                                                                                                                                                                                                                                                    
    qqisign = 1;                                                                                                                                                                                                                                                    
    qqcptr = qqscan_str;                                                                                                                                                                                                                                            
    /* Skip spaces */                                                                                                                                                                                                                                               
    while (qqcptr[0] == ' ')                                                                                                                                                                                                                                        
    {                                                                                                                                                                                                                                                               
      qqcptr++;                                                                                                                                                                                                                                                     
    }                                                                                                                                                                                                                                                               
    /* Check for a leading --- */                                                                                                                                                                                                                                   
    if (qqcptr[0] == '-')                                                                                                                                                                                                                                           
    {                                                                                                                                                                                                                                                               
      qqisign = -1;                                                                                                                                                                                                                                                 
      qqcptr++;                                                                                                                                                                                                                                                     
    }                                                                                                                                                                                                                                                               
    /* Extract digits */                                                                                                                                                                                                                                            
    while ((qqcptr[0] >= '0') && (qqcptr[0] <= '9'))                                                                                                                                                                                                                
    {                                                                                                                                                                                                                                                               
      qqvalue = 10 * qqvalue;                                                                                                                                                                                                                                       
      qqvalue = qqvalue + (qqcptr[0] - '0');                                                                                                                                                                                                                        
      qqcptr++;                                                                                                                                                                                                                                                     
    }                                                                                                                                                                                                                                                               
    qqvalue = qqisign * qqvalue;                                                                                                                                                                                                                                    
    return qqvalue;                                                                                                                                                                                                                                                 
  } /* end of zscanf */                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 202 *                                                                                                                                                                                  
   *            qqswitchgetxx                                                                                                                                                                                                                                       
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int qqswitchgetxx(qqnull_params)                                                                                                                                                                                                                           
  {                                                                                                                                                                                                                                                                 
    int ret = qqxxswitch;                                                                                                                                                                                                                                           
    return ret;                                                                                                                                                                                                                                                     
  } /* end of qqswitchgetxx */                                                                                                                                                                                                                                      
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 203 *                                                                                                                                                                                  
   *            qqswitchgetyy                                                                                                                                                                                                                                       
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int qqswitchgetyy(qqnull_params)                                                                                                                                                                                                                           
  {                                                                                                                                                                                                                                                                 
    int ret = qqyyswitch;                                                                                                                                                                                                                                           
    return ret;                                                                                                                                                                                                                                                     
  } /* end of qqswitchgetyy */                                                                                                                                                                                                                                      
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 204 *                                                                                                                                                                                  
   *            qqswitchxx                                                                                                                                                                                                                                          
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int qqswitchxx(qqnull_params)                                                                                                                                                                                                                              
  {                                                                                                                                                                                                                                                                 
    if ( qqxxswitch == 0 )                                                                                                                                                                                                                                          
    {                                                                                                                                                                                                                                                               
      qqxxswitch = 1;                                                                                                                                                                                                                                               
    } else {                                                                                                                                                                                                                                                        
      qqxxswitch = 0;                                                                                                                                                                                                                                               
    }                                                                                                                                                                                                                                                               
    return 1;                                                                                                                                                                                                                                                       
  } /* end of qqswitchxx */                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 205 *                                                                                                                                                                                  
   *            qqswitchyy                                                                                                                                                                                                                                          
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int qqswitchyy(qqnull_params)                                                                                                                                                                                                                              
  {                                                                                                                                                                                                                                                                 
    if ( qqyyswitch == 0 )                                                                                                                                                                                                                                          
    {                                                                                                                                                                                                                                                               
      qqyyswitch = 1;                                                                                                                                                                                                                                               
    } else {                                                                                                                                                                                                                                                        
      qqyyswitch = 0;                                                                                                                                                                                                                                               
    }                                                                                                                                                                                                                                                               
    return 1;                                                                                                                                                                                                                                                       
  } /* end of qqswitchyy */                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 206 *                                                                                                                                                                                  
   *            uuswitchqq                                                                                                                                                                                                                                          
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int uuswitchqq(qqnull_params)                                                                                                                                                                                                                              
  {                                                                                                                                                                                                                                                                 
    if ( qqyyswitch == 1 && qqxxswitch == 0 )                                                                                                                                                                                                                       
    {                                                                                                                                                                                                                                                               
      qqxxswitch = 1;                                                                                                                                                                                                                                               
    }                                                                                                                                                                                                                                                               
    else if ( qqyyswitch == 1 && qqxxswitch == 1 )                                                                                                                                                                                                                  
    {                                                                                                                                                                                                                                                               
      qqxxswitch = 0;                                                                                                                                                                                                                                               
    }                                                                                                                                                                                                                                                               
    return 1;                                                                                                                                                                                                                                                       
  } /* end of uuswitchqq */                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 214 *                                                                                                                                                                                  
   *            qqoutput                                                                                                                                                                                                                                            
   *    This is the principle output routine.                                                                                                                                                                                                                       
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static void qqoutput(FILEPOINT char* s, int i)                                                                                                                                                                                                                    
  {                                                                                                                                                                                                                                                                 
    ldra_sprintf2 (&ldra_buffer[0], s, i, zzfileid);                                                                                                                                                                                                                
    ldra_port_write (&ldra_buffer[0]);                                                                                                                                                                                                                              
  } /* end of qqoutput */                                                                                                                                                                                                                                           
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 215 *                                                                                                                                                                                  
   *            qqoutput0                                                                                                                                                                                                                                           
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static void qqoutput0(FILEPOINT char* s)                                                                                                                                                                                                                          
  {                                                                                                                                                                                                                                                                 
    ldra_port_write(s);                                                                                                                                                                                                                                             
  } /* end of qqoutput0 */                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 216 *                                                                                                                                                                                  
   *            qqoutput2                                                                                                                                                                                                                                           
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static void qqoutput2(FILEPOINT char* s, int i, int j)                                                                                                                                                                                                            
  {                                                                                                                                                                                                                                                                 
    ldra_sprintf2 (&ldra_buffer[0], s, i, j);                                                                                                                                                                                                                       
    ldra_port_write (&ldra_buffer[0]);                                                                                                                                                                                                                              
  } /* end of qqoutput2 */                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 217 *                                                                                                                                                                                  
   *            qqoutput3                                                                                                                                                                                                                                           
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static void qqoutput3(FILEPOINT char* s, int i, int j, int k)                                                                                                                                                                                                     
  {                                                                                                                                                                                                                                                                 
    ldra_sprintf3 (&ldra_buffer[0], s, i, j, k);                                                                                                                                                                                                                    
    ldra_port_write (&ldra_buffer[0]);                                                                                                                                                                                                                              
  } /* end of qqoutput3 */                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 218 *                                                                                                                                                                                  
   *            qqoutput4                                                                                                                                                                                                                                           
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static void qqoutput4(FILEPOINT char* s, int i, int j, int k, int l)                                                                                                                                                                                              
  {                                                                                                                                                                                                                                                                 
    ldra_sprintf4 (&ldra_buffer[0], s, i, j, k, l);                                                                                                                                                                                                                 
    ldra_port_write (&ldra_buffer[0]);                                                                                                                                                                                                                              
  } /* end of qqoutput4 */                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 222 *                                                                                                                                                                                  
   *            qqqqinitialise                                                                                                                                                                                                                                      
   * This procedure initialises the structures for                                                                                                                                                                                                                  
   * compressed execution histories.                                                                                                                                                                                                                                
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static void qqqqinitialise(int ii)                                                                                                                                                                                                                                
  {                                                                                                                                                                                                                                                                 
    qqqstoreused = -1;                                                                                                                                                                                                                                              
    /* bitmap separate */                                                                                                                                                                                                                                           
    qqqlast = 1; /* stops qqfun() calling initialise again */                                                                                                                                                                                                       
    /* bitmap */                                                                                                                                                                                                                                                    
    /* bitmap singlefile */                                                                                                                                                                                                                                         
    /* struct singlefile notmainfl */                                                                                                                                                                                                                               
  } /* end of qqqqinitialise */                                                                                                                                                                                                                                     
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 225 *                                                                                                                                                                                  
   *            qqqbitmapreset                                                                                                                                                                                                                                      
   * This procedure resets the structures for compressed execution histories.                                                                                                                                                                                       
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static void qqqbitmapreset()                                                                                                                                                                                                                                      
  {                                                                                                                                                                                                                                                                 
    int iz = 0;                                                                                                                                                                                                                                                     
    struct bitmapstruct_t localbitmap = {0};                                                                                                                                                                                                                        
    bitmapstruct = localbitmap;                                                                                                                                                                                                                                     
    for (iz=3; iz<QQQMAXMCDCSIZE; iz++)                                                                                                                                                                                                                             
    {                                                                                                                                                                                                                                                               
      aqqqmcdcstore[iz] = 0;                                                                                                                                                                                                                                        
    }                                                                                                                                                                                                                                                               
  } /* end of qqqbitmapreset */                                                                                                                                                                                                                                     
                                                                                                                                                                                                                                                                    
/* ----------------------------------------------------------------------* 247 *                                                                                                                                                                                    
*            qqqzzuploadmcdc                                                                                                                                                                                                                                        
* This routine uploads the MC/DC sequences from compressed execution                                                                                                                                                                                                
* or bitmap histories which use separate storage.                                                                                                                                                                                                                   
* -----------------------------------------------------------------------------                                                                                                                                                                                     
*/                                                                                                                                                                                                                                                                  
  static void qqqzzuploadmcdc(int pfileid)                                                                                                                                                                                                                          
  {                                                                                                                                                                                                                                                                 
    int iz, jz, kz;                                                                                                                                                                                                                                                 
    /* Output the header for bitmap MC/DC */                                                                                                                                                                                                                        
    qqoutput4("%8d%8d%8d%8d\n", (-2), (pfileid), (-2), (-2));                                                                                                                                                                                                       
    /* Output the error indicator and file id */                                                                                                                                                                                                                    
    iz = 0;                                                                                                                                                                                                                                                         
    qqoutput3("%8d%8d%8d\n", aqqqmcdcstore[iz], pfileid, QQQBMAPMCDCFWDTH);                                                                                                                                                                                         
    /* Loop over all cases to be output */                                                                                                                                                                                                                          
    iz++;                                                                                                                                                                                                                                                           
    while (iz < QQQMAXMCDCSIZE - 1)                                                                                                                                                                                                                                 
    {                                                                                                                                                                                                                                                               
      /* Output the number of cases */                                                                                                                                                                                                                              
      jz = aqqqmcdcstore[iz];                                                                                                                                                                                                                                       
      qqoutput(QQQBMAPMCDCFORMAT, jz);                                                                                                                                                                                                                              
      qqoutput("%8d", pfileid);                                                                                                                                                                                                                                     
      qqoutput0("\n");                                                                                                                                                                                                                                              
      iz = iz + 2;                                                                                                                                                                                                                                                  
      kz = 0;                                                                                                                                                                                                                                                       
      while (jz > 0)                                                                                                                                                                                                                                                
      {                                                                                                                                                                                                                                                             
        qqoutput(QQQBMAPMCDCFORMAT, aqqqmcdcstore[iz]);                                                                                                                                                                                                             
        if (kz == 0)                                                                                                                                                                                                                                                
        {                                                                                                                                                                                                                                                           
          qqoutput("%8d", pfileid);                                                                                                                                                                                                                                 
        }                                                                                                                                                                                                                                                           
        iz++;                                                                                                                                                                                                                                                       
        jz--;                                                                                                                                                                                                                                                       
        kz++;                                                                                                                                                                                                                                                       
        /* Check for end of record */                                                                                                                                                                                                                               
        if (kz == 10)                                                                                                                                                                                                                                               
        {                                                                                                                                                                                                                                                           
          qqoutput0("\n");                                                                                                                                                                                                                                          
          kz = 0;                                                                                                                                                                                                                                                   
        }                                                                                                                                                                                                                                                           
      }                                                                                                                                                                                                                                                             
      /* Check for an incomplete record */                                                                                                                                                                                                                          
      if (kz > 0)                                                                                                                                                                                                                                                   
      {                                                                                                                                                                                                                                                             
        qqoutput0("\n");                                                                                                                                                                                                                                            
      }                                                                                                                                                                                                                                                             
    }                                                                                                                                                                                                                                                               
    /* Output a trailer */                                                                                                                                                                                                                                          
    for (iz = 0; iz < 3; iz++)                                                                                                                                                                                                                                      
    {                                                                                                                                                                                                                                                               
      if (iz == 1)                                                                                                                                                                                                                                                  
      {                                                                                                                                                                                                                                                             
        qqoutput("%8d", pfileid);                                                                                                                                                                                                                                   
      }                                                                                                                                                                                                                                                             
      qqoutput(QQQBMAPMCDCFORMAT, 0);                                                                                                                                                                                                                               
    }                                                                                                                                                                                                                                                               
    qqoutput0("\n");                                                                                                                                                                                                                                                
  } /* end of uploadmcdc */                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                                                    
#undef QQQTEMP1                                                                                                                                                                                                                                                     
#define QQQTEMP1                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 312 *                                                                                                                                                                                  
   * This routine opens the execution history file. It is instrumented at the                                                                                                                                                                                       
   * start of the main program if one exists in the file. In general this is                                                                                                                                                                                        
   * superceded by CChannelState_11zqqzqz1 below.                                                                                                                                                                                                                   
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int CChannelState_11zqqzqz(qqnull_params)                                                                                                                                                                                                                  
  {                                                                                                                                                                                                                                                                 
    if ( CChannelState_11zzopen != 1 )                                                                                                                                                                                                                              
    {                                                                                                                                                                                                                                                               
      CChannelState_11zzopen = 1;                                                                                                                                                                                                                                   
    }                                                                                                                                                                                                                                                               
    return 1;                                                                                                                                                                                                                                                       
  } /* end of zqqzqz */                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 317 *                                                                                                                                                                                  
   * This routine also opens the execution history file.  It is called                                                                                                                                                                                              
   * automatically if a probe fires and the execution history is not already                                                                                                                                                                                        
   * opened (CChannelState_11zzopen = 0 ).                                                                                                                                                                                                                          
   * Because this always works ( it was intended for files with no main program                                                                                                                                                                                     
   * it is now the de facto common way to open the execution history.                                                                                                                                                                                               
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int CChannelState_11zqqzqz1(qqnull_params)                                                                                                                                                                                                                 
  {                                                                                                                                                                                                                                                                 
    if ( CChannelState_11zzopen != 1 )                                                                                                                                                                                                                              
    {                                                                                                                                                                                                                                                               
      ldra_port_open();  /* 7 */                                                                                                                                                                                                                                    
      qqqqinitialise(0);                                                                                                                                                                                                                                            
      CChannelState_11zzopen = 1;                                                                                                                                                                                                                                   
    }                                                                                                                                                                                                                                                               
    return 1;                                                                                                                                                                                                                                                       
  } /* end of zqqzqz1 */                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                    
  /* ----------- zqendz ---------------------------------------------------* 330 *                                                                                                                                                                                  
   * This routine is called on exiting a routine in a module.                                                                                                                                                                                                       
   * It closes the execution history.                                                                                                                                                                                                                               
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int CChannelState_11zqendz(int qqqi)                                                                                                                                                                                                                       
  {                                                                                                                                                                                                                                                                 
    /* For struct bitmap in one file, ensure upload and reset functions are registered */                                                                                                                                                                           
    if (!qqqstructzzopen)                                                                                                                                                                                                                                           
    {                                                                                                                                                                                                                                                               
      qqpopulate_array_fcn_ptrQQ (QQQfcn_ptr_num, qqqupload, qqqbitmapreset);                                                                                                                                                                                       
      qqqstructzzopen = 1;                                                                                                                                                                                                                                          
    }                                                                                                                                                                                                                                                               
                                                                                                                                                                                                                                                                    
    if ( qqswitchgetxx() == 0 )                                                                                                                                                                                                                                     
    {                                                                                                                                                                                                                                                               
      if ( CChannelState_11zzopen != 1 )                                                                                                                                                                                                                            
      {                                                                                                                                                                                                                                                             
        CChannelState_11zqqzqz1();                                                                                                                                                                                                                                  
      }                                                                                                                                                                                                                                                             
      /* ----------------------------------------------------------------------* 331 *                                                                                                                                                                              
       * this is the one which puts an integer into                                                                                                                                                                                                                 
       * the execution history file and returns unity.                                                                                                                                                                                                              
       * The format of each field consists of six columns,                                                                                                                                                                                                          
       * the number is right justified in this field.                                                                                                                                                                                                               
       * -----------------------------------------------------------------------------                                                                                                                                                                              
       */                                                                                                                                                                                                                                                           
      if ( CChannelState_11zzopen )                                                                                                                                                                                                                                 
      {                                                                                                                                                                                                                                                             
        /* uncompressed */                                                                                                                                                                                                                                          
        /* uncompressed unbuffered */                                                                                                                                                                                                                               
        /* uncompressed unbuffered bitmap  */                                                                                                                                                                                                                       
        if ( qqqi > 0 )                                                                                                                                                                                                                                             
        {                                                                                                                                                                                                                                                           
        } else {                                                                                                                                                                                                                                                    
        }                                                                                                                                                                                                                                                           
      }                                                                                                                                                                                                                                                             
    }                                                                                                                                                                                                                                                               
    qqqlast = 0;                                                                                                                                                                                                                                                    
    return 1;                                                                                                                                                                                                                                                       
  } /* end of zqendz */                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 335 *                                                                                                                                                                                  
   *            Output structure - qqbmsoutput                                                                                                                                                                                                                      
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int qqqbranches_printed = 0;                                                                                                                                                                                                                               
  static void qqbmsoutput(FILEPOINT char* s, unsigned int i)                                                                                                                                                                                                        
  {                                                                                                                                                                                                                                                                 
    int b, last = 0;                                                                                                                                                                                                                                                
    for (b=0; b<qqqqbmselwidth/8; b++)                                                                                                                                                                                                                              
    {                                                                                                                                                                                                                                                               
      ldra_sprintf1 (&ldra_buffer[0], s, (i >> last) & ~(~0 << 8));                                                                                                                                                                                                 
      ldra_port_write (&ldra_buffer[0]);                                                                                                                                                                                                                            
      ldra_sprintf1 (&ldra_buffer[0], "%8d\n", zzfileid);                                                                                                                                                                                                           
      ldra_port_write (&ldra_buffer[0]);                                                                                                                                                                                                                            
      last += 8;                                                                                                                                                                                                                                                    
      qqqbranches_printed += 8;                                                                                                                                                                                                                                     
      if (qqqbranches_printed >= qqqbranches)                                                                                                                                                                                                                       
      {                                                                                                                                                                                                                                                             
        /* do not print any more, can be left over when using more than 8 bits to store bitmap */                                                                                                                                                                   
        break;                                                                                                                                                                                                                                                      
      }                                                                                                                                                                                                                                                             
    }                                                                                                                                                                                                                                                               
  } /* end of qqbmsoutput */                                                                                                                                                                                                                                        
                                                                                                                                                                                                                                                                    
 /* ----------------------------------------------------------------------* 336 *                                                                                                                                                                                   
  *            qqqupload                                                                                                                                                                                                                                            
  * This routine loops through the stored bitmap and outputs it.                                                                                                                                                                                                    
  * It then uploads the stored mcdc.                                                                                                                                                                                                                                
  * -----------------------------------------------------------------------------                                                                                                                                                                                   
  */                                                                                                                                                                                                                                                                
  static void qqqupload(qqnull_params)                                                                                                                                                                                                                              
  {                                                                                                                                                                                                                                                                 
    int i;                                                                                                                                                                                                                                                          
    /* uncompressed  bitmap (!singlefile or mainfl) separate */                                                                                                                                                                                                     
    {                                                                                                                                                                                                                                                               
      CChannelState_11zqqzqz1();                                                                                                                                                                                                                                    
#define ELEMENT(N) qqbmsoutput("%8d", bitmapstruct.element##N);                                                                                                                                                                                                     
#define LASTELEMENT                                                                                                                                                                                                                                                 
#include "CChannelState_11zbelem.def"                                                                                                                                                                                                                               
      qqqbranches_printed = 0;                                                                                                                                                                                                                                      
#undef LASTELEMENT                                                                                                                                                                                                                                                  
#undef ELEMENT                                                                                                                                                                                                                                                      
    }                                                                                                                                                                                                                                                               
    qqqzzuploadmcdc(zzfileid);                                                                                                                                                                                                                                      
    /* bitmap separate */                                                                                                                                                                                                                                           
    qqqlast = 1; /* stops qqfun() calling initialise again */                                                                                                                                                                                                       
    qqqstoreused = -1;                                                                                                                                                                                                                                              
  } /* end of qqqupload */                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 344 *                                                                                                                                                                                  
   * This routine should be called before the program terminates.                                                                                                                                                                                                   
   * It closes the execution history                                                                                                                                                                                                                                
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int CChannelState_11zqzqzq(int qqqi)                                                                                                                                                                                                                       
  {                                                                                                                                                                                                                                                                 
    if ( qqswitchgetxx() == 0 )                                                                                                                                                                                                                                     
      {                                                                                                                                                                                                                                                             
      if ( CChannelState_11zzopen != 1 )                                                                                                                                                                                                                            
      {                                                                                                                                                                                                                                                             
        CChannelState_11zqqzqz1();                                                                                                                                                                                                                                  
      }                                                                                                                                                                                                                                                             
      /* not compressed */                                                                                                                                                                                                                                          
      /* do nothing for bitmap*/                                                                                                                                                                                                                                    
      /* upload the history */                                                                                                                                                                                                                                      
      /* bitmap */                                                                                                                                                                                                                                                  
      /* uncompressed  bitmap */                                                                                                                                                                                                                                    
      CChannelState_11zqendz(qqqi);                                                                                                                                                                                                                                 
      /* qqqupload closes the execution history file */                                                                                                                                                                                                             
      }                                                                                                                                                                                                                                                             
    return 1;                                                                                                                                                                                                                                                       
  } /* end of zqzqzq */                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                    
  /* ----------------------------------------------------------------------* 357 *                                                                                                                                                                                  
   *            CChannelState_11zzdo17                                                                                                                                                                                                                              
   * -----------------------------------------------------------------------------                                                                                                                                                                                  
   */                                                                                                                                                                                                                                                               
  static int CChannelState_11zzdo17(int qqzdummy, int a, int b)                                                                                                                                                                                                     
  {                                                                                                                                                                                                                                                                 
    int qqqmcdcok;                                                                                                                                                                                                                                                  
    int qqqmcdcnptr;                                                                                                                                                                                                                                                
    int iz, jz;                                                                                                                                                                                                                                                     
    /* Check for defined instrumentation */                                                                                                                                                                                                                         
    if (b > 0)                                                                                                                                                                                                                                                      
    {                                                                                                                                                                                                                                                               
      /* check within bounds */                                                                                                                                                                                                                                     
      if (b < QQQMAXMCDCSIZE)                                                                                                                                                                                                                                       
      {                                                                                                                                                                                                                                                             
        /* Set the default nest pointer */                                                                                                                                                                                                                          
        qqqmcdcnptr = qqqmcdcnest;                                                                                                                                                                                                                                  
        /* Check for a mismatch with the highest nest level */                                                                                                                                                                                                      
        if ((qqqmcdcnptr > 0) && (b != qqqmcdcoffset[qqqmcdcnptr]))                                                                                                                                                                                                 
        {                                                                                                                                                                                                                                                           
          /* Search for which entry matches */                                                                                                                                                                                                                      
          iz = qqqmcdcnptr;                                                                                                                                                                                                                                         
          while (iz > 0)                                                                                                                                                                                                                                            
          {                                                                                                                                                                                                                                                         
            iz--;                                                                                                                                                                                                                                                   
            /* Test for a match */                                                                                                                                                                                                                                  
            if ( b == qqqmcdcoffset[iz])                                                                                                                                                                                                                            
            {                                                                                                                                                                                                                                                       
              qqqmcdcnptr = iz;                                                                                                                                                                                                                                     
              iz = 0;                                                                                                                                                                                                                                               
            }                                                                                                                                                                                                                                                       
          }                                                                                                                                                                                                                                                         
        }                                                                                                                                                                                                                                                           
        /* Check for the start of a new condition */                                                                                                                                                                                                                
        if ((qqqmcdcnptr == 0) || (b != qqqmcdcoffset[qqqmcdcnptr]))                                                                                                                                                                                                
        {                                                                                                                                                                                                                                                           
          /* Set the nest level */                                                                                                                                                                                                                                  
          qqqmcdcnest++;                                                                                                                                                                                                                                            
          qqqmcdcnptr = qqqmcdcnest;                                                                                                                                                                                                                                
          /* Set whether still in range */                                                                                                                                                                                                                          
          qqqmcdcok = (qqqmcdcnptr <= QQQMAXMCDCNEST);                                                                                                                                                                                                              
          if (qqqmcdcok)                                                                                                                                                                                                                                            
          {                                                                                                                                                                                                                                                         
            /* Initialise the value to return */                                                                                                                                                                                                                    
            qqqmcdcval[qqqmcdcnptr] = 1;                                                                                                                                                                                                                            
            /* Record the offset for this entry */                                                                                                                                                                                                                  
            qqqmcdcoffset[qqqmcdcnptr] = b;                                                                                                                                                                                                                         
          } else {                                                                                                                                                                                                                                                  
            /* Check for a clear error location */                                                                                                                                                                                                                  
            if (aqqqmcdcstore[0] == 0)                                                                                                                                                                                                                              
            {                                                                                                                                                                                                                                                       
              /* Note nest depth violated */                                                                                                                                                                                                                        
              aqqqmcdcstore[0] = 1;                                                                                                                                                                                                                                 
            }                                                                                                                                                                                                                                                       
          }                                                                                                                                                                                                                                                         
        }                                                                                                                                                                                                                                                           
        /* Shift all bits to the left */                                                                                                                                                                                                                            
        qqqmcdcval[qqqmcdcnptr] = qqqmcdcval[qqqmcdcnptr] << 1;                                                                                                                                                                                                     
        /* Add the current value */                                                                                                                                                                                                                                 
        qqqmcdcval[qqqmcdcnptr] = qqqmcdcval[qqqmcdcnptr] | (a & 1);                                                                                                                                                                                                
        /* Check for the last entry */                                                                                                                                                                                                                              
        if (qqzdummy == 0)                                                                                                                                                                                                                                          
        {                                                                                                                                                                                                                                                           
          /* Set the number of cases permitted */                                                                                                                                                                                                                   
          iz = aqqqmcdcstore[b];                                                                                                                                                                                                                                    
          /* Set the start location for scanning */                                                                                                                                                                                                                 
          jz = b + 2;                                                                                                                                                                                                                                               
          /* Set the end location of the scan */                                                                                                                                                                                                                    
          iz = iz + jz;                                                                                                                                                                                                                                             
          /* Loop looking for a match or free entry */                                                                                                                                                                                                              
          while ((jz < iz) && !((aqqqmcdcstore[jz] == qqqmcdcval[qqqmcdcnptr]) || (aqqqmcdcstore[jz] == 0)))                                                                                                                                                        
          {                                                                                                                                                                                                                                                         
            jz++;                                                                                                                                                                                                                                                   
          }                                                                                                                                                                                                                                                         
          /* Check for over-run */                                                                                                                                                                                                                                  
          if (jz == iz)                                                                                                                                                                                                                                             
          {                                                                                                                                                                                                                                                         
            /* Check availability of the error location */                                                                                                                                                                                                          
            if (aqqqmcdcstore[0] == 0)                                                                                                                                                                                                                              
            {                                                                                                                                                                                                                                                       
              /* Note an over-run */                                                                                                                                                                                                                                
              aqqqmcdcstore[0] = 3;                                                                                                                                                                                                                                 
            }                                                                                                                                                                                                                                                       
          } else {                                                                                                                                                                                                                                                  
            /* Check for a free slot */                                                                                                                                                                                                                             
            if (aqqqmcdcstore[jz] == 0)                                                                                                                                                                                                                             
            {                                                                                                                                                                                                                                                       
              /* Record this value */                                                                                                                                                                                                                               
              aqqqmcdcstore[jz] = qqqmcdcval[qqqmcdcnptr];                                                                                                                                                                                                          
            }                                                                                                                                                                                                                                                       
          }                                                                                                                                                                                                                                                         
          /* Check if working at the highest nest level */                                                                                                                                                                                                          
          if (qqqmcdcnptr == qqqmcdcnest)                                                                                                                                                                                                                           
          {                                                                                                                                                                                                                                                         
            /* Reset the nest level */                                                                                                                                                                                                                              
            qqqmcdcnest--;                                                                                                                                                                                                                                          
            qqqmcdcnptr = qqqmcdcnest;                                                                                                                                                                                                                              
            /* Reset any other completed entries */                                                                                                                                                                                                                 
            while (qqqmcdcnptr > 0)                                                                                                                                                                                                                                 
            {                                                                                                                                                                                                                                                       
               /* Check for a completed entry */                                                                                                                                                                                                                    
               if (qqqmcdcoffset[qqqmcdcnptr] == 0)                                                                                                                                                                                                                 
               {                                                                                                                                                                                                                                                    
                 qqqmcdcnest--;                                                                                                                                                                                                                                     
                 qqqmcdcnptr = qqqmcdcnest;                                                                                                                                                                                                                         
               } else {                                                                                                                                                                                                                                             
                 qqqmcdcnptr = 0;                                                                                                                                                                                                                                   
               }                                                                                                                                                                                                                                                    
            }                                                                                                                                                                                                                                                       
          } else {                                                                                                                                                                                                                                                  
            /* Mark the entry as completed */                                                                                                                                                                                                                       
            qqqmcdcoffset[qqqmcdcnptr] = 0;                                                                                                                                                                                                                         
          }                                                                                                                                                                                                                                                         
        }                                                                                                                                                                                                                                                           
      } else {                                                                                                                                                                                                                                                      
        /* Check for a clear error location */                                                                                                                                                                                                                      
        if (aqqqmcdcstore[0] == 0)                                                                                                                                                                                                                                  
        {                                                                                                                                                                                                                                                           
          /* Note offset out of bounds */                                                                                                                                                                                                                           
          aqqqmcdcstore[0] = 2;                                                                                                                                                                                                                                     
        }                                                                                                                                                                                                                                                           
      }                                                                                                                                                                                                                                                             
    }                                                                                                                                                                                                                                                               
    return a;                                                                                                                                                                                                                                                       
  } /* end of zzdo17 */                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                    
/*                                                                                                                                                                                                                                                                  
 * This include is in a separate file, otherwise                                                                                                                                                                                                                    
 * the instrumenter strips the #if #endif statements                                                                                                                                                                                                                
 */                                                                                                                                                                                                                                                                 
#include "C:\LDRA_Toolsuite\Compiler_spec\Greenhills\Integrity_ppc\ldra_port_shared_memory.c"                                                                                                                                                                       
/* END OF TESTBED INSTRUMENTATION */                                                                                                                                                                                                                                
 
