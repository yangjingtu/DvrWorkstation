#include "stdafx.h"
#include "HADvr.h"
#include "I43_Api.h"

CHADvr::CHADvr(void)
{
}


CHADvr::~CHADvr(void)
{

}

BOOL CHADvr::GetIDEx(CString &strID)
{
	char uID[20] = {0};	
	char ulen = 0;

	//华安的机器读快了会读不到，只能牺牲其它的了
	Sleep(750);
	//x6机器太快读不到
	Sleep(750);
	
	BOOL bret = GetValue(GET_HA_ID, uID, &ulen);
	//我们自己的机器GET_HA_ID获取的不是ID，是时间,长度为12
	if(ulen == 12)
	{
		STime Time = {0};
		memcpy(&Time, uID, ulen);
		if(Time.uYear > 2000 && Time.uHour >= 0 && Time.uHour < 24 &&
			Time.uMonth > 0 && Time.uMonth <= 12 && Time.uDay > 0 
			&& Time.uDay <= 31 &&Time.uMinute >= 0 && Time.uMinute < 60
			&& Time.uSecond >= 0 && Time.uSecond < 60)
		{
			strID.Empty();
			return FALSE;
		}
	}

	if( bret)
	{
		strID = uID;
	}
	else
	{
		strID.Empty();
	}

	return bret;
}

BOOL CHADvr::SetIDEx(const CString& strID)
{
	char uID[20] = {0};
	char ulen = 0;

	strcpy(uID, strID);
	ulen = strID.GetLength();

	return SetValue(SET_HA_ID, uID, ulen);
}

BOOL CHADvr::SetTimeEx()
{
	BOOL bret = TRUE;
	SYSTEMTIME st = {0};

	I43_ERROR_CODE i43_ret = I43IO_ComOpen();
	if( i43_ret != I43ERR_OK )
	{
		return FALSE;
	}

	GetLocalTime(&st);

	i43_ret = I43_SetClock(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	if( i43_ret != I43ERR_OK )
	{
		bret = FALSE;
	}

	I43IO_ComClose();

	return bret;
}

BOOL CHADvr::GetTimeEx(SYSTEMTIME *pst)
{
	char ulen = 0;
	STime Time = {0};

	BOOL bRet = 0;

	bRet = GetValue(GET_HA_TIME,(char *)&Time,&ulen);
	if(bRet && pst)
	{
		pst->wYear = Time.uYear;
		pst->wMonth = Time.uMonth;
		pst->wDay = Time.uDay;
		pst->wHour = Time.uHour;
		pst->wMinute = Time.uMinute;
		pst->wSecond = Time.uSecond;
	}
	return bRet;
}

BOOL CHADvr::SetMassEx()
{
	I43_ERROR_CODE i43_ret = I43IO_ComOpen();
	if( i43_ret != I43ERR_OK )
	{
		return FALSE;
	}

	if(I43_SetParam(0x102,1) != I43ERR_OK)
	{
		I43IO_ComClose();
		return FALSE;
	}

	if( I43ERR_OK != I43_SetUsbMode(I43USB_MS_BULK_ONLY_MODE))
	{
		I43IO_ComClose();
		return FALSE;
	}

	I43IO_ComClose();

	m_bMass = true;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//CA4Dvr
//////////////////////////////////////////////////////////////////////////
BOOL CA4Dvr::SetMassEx()
{
	char uMass = 1;
	int ulen = 1;
	BOOL bret = TRUE;

	int ret = SetValue(SET_HA_MASS, (char *)&uMass, ulen);
	if( ret != 0 )
		bret = FALSE;

	m_bMass = true;
	return bret;
}

BOOL CA4Dvr::SetValue(char uCommandID, char *pData, char cLen)
{
	unsigned short pAdrrH = 0;
	unsigned short pAdrrL = 0;
	unsigned long pAdd = 0;
	SUsbSetting Setting = {0};
	unsigned short uAck = 0;

	unsigned short uRet = 0xff;

	I43IO_ComOpen();

	I43_GetParam(0xb0,&pAdrrH);
	I43_GetParam(0xaf,&pAdrrL);

	pAdd = pAdrrH<<16|pAdrrL;

	char output[20] = {0};

	sprintf(output,"0x%x",pAdd);

	Setting.uwCommand = uCommandID;

	memcpy(Setting.pParam,pData,cLen);

	Setting.uwCommandLenth = 2 + cLen;

	I43_SetMemLocationPtr((I43_MEMORY_LOCATION)0xE,(I43_UINT8*)&Setting,Setting.uwCommandLenth) ;

	I43_ConfigMemAccess((I43_MEM_TYPE)1,pAdd,Setting.uwCommandLenth);

	uRet = I43_SetMem();

	if(uRet != I43ERR_OK)
	{
		I43IO_ComClose();
		return FALSE;
	}

	//modified by yjt 2014-06-12
	//D6会卡在这里，回不来
	//D6会返回240
	int nCount = 0;
	int nRlt = -1;
	while(uAck != ACK && uAck != D6_ACK)
	{
		nRlt = I43_GetParam(0xAD,&uAck);
		if(nCount++ > 200 )
		{
			//HA的机器获取0xAD为0
			if(nRlt == 0)
			{
				CHADvr::SetMassEx();
			}
			break;
		}
		Sleep(10);
	}

	I43_SetParam(0xAD,0);

	I43IO_ComClose();

	return TRUE;
}


BOOL CHADvr::GetValue(char uCommandID,char *pData,char *cLen)
{
	unsigned short pAdrrH = 0;
	unsigned short pAdrrL = 0;
	unsigned long pAdd = 0;
	SUsbSetting Setting = {0};
	unsigned short uAck = 0;
	unsigned int uTimeout = 0;
	unsigned short uRet = 0xff;

	I43IO_ComOpen();

	I43_GetParam(0xb0,&pAdrrH);
	I43_GetParam(0xaf,&pAdrrL);
	pAdd = pAdrrH<<16|pAdrrL;
	char output[20] = {0};
	sprintf(output,"0x%x",pAdd);

	Setting.uwCommand = uCommandID;
	Setting.uwCommandLenth = 2;

	I43_SetMemLocationPtr((I43_MEMORY_LOCATION)0xE,(I43_UINT8*)&Setting,Setting.uwCommandLenth) ;
	I43_ConfigMemAccess((I43_MEM_TYPE)1,pAdd,Setting.uwCommandLenth);

	uRet = I43_SetMem();

	if(uRet != I43ERR_OK)
	{
		I43IO_ComClose();
		return FALSE;
	}

	uTimeout = TIME_OUT;

	while((uAck != ACK)&&uTimeout)
	{
		I43_GetParam(0xAD,&uAck);
		Sleep(20);
		uTimeout--;
	}

	if(uTimeout == 0)
	{
		I43IO_ComClose();
		return FALSE;
	}

	I43_SetParam(0xAD,0);

	//A4太快读不到
	Sleep(50);

	memset(&Setting,0,sizeof(SUsbSetting));

	I43_SetMemLocationPtr((I43_MEMORY_LOCATION)0xF,(I43_UINT8*)(&Setting),sizeof(Setting)) ;
	I43_ConfigMemAccess((I43_MEM_TYPE)1,pAdd,sizeof(Setting));

	uRet = I43_GetMem();

	if(Setting.uwCommand == uCommandID)
	{
		memcpy(pData,Setting.pParam,Setting.uwCommandLenth - 2);
		*cLen = Setting.uwCommandLenth - 2;
		I43IO_ComClose();
		return TRUE;
	}
	else
	{
		*cLen = 0;
		I43IO_ComClose();
		return FALSE;
	}
}

BOOL CHADvr::SetValue(char uCommandID,char *pData,char cLen)
{
	unsigned short pAdrrH = 0;
	unsigned short pAdrrL = 0;
	unsigned long pAdd = 0;
	SUsbSetting Setting = {0};
	unsigned short uAck = 0;

	unsigned short uRet = 0xff;

	unsigned int uTimeout = 0;

	I43IO_ComOpen();

	I43_GetParam(0xb0,&pAdrrH);
	I43_GetParam(0xaf,&pAdrrL);

	pAdd = pAdrrH<<16|pAdrrL;

	char output[20] = {0};

	sprintf(output,"0x%x",pAdd);

	Setting.uwCommand = uCommandID;

	memcpy(Setting.pParam,pData,cLen);

	Setting.uwCommandLenth = 2 + cLen;

	I43_SetMemLocationPtr((I43_MEMORY_LOCATION)0xE,(I43_UINT8*)&Setting,Setting.uwCommandLenth) ;

	I43_ConfigMemAccess((I43_MEM_TYPE)1,pAdd,Setting.uwCommandLenth);

	uRet = I43_SetMem();

	if(uRet != I43ERR_OK)
	{
		I43IO_ComClose();
		return FALSE;
	}

	uTimeout = TIME_OUT;

	while((uAck != ACK)&&uTimeout)
	{
		I43_GetParam(0xAD,&uAck);
		Sleep(10);
		uTimeout--;
	}

	if(uTimeout == 0)
	{
		I43IO_ComClose();
		return FALSE;
	}

	I43_SetParam(0xAD,0);

	I43IO_ComClose();

	return TRUE;
}