//////////////////////////////////////////////////////////////////////////
//描    述： 华安（二代dvr)设备
//时    间： created by yjt 2014-5-15
//历史记录:
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "interface.h"

#define GET_HA_ID    		0x1
#define SET_HA_ID    		0x2
#define GET_HA_TIME        	0x3
#define SET_HA_TIME        	0x4
#define SET_HA_MASS  		0x5

#define D6_ACK				240


class CHADvr : public CDevBase
{
public:
	CHADvr(void);
	virtual ~CHADvr(void);
	
public:
	virtual BOOL GetIDEx(CString &strID);
	virtual BOOL SetIDEx(const CString& strID);

	virtual BOOL SetTimeEx();
	virtual BOOL GetTimeEx(SYSTEMTIME *pst);
	virtual BOOL SetMassEx();
protected:
	BOOL GetValue(char uCommandID,char *pData,char *cLen);
	BOOL SetValue(char uCommandID,char *pData,char cLen);
};

class CA4Dvr : public CHADvr
{
public:
	virtual BOOL SetMassEx();
protected:

	virtual BOOL SetValue(char uCommandID, char *pData, char cLen);
};