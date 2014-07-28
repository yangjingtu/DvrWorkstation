/**
                                                                                
2002 ZORAN Corporation, All Rights Reserved THIS IS PROPRIETARY SOURCE CODE OF  
ZORAN CORPORATION                                                               
                                                                                
%file                                                                           
                                                                                
  Burn.h                                                                     
                                                                                
%desc                                                                                                                                                           

  This file contains all application related definition, functions and data.
                                                                                
%author                                                                         
                                                                                
  Eyal Cohen
                                                                                
%created                                                                        
                                                                                
  Apr 25, 2002                                                                  
                                                                                
*/

#ifndef __BURN_H
#define __BURN_H

// Determine if a C++ compiler is being used.  If so, ensure that standard
// C is used to process the API information.
#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
// Zburn definitions
////////////////////////////////////////////////////////////////////////////////

// Options for download program source.
#define DOWNLOAD_FROM_UART              0x0
#define DOWNLOAD_FROM_SD_4BIT           0x8
#define DOWNLOAD_FROM_CF                0x9
#define DOWNLOAD_FROM_SSFDC             0xA
#define DOWNLOAD_FROM_USB               0xB
#define DOWNLOAD_FROM_ILLEGAL           0xFF

// Donwload source in CFG register.
#define DOWNLOAD_SOURCE_CFG_MASK        0x3C0
#define DOWNLOAD_SOURCE_CFG_BITS_SHIFT  6

// Resident flash types.
#define BURN_RESIDENT_TYPE_NOR_INTEL    0x0
#define BURN_RESIDENT_TYPE_NOR_AMD      0x1
#define BURN_RESIDENT_TYPE_NAND         0x2

// Options for signals for burn ending.
#define BURN_END_SIGNAL_NONE            0
#define BURN_END_SIGNAL_LED             1
             
#define BURN_STATUS_STAND_BY            0
#define BURN_STATUS_SUCCESS             1
#define BURN_STATUS_FAIL                2

////////////////////////////////////////////////////////////////////////////////
// Zburn data structures
////////////////////////////////////////////////////////////////////////////////

typedef struct tagSBURNPROP
{
    // The total size of the program to be burned.
    ULONG ulTotalSize;

    // A size of a transfer chunk of the program
    ULONG ulChunkSize;

    // Specifies the type of the resident flash for program burning.
    // The allowed values are:
    // BURN_RESIDENT_TYPE_NOR_INTEL 
    // BURN_RESIDENT_TYPE_NOR_AMD   
    // BURN_RESIDENT_TYPE_NAND         
    ULONG ulResidentType;

    // Specifies the burn end signal.
    // The allowed values are: BURN_END_SIGNAL_NONE
    //                         BURN_END_SIGNAL_LED
    ULONG ulEndSignal;

    // If the burning end should be signaled by turning on/off a led, the
    // corresponding gpio parameters are suppied: gpio group and a pin
    // number within that group.
    ULONG ulGpioGroup;
    ULONG ulGpioPin;
    
    // if 0 - the led will be turned on during the program burning and it
    //        will be turned off, once the burning has successfully ended.
    // if 1 - the led will be turned off during the program burning and it will
    //        be turned on, once the burning has successfully ended.
    // in both cases of program burning has failed the led will blink. 
    ULONG ulVal;

    ULONG ulReserved[9];

} SBURNPROP, *PSBURNPROP;  

///////////////////////////////////////////////////////////////////////////////
// Zburn functions
////////////////////////////////////////////////////////////////////////////////

BOOL
Burn(UINT  uiResidentType,
     ULONG ulTotalSize,
     ULONG ulChunkSize,
     BOOL  (*pfRead)(ULONG ulSize, PBYTE pbyBuffer),
     BOOL  (*pfWrite)(ULONG ulSize, PBYTE pbyBuffer));

VOID
BurnMainUart(ULONG ulParam);

VOID
BurnMainUsb(ULONG ulParam);

VOID
BurnMainCard(ULONG ulParam);

VOID
BurnBoot(ULONG ulParam);

///////////////////////////////////////////////////////////////////////////////
// Application management data declarations follow.
//
// Determine if the initialization function of this component is including
// this file.  If so, make the data definitions really happen. Otherwise,
// make them extern so other functions in the component can access them.
///////////////////////////////////////////////////////////////////////////////

#ifdef  BURN_INIT
#define BURN_DECLARE 
#else
#define BURN_DECLARE extern
#endif
/*
BURN_DECLARE TX_THREAD txBurnBoot;

// Application main thread. The thread is responsible for loading the new
// flash file and burn it into resident.
BURN_DECLARE TX_THREAD txBurnMain;

BURN_DECLARE UINT uiBurnStatus;

// Determine if a C++ compiler is being used.  If so, ensure that standard
// C is used to process the API information. 
*/
#ifdef __cplusplus
}
#endif

#endif
