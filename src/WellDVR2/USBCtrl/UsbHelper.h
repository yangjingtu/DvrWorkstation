//////////////////////////////////////////////////////////////////////////
//Describe: USB辅助类
//
//Date:	created by yjt 2014-07-02
//History:
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
using namespace std;

#include "UsbEnum.h"

#define USBHUB CUsbHelper::Instance()

#define IVS_COMM_EXPORTS

#ifdef IVS_COMM_EXPORTS
#define IVS_COMM_API __declspec(dllexport)
#else 
#define IVS_COMM_API __declspec(dllimport)
#endif


class IVS_COMM_API CUsbHelper
{
private:
	CUsbHelper(void);
	~CUsbHelper(void);

public:
	static CUsbHelper& Instance();

	//获取新插入的USB 对应的hub口,如[Port1] ~ [Portn]
	wstring GetNewInsertUsbPort();

	wstring GetRemoveUsbPort();

	//获取USB hub口和盘符的对应关系
	MapUsb& GetUsbPort_DiskName();

	//获取USB_HUB口对应的是设备名称
	MapUsb& GetMapPortName();

	bool UnInstallUsb(char szDriveName) ;

private:
	bool ClearUsbRegKey(char szDriveName);
	DWORD SetRegKeyValue(const wstring& strSubKey, const wstring& strKey, DWORD keyType, LPBYTE strValue, DWORD dwLen);
	bool DelRegKey(const wstring& strSubKey, const wstring& strKey);

private:
	CUsbEnum m_usb;
};

