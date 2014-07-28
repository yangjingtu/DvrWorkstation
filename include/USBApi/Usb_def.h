/* ****************************************************************** */
/*                             Usb_def.h                              */
/* ****************************************************************** */
/* Copyright (c) 1997 ZORAN Corporation, All Rights Reserved          */
/* THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION               */
/*                                                                    */
/* $Workfile: Usb_def.h $                                            */
/* $Modtime: 9/18/98 12:32p $                                          */
/* $Revision: 2 $                                                    */
/* $Date: 9/20/98 10:09a $                                             */
/* ****************************************************************** */

#ifndef _USB_DEF_H_
#define _USB_DEF_H_

/* ****************************************************************** */
/*                           USB sturctures                           */
/* ****************************************************************** */

#define CONTROL_DATA_PHASE_SIZE 64

/* This structure is used in Control Read/Write operations. */
typedef struct _USB_CONTROL_OPERATION_BLOCK
{
    unsigned char bmRequestType;
    unsigned char bRequest;
    unsigned short wValue;
    unsigned short wIndex;
    unsigned short wLength;
    unsigned char bData[CONTROL_DATA_PHASE_SIZE];

} USB_CONTROL_OPERATION_BLOCK;



/* This sturcture is the representation of a memory location in the 
   PC case. It consists of a pointer to a buffer and the buffer size. 
   and the number of words read in the last read operation.           */
typedef struct _USB_MEM_LOCATION
{
    unsigned char* pbBuffer;
    unsigned long  dwSize;
    unsigned long  dwReadBytes;

} USB_MEM_LOCATION;


#endif /* _USB_DEF_H_ */


