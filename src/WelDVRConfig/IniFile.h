#ifndef __INIFILE_H__
#define __INIFILE_H__

#if _MSC_VER > 1000
#pragma once
#endif

class CIniFile  
{
public:
	CIniFile() {}
	CIniFile(CString strPathName) { m_strPathName = strPathName; }
	virtual ~CIniFile() {}

public:
	void  SetIniPathName(CString strPathName);
	CString GetIniPathName();

	CString ReadString(CString strSecName, CString strKeyName, CString strDefault);
	BOOL WriteString (CString strSecName, CString strKeyName, CString strContent);
	int ReadInt(CString strSecName, CString strKeyName, int nDefault);
	
private:
	CString m_strPathName;
};

#endif //#define __INIFILE_H__
