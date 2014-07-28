/* **************************************************************************** */
/*                                CallSys.h                                     */
/* **************************************************************************** */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 1997 ZORAN Corporation, All Rights Reserved   
 * THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION        
 *
 * $Workfile: CallSys.h $ 
 * $Modtime: 4/27/99 4:06p $
 * $Revision: 4 $ 
 * $Date: 4/27/99 4:13p $ 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _CALLSYS_H_
#define _CALLSYS_H_

#include <windows.h>
#include <UI43ApiDef.h>


/* ********************************************************************** */
/*                               CallSys                                  */
/* ********************************************************************** */
class EXT_CLASS_UI43Api CallSys {
    public:   
        static CallSys* FindSys();

        virtual BOOL BulkRead(void* pInBuffer=NULL, DWORD dwInBufferSize=0, DWORD* pdwBytesReturned=NULL)=0;
        virtual BOOL BulkWrite(void* OutBuffer=NULL, DWORD dwOutBufferSize=0, DWORD* pdwBytesReturned=NULL)=0;
        virtual BOOL Call(DWORD dwControlCode, BYTE* pInBuffer=NULL, DWORD dwInBufferSize=0, BYTE* OutBuffer=NULL, DWORD dwOutBufferSize=0, DWORD* pdwBytesReturned=NULL)=0;
        virtual BOOL MessageRead(void* pInBuffer=NULL, DWORD dwInBufferSize=0, DWORD* pdwBytesReturned=NULL)=0;
        virtual BOOL isExist()=0;
        virtual ~CallSys(){};

   protected:      
        CallSys();
};


/* ********************************************************************** */
/*                              SysNotFound                               */
/* ********************************************************************** */
class EXT_CLASS_UI43Api SysNotFound : public CallSys {
    public:   
        BOOL Call(DWORD dwControlCode, BYTE* pInBuffer=NULL, DWORD dwInBufferSize=0, BYTE* OutBuffer=NULL, DWORD dwOutBufferSize=0, DWORD* pdwBytesReturned=NULL);
        BOOL BulkRead(void* pInBuffer=NULL, DWORD dwInBufferSize=0, DWORD* pdwBytesReturned=NULL);
        BOOL BulkWrite(void* OutBuffer=NULL, DWORD dwOutBufferSize=0, DWORD* pdwBytesReturned=NULL);
        BOOL MessageRead(void* pInBuffer=NULL, DWORD dwInBufferSize=0, DWORD* pdwBytesReturned=NULL);
        virtual BOOL isExist();
};


/* ********************************************************************** */
/*                                OpenSys                                 */
/* ********************************************************************** */
class EXT_CLASS_UI43Api OpenSys 
{
	private:
		CallSys* pSys; // pointer to the Sys.
    public:
		OpenSys();
		CallSys* GetSys();
		~OpenSys();
		void CloseSys();
        BOOL ConnectSys();
};

#endif /* _CALLSYS_H_ */


