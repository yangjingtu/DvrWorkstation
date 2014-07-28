/* ****************************************************************** */
/*                            USB43CTL.h                              */
/* ****************************************************************** */
/* This module defines the USB IO control constants and the data      */
/* structures to be use with the chiptest utility and its WDM.        */
/* ****************************************************************** */


#ifndef _USBIOCTL_H_
#define _USBIOCTL_H_


//
// Macro definition for defining IOCTL and FSCTL function control codes.  Note
// that function codes 0-2047 are reserved for Microsoft Corporation, and
// 2048-4095 are reserved for customers.
//

#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)

//
// Define the method codes for how buffers are passed for I/O and FS controls
//

#define METHOD_BUFFERED                 0
#define METHOD_IN_DIRECT                1
#define METHOD_OUT_DIRECT               2
#define METHOD_NEITHER                  3

//
// Define the access check value for any access
//
//
// The FILE_READ_ACCESS and FILE_WRITE_ACCESS constants are also defined in
// ntioapi.h as FILE_READ_DATA and FILE_WRITE_DATA. The values for these
// constants *MUST* always be in sync.
//


#define FILE_ANY_ACCESS                 0
#define FILE_READ_ACCESS          ( 0x0001 )    // file & pipe
#define FILE_WRITE_ACCESS         ( 0x0002 )    // file & pipe


/* ****************************************************************** */
/*                     IO CONTROL DEFINITIONS                         */
/* ****************************************************************** */
/* User mode applications wishing to send IOCTLs to a kernel mode     */
/* driver must use this file to set up the correct type of IOCTL code */
/* permissions.                                                       */
/* Note: this file depends on the file DEVIOCTL.H which contains the  */
/* macro definition for "CTL_CODE" below.  Include that file before   */
/* you include this one in your source code.                          */
/* ****************************************************************** */
/*                                                                    */
/* Set the base of the IOCTL control codes.  This is somewhat of an   */
/* arbitrary base number, so you can change this if you want unique   */
/* IOCTL codes.  You should consult the Windows NT DDK for valid      */
/* ranges of IOCTL index codes before you choose a base index number. */
/* ****************************************************************** */
#define USB_BASE_IOCTL_INDEX  0x0950

#define FILE_DEVICE_UNKNOWN 0x00000022

#define USB_CTL_CODE_BUFFERD_ANY(Index)						\
					(CTL_CODE(FILE_DEVICE_UNKNOWN,			\
								USB_BASE_IOCTL_INDEX+Index,	\
                                METHOD_BUFFERED,			\
                                FILE_ANY_ACCESS))





#define IOCTL_USB_HELLO							USB_CTL_CODE_BUFFERD_ANY(0)
#define IOCTL_USB_WAIT_DISCONNECT				USB_CTL_CODE_BUFFERD_ANY(1)
#define IOCTL_USB_CANCEL						USB_CTL_CODE_BUFFERD_ANY(2)


#define BASIC_USB_BASE							        10
#define IOCTL_USB_GET_STATUS				        	USB_CTL_CODE_BUFFERD_ANY(BASIC_USB_BASE+1)
#define IOCTL_USB_CLEAR_ENDPOINT_FEATURE	        	USB_CTL_CODE_BUFFERD_ANY(BASIC_USB_BASE+2)
#define IOCTL_USB_SET_ENDPOINT_FEATURE		        	USB_CTL_CODE_BUFFERD_ANY(BASIC_USB_BASE+3)
#define IOCTL_USB_GET_DEVICE_DESCRIPTOR		        	USB_CTL_CODE_BUFFERD_ANY(BASIC_USB_BASE+4)
#define IOCTL_USB_GET_CONFIGURATION_DESCRIPTOR			USB_CTL_CODE_BUFFERD_ANY(BASIC_USB_BASE+5)
#define IOCTL_USB_GET_CONFIGURATION_DESCRIPTOR_LENGTH	USB_CTL_CODE_BUFFERD_ANY(BASIC_USB_BASE+6)
#define IOCTL_USB_GET_CONFIGURATION						USB_CTL_CODE_BUFFERD_ANY(BASIC_USB_BASE+7)
#define IOCTL_USB_SET_CONFIGURATION						USB_CTL_CODE_BUFFERD_ANY(BASIC_USB_BASE+8)
#define IOCTL_USB_ABORT_PIPE    						USB_CTL_CODE_BUFFERD_ANY(BASIC_USB_BASE+9)



#endif // _USBIOCTL_H_