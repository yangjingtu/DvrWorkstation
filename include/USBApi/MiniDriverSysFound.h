/* **************************************************************************** */
/*                                CallSys.h                                     */
/* **************************************************************************** */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 1997 ZORAN Corporation, All Rights Reserved   
 * THIS IS PROPRIETARY SOURCE CODE OF ZORAN CORPORATION        
 *
 * $Workfile: MiniDriverSysFound.h $ 
 * $Modtime: 4/27/99 4:06p $
 * $Revision: 4 $ 
 * $Date: 4/27/99 4:13p $ 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _MiniDriverSysFound_H_
#define _MiniDriverSysFound_H_

#include "CallSys.h"
#include <streams.h>

/* ********************************************************************** */
/*                                MiniDriverSysFound                                */
/* ********************************************************************** */

struct SDriverStatus
{
	DWORD dwControlPipeStatus ;
	DWORD dwDataPipeStatus ;
	DWORD dwMessagePipeStatus ;
} ;


class MiniDriverSysFound : public CallSys 
{
    public:                                       
		static CallSys* FindSys();

        MiniDriverSysFound(IKsPropertySet * pKsProp);
        BOOL Call(DWORD dwControlCode, BYTE* pInBuffer=NULL, DWORD dwInBufferSize=0, BYTE* OutBuffer=NULL, DWORD dwOutBufferSize=0, DWORD* pdwBytesReturned=NULL);
        BOOL BulkRead(void* pInBuffer=NULL, DWORD dwInBufferSize=0, DWORD* pdwBytesReturned=NULL);
        BOOL BulkWrite(void* OutBuffer=NULL, DWORD dwOutBufferSize=0, DWORD* pdwBytesReturned=NULL);
        BOOL MessageRead(void* pInBuffer=NULL, DWORD dwInBufferSize=0, DWORD* pdwBytesReturned=NULL);
        virtual BOOL isExist();
        ~MiniDriverSysFound();

	private:
		enum pipe_type { CONTROL_PIPE , DATA_PIPE , MESSAGE_PIPE } ;
		BOOL CheckDriverStatus( pipe_type PipeType ) ;
		BOOL ReadDriverStatus( SDriverStatus& rdStatus ) ;

	private:
		IKsPropertySet * m_pKsProp	;
};           




#endif /* _MiniDriverSysFound_H_ */


