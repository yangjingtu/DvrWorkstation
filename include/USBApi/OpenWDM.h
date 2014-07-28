/* ********************************************************************** */
/*                               OpenWDM.h                                */
/* ********************************************************************** */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 1997 ZORAN Corporation, All Rights Reserved   
 * THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION        
 *
 * $Workfile: OpenWDM.h $ 
 * $Modtime: 28-07-00 11:06 $
 * $Revision: 4 $ 
 * $Date: 28-07-00 13:36 $ 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#ifndef __OPENWDM_H__
#define __OPENWDM_H__

#include <windows.h>
#include <setupapi.h>


HANDLE OpenOneDevice (IN       HDEVINFO                    HardwareDeviceInfo,
                      IN       PSP_DEVICE_INTERFACE_DATA   DeviceInfoData,
                      IN	   char *devName);

HANDLE OpenUsbDevice(LPGUID  pGuid, char *outNameBuf);

BOOL GetUsbDeviceFileName(LPGUID  pGuid, char *outNameBuf);

HANDLE open_dev();

HANDLE open_file(char *filename);


#endif /* __OPENWDM_H__ */





