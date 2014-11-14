#pragma once

#include <vector>
#include <map>
using namespace std;

#include "mmsystem.h"				//导入声音头文件
#pragma comment(lib,"winmm.lib")	//导入声音头文件库

/////////////////////////////////////////////////////////////////////////////////////
//宏定义
/////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
//定义单机模式
//#define ONE_DVR
#ifdef ONE_DVR

#define ROWS	1
#define COLS	1
#define DVR_TOTAL_NUM	ROWS*COLS

#define DVR_INSTANCE _T("WellDvrOne")
#else

#define ROWS	4
#define COLS	4
#define DVR_TOTAL_NUM	ROWS*COLS

#define DVR_INSTANCE _T("WellDvr")
#endif
////////////////////////////////////////////////////////
//是否启动指纹
#define FINGER_ENABLE  1


#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

//V1.00.10 是旧界面版本
//V1.01.00 是新界面版本，新界面由中间版本号区分
//V1.01.04 磁盘空间不足的声音报警
//V1.01.05 添加了A4,X6,D6的支持
//V1.02.01 更改了新的Hub口扫描方式
//V1.02.02 更改了一些小bug
//V1.02.03 可以随意指定行列，把设备型号提到配置文件中
//				 注:内蒙也添加了流媒体(Win32)
//V1.02.05 添加了流媒体(MFC)及monitor
//V1.02.06 修复了内存泄露和句柄数增长的问题
//V1.03.01 添加了指纹仪和摄像头
#define SOFT_VERSION	_T("版本:V1.02.06")

#define COMPANY _T("深圳市威尔电器有限公司")
#define PHONE _T("客服:4000602856")

#define BK_COLOR RGB(255, 50, 50)

#define DVR_BK_ACTIVE	RGB(255, 255, 0)
#define DVR_BK_NORMAL	RGB(0, 255, 255)
#define DVR_BK_DISABLE	RGB(128, 128, 128)

#define TEXT_COLOR		RGB(206, 34, 176)
//#define TEXT_COLOR		RGB(255, 0, 0)

#define DISP_MSG_CNT	30

#define WM_NOTIFYDATA           WM_USER + 3000
#define IDM_SHOW                WM_NOTIFYDATA + 1
#define IDM_EXIT                WM_NOTIFYDATA + 2
#define IDM_ABOUT             WM_NOTIFYDATA + 3

#define WM_NOTIFYID             WM_NOTIFYDATA + 20

#define CMD_VID_PID _T("VID_0595&PID_4343")
#define MASS_VID_PID _T("VID_0595&PID_2002")

#define APP_NAME _T("WellDVR2.exe") 
/////////////////////////////////////////////////////////////////////////////////////
//常量定义
/////////////////////////////////////////////////////////////////////////////////////
#ifdef ONE_DVR
const CString gc_AppName(_T("执法数据采集终端 - 个人版"));
#else
const CString gc_AppName(_T("执法数据采集终端"));
#endif

const CString gc_Config(_T("\\dvr_cfg.ini"));
const CString gc_LocationConfig(_T("\\location.xml"));
const CString gc_LocationConfig_BackUp(_T("\\location.back"));
const CString gc_Config_BackUp(_T("\\..\\dvr_cfg.back"));
const CString gc_DefaultSavePath(_T("d:\\well-ftp"));

const CString gc_configApp(_T("\\WellDVRConfig.exe"));
const CString gc_GetMachineApp(_T("\\GetMachineCode.exe"));
const CString gc_RegisterApp(_T("\\RegisterWnd.exe"));

//最小的空间限制
const UINT gc_MinSpaceLimit = 500;

//拷贝定时器
const UINT gc_TimerId_CopySpeed = 0;
const UINT gc_TimerSpace_CopySpeed = 1000;

/////////////////////////////////////////////////////////////////////////////////////
//枚举定义
/////////////////////////////////////////////////////////////////////////////////////
enum{ 
	COPY_OK = 0, 
	COPY_STOP, 
	COPY_SPACE_LIMIT,
	COPY_UNKNOWN 
};

enum EM_DEV_COLOR{
	//颜色定义
	CLR_DISABLE_BK = 0x00c0DCC0,
	CLR_DISABLE_BORDER = 0x000000FF,

	CLR_NOMAL_BK = 0x0DC01330,
	CLR_NOMAL_BORDER = 0x0000FFFF,

	CLR_ACTIVR_BK = 0x72C02CC0,
	CLR_ACTIVR_BORDER = 0xFF000000,

	CLR_DERICT_BORDER = 0x00FFFF00,
	CLR_DERICT_BK = 0x7E67787F,

	CLR_COPY_BORDER = 0x00FFFF00,
	CLR_COPY_BK = 0x7E67787F,

	CLR_COPY_OK_BORDER = 0x72C02CC0,
	CLR_COPY_OK_BK = 0x68CC3CE2,

	CLR_STOP_BORDER = 0x00FFFF00,
	CLR_STOP_BK = 0x7E67787F,

	CLR_MSG_ADD_DEV = 0x000000FF,
	CLR_MSG_DEL_DEV	= 0x00FF0000
};

//工作级别 
enum EM_WORK_LEVEL{
	LOCATION = 1,				//定位模式
	WORKING						//工作模式
};

enum EM_DVR_TYPE
{
	DVR_TYPE_WELL_34 = 0,					//WELL 3代 4代DVR
	DVR_TYPE_HA,									//华安（WELL 2代)
	DVR_TYPE_SHLR_A34,						//上海凌锐 A3/A4
	DVR_TYPE_SHLR_D6,						//上海凌锐 D6
	DVR_TYPE_SHLR_X6							//上海凌锐 X6
};

/////////////////////////////////////////////////////////////////////////////////////
//结构定义
/////////////////////////////////////////////////////////////////////////////////////
typedef struct tsDVRPROP
{
	int numDvr;
	int numRow;
	int numCol;
} DVRPROP, *PDVRPROP; 

typedef enum teDVRSTATUS
{
	DVR_ACTIVE = 0,			//激活状态（插入后识别成功）
	DVR_NORMAL,				//正常状态
	DVR_DISABLE,			//不可用（拔出状态）
	DVR_COPY,				//正在拷贝
	DVR_COPY_OK,			//拷贝完成
	DVR_STOP,				//停止传输
	DVR_DERICT				//定位模式
} DVRSTATUS, *PDVRSTATUS;

typedef struct tsDVRITEMPROP
{
	CRect rcPos;
	DVRSTATUS status;
} DVRITEMPROP, *PDVRITEMPROP;

typedef struct tsVIDPID
{
	USHORT idVendor;
	USHORT idProduct;
} VIDPID, *PVIDPID;

typedef struct tsDVRIDNAME
{
	CString strID;
	CString strName;
} DVRIDNAME, *PDVRIDNAME;

//////////////////////////////////////////////////////////////////////////
//配置文件
//FTP信息
typedef struct tagFTPInfo{
	bool bEnable;
	CString strServ;
	UINT nPort;
	CString strUser;
	CString strPwd;
	bool bTransIMP;
	bool bTransHD;
	bool bTransSD;
	bool bDelAfterTrans;
}FTPInfo, *PFTPInfo;

//数据库信息
typedef struct tagDBInfo{
	bool bEnable;
	CString strHost;
	UINT nPort;
	CString strSid;
	CString strUser;
	CString strPwd;
	long lConnTime;
}DBInfo, *PDBInfo;

//采集终端设备信息
typedef struct tagDeviceInfo
{
	CString strId;
}DeviceInfo, *PDeviceInfo;

typedef struct tagWebInfo
{
	CString strIp;
	int nPort;
}WebInfo, *PWebInfo;

typedef struct tagDvrWndInfo{
	CString m_strId;			//ID
	CString m_strName;			//NAME
	CString m_strDisk;			//DiskName
	DVRSTATUS m_status;			//状态
	//状态显示字符串
	CString m_strStatus;
	int nFileCount;						//總文件數
	int nTransFileCount;				//已偉輸文件數
}DvrWndInfo, *PDvrWndInfo;

typedef struct tagSoftWareInfo
{
	CString strPhone;
	CString strCpy;
	CString strVersion;
}SoftWareInfo, *PSoftWareInfo;

typedef struct tagSettingInfo{
	DVRPROP dvrProp;
}SettingInfo, *PSettingInfo;
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//数据库表对应的实体类
//////////////////////////////////////////////////////////////////////////
typedef struct tagDVRMEDIA_INFO
{
	wstring strDvrNumber;		//-- DVR编号
	wstring strFileName;		//--文件名
	wstring strFileSize;		//--文件大小
	wstring strViewWidth;		//-- 宽
	wstring strViewHeight;		//-- 高
	wstring strMediaDuration;	//--时长
	wstring strFrameRate;		//--帧率
	wstring strDataUploadTime;	//--上传时间
	wstring strMediaStartTime;	//--开始时间
	wstring strMediaEndTime;	//--结束时间
	wstring strRecordTime;		//-- 录像时间
	wstring strFileType;		//-- 文件类型
	wstring strVideoType;		//-- 重点/高清/标清
	wstring strLocateFilePath;	//--本地文件路径
	wstring strFtpFileUrl;		//--ftp文件路径
	wstring strIISFileUrl;		//--iis文件路径
	wstring strDataIp;			//--数据存储ip
	wstring strRemark;			//--备注
}DVRMEDIA_INFO, *PDVRMEDIA_INFO;

typedef struct tagDVR_DEVICE_LOG{
	wstring strDvrNumber;			//--dvr编号
	wstring strDeviceInsertTime;	//--设备插入时间
	wstring strDeviceOperTime;		//--设备操作时间
	wstring strDeviceOperUser;		//--设备操作用户
	wstring strLogContent;			//--日志内容
	wstring strRemark;				//--备注
}DVR_DEVICE_LOG,*PDVR_DEVICE_LOG;

typedef struct tagTERMINAL_DEV_LOG{
	wstring strDeviceNumber;		//--设备号
	wstring strHarewareVersion;		//--硬件版本
	wstring strSoftwareVersion;		//-软件版本
	wstring strDiskSpace;			//--磁盘空间
	wstring strTerminalIp;			//--IP
	wstring strIsusing;				//--是否启用 -Y是 -N否
	wstring strDetachment;			//--支队
	wstring strBattalion;			//--大队
	wstring strSquadron;			//--中队
	wstring strDescribe;			//--描述
	wstring strRemark;				//--备注
}TERMINAL_DEV_LOG, *PTERMINAL_DEV_LOG;

typedef struct tagTERMINAL_STATE{
	wstring strDeviceNumber;		//--设备号
	wstring strReportTime;			//--报告时间
	wstring strDeviceState;			//--设备状态
	wstring strRemark;				//--备注
}TERMINAL_STATE, *PTERMINAL_STATE;