/* ****************************************************************** */
/*                             Usb_func.h                             */
/* ****************************************************************** */
/* Copyright (c) 1997 ZORAN Corporation, All Rights Reserved          */
/* THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION               */
/*                                                                    */
/* $Workfile: Usb_func.h $                                            */
/* $Modtime: 6/22/00 14:20 $                                          */
/* $Revision: 5 $                                                     */
/* $Date: 6/22/00 14:20 $                                             */
/* ****************************************************************** */

#include "I43_Api.h"


#ifndef _USB_FUNC_H_
#define _USB_FUNC_H_



/* ****************************************************************** */
/*                        I43_SetMemLocationPtr                       */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wLocation   - the memory location to set the values for.          */
/*	pbBuffer    - pointer to the buffer to set as the new memory      */
/*                location.                                           */
/*  dwSize      - the buffer size.                                    */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function sets the memory location to the given pointer.       */
/* The buffer size will be used for Read/Write operations.            */
/* When the user wants to use a function that involves bulk transfers */
/* to a predefined memory location, he must set the memory location   */
/* pointer by calling this function before using the API function.    */
/* Note that when the buffer is not to be used any more, the buffer   */
/* should be UnSet by calling the I43_UnSetMemLocationPtr API.        */
/* failing to do so, will cause the API to try to release this memory */
/* buffer when the application will shut down.                        */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*	None.                                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43_SetMemLocationPtr(I43_MEMORY_LOCATION wLocation,
                                     I43_UINT8*          pbBuffer,
                                     I43_UINT32          dwSize
                                    ) CODE_SECT;

I43_ERROR_CODE I43_UsbSetMemLocationPtr(I43_MEMORY_LOCATION wLocation,
                                     I43_UINT8*          pbBuffer,
                                     I43_UINT32          dwSize
                                    ) CODE_SECT;

I43_ERROR_CODE I43_UsbSetMode( I43_MODE bNewMode);

/* ****************************************************************** */
/*                        I43_UnSetMemLocationPtr                     */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wLocation - the memory location to unset.                         */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function unsets the memory location pointer.                  */
/* Note: The buffer should be unset before it is deleted.             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*	None.                                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43_UnSetMemLocationPtr(I43_MEMORY_LOCATION wLocation
                                      ) CODE_SECT;


/* ****************************************************************** */
/*                      I43_GetMemLocationPtrReadBytes                */
/* ****************************************************************** */
/* Input Parameters:                                                  */
/*  wLocation    - the memory location to query.                      */
/*  pdwReadBytes - Pointer where to write the number of bytes read in */
/*                 the last transfer to this memory location.         */
/* Return Value:                                                      */
/*	Success - I43ERR_OK.                                              */
/*  Fail    - I43 error code according to the specific error.         */
/* ****************************************************************** */
/* This function unsets the memory location pointer.                  */
/* Note: The buffer should be unset before it is deleted.             */
/* ****************************************************************** */
/* I43 host commands in use:                                          */
/*	None.                                                             */
/* ****************************************************************** */
I43_ERROR_CODE I43_GetMemLocationPtrReadBytes(I43_MEMORY_LOCATION wLocation,
                                              I43_UINT32*         pdwReadBytes
                                             ) CODE_SECT;




#endif /* _USB_FUNC_H_ */
