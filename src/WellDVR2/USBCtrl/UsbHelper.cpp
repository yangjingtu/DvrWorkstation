#include "StdAfx.h"
#include "UsbHelper.h"
#include <WinIoCtl.h>

CUsbHelper::CUsbHelper(void)
{

}


CUsbHelper::~CUsbHelper(void)
{

}

CUsbHelper& CUsbHelper::Instance()
{
	static CUsbHelper uh;
	return uh;
}

//返回新插入的端口
wstring CUsbHelper::GetNewInsertUsbPort()
{
	MapUsb mapOld = m_usb.GetMapPortName();
	m_usb.EnumerateHostControllers();
	MapUsb mapNew = m_usb.GetMapPortName();
	
	MapUsbItor itOld = mapOld.begin();
	MapUsbItor itNew = mapNew.begin();
	for( ; itNew != mapNew.end() && itOld != mapOld.end(); ++itNew, ++itOld)
	{
		if((*itOld).second != (*itNew).second)
		{
			return (*itNew).first;
		}
	}

	return L"";
}

wstring CUsbHelper::GetRemoveUsbPort()
{
	MapUsb mapOld = m_usb.GetMapPortName();
	m_usb.EnumerateHostControllers();
	MapUsb mapNew = m_usb.GetMapPortName();

	MapUsbItor itOld = mapOld.begin();
	MapUsbItor itNew = mapNew.begin();
	for( ; itNew != mapNew.end() && itOld != mapOld.end(); ++itNew, ++itOld)
	{
		if((*itNew).second != (*itOld).second)
		{
			return (*itOld).first;
		}
	}

	return L"";
}

MapUsb& CUsbHelper::GetUsbPort_DiskName()
{
	return m_usb.EnumerateHostControllers();
}


MapUsb& CUsbHelper::GetMapPortName()
{
	m_usb.EnumerateHostControllers();
	return m_usb.GetMapPortName(); 
}

BOOL EnablePrivilege(PCTSTR pszPrivName, BOOL bEnable);

//参数是要弹出的盘符如：G，F
bool CUsbHelper::UnInstallUsb(char szDriveName) 
{
	DWORD accessMode = 0, shareMode = 0;
	HANDLE   hDevice; 
	ULONG returned = 0,bResult = 0;
	DWORD   dwError;  

	shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;  // default
	accessMode = GENERIC_WRITE | GENERIC_READ;       // default

	if (szDriveName == 0)
	{
		return FALSE;
	}

	CString vol_string = _T("\\\\.\\G:");
	vol_string.SetAt(4, szDriveName);
	hDevice = CreateFile(vol_string,
		accessMode,   shareMode,     NULL, OPEN_EXISTING, 0,       NULL);

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		CString debugInfo;
		dwError   =   GetLastError();    
		debugInfo.Format(_T("error = %d "), dwError);
		TRACE(_T("IOCTL_STORAGE_EJECT_MEDIA  errorcode = %d \n"), dwError);
		return FALSE;
	}

	//弹出U盘的具体命令。
	bResult   =   DeviceIoControl(hDevice, IOCTL_STORAGE_EJECT_MEDIA, 
		NULL, 0, NULL, 0,&returned,      NULL);

	if (!bResult)   //   IOCTL   failed     //经实验，有时虽然失败了，U盘还是能弹出
	{  
		CString debugInfo;
		dwError   =   GetLastError();    
		debugInfo.Format(_T("error = %d "), dwError);
		TRACE(_T("IOCTL_STORAGE_EJECT_MEDIA  errorcode = %d \n"), dwError);
	} 

	bResult   =   CloseHandle(hDevice);    
	if   (!bResult)    
	{    
		CString debugInfo;
		dwError   =   GetLastError();    
		debugInfo.Format(_T("error = %d "), dwError);
		TRACE(_T("IOCTL_STORAGE_EJECT_MEDIA  errorcode = %d \n"), dwError);
		return FALSE;
	} 
	
	EnablePrivilege(SE_DEBUG_NAME, TRUE);
	ClearUsbRegKey(szDriveName);

	return TRUE;
}


//从注册表中读取盘符对应的标识串
bool CUsbHelper::ClearUsbRegKey(char szDriveName)
{
	wstring strSKey1(_T("SYSTEM\\MountedDevices"));
	CString strKey(_T("\\DosDevices\\H:"));
	strKey.SetAt(12, szDriveName);

	return DelRegKey(strSKey1, strKey.GetString());
	//BYTE bValue[20] = {0};
	//SetRegKeyValue(strSKey1, strKey.GetString(), REG_BINARY, bValue, 20);
	//return true;
}

bool CUsbHelper::DelRegKey(const wstring& strSubKey, const wstring& strKey)
{
	HKEY hKEY;
	HKEY hKeyRoot = HKEY_LOCAL_MACHINE;

	long ret0 = RegOpenKeyEx(hKeyRoot,strSubKey.c_str(),0,KEY_ALL_ACCESS,&hKEY);
	if(ret0 != ERROR_SUCCESS) //如果无法打开hKEY,则中止程序的执行
	{
		return false;
	}

	ret0 = ::RegDeleteKey(hKEY, strKey.c_str());
	if(ret0 != ERROR_SUCCESS)
	{
		DWORD dwError = GetLastError();
		return false;
	}

	RegCloseKey(hKEY);

	return true;
}

//////////////////////////////////////////////////////////////////////////
//LPCSTR strSubKey = "SYSTEM\\CurrentControlSet\\Enum\\USB\\VID_0595&PID_2002\\7&52127c6&0&1";
//LPCSTR strKey = "ParentIdPrefix";//要查询的键名称
//DWORD keyType = REG_SZ;//定义数据类型
DWORD CUsbHelper::SetRegKeyValue(const wstring& strSubKey, const wstring& strKey, DWORD keyType, LPBYTE strValue, DWORD dwLen)
{
	HKEY hKEY;
	HKEY hKeyRoot = HKEY_LOCAL_MACHINE;

	long ret0 = RegOpenKeyEx(hKeyRoot,strSubKey.c_str(), 0, KEY_WRITE, &hKEY);
	if(ret0 != ERROR_SUCCESS)//如果无法打开hKEY,则中止程序的执行
	{
		return 0;
	}

	ret0 = ::RegSetValueEx(hKEY, strKey.c_str(),  0, keyType,  (const BYTE *) strValue, dwLen+1);
	if(ret0!=ERROR_SUCCESS)
	{
		DWORD dwError = GetLastError();
		return 0;
	}

	RegCloseKey(hKEY);

	return dwLen;
}
//////////////////////////////////////////////////////////////////////////


//提升权限
BOOL EnablePrivilege(PCTSTR pszPrivName, BOOL bEnable)
{
	BOOL bOk = FALSE;
	HANDLE hToken;

	if (::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		TOKEN_PRIVILEGES tp = { 1 };
		::LookupPrivilegeValue(NULL, pszPrivName, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;
		::AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
		bOk = (GetLastError() == ERROR_SUCCESS);
		::CloseHandle(hToken);
	}
	return bOk;
} 
