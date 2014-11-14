#include "StdAfx.h"
#include "UsbEnum.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
//注册表
#include <WinReg.h>
#pragma comment(lib, "advapi32.lib")

//////////////////////////////////////////////////////////////////////////
//DDK CM_Get_Child等相关函数
#include <setupapi.h>
#pragma comment(lib,"setupapi.lib")

#include <Cfgmgr32.h>
#pragma comment(lib,"USBCtrl/Cfgmgr32.lib")

#include <basetyps.h>
#include <winioctl.h>
#include "usbdesc.h"
#include <sstream>


wstring ConnectionStatuses[] =
{
	_T("NoDeviceConnected"),
	_T("DeviceConnected"),
	_T("DeviceFailedEnumeration"),
	_T("DeviceGeneralFailure"),
	_T("DeviceCausedOvercurrent"),
	_T("DeviceNotEnoughPower"),
	_T("DeviceNotEnoughBandwidth"),
	_T("UnKnow")
};


CUsbEnum::CUsbEnum(void)
{
	Init();
}


CUsbEnum::~CUsbEnum(void)
{
}

void CUsbEnum::Init()
{
	TotalDevicesConnected = 0;
	TotalHubs = 0;
	m_nLevel = 0;
	m_nPort = 0;

	m_mapPort_Disk.clear();
	m_mapPort_Name.clear();
}

MapUsb& CUsbEnum::EnumerateHostControllers()
{
    TCHAR       HCName[16];
    HANDLE      hHCDev;

	Init();

    // Iterate over some Host Controller names and try to open them.
    //
    for (int HCNum = 0; HCNum < NUM_HCS_TO_CHECK; HCNum++)
    {
        wsprintf(HCName, _T("\\\\.\\HCD%d"), HCNum);

        hHCDev = CreateFile(HCName,
                            GENERIC_WRITE,
                            FILE_SHARE_WRITE,
                            NULL,
                            OPEN_EXISTING,
                            0,
                            NULL);

        // If the handle is valid, then we've successfully opened a Host
        // Controller.  Display some info about the Host Controller itself,
        // then enumerate the Root Hub attached to the Host Controller.
        //
        if (hHCDev != INVALID_HANDLE_VALUE)
        {
            wstring driverKN = GetHCDDriverKeyName(hHCDev);
            wstring leafName = HCName + sizeof("\\\\.\\") - sizeof("");

            if (!driverKN.empty())
			{
                wstring deviceDesc = DriverNameToDeviceDesc(driverKN);

                if (!deviceDesc.empty())
                {
                    leafName = deviceDesc;
                }
            }

			m_nLevel = 0;
			AddLeaf(m_nLevel, leafName);

            wstring rootHN = GetRootHubName(hHCDev);

            if (!rootHN.empty())
            {			
                EnumerateHub( rootHN,
                                NULL,      // ConnectionInfo
                                _T("RootHub")  // DeviceDesc
                            );
            }

            CloseHandle(hHCDev);
        }
    }

	return m_mapPort_Disk;
}

VOID CUsbEnum::EnumerateHub( const wstring& HubName, PUSB_NODE_CONNECTION_INFORMATION ConnectionInfo, const wstring& DeviceDesc)
{
	HTREEITEM       hItem;
	BOOL            success;
	ULONG           nBytes;
	wstringstream leafName;
	wstring deviceName;

	// Initialize locals to not allocated state so the error cleanup routine
	// only tries to cleanup things that were successfully allocated.
	//
	HANDLE hHubDevice  = INVALID_HANDLE_VALUE;

	// Allocate some space for a USBDEVICEINFO structure to hold the
	// hub info, hub name, and connection info pointers.  GPTR zero
	// initializes the structure for us.
	//
	PUSB_NODE_INFORMATION HubInfo = (PUSB_NODE_INFORMATION)ALLOC(sizeof(USB_NODE_INFORMATION));

	if (HubInfo == NULL)
	{
		OOPS();
		goto EnumerateHubError;
	}

	deviceName = _T("\\\\.\\") + HubName;

	// Try to hub the open device
	//
	hHubDevice = CreateFile(deviceName.c_str(),
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);


	if (hHubDevice == INVALID_HANDLE_VALUE)
	{
		OOPS();
		goto EnumerateHubError;
	}

	//
	// Now query USBHUB for the USB_NODE_INFORMATION structure for this hub.
	// This will tell us the number of downstream ports to enumerate, among
	// other things.
	//
	success = DeviceIoControl(hHubDevice,
		IOCTL_USB_GET_NODE_INFORMATION,
		HubInfo,
		sizeof(USB_NODE_INFORMATION),
		HubInfo,
		sizeof(USB_NODE_INFORMATION),
		&nBytes,
		NULL);

	if (!success)
	{
		OOPS();
		goto EnumerateHubError;
	}

	leafName.clear();
	leafName.str(_T(""));
	// Build the leaf name from the port number and the device description
	//
	if (ConnectionInfo)
	{
		leafName << _T("[Port") << ConnectionInfo->ConnectionIndex;
		leafName << _T("][hub ") << TotalHubs;
		leafName << _T("] ");
		leafName << ConnectionStatuses[ConnectionInfo->ConnectionStatus];
		leafName << _T(" :  ");
	}

	if(DeviceDesc.empty())
		leafName << HubName;
	else
		leafName << DeviceDesc;

	int nLevel = ++m_nLevel;

	AddLeaf(m_nLevel, leafName.str());

	// Now recursively enumrate the ports of this hub.
	//
#if 1
	EnumerateHubPorts( hHubDevice, HubInfo->u.HubInformation.HubDescriptor.bNumberOfPorts);
#endif

	m_nLevel = nLevel;

	CloseHandle(hHubDevice);
	return;

EnumerateHubError:
	//
	// Clean up any stuff that got allocated
	//

	if (hHubDevice != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hHubDevice);
		hHubDevice = INVALID_HANDLE_VALUE;
	}


	if (HubInfo != NULL)
	{
		FREE(HubInfo);
		HubInfo = NULL;
	}

	if (ConnectionInfo != NULL)
	{
		FREE(ConnectionInfo);
		ConnectionInfo = NULL;
	}
}

//*****************************************************************************
//
// EnumerateHubPorts()
//
// hTreeParent - Handle of the TreeView item under which the hub port should
// be added.
//
// hHubDevice - Handle of the hub device to enumerate.
//
// NumPorts - Number of ports on the hub.
//
//*****************************************************************************

VOID CUsbEnum::EnumerateHubPorts(
    HANDLE      hHubDevice,
    ULONG       NumPorts
)
{
    ULONG       index;
    BOOL        success = false;

    PUSB_NODE_CONNECTION_INFORMATION    connectionInfo;

	TCHAR driverKeyName[200] = {0};
    wstring deviceDesc;
    wstringstream leafName;
	wstring diskName;
	wstring mapKey;

	//////////////////////////////////////////////////////////////////////////
	//add by yjt 2014-07-01
	//获取对应盘符串
	vector<wstring> diskStrings = ReadDeviceStrings();

	int nLevel = ++m_nLevel;
    // Loop over all ports of the hub.
    //
    // Port indices are 1 based, not 0 based.
    //
    for (index=1; index <= NumPorts; index++)
    {
        ULONG nBytes;

        // Allocate space to hold the connection info for this port.
        // For now, allocate it big enough to hold info for 30 pipes.
        //
        // Endpoint numbers are 0-15.  Endpoint number 0 is the standard
        // control endpoint which is not explicitly listed in the Configuration
        // Descriptor.  There can be an IN endpoint and an OUT endpoint at
        // endpoint numbers 1-15 so there can be a maximum of 30 endpoints
        // per device configuration.
        //
        // Should probably size this dynamically at some point.
        //
        nBytes = sizeof(USB_NODE_CONNECTION_INFORMATION) +
                 sizeof(USB_PIPE_INFO) * 30;

        connectionInfo = (PUSB_NODE_CONNECTION_INFORMATION)ALLOC(nBytes);

        if (connectionInfo == NULL)
        {
            OOPS();
            break;
        }

        //
        // Now query USBHUB for the USB_NODE_CONNECTION_INFORMATION structure
        // for this port.  This will tell us if a device is attached to this
        // port, among other things.
        //
        connectionInfo->ConnectionIndex = index;

        success = DeviceIoControl(hHubDevice,
                                  IOCTL_USB_GET_NODE_CONNECTION_INFORMATION,
                                  connectionInfo,
                                  nBytes,
                                  connectionInfo,
                                  nBytes,
                                  &nBytes,
                                  NULL);

        if (!success)
        {
            FREE(connectionInfo);
            continue;
        }

        // Update the count of connected devices
        //
        if (connectionInfo->ConnectionStatus == DeviceConnected)
        {
            TotalDevicesConnected++;
        }

        if (connectionInfo->DeviceIsHub)
        {
            TotalHubs++;
        }

        // If there is a device connected, get the Device Description
        //
		diskName.clear();

        deviceDesc.clear();
        if (connectionInfo->ConnectionStatus == DeviceConnected)
		//if (connectionInfo->ConnectionStatus != NoDeviceConnected)
        {
            wstring driverKN = GetDriverKeyName(hHubDevice,
                                             index);
            if (!driverKN.empty())
            {
                deviceDesc = DriverNameToDeviceDesc(driverKN);
            }

			//////////////////////////////////////////////////////////////////////////
			//add by yjt 2014-07-01
			//获取盘符
			diskName = GetDiskName(deviceDesc, diskStrings);
			
        }

        // If the device connected to the port is an external hub, get the
        // name of the external hub and recursively enumerate it.
        //
        if (connectionInfo->DeviceIsHub)
        {
            wstring extHubName = GetExternalHubName(hHubDevice, index);
            if (!extHubName.empty())
            {
				--m_nLevel;

                //EnumerateHub(tHubName, connectionInfo, configDesc, stringDescs, deviceDesc);
				EnumerateHub(extHubName, connectionInfo, deviceDesc);

                // On to the next port
				//
				FREE(connectionInfo);
                continue;
            }
        }

		//modified by yjt 2014-10-18 有少许的内存泄露
		FREE(connectionInfo);

		m_nPort++;

		leafName.clear();
		leafName.str(_T(""));

		leafName << _T("Port") << m_nPort;
		mapKey = leafName.str();

		//把盘符和端口对应起来
		m_mapPort_Disk[mapKey] = diskName;

		leafName.clear();
		leafName.str(_T(""));
		//leafName << ConnectionStatuses[connectionInfo->ConnectionStatus];
		
        if (!deviceDesc.empty())
        {
			leafName << deviceDesc;
            //leafName << _T(" :  ") << deviceDesc;
			if(!diskName.empty())
			{
				wstring strdisk(_T("   盘符["));
				strdisk += diskName;
				strdisk += _T(":]");
				leafName << strdisk;
			}
        }
		m_mapPort_Name[mapKey] = leafName.str();

		AddLeaf(m_nLevel, leafName.str());
    }
	m_nLevel = nLevel;
}

//////////////////////////////////////////////////////////////////////////
//LPCSTR strSubKey = "SYSTEM\\CurrentControlSet\\Enum\\USB\\VID_0595&PID_2002\\7&52127c6&0&1";
//LPCSTR strKey = "ParentIdPrefix";//要查询的键名称
//DWORD keyType = REG_SZ;//定义数据类型
//modifiey by yjt 2014-10-18 程序句柄数一直在增加，RegQueryValueEx分支添加RegCloseKey(hKey)
DWORD CUsbEnum::GetRegKeyValue(const wstring& strSubKey, const wstring& strKey, DWORD keyType, LPBYTE strValue, DWORD dwLen)
{
	// 打开HKEY_LOCAL_MACHINE主键下的SoftWare\\Knight Studio\\Knight子键
	HKEY hKEY;
	HKEY hKeyRoot = HKEY_LOCAL_MACHINE;

	long ret0 = RegOpenKeyEx(hKeyRoot,strSubKey.c_str(),0,KEY_READ,&hKEY);
	if(ret0 != ERROR_SUCCESS)//如果无法打开hKEY,则中止程序的执行
	{
		//AfxMessageBox("错误：无法打开有关的hKEY");
		return 0;
	}

	// hKEY是上面打开时得到的指针。
	ret0 = RegQueryValueEx(hKEY,strKey.c_str(),NULL,&keyType, strValue, &dwLen);
	if(ret0 != ERROR_SUCCESS)
	{
		RegCloseKey(hKEY);
		//AfxMessageBox("错误：无法查询有关的注册表信息");
		return 0;
	}

	RegCloseKey(hKEY);

	return dwLen;
}
//////////////////////////////////////////////////////////////////////////

//*****************************************************************************
//
// GetDriverKeyName()
//
//*****************************************************************************

wstring CUsbEnum::GetDriverKeyName (
    HANDLE  Hub,
    ULONG   ConnectionIndex
)
{
    BOOL                                success;
    ULONG                               nBytes;
    USB_NODE_CONNECTION_DRIVERKEY_NAME  driverKeyName;
    PUSB_NODE_CONNECTION_DRIVERKEY_NAME driverKeyNameW;
    wstring                               driverKeyNameA;

    driverKeyNameW = NULL;

    // Get the length of the name of the driver key of the device attached to
    // the specified port.
    //
    driverKeyName.ConnectionIndex = ConnectionIndex;

    success = DeviceIoControl(Hub,
                              IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME,
                              &driverKeyName,
                              sizeof(driverKeyName),
                              &driverKeyName,
                              sizeof(driverKeyName),
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetDriverKeyNameError;
    }

    // Allocate space to hold the driver key name
    //
    nBytes = driverKeyName.ActualLength;

    if (nBytes <= sizeof(driverKeyName))
    {
        OOPS();
        goto GetDriverKeyNameError;
    }

    driverKeyNameW = (PUSB_NODE_CONNECTION_DRIVERKEY_NAME)ALLOC(nBytes);

    if (driverKeyNameW == NULL)
    {
        OOPS();
        goto GetDriverKeyNameError;
    }

    // Get the name of the driver key of the device attached to
    // the specified port.
    //
    driverKeyNameW->ConnectionIndex = ConnectionIndex;

    success = DeviceIoControl(Hub,
                              IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME,
                              driverKeyNameW,
                              nBytes,
                              driverKeyNameW,
                              nBytes,
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetDriverKeyNameError;
    }

    // Convert the driver key name
    //
	driverKeyNameA = driverKeyNameW->DriverKeyName;

    // All done, free the uncoverted driver key name and return the
    // converted driver key name
    //
    FREE(driverKeyNameW);

    return driverKeyNameA;


GetDriverKeyNameError:
    // There was an error, free anything that was allocated
    //
    if (driverKeyNameW != NULL)
    {
        FREE(driverKeyNameW);
        driverKeyNameW = NULL;
    }

    return L"";
}

//*****************************************************************************
//
// GetExternalHubName()
//
//*****************************************************************************

wstring CUsbEnum::GetExternalHubName ( HANDLE  Hub, ULONG ConnectionIndex)
{
    BOOL                        success;
    ULONG                       nBytes;
    USB_NODE_CONNECTION_NAME    extHubName;
    PUSB_NODE_CONNECTION_NAME   extHubNameW;
	wstring extHubNameA;

    extHubNameW = NULL;

    // Get the length of the name of the external hub attached to the
    // specified port.
    //
    extHubName.ConnectionIndex = ConnectionIndex;

    success = DeviceIoControl(Hub,
                              IOCTL_USB_GET_NODE_CONNECTION_NAME,
                              &extHubName,
                              sizeof(extHubName),
                              &extHubName,
                              sizeof(extHubName),
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetExternalHubNameError;
    }

    // Allocate space to hold the external hub name
    //
    nBytes = extHubName.ActualLength;

    if (nBytes <= sizeof(extHubName))
    {
        OOPS();
        goto GetExternalHubNameError;
    }

    extHubNameW = (PUSB_NODE_CONNECTION_NAME)ALLOC(nBytes);

    if (extHubNameW == NULL)
    {
        OOPS();
        goto GetExternalHubNameError;
    }

    // Get the name of the external hub attached to the specified port
    //
    extHubNameW->ConnectionIndex = ConnectionIndex;

    success = DeviceIoControl(Hub,
                              IOCTL_USB_GET_NODE_CONNECTION_NAME,
                              extHubNameW,
                              nBytes,
                              extHubNameW,
                              nBytes,
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetExternalHubNameError;
    }

    // Convert the External Hub name
    //
	extHubNameA = extHubNameW->NodeName;

    // All done, free the uncoverted external hub name and return the
    // converted external hub name
    //
    FREE(extHubNameW);

    return extHubNameA;


GetExternalHubNameError:
    // There was an error, free anything that was allocated
    //
    if (extHubNameW != NULL)
    {
        FREE(extHubNameW);
        extHubNameW = NULL;
    }

    return L"";
}

//*****************************************************************************
//
// GetRootHubName()
//
//*****************************************************************************

wstring CUsbEnum::GetRootHubName (
    HANDLE HostController
)
{
    BOOL                success;
    ULONG               nBytes;
    USB_ROOT_HUB_NAME   rootHubName;
    PUSB_ROOT_HUB_NAME  rootHubNameW;
	wstring rootHubNameA;

    rootHubNameW = NULL;

    // Get the length of the name of the Root Hub attached to the
    // Host Controller
    //
    success = DeviceIoControl(HostController,
                              IOCTL_USB_GET_ROOT_HUB_NAME,
                              0,
                              0,
                              &rootHubName,
                              sizeof(rootHubName),
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetRootHubNameError;
    }

    // Allocate space to hold the Root Hub name
    //
    nBytes = rootHubName.ActualLength;

    rootHubNameW = (PUSB_ROOT_HUB_NAME)ALLOC(nBytes);

    if (rootHubNameW == NULL)
    {
        OOPS();
        goto GetRootHubNameError;
    }

    // Get the name of the Root Hub attached to the Host Controller
    //
    success = DeviceIoControl(HostController,
                              IOCTL_USB_GET_ROOT_HUB_NAME,
                              NULL,
                              0,
                              rootHubNameW,
                              nBytes,
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetRootHubNameError;
    }

    // Convert the Root Hub name
    //
	rootHubNameA = rootHubNameW->RootHubName;

    // All done, free the uncoverted Root Hub name and return the
    // converted Root Hub name
    //
    FREE(rootHubNameW);

    return rootHubNameA;


GetRootHubNameError:
    // There was an error, free anything that was allocated
    //
    if (rootHubNameW != NULL)
    {
        FREE(rootHubNameW);
        rootHubNameW = NULL;
    }

    return L"";
}

//*****************************************************************************
//
// GetHCDDriverKeyName()
//
//*****************************************************************************

wstring CUsbEnum::GetHCDDriverKeyName (
    HANDLE  HCD
)
{
    BOOL                    success;
    ULONG                   nBytes;
    USB_HCD_DRIVERKEY_NAME  driverKeyName;
    PUSB_HCD_DRIVERKEY_NAME driverKeyNameW;
	wstring driverKeyNameA;

    driverKeyNameW = NULL;

    // Get the length of the name of the driver key of the HCD
    //
    success = DeviceIoControl(HCD,
                              IOCTL_GET_HCD_DRIVERKEY_NAME,
                              &driverKeyName,
                              sizeof(driverKeyName),
                              &driverKeyName,
                              sizeof(driverKeyName),
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetHCDDriverKeyNameError;
    }

    // Allocate space to hold the driver key name
    //
    nBytes = driverKeyName.ActualLength;

    if (nBytes <= sizeof(driverKeyName))
    {
        OOPS();
        goto GetHCDDriverKeyNameError;
    }

    driverKeyNameW = (PUSB_HCD_DRIVERKEY_NAME)ALLOC(nBytes);

    if (driverKeyNameW == NULL)
    {
        OOPS();
        goto GetHCDDriverKeyNameError;
    }

    // Get the name of the driver key of the device attached to
    // the specified port.
    //
    success = DeviceIoControl(HCD,
                              IOCTL_GET_HCD_DRIVERKEY_NAME,
                              driverKeyNameW,
                              nBytes,
                              driverKeyNameW,
                              nBytes,
                              &nBytes,
                              NULL);

    if (!success)
    {
        OOPS();
        goto GetHCDDriverKeyNameError;
    }

    // Convert the driver key name
    //
	driverKeyNameA = driverKeyNameW->DriverKeyName;

    // All done, free the uncoverted driver key name and return the
    // converted driver key name
    //
    FREE(driverKeyNameW);

    return driverKeyNameA;


GetHCDDriverKeyNameError:
    // There was an error, free anything that was allocated
    //
    if (driverKeyNameW != NULL)
    {
        FREE(driverKeyNameW);
        driverKeyNameW = NULL;
    }

    return L"";
}

//*****************************************************************************
//
// DriverNameToDeviceDesc()
//
// Returns the Device Description of the DevNode with the matching DriverName.
// Returns NULL if the matching DevNode is not found.
//
// The caller should copy the returned string buffer instead of just saving
// the pointer value.  XXXXX Dynamically allocate return buffer?
//
//*****************************************************************************

wstring CUsbEnum::DriverNameToDeviceDesc (const wstring& DriverName)
{
    DEVINST     devInst;
    DEVINST     devInstNext;
    CONFIGRET   cr;
    ULONG       walkDone = 0;
    ULONG       len;

    // Get Root DevNode
    //
    cr = CM_Locate_DevNode(&devInst,
                           NULL,
                           0);

    if (cr != CR_SUCCESS)
    {
        return NULL;
    }

    // Do a depth first search for the DevNode with a matching
    // DriverName value
    //
    while (!walkDone)
    {
        // Get the DriverName value
        //
        len = sizeof(buf);
        cr = CM_Get_DevNode_Registry_Property(devInst,
                                              CM_DRP_DRIVER,
                                              NULL,
                                              buf,
                                              &len,
                                              0);

        // If the DriverName value matches, return the DeviceDescription
        //
        if (cr == CR_SUCCESS && wcscmp(DriverName.c_str(), buf) == 0)
        {
            len = sizeof(buf);
            cr = CM_Get_DevNode_Registry_Property(devInst,
                                                  CM_DRP_DEVICEDESC,
                                                  NULL,
                                                  buf,
                                                  &len,
                                                  0);

            if (cr == CR_SUCCESS)
            {
				//DEVINST devInstParent;
				//CM_Get_Parent(&devInstParent,devInst,  0); 
				CM_Get_Device_ID(devInst,  buf,  512, 0);

				return buf;
            }
            else
            {
                return NULL;
            }
        }

        // This DevNode didn't match, go down a level to the first child.
        //
        cr = CM_Get_Child(&devInstNext,
                          devInst,
                          0);

        if (cr == CR_SUCCESS)
        {
            devInst = devInstNext;
            continue;
        }

        // Can't go down any further, go across to the next sibling.  If
        // there are no more siblings, go back up until there is a sibling.
        // If we can't go up any further, we're back at the root and we're
        // done.
        //
        for (;;)
        {
            cr = CM_Get_Sibling(&devInstNext,
                                devInst,
                                0);

            if (cr == CR_SUCCESS)
            {
                devInst = devInstNext;
                break;
            }

            cr = CM_Get_Parent(&devInstNext,
                               devInst,
                               0);


            if (cr == CR_SUCCESS)
            {
                devInst = devInstNext;
            }
            else
            {
                walkDone = 1;
                break;
            }
        }
    }

    return L"";
}

void CUsbEnum::AddLeaf(int level, const wstring& text)
{
	TCHAR msg[200] = {0};
	int nOffset = 5;
	for (int i = 0; i < level; ++i)
	{
		wsprintf(msg + i * nOffset, _T("-----"));
	}
	wsprintf(msg + level * nOffset, _T("%s\r\n"), text.c_str());

	//OutputDebugString(msg);
}

//从注册表中读取盘符对应的标识串
vector<wstring> CUsbEnum::ReadDeviceStrings()
{
	wstring strSKey1(_T("SYSTEM\\MountedDevices"));
	BYTE strValue[512] = {0};
	TCHAR strValue1[512] = {0};
 	
	DWORD dwLen = 0;
 	TCHAR strTmp[30] = {0};

 	int j = 0;

	vector<wstring> vecRlt;
	vecRlt.reserve(26);

	//////////////////////////////////////////////////////////////////////////
	//盘符对应
	for (int n = 0; n < 26; ++n)
	{
		memset(strValue1, 0, sizeof(strValue1));

		swprintf(strTmp, _T("\\DosDevices\\%c:"), 'A' + n);
		dwLen = sizeof(strValue);
		if( (dwLen = GetRegKeyValue(strSKey1, strTmp, REG_BINARY, strValue, dwLen)) != 0)
		{
			j = 0;
			for(int i = 0; i < dwLen; ++i)
			{
				if(strValue[i] != 0)
				{
					*(strValue1 + j++) =strValue[i];
				}
			}
		}
		else
			memset(strValue, 0, sizeof(strValue));

		vecRlt.push_back(strValue1);
	}

	return vecRlt;
}

//获取盘符
wstring CUsbEnum::GetDiskName( const wstring& deviceDesc, const vector<wstring>& vecDiskStrings)
{
 	wstring strSubKeyPrefix = _T("SYSTEM\\CurrentControlSet\\Enum\\");
	//要查询的键名称
 	wstring strKey = _T("ParentIdPrefix");
	TCHAR strValue[512] = {0};
 	wstring diskName;
	//这个长度要传，否则返回234（接收缓冲区太小)
	DWORD dwLen = sizeof(strValue);

	wstring str(deviceDesc);
	if(str.find(_T("USB\\VID_0595&PID_2002\\")) != wstring::npos)
	{
		//////////////////////////////////////////////////////////////////////////
		//add by yjt 2014-06-25
		wstring strSubKey = strSubKeyPrefix + deviceDesc;

		//有ParentIdPrefix的，直接可以找到盘符
		//_??_USBSTOR#Disk&Ven_ZOKOD_DV&Prod_R&Rev_1.10#8&16a2684b&0&ZORAN01234567&0#{53f56307-b6bf-11d0-94f2-00a0c91efb8b}
		if( (dwLen = GetRegKeyValue(strSubKey, strKey, REG_SZ, (LPBYTE)strValue, dwLen)) != 0)
		{
			wstring strP(strValue);
			for (int n = 0; n < 26; ++n)
			{
				str = vecDiskStrings[n];
				if(str.find(strP) != wstring::npos)
				{
					diskName = 'A' + n;
					break;
				}
			}
		}
		else
		{
			//第一个枚举成U盘的，没有ParentIdPrefix的
			//_??_USBSTOR#Disk&Ven_ZOKOD&Prod___DVR&Rev_1.10#ZORAN01234567&0#{53f56307-b6bf-11d0-94f2-00a0c91efb8b}

			//取出ZORAN01234567
			wstring strId = str.substr( str.rfind('\\') + 1);
			//查找#ZORAN01234567, 和有ParentIdPrefix区别开
			strId = _T("#") + strId;
			for (int n = 0; n < 26; ++n)
			{
				str = vecDiskStrings[n];
				if(str.find(strId) != wstring::npos)
				{
					diskName = 'A' + n;
					break;
				}
			}

		}
	}
	//////////////////////////////////////////////////////////////////////////

	return diskName;
}


