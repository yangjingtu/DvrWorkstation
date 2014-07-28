
#include <windows.h>
#include <winioctl.h>
#include <stdio.h>
#include <initguid.h>
#include <string.h>

#include <setupapi.h>
#pragma comment(lib,"setupapi.lib")

int gTag = 0;
#define MAX_DEVICE 256
wchar_t USBSerial[5][100] = {0};
//#define USBSERIAL_PATH C:\\Windows\\system32\\USBSerial.dat
DEFINE_GUID(UsbClassGuid, 0xa5dcbf10L, 0x6530, 0x11d2, 0x90, 0x1f, 0x00, 0xc0, 0x4f, 0xb9, 0x51, 0xed);

// SetupDiGetInterfaceDeviceDetail所需要的输出长度，定义足够大
#define INTERFACE_DETAIL_SIZE    (1024)

// IOCTL控制码
#define IOCTL_STORAGE_QUERY_PROPERTY   CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)



// 查询存储设备属性的类型
/*typedef enum _STORAGE_QUERY_TYPE {
PropertyStandardQuery = 0,          // 读取描述
PropertyExistsQuery,                // 测试是否支持
PropertyMaskQuery,                  // 读取指定的描述
PropertyQueryMaxDefined             // 验证数据
} STORAGE_QUERY_TYPE, *PSTORAGE_QUERY_TYPE;
*/


// 查询存储设备还是适配器属性
//typedef enum _STORAGE_PROPERTY_ID {
//    StorageDeviceProperty = 0,          // 查询设备属性
//    StorageAdapterProperty              // 查询适配器属性
//} STORAGE_PROPERTY_ID, *PSTORAGE_PROPERTY_ID;
// 
// 查询属性输入的数据结构
//typedef struct _STORAGE_PROPERTY_QUERY {
//    STORAGE_PROPERTY_ID PropertyId;     // 设备/适配器
//    STORAGE_QUERY_TYPE QueryType;       // 查询类型 
//    UCHAR AdditionalParameters[1];      // 额外的数据(仅定义了象征性的1个字节)
//} STORAGE_PROPERTY_QUERY, *PSTORAGE_PROPERTY_QUERY;
// 
//// 查询属性输出的数据结构
//typedef struct _STORAGE_DEVICE_DESCRIPTOR {
//    ULONG Version;                    // 版本
//    ULONG Size;                       // 结构大小
//    UCHAR DeviceType;                 // 设备类型
//    UCHAR DeviceTypeModifier;         // SCSI-2额外的设备类型
//    BOOLEAN RemovableMedia;           // 是否可移动
//    BOOLEAN CommandQueueing;          // 是否支持命令队列
//    ULONG VendorIdOffset;             // 厂家设定值的偏移
//    ULONG ProductIdOffset;            // 产品ID的偏移
//    ULONG ProductRevisionOffset;      // 产品版本的偏移
//    ULONG SerialNumberOffset;         // 序列号的偏移
//    STORAGE_BUS_TYPE BusType;         // 总线类型
//    ULONG RawPropertiesLength;        // 额外的属性数据长度
//    UCHAR RawDeviceProperties[1];     // 额外的属性数据(仅定义了象征性的1个字节)
//} STORAGE_DEVICE_DESCRIPTOR, *PSTORAGE_DEVICE_DESCRIPTOR;

// 根据GUID获得设备路径
// lpGuid: GUID指针
// pszDevicePath: 设备路径指针的指针
// 返回: 成功得到的设备路径个数，可能不止1个
int GetDevicePath(LPGUID lpGuid, LPTSTR* pszDevicePath)
{
	HDEVINFO hDevInfoSet;    //设备信息集句柄；
	SP_DEVICE_INTERFACE_DATA ifdata;
	PSP_DEVICE_INTERFACE_DETAIL_DATA pDetail;
	int nCount;
	BOOL bResult;

	// 取得一个该GUID相关的设备信息集句柄
	hDevInfoSet = ::SetupDiGetClassDevs((LPGUID)&UsbClassGuid,	// class GUID 
		NULL,// 无关键字
		NULL,// 不指定父窗口句柄
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);	 // 目前存在的设备

	// 失败...
	if (hDevInfoSet == INVALID_HANDLE_VALUE)
	{
		printf("Error!\n");
		//   break;
		return 0;
	}

	// 申请设备接口数据空间
	pDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)::GlobalAlloc(LMEM_ZEROINIT, INTERFACE_DETAIL_SIZE);

	pDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

	nCount = 0;
	bResult = TRUE;

	// 设备序号=0,1,2... 逐一测试设备接口，到失败为止
	while (bResult)
	{
		ifdata.cbSize = sizeof(ifdata);

		// 枚举符合该GUID的设备接口
		bResult = ::SetupDiEnumDeviceInterfaces(
			hDevInfoSet,     // 设备信息集句柄
			NULL,            // 不需额外的设备描述
			lpGuid,          // GUID
			(ULONG)nCount,   // 设备信息集里的设备序号
			&ifdata);        // 设备接口信息

		if (bResult)
		{
			// 取得该设备接口的细节(设备路径)
			bResult = SetupDiGetInterfaceDeviceDetail(
				hDevInfoSet,    // 设备信息集句柄
				&ifdata,        // 设备接口信息
				pDetail,        // 设备接口细节(设备路径)
				INTERFACE_DETAIL_SIZE,   // 输出缓冲区大小
				NULL,           // 不需计算输出缓冲区大小(直接用设定值)
				NULL);          // 不需额外的设备描述
			if (bResult)
			{
				// 复制设备路径到输出缓冲区
				//wcscpy_s(pszDevicePath[nCount],wcslen(pDetail->DevicePath)+1, pDetail->DevicePath);
				strcpy_s(pszDevicePath[nCount],strlen(pDetail->DevicePath)+1, pDetail->DevicePath);
				// 调整计数值
				nCount++;
			}
		}
	}
	// printf("%d\n", nCount);
	// printf("%s\n",pszDevicePath[1]);
	// 释放设备接口数据空间
	::GlobalFree(pDetail);
	// 关闭设备信息集句柄
	::SetupDiDestroyDeviceInfoList(hDevInfoSet);
	return nCount;
}

// OpenDevice(char* DevicePath)
// 返回句柄 hDevice
HANDLE OpenDevice(TCHAR* DevicePath)
{
	HANDLE hDevice;
	hDevice = CreateFile(DevicePath,
		GENERIC_READ && GENERIC_WRITE,
		FILE_SHARE_READ && FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	return hDevice;
}

#if 0
int WINAPI
	WinMain (
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpszCmdLine,
	int       nCmdShow
	)
{
#else

int main(int argc, char *argv[])
{
#endif
	int i, nDevice; // nDevice 表示有多少个USB设备
	int ndevice = 0; // 表示多少个U盘设备(可进行读写的设备)
	TCHAR* szDevicePath[MAX_DEVICE];        // 设备路径
	char pdg[1024] ;
	DWORD junk;
	HANDLE hDevice;
	BOOL bResult;

	// DWORD dwOutBytes; // IOCTL输出数据长度
	// 定义一个 PSTORAGE_DEVICE_DESCRIPTOR 变量，存放设备属性
	PSTORAGE_DEVICE_DESCRIPTOR DeviceDesc;
	// 变量初始化
	DeviceDesc=(PSTORAGE_DEVICE_DESCRIPTOR)new BYTE[sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1];
	DeviceDesc->Size = sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1;

	// 分配需要的空间
	for (i = 0; i < MAX_DEVICE; i++)
	{
		szDevicePath[i] = new TCHAR[256];
	}

	// 取设备路径
	nDevice = ::GetDevicePath((LPGUID)&UsbClassGuid, szDevicePath);

	// printf("%d\n", nDevice);
	// for(i = 0; i< nDevice; i++)
	//   printf("%s\n",szDevicePath[i]);

	// 逐一获取设备信息
	for (i = 0; i < nDevice; i++)
	{
		// 打开设备
		hDevice = OpenDevice(szDevicePath[i]);

		if (hDevice != INVALID_HANDLE_VALUE)
		{

			bResult = ::DeviceIoControl(hDevice, // device to be queried
				IOCTL_STORAGE_GET_MEDIA_TYPES, // operation to perform
				NULL, 0, // no input buffer
				pdg, 1024,     // output buffer
				&junk,                 // # bytes returned
				(LPOVERLAPPED) NULL); // synchronous I/O

			for(int j = 0; j < 4; j++)
			{
				USBSerial[ndevice][j] = szDevicePath[i][j+12]; 
			}
			for(int j = 4; j < 28; j++)
			{
				USBSerial[ndevice][j] = szDevicePath[i][j+22]; 
			}
			printf("U盘序列号为：");
			wprintf(L"%ws\n", USBSerial[ndevice]);
			ndevice ++;

			::CloseHandle(hDevice);
		}

	} 

	// 释放空间
	for (i = 0; i < MAX_DEVICE; i++)
	{
		delete []szDevicePath[i];
	}

	return gTag;
/*
	////////////////// 文件操作 ////////////////////////////////////////
	HANDLE hFile; 
	DWORD nBytesRead = 0, dwBytesWritten = 0;
	// 打开文件
	hFile = CreateFile(TEXT("C:\\Windows\\system32\\USBSerial.dat"),    // file to open
		GENERIC_READ | GENERIC_WRITE,          // open for reading
		FILE_SHARE_READ | FILE_SHARE_WRITE,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING ,         // existing file only
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL);                 // no attr. template
	if (hFile == INVALID_HANDLE_VALUE) 
	{

		// printf("1111111111111111111111111111\n");
		// printf("Could not open file!\n");
		hFile = CreateFile(TEXT("C:\\Windows\\system32\\USBSerial.dat"),     // file to create
			GENERIC_READ | GENERIC_WRITE,          // open for writing
			FILE_SHARE_READ | FILE_SHARE_WRITE,                      // do not share
			NULL,                   // default security
			CREATE_ALWAYS,          // overwrite existing
			FILE_ATTRIBUTE_NORMAL | // normal file
			FILE_ATTRIBUTE_NORMAL,   // asynchronous I/O
			NULL); 
		// printf("Could not open file (error %d)\n", GetLastError());

	}
	long nFileSize = GetFileSize(hFile, NULL);
	// printf("first:%d\n",nFileSize);
	wchar_t   *tempbuf =   new   wchar_t[nFileSize]   ; 
	// 读文件内容
	if (nFileSize == 0) 
	{ 
		// 创建文件，并把序列号写入文件中
		printf("创建文件，并把序列号写入文件中!\n");
		hFile = CreateFile(TEXT("C:\\Windows\\system32\\USBSerial.dat"),     // file to create
			GENERIC_READ | GENERIC_WRITE,          // open for writing
			FILE_SHARE_READ | FILE_SHARE_WRITE,                      // do not share
			NULL,                   // default security
			CREATE_ALWAYS,          // overwrite existing
			FILE_ATTRIBUTE_NORMAL | // normal file
			FILE_ATTRIBUTE_NORMAL,   // asynchronous I/O
			NULL);                  // no attr. template

		if (hFile == INVALID_HANDLE_VALUE) 
		{ 
			printf("Could not open file (error %d)\n", GetLastError());
			return 0; 
		}
		// 把序列号写入文件中
		WriteFile(hFile, 
			USBSerial, 
			2*wcslen(* USBSerial), 
			&dwBytesWritten, 
			NULL); 
		nFileSize = GetFileSize(hFile, NULL);
		// printf("second: %d\n", nFileSize);

	}

	else
	{
		// printf("third :%d\n",nFileSize);
		printf("进入比较序列号\n");
		ReadFile(hFile, 
			tempbuf, 
			nFileSize, 
			&nBytesRead, 
			NULL);
		//   printf("实际读取到的字节数目：%d\n", &nBytesRead);
		//   for (int i = 0; i< nFileSize/2; i ++)
		//    printf("%c", tempbuf[i]);
		//   printf("\n");
		//   wprintf(L"%ws\n", tempbuf);
		// 比较已经有的序列号与新读的是否相等
		for(int i = 0; i< ndevice; i ++)
		{
			for(int j = 0; j < nFileSize/2; j++)
			{
				//   if( wcscmp( tempbuf, USBSerial[i] ) == 0)
				//    printf("%c,%c; ",tempbuf[j], USBSerial[i][j] );
				if(tempbuf[j] == USBSerial[i][j])    
					gTag = 1;
				else
					gTag = 0;
			}
			if(gTag == 1)
				break;

		}
		delete tempbuf;
	}
	printf("gTag is :%d\n", gTag);
	if(gTag == 1)
		printf("匹配成功！\n");

	return gTag;
	// 返回值 gTag,如果 gTag 为1，表示U盘序列号与保存在文件中的序列号相同，
	// 若 gTag 为0，表示U盘序列号与保存在文件中的不同。
*/
}


//http://bbs.csdn.net/topics/350036814
//HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Disk\Enum 的键
//获取I:盘对应的编号
//获取指定盘符对应的驱动器号
int GetDiskNumber(char diskName)
{
	CHAR szPath[20] = {0};
	sprintf(szPath, "\\\\.\\%c:", diskName);
	HANDLE hDev = CreateFile(szPath, //"\\\\.\\I:", 
		0, 
		FILE_SHARE_READ|FILE_SHARE_WRITE, 
		NULL, 
		OPEN_EXISTING, 
		0, 
		NULL); 

	STORAGE_DEVICE_NUMBER sdn; 
	DWORD dwBytesRetuned=0; 
	int physicaldrivenum; 
	long res = DeviceIoControl(hDev, 
		IOCTL_STORAGE_GET_DEVICE_NUMBER, 
		NULL, 
		0, 
		&sdn,sizeof(sdn), 
		&dwBytesRetuned, 
		NULL); 
	if(res) 
	{ 
		physicaldrivenum = (int)sdn.DeviceNumber; 
	} 
	CloseHandle(hDev); 
	return physicaldrivenum;
}


//////////////////////////////////////////////////////////////////////////
// {
// 	CRegKey reg;
// 	LPCTSTR ps = _T("");
// 	LONG lRlt = reg.Open(HKEY_LOCAL_MACHINE, ps, KEY_ALL_ACCESS);
// 	if(ERROR_SUCCESS != lRlt)
// 	{
// 		//打开失败
// 	}
// 
// 	TCHAR szPath[MAX_PATH]; 
// 	DWORD dl = 0;
// 	DWORD dwLen = reg.QueryValue(szPath, _T("WallPaperDir"), &dl);
// 	if(ERROR_SUCCESS != lRlt)
// 	{
// 
// 	}
// 	reg.Close();
// 
// }
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
bool GetRegKeyValue()
{
	// 打开HKEY_LOCAL_MACHINE主键下的SoftWare\\Knight Studio\\Knight子键
	HKEY hKEY;
	HKEY hKeyRoot = HKEY_LOCAL_MACHINE;
	long ret0 = ::RegOpenKeyEx(hKeyRoot,"SYSTEM\\CurrentControlSet\\Enum\\USB\\VID_0595&PID_2002\\7&52127c6&0&1",0,KEY_READ,&hKEY);
	if(ret0 != ERROR_SUCCESS)//如果无法打开hKEY,则中止程序的执行
	{
		//AfxMessageBox("错误：无法打开有关的hKEY");
		return false;
	}

	// hKEY是上面打开时得到的指针。
	LPBYTE getValue = new BYTE[80];//得到的键值
	DWORD keyType = REG_SZ;//定义数据类型
	DWORD DataLen = 80;//定义数据长度
	LPCSTR strKey = "ParentIdPrefix";//要查询的键名称
	long ret1=::RegQueryValueEx(hKEY,strKey,NULL,&keyType,getValue,&DataLen);
	if(ret1!=ERROR_SUCCESS)
	{
		//AfxMessageBox("错误：无法查询有关的注册表信息");
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////