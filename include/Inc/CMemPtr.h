/* ****************************************************************** */
/*                              CMemPtr.h                             */
/* ****************************************************************** */

#ifndef _CMEMPTR_H_
#define _CMEMPTR_H_

#include <windows.h>

#include "Api_def.h"
#include "..\USBApi\Usb_def.h"

/* ****************************************************************** */
/*                      CMemPtr Class Definition                      */
/* ****************************************************************** */
class CMemPtr
{
private:
    /* Array that translates memory locations to pointers. */
    USB_MEM_LOCATION MemLocationPointers[NUMBER_OF_MEM_LOCATIONS];

public:
	CMemPtr();
	~CMemPtr();
    I43_UINT8* GetLocationBuffer(I43_MEMORY_LOCATION wLocation);
    I43_UINT32 GetLocationBufferSize(I43_MEMORY_LOCATION wLocation);
    void SetLocationBufferReadBytes(I43_MEMORY_LOCATION wLocation, I43_UINT32 dwReadBytes);
    I43_UINT32 GetLocationBufferReadBytes(I43_MEMORY_LOCATION wLocation);
    BOOL AllocateLocationBuffer(I43_MEMORY_LOCATION wLocation, I43_UINT32 dwSize);
    void FreeLocationBuffer(I43_MEMORY_LOCATION wLocation);
    void SetLocationBuffer(I43_MEMORY_LOCATION wLocation,
                           I43_UINT8*              pbBuffer,
                           I43_UINT32          dwSize);
    void UnSetLocationBuffer(I43_MEMORY_LOCATION wLocation);

};



#endif // _CMEMPTR_H_