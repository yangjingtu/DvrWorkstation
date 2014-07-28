//////////////////////////////////////////////////////////////////////////
//Describe: USB枚举类
//			1. 把DDK的USBView的相关东东搬过来
//			2. 加上读取盘符操作
//			参考：
//				http://bbs.csdn.net/topics/350036814
//				http://www.laomaotao.net/new/2012/0218/499.html 《深入分析固定U盘盘符原理》
//			实现：
//				1. 遍历所有USB设备，获取他拉ID
//					1.1 CM_Get_Child()和CM_Get_Device_ID()获得其对应的USBSTOR的设备ID（形如USB\VID_0595&PID_2002\ZORAN01234567）
//					1.2 通过 USB\\VID_0595&PID_2002\\ 过滤掉不相关的设备
//				2. 遍历SYSTEM\\MountedDevices下带\\DosDevices\\X:的健，把他二进值存进来(盘符和值的应射表）
//						//遍历A-Z
// 						for (n = 0; n < 26; ++n)
// 						{
// 							sprintf(strTmp, "\\DosDevices\\%c:", 'A' + n);
// 							dwLen = sizeof(strValue);
// 							if( (dwLen = GetRegKeyValue(strSKey1, strTmp, REG_BINARY, strValue, dwLen)) != 0)
// 							{
// 								j = 0;
// 								for( i = 0; i < dwLen; ++i)
// 								{
// 									if(strValue[i] != 0)
// 									{
//										//去掉每个字符中间00
// 										*(strValue1[n] + j++) =strValue[i];
// 									}
// 								}
// 							}
// 						}
//
//				3. 打开SYSTEM\\CurrentControlSet\\Enum\\ + USBSTOR的设备ID 的键
//					如 SYSTEM\\CurrentControlSet\\Enum\\USB\\VID_0595&PID_2002\\ZORAN01234567
//					2.1 获取ParentIdPrefix的值(),如果获得，转到4, 如果没有ParentIdPrefix转到5
//				4. 把获取得到的ParentIdPrefix的值（8&16a2684b&0）,和第二步得到的值对比，找到则说明盘符找到
//					//有ParentIdPrefix的，直接可以找到盘符
//					//_??_USBSTOR#Disk&Ven_ZOKOD_DV&Prod_R&Rev_1.10#8&16a2684b&0&ZORAN01234567&0#{53f56307-b6bf-11d0-94f2-00a0c91efb8b}
//					4.1 匹配到ParentIdPrefix则找到盘符
//
//				5. 没有ParentIdPrefix(每一个插入或枚举的盘不会产生ParentIdPrefix)
//					//第一个枚举成U盘的，没有ParentIdPrefix的
//					//_??_USBSTOR#Disk&Ven_ZOKOD&Prod___DVR&Rev_1.10#ZORAN01234567&0#{53f56307-b6bf-11d0-94f2-00a0c91efb8b}
//					5.1 提取查找串( # + USBSTOR的设备ID的最后一部分),如#ZORAN01234567
//					5.2 和第二步得到的值对比（查找），得到盘符
//
//Date: created by yjt 2014-06-26
//History:
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "usbioctl.h"

#include <string>
#include <map>
#include <vector>
using namespace std;

wstring ConnectionStatuses[] =
{
	_T("NoDeviceConnected"),
	_T("DeviceConnected"),
	_T("DeviceFailedEnumeration"),
	_T("DeviceGeneralFailure"),
	_T("DeviceCausedOvercurrent"),
	_T("DeviceNotEnoughPower")
};

#define NUM_HCS_TO_CHECK 20

#ifdef  DEBUG
#undef  DBG
#define DBG 1
#endif

//test
#define DBG 0

#if DBG
#define OOPS() Oops(__FILE__, __LINE__)
#else
#define OOPS()
#endif

#if DBG

#define ALLOC(dwBytes) MyAlloc(__FILE__, __LINE__, (dwBytes))

#define REALLOC(hMem, dwBytes) MyReAlloc((hMem), (dwBytes))

#define FREE(hMem)  MyFree((hMem))

#define CHECKFORLEAKS() MyCheckForLeaks()

#else

#define ALLOC(dwBytes) GlobalAlloc(GPTR,(dwBytes))

#define REALLOC(hMem, dwBytes) GlobalReAlloc((hMem), (dwBytes), (GMEM_MOVEABLE|GMEM_ZEROINIT))

#define FREE(hMem)  GlobalFree((hMem))

#define CHECKFORLEAKS()

#endif

//<port1-n, usb string>
typedef map<wstring, wstring> MapUsb;
typedef MapUsb::iterator MapUsbItor;

class AFX_EXT_CLASS CUsbEnum
{
public:
	CUsbEnum(void);

	void Init();

	~CUsbEnum(void);
	
	//枚举控制器
	MapUsb& EnumerateHostControllers();

protected:
	VOID EnumerateHubPorts(HANDLE hHubDevice, ULONG NumPorts);

	VOID EnumerateHub (const wstring& HubName, PUSB_NODE_CONNECTION_INFORMATION	ConnectionInfo, const wstring& DeviceDesc);

private:
	wstring GetDriverKeyName ( HANDLE Hub, ULONG ConnectionIndex );
	wstring GetHCDDriverKeyName (HANDLE  HCD);
	wstring GetRootHubName( HANDLE HostController );
	wstring GetExternalHubName (HANDLE Hub, ULONG ConnectionIndex);
	wstring DriverNameToDeviceDesc (const wstring& DriverName);

	DWORD GetRegKeyValue(const wstring& strSubKey, const wstring& strKey, DWORD keyType, LPBYTE strValue, DWORD dwLen);

	void AddLeaf(int level, const wstring& text);

	//从注册表中读取盘符对应的标识串
	vector<wstring> ReadDeviceStrings();
	//获取盘符
	wstring GetDiskName(const wstring& deviceDesc, const vector<wstring>& vecDiskStrings);
private:
	ULONG TotalDevicesConnected;
	ULONG TotalHubs;

	//DriverNameToDeviceDesc用到
	TCHAR buf[512];
	
	//级别--打印用
	int m_nLevel;

	//端口--把所有的端口都进行编号
	int m_nPort;

	MapUsb m_mapUsb;
};

