/* ****************************************************************** */
/*                              IO_Level.h                            */
/* ****************************************************************** */
/* Copyright (c) 1997 ZORAN Corporation, All Rights Reserved          */
/* THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION               */
/*                                                                    */
/* $Workfile: IO_Level.h $                                            */
/* $Modtime: 4/25/99 4:53p $                                         */
/* $Revision: 9 $                                                     */
/* $Date: 4/26/99 11:54a $                                             */
/* ****************************************************************** */


#ifndef _IO_LEVEL_H_
#define _IO_LEVEL_H_


/* ****************************************************************** */
/*                            I43IO_ComOpen                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  None.                                                             */
/* Return Value:                                                      */
/*  Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function opens the communication port.                        */
/* The function also initilizes the port and set its state.           */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ComOpen(void);
I43_ERROR_CODE I43IO_UsbComOpen(void);


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
I43_ERROR_CODE I43IO_UsbComClose(void);


/* ****************************************************************** */
/*                           I43IO_ControlRead                        */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pOperationBlock - pointer to the operation block sturcture that */
/*                      holds all the needed information for the      */
/*                      read operation.                               */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function sends the read command according to the parameters   */
/* in the operation block on the command pipe.                        */
/* The returned data is written in the bData array of the operation   */
/* block.                                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ControlRead(USB_CONTROL_OPERATION_BLOCK* pOperationBlock);


/* ****************************************************************** */
/*                         I43IO_ControlWrite                         */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pOperationBlock - pointer to the operation block sturcture that */
/*                      holds all the needed information for the      */
/*                      write operation.                              */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function sends the write command according to the parameters  */
/* in the operation block on the command pipe.                        */
/* The data to be send is given in the bData array of the operation   */
/* block.                                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_ControlWrite(USB_CONTROL_OPERATION_BLOCK* pOperationBlock);


/* ****************************************************************** */
/*                          I43IO_BulkWrite                           */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pbBuffer - pointer to the buffer holding the data to be sent.   */
/*    dwBufferLength - Length of the buffer in bytes.                 */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function writes the buffer to the I43 through the bulk pipe.  */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_BulkWrite(I43_UINT8* pbBuffer, 
                               I43_UINT32 dwBufferLength);


/* ****************************************************************** */
/*                          I43IO_BulkRead                            */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    pbBuffer       - Pointer to the buffer where to write the       */
/*                     returned data.                                 */
/*    dwBufferLength - Length of the buffer in bytes.                 */
/*    pdwBytesRead   - Pointer where to write the number of bytes     */
/*                     transfered.                                    */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/* This function reads the data from the I43 through the bulk pipe.   */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_BulkRead(I43_UINT8*  pbBuffer,
                              I43_UINT32  dwBufferLength,
                              I43_UINT32* pdwBytesRead);



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
/*                            I43IO_BasicUSB                          */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*    BUGBUG - documentation.                                         */
/* Return Value:                                                      */
/*    Success - I43ERR_OK.                                            */
/*    Fail    - I43 error code according to the specific error.       */
/* ****************************************************************** */
/*    BUGBUG - documentation.                                         */
/* ****************************************************************** */
I43_ERROR_CODE I43IO_BasicUSB(DWORD  dwControlCode, 
                              BYTE*  pInBuffer, 
                              DWORD  dwInBufferSize, 
                              BYTE*  pOutBuffer, 
                              DWORD  dwOutBufferSize, 
                              DWORD* pdwBytesReturned=NULL);




/* ****************************************************************** */
/*                         IO Level Variables                         */
/* ****************************************************************** */

I43EXTERN OpenSys Sys;

#endif /* _IO_LEVEL_H_ */

