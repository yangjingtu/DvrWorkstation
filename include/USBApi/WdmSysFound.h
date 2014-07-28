/* **************************************************************************** */
/*                                CallSys.h                                     */
/* **************************************************************************** */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 1997 ZORAN Corporation, All Rights Reserved   
 * THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION        
 *
 * $Workfile: WdmSysFound.h $ 
 * $Modtime: 4/27/99 4:06p $
 * $Revision: 4 $ 
 * $Date: 4/27/99 4:13p $ 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _WdmSysFound_H_
#define _WdmSysFound_H_

#include "CallSys.h"


/* ********************************************************************** */
/*                                WdmSysFound                                */
/* ********************************************************************** */
class WdmSysFound : public CallSys {
    public:                                       
        static CallSys* FindSys();

        WdmSysFound(HANDLE  hSys, HANDLE  hBulkRead, HANDLE  hBulkWrite);
        BOOL Call(DWORD dwControlCode, BYTE* pInBuffer=NULL, DWORD dwInBufferSize=0, BYTE* OutBuffer=NULL, DWORD dwOutBufferSize=0, DWORD* pdwBytesReturned=NULL);
        BOOL BulkRead(void* pInBuffer=NULL, DWORD dwInBufferSize=0, DWORD* pdwBytesReturned=NULL);
        BOOL BulkWrite(void* OutBuffer=NULL, DWORD dwOutBufferSize=0, DWORD* pdwBytesReturned=NULL);
        BOOL MessageRead(void* pInBuffer=NULL, DWORD dwInBufferSize=0, DWORD* pdwBytesReturned=NULL);
        virtual BOOL isExist();
        ~WdmSysFound();

	private:
        HANDLE  hSysDevice;
        HANDLE  hRead;
        HANDLE  hWrite;
};           




#endif /* _WdmSysFound_H_ */


