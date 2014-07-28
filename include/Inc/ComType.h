/* ****************************************************************** */
/*                             ComType.h                              */
/* ****************************************************************** */
/* Copyright (c) 1997 ZORAN Corporation, All Rights Reserved          */
/* THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION               */
/*                                                                    */
/* $Workfile: ComType.h $                                             */
/* $Modtime: 9/28/00 19:58 $                                          */
/* $Revision: 44 $                                                    */
/* $Date: 10/03/00 17:26 $                                             */
/* ****************************************************************** */
/* This header contains an array that tells on each command, whether  */
/* it should be sent immidiately when the I43PR_SendCommandOpCode     */
/* function is called or should it wait for the                       */
/* I43PR_TransactionCompleted function call.                          */
/* ****************************************************************** */

#ifndef _COMTYPE_H_
#define _COMTYPE_H_

#define I43_USB_READ    0
#define I43_USB_WRITE   1

#define I43_NO_WAIT     0
#define I43_WAIT        1
#define I43_DELAY       2

/* The values that can be placed in the array are:
    bWaitToComplete:
    I43_NO_WAIT - don't wait for I43PR_TransactionCompleted.
                  if the command has no operands, we do not wait 
                  for I43PR_TransactionCompleted.
    I43_WAIT    - wait for I43_TransactionComplete.
                  if the command has operands we wait for I43_TransactionComplete.
    I43_DELAY   - don't wait for I43PR_TransactionCompleted, but send only 
                  when I43PR_WriteBufferToI43 arrives.
                  if the command has operands, and a buffer to transfer, we
                  wait for the I43PR_WriteBufferToI43 before sending the command
                  with the operands.
                  A command that uses I43_DELAY has a bulk to write. Those command
                  must send the TransactionComplete host command to the I43 after 
                  the buffer is written to the I43.
    bDirection:
    I43_USB_READ - Read operation.
    I43_USB_WRITE - Write operation.
    bLength:
    The length of the data phase of the control transfer in bytes.         
 */

typedef struct _USB_COMMAND_INFO
{
    BYTE bWaitToComplete; 
    BYTE bDirection;
    BYTE bLength;

} USB_COMMAND_INFO;

extern USB_COMMAND_INFO* gUsbCommandArray;

#endif /* _COMTYPE_H_ */


