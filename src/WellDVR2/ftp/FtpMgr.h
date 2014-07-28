//////////////////////////////////////////////////////////////////////////
//Describe:	FTP管理类
//			1. 通过注册回调的方式来控制文件的上传
//				1.1 判断重点视频，高清视频等
//Date:		created by yjt 2014-06-13
//History:
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "../DataDef.h"
#include "FtpHelper.h"
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define FTP_CLIENT CFtpMgr::Instance()

//////////////////////////////////////////////////////////////////////////
//上传文件回调处理
//	可以在此过滤重点视频，分辨率等
int __stdcall FtpOneTransFileCB(const wstring& );
int __stdcall FtpFirstTransFileCB(const wstring& );
int __stdcall FtpSecondTransFileCB(const wstring& );


int __stdcall FtpTransMsgCB(EM_MSG_TYPE );
int __stdcall Ftp1TransMsgCB(EM_MSG_TYPE );
int __stdcall Ftp2TransMsgCB(EM_MSG_TYPE );

//////////////////////////////////////////////////////////////////////////

//传输信息回调
typedef void (* TransInfoCB)(const wstring& file, const wstring& info, int nPrecent);


#define FTP_TRANS_UNKONW -1
#define FTP_TRANS_BEGIN 0
#define FTP_TRANS_END 1


typedef queue<FTPInfo*> QueueLevel;

class CFtpMgr
{
	friend int __stdcall FtpOneTransFileCB(const wstring& );
	friend int __stdcall FtpFirstTransFileCB(const wstring& );
	friend int __stdcall FtpSecondTransFileCB(const wstring& );
	friend int __stdcall FtpTransMsgCB(EM_MSG_TYPE );
	friend int __stdcall Ftp1TransMsgCB(EM_MSG_TYPE );
	friend int __stdcall Ftp2TransMsgCB(EM_MSG_TYPE );
private:
	CFtpMgr(void);
	~CFtpMgr(void);

public:
	static CFtpMgr& Instance();

	//运行
	bool Run();

	void InitLevelEx();


	//是否有ftp可用
	bool IsFtpValid(){ return m_bFtpValid; }

	
	void Register(TransInfoCB tif){ m_transInfo = tif; }

	//////////////////////////////////////////////////////////////////////////
	//功能： 获取传送信息, 文件, 速度和百分比，调用一次会回调
	//////////////////////////////////////////////////////////////////////////
	void GetTransInfo();

private:
	//获取当前工作的FTP辅助类
	CFtpHelper& GetCurWorkFtp();

	int FtpOneTransFileFunc(const wstring& );
	int FtpFirstTransFileFunc(const wstring& );
	int FtpSecondTransFileFunc(const wstring& );

	int FtpTransMsgFunc(EM_MSG_TYPE );
	int Ftp1TransMsgFunc(EM_MSG_TYPE );
	int Ftp2TransMsgFunc(EM_MSG_TYPE );

	//是否继续上传
	int IsContinueTrans(const wstring& strFile, const FTPInfo& ftpIf);

	//是否是重点视频
	bool IsIMPVideo(const wstring& strFile);
	//是否是视频文件
	bool IsVideoFile(const wstring& strFile);
	//是否为高清视频
	bool IsHDVideo(const wstring& strFile);

	//是否是高清（通过高清定义标识来判断)
	bool IsHD(int width, int height);

	//根据优先级判断是否要等待
	bool IsWait(const wstring& level);
private:
	//单机ftp
	CFtpHelper m_ftpOne;
	FTPInfo m_fiOne;
	//一级FTP
	CFtpHelper m_ftpFirst;
	FTPInfo m_fiFirst;
	//二级FTP
	CFtpHelper m_ftpSecond;
	FTPInfo m_fiSecond;

	//是否有ftp可用
	bool m_bFtpValid;

	//重要视频标志
	wstring m_strFlagIMP;
	//高清定义
	int m_nHDDef;


	CCriticalSection m_cs;
	//优先级
	vector<wstring> m_vecLevel;
	QueueLevel m_qLevel;

	TransInfoCB m_transInfo;
};

