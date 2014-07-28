#include "stdafx.h"
#include "IniFile.h"

CString CIniFile::GetIniPathName()
{
	return m_strPathName;
}

void CIniFile::SetIniPathName(CString strPathName)
{
	m_strPathName = strPathName;
}

CString CIniFile::ReadString(CString strSecName, CString strKeyName, CString strDefault)
{
	TCHAR buf[MAX_PATH];
	::GetPrivateProfileString(strSecName, strKeyName, strDefault, buf, MAX_PATH, m_strPathName);
	return buf;
}

BOOL CIniFile::WriteString(CString strSecName, CString strKeyName, CString strContent)
{
	BOOL result;
	result = ::WritePrivateProfileString(strSecName, strKeyName, strContent, m_strPathName);
	return result;
}

int CIniFile::ReadInt(CString strSecName, CString strKeyName, int nDefault)
{
	int result;
	result = ::GetPrivateProfileInt(strSecName, strKeyName, nDefault, m_strPathName);
	return result;
}
