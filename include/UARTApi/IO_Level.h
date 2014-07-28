/* ****************************************************************** */
/*                              IO_Level.h                            */
/* ****************************************************************** */
/* Copyright (c) 1997 ZORAN Corporation, All Rights Reserved          */
/* THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION               */
/*                                                                    */
/* $Workfile: IO_Level.h $                                            */
/* $Modtime: 4/25/99 4:53p $                                          */
/* $Revision: 7 $                                                    */
/* $Date: 4/26/99 11:53a $                                             */
/* ****************************************************************** */


#ifndef _IO_LEVEL_H_
#define _IO_LEVEL_H_

#include "uart.h"


/* ****************************************************************** */
/*                            I43IO_ComOpen                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bPortNum   - The port number to open.                             */
/*  dwBaudRate - The communication baud rate.                         */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function opens the communication port.                        */
/* The function also initilizes the port and set its state.           */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ComOpen(I43_UINT8 bPortNum, I43_UINT32 dwBoadRate);
I43_ERROR_CODE I43IO_UartComOpen(I43_UINT8 bPortNum, I43_UINT32 dwBoadRate);


/* ****************************************************************** */
/*                            I43IO_ComClose                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function closes the connection to the communication port.     */
/* The function also releases any allocated resources.                */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ComClose(void);
I43_ERROR_CODE I43IO_UartComClose(void);


/* ****************************************************************** */
/*                            I43IO_ComRead                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bBytesToRead - The number of bytes to read from the port.         */
/*  pbData       - Buffer to read the data into.                      */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function reads data from the communication port.              */
/* The function reads the exact amount of data requested from the     */
/* UART input buffer to the input buffer.                             */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ComRead(I43_UINT8* pbData, I43_UINT8 bBytesToRead);



/* ****************************************************************** */
/*                            I43IO_ComWrite                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  bBytesToWrite - The number of bytes to write to the port.         */
/*  pbData        - Data buffer to write to the I43.                  */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function reads data from the communication port.              */
/* The function reads the exact amount of data requested from the     */
/* UART input buffer to the input buffer.                             */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ComWrite(I43_UINT8* pbData, I43_UINT8 bBytesToWrite);



/* ****************************************************************** */
/*                            I43IO_Wait                              */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    wDelay - The number of Micro Seconds to wait before returning.  */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function generates a delay, by not returning until wDelay     */
/* Micro Seconds have past since it was called.                       */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_Wait(I43_UINT16 wDelay);



/* ****************************************************************** */
/*                           I43IO_DbgPrint                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pszString - the string to print.                                */
/*    dwVAlue   - the value to print.                                 */
/* Return Value:                                                      */
/*    None.                                                           */
/* ****************************************************************** */
/* This function prints a debug message to the debug output.          */
/* The function prints the string and immidiately after that the      */
/* dwValue as a hexadecimal number.                                   */
/* ****************************************************************** */
#ifndef _I43_DEBUG_
#define I43IO_DbgPrint(pszString, dwValue)
#endif

#ifdef _I43_DEBUG_
void I43IO_DbgPrint(char*      pszString,
                    I43_UINT32 dwValue);
#endif




/* ****************************************************************** */
/*                         IO Level Variables                         */
/* ****************************************************************** */


//
// The Comm Connection class.
// We use this class for COM port functions.
//
I43EXTERN CCommConnection Comm;


#endif /* _IO_LEVEL_H_ */

