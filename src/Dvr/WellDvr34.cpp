#include "stdafx.h"
#include "WellDvr34.h"
#include "I43_Api.h"


CWellDvr34::CWellDvr34(void)
{
}


CWellDvr34::~CWellDvr34(void)
{
}

BOOL CWellDvr34::GetTimeEx(SYSTEMTIME *pst)
{
	I43_ERROR_CODE i43_ret = I43ERR_OK;	
	BOOL bret = TRUE;

	i43_ret = I43IO_ComOpen();
	if( i43_ret != I43ERR_OK )
	{
		bret = FALSE;
		goto ERR_EXIT;
	}

	i43_ret = I43_GetClock(&pst->wYear, &pst->wMonth, &pst->wDay, &pst->wHour, &pst->wMinute, &pst->wSecond, &pst->wDayOfWeek);
	if( i43_ret != I43ERR_OK )
	{
		bret = FALSE;
		goto ERR_EXIT;
	}

	I43IO_ComClose();

ERR_EXIT:
	return bret;
}


BOOL CWellDvr34::SetTimeEx()
{
	I43_ERROR_CODE i43_ret = I43ERR_OK;	
	BOOL bret = TRUE;
	SYSTEMTIME st = {0};

	i43_ret = I43IO_ComOpen();
	if( i43_ret != I43ERR_OK )
	{
		bret = FALSE;
		goto ERR_EXIT;
	}

#if 1
	GetLocalTime(&st);

	i43_ret = I43_SetClock(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	if( i43_ret != I43ERR_OK )
	{
		bret = FALSE;
	}
#else
	{
		st.wYear = 2014;
		st.wMonth = 3;
		st.wDay = 22;
		st.wHour = 1;
		st.wMinute = 1;
		st.wSecond = 1;
		st.wDayOfWeek = 0;

		i43_ret = I43_SetClock(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		if( i43_ret != I43ERR_OK )
		{
			bret = FALSE;
		}
		else
		{
			memset(&st, 0, sizeof(st));
			i43_ret = I43_GetClock(&st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond, &st.wDayOfWeek);
		}	
	}
#endif

	I43IO_ComClose();

ERR_EXIT:
	return bret;
}

BOOL CWellDvr34::GetIDEx(CString &strID)
{
	char uID[20] = {0};	
	char ulen = 0;

	BOOL bret = GetValue(GET_ID, uID, &ulen);
	if( bret )
	{
		strID = uID;
	}
	else
	{
		strID.Empty();
	}

	return bret;
}

BOOL CWellDvr34::SetIDEx(const CString& strID)
{
	char uID[20] = {0};
	BOOL bret = TRUE;
	int ulen = 0;

	strcpy(uID, strID);
	ulen = strID.GetLength();

	return SetValue(SET_ID, uID, ulen);
}

BOOL CWellDvr34::SetMassEx()
{
	char uMass = 1;
	int ulen = 1;
	m_bMass = SetValue(SET_MASS, (char *)&uMass, ulen);
	return m_bMass;
}

BOOL CWellDvr34::GetPwd(CString &strPwd)
{
	char uPwd[50] = {0};	
	char ulen = 0;
	BOOL bret = GetValue(GET_PWD, uPwd, &ulen);
	if( bret )
	{
		strPwd = uPwd;
	}
	else
	{
		strPwd.Empty();
	}

	return bret;
}

BOOL CWellDvr34::SetPwd(const CString& strPwd)
{
	char uPwd[50] = {0};	
	char ulen = 0;
#define PWD_LEN 8

	strcpy(uPwd, strPwd);
	ulen = strPwd.GetLength();

	if( ulen > PWD_LEN )
		ulen = PWD_LEN;

	return SetValue(SET_PWD, uPwd, ulen);
}

BOOL CWellDvr34::GetMachinID(CString &str)
{
	char uMachinID[50] = {0};
	char ulen = 0;
	
	BOOL bret = GetValue(GET_MACHINE_ID, uMachinID, &ulen);
	if( bret )
	{
		str = uMachinID;
	}
	else
	{
		str.Empty();
	}

	return bret;
}

BOOL CWellDvr34::SetMachinID(const CString& MachiID)
{
	char uMachinID[50] = {0};
	char ulen = 0;

	strcpy(uMachinID, MachiID);
	ulen = MachiID.GetLength();

	return SetValue(SET_MACHINE_ID,uMachinID,ulen);
	
}


BOOL CWellDvr34::GetValue(char uCommandID, char *pData, char *cLen)
{
	unsigned short pAdrrH = 0;
	unsigned short pAdrrL = 0;
	unsigned long pAdd = 0;
	unsigned short uAck = 0;
	unsigned short uRet = 0xff;
	I43_ERROR_CODE i43_ret = I43ERR_OK;
	volatile int cnt = 0;	

	i43_ret = I43IO_ComOpen();
	if( i43_ret != I43ERR_OK )
	{
		return FALSE;
	}

	i43_ret = I43_GetParam(0xb0, &pAdrrH);
	i43_ret = I43_GetParam(0xaf, &pAdrrL);
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}
	else
	{
		pAdd = (pAdrrH<<16) | pAdrrL;
	}

	pSetting->uwCommand = uCommandID;
	pSetting->uwCommandLenth = COMMAND_LEN;
	memset(pSetting->pParam, 0, DATA_LEN);
	i43_ret = I43_SetMemLocationPtr((I43_MEMORY_LOCATION)0xE, (I43_UINT8*)pSetting, pSetting->uwCommandLenth);
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	i43_ret = I43_ConfigMemAccess((I43_MEM_TYPE)1, pAdd, pSetting->uwCommandLenth);
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	i43_ret = I43_SetMem();
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	//---------------------------------------------------------------	
	cnt = 0;
	uAck = 0;
	while( cnt++ < 10 )
	{
		i43_ret = I43_GetParam(0xAD, &uAck);
		if( i43_ret != I43ERR_OK )
		{
			I43IO_ComClose();
			return FALSE;
		}
		else
		{
			if( uAck != ACK )
				Sleep(200);
			else
				break;
		}
	}
	//---------------------------------------------------------------

	i43_ret = I43_SetParam(0xAD, 0);
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	memset(pSetting, 0, sizeof(SUsbSetting));
	i43_ret = I43_SetMemLocationPtr((I43_MEMORY_LOCATION)0xF, (I43_UINT8*)pSetting, sizeof(SUsbSetting));
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	i43_ret = I43_ConfigMemAccess((I43_MEM_TYPE)1, pAdd, sizeof(SUsbSetting));
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	i43_ret = I43_GetMem();
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	i43_ret = I43_SetParam(0xAD, 0);
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	if( pSetting->uwCommand == uCommandID )
	{
		memcpy(pData, pSetting->pParam, pSetting->uwCommandLenth - COMMAND_LEN);
		*cLen = pSetting->uwCommandLenth - COMMAND_LEN;
	}
	else
	{
		*cLen = 0;
	}

	I43IO_ComClose();
	return TRUE;
}

//----------------------------------------------------------------------------
BOOL CWellDvr34::SetValue(char uCommandID, char *pData, char cLen)
{
	unsigned short pAdrrH = 0;
	unsigned short pAdrrL = 0;
	unsigned long pAdd = 0;
	unsigned short uAck = 0;
	unsigned short uRet = 0xff;
	I43_ERROR_CODE i43_ret = I43ERR_OK;
	volatile int cnt = 0;

	i43_ret = I43IO_ComOpen();
	if( i43_ret != I43ERR_OK )
	{
		return FALSE;
	}

	i43_ret = I43_GetParam(0xb0, &pAdrrH);
	i43_ret = I43_GetParam(0xaf, &pAdrrL);
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	pAdd = (pAdrrH<<16) | pAdrrL;

	pSetting->uwCommand = uCommandID;
	memcpy(pSetting->pParam, pData, cLen);
	pSetting->uwCommandLenth = COMMAND_LEN + cLen;

	i43_ret = I43_SetMemLocationPtr((I43_MEMORY_LOCATION)0xE, (I43_UINT8*)pSetting, pSetting->uwCommandLenth);
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	i43_ret = I43_ConfigMemAccess((I43_MEM_TYPE)1, pAdd, pSetting->uwCommandLenth);
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	i43_ret = I43_SetMem();
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	//---------------------------------------------------------------	
	cnt = 0;
	uAck = 0;
	while( cnt++ < 10 )
	{
		i43_ret = I43_GetParam(0xAD, &uAck);
		if( i43_ret != I43ERR_OK )
		{
			I43IO_ComClose();
			return FALSE;
		}
		else
		{
			if( uAck != ACK )
				Sleep(200);
		}
	}
	//---------------------------------------------------------------

	i43_ret = I43_SetParam(0xAD, 0);
	if( i43_ret != I43ERR_OK )
	{
		I43IO_ComClose();
		return FALSE;
	}

	I43IO_ComClose();
	return TRUE;
}
