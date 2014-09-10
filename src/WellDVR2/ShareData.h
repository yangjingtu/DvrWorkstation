/************************************************************************/
/*
*描述：共享数据类（全局变量）
*		1. 放在类中可以实现访问控制（加锁等）
*/
/************************************************************************/
#pragma once

#include "DataDef.h"
#include "CMainFrameWnd.h"

#define SHAREDATA CShareData::Instance()

class CShareData
{
private:
	CShareData(void);

	~CShareData(void);
public:
	static CShareData& Instance();

private:
	void Init();
	void UnInit();

public:
	DVRPROP g_dvrProp;					//DVR 行列固定参数

	EM_WORK_LEVEL g_dbgLevel;						//级别　1:定位　其它：正常模式

	CMainFrameWnd* g_pMainFrame;

	CString g_strFileTarget;			//存储文件的目标地址, 如 localhost
	CString g_strFilePath;				//存储文件的目录，如d://well-ftp

	double g_dwTotalSpace;				//总空间(MB)
	double g_dwFreeSpace;				//剩余空间(MB)

	CString g_strDeviceId;				//设备ID

	CString g_strWebIp;					//WebIP
	int g_nWebPort;						//WebPort

	int g_nDvrType;
};

