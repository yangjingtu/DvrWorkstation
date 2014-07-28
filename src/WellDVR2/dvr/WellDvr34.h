//////////////////////////////////////////////////////////////////////////
//Describe:  3´ú4´úDVR
//Date:		 created by yjt 2014-05-15
//History:
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "interface.h"


#define GET_TIME    		0x1
#define SET_TIME    		0x2
#define SET_MASS  		0x3
#define GET_ID        		0x4
#define SET_ID        		0x5
#define GET_PWD             0x6
#define SET_PWD             0x7
#define SET_MACHINE_ID		0x8
#define GET_MACHINE_ID		0x9

class CWellDvr34 : public CDevBase
{
public:
	CWellDvr34(void);
	virtual ~CWellDvr34(void);

	virtual BOOL GetTimeEx(SYSTEMTIME *pst);
	virtual BOOL SetTimeEx();

	virtual BOOL GetIDEx(CString &strID);
	virtual BOOL SetIDEx(const CString& strID);

	virtual BOOL SetMassEx();

	virtual BOOL GetPwd(CString &strPwd);
	virtual BOOL SetPwd(const CString& strPwd);

	virtual BOOL GetMachinID(CString &str);
	virtual BOOL SetMachinID(const CString& MachiID);

protected:
	virtual BOOL GetValue(char uCommandID,char *pData,char *cLen);
	virtual BOOL SetValue(char uCommandID,char *pData,char cLen);
};