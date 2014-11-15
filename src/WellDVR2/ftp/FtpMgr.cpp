#include "stdafx.h"
#include "FtpMgr.h"
#include "../config/Config.h"
#include "../ShareData.h"
#include "../WellCommon/AviHelper.h"
#include "../WellCommon/StringHelper.h"

typedef struct tagResolution
{
	int w;
	int h;
}Resolution,*PResolution;

Resolution g_resolution[] ={
	{176,144},
	{352,288},
	{720,576},
	{1280,720},
	{1280,960},
	{1920,1080}
};




CFtpMgr::CFtpMgr(void)
	: m_bFtpValid(false)
	, m_nHDDef(3)
{

}


CFtpMgr::~CFtpMgr(void)
{

}

CFtpMgr& CFtpMgr::Instance()
{
	static CFtpMgr ftp;
	return ftp;
}


bool CFtpMgr::Run()
{
	bool bRlt = false;

	CString strImp;
	//获取其它参数
	CONF.GetFtpSetting(strImp, m_nHDDef);
	m_strFlagIMP = strImp.GetString();

	m_vecLevel = CONF.GetFtpLevel();

	wstring strIp, strUser, strPwd;
	wstring strDir(SHAREDATA.g_strFilePath.GetBuffer());

	m_fiOne = CONF.GetFTPInfo(SEC_FTP_ONE);
	m_fiFirst = CONF.GetFTPInfo(SEC_FTP_FIRST);
	m_fiSecond = CONF.GetFTPInfo(SEC_FTP_SECOND);

	InitLevelEx();

#ifdef ONE_DVR
	//运行单机版的FTP服务
	if(m_fiOne.bEnable)
	{
		strIp = m_fiOne.strServ.GetString();
		strUser = m_fiOne.strUser.GetString();
		strPwd = m_fiOne.strPwd.GetString();

		bRlt = m_ftpOne.Start(strIp, strUser, strPwd, m_fiOne.nPort, strDir);
		if(bRlt)
		{
			RegCB cb;
			cb.tfCB = FtpOneTransFileCB;
			cb.ttNotify = FtpTransMsgCB;

			m_ftpOne.Register(cb);
			m_ftpOne.ServiceRun();
		}

		m_bFtpValid |= bRlt;
	}
#else
	//一级FTP服务
	if(m_fiFirst.bEnable)
	{
		strIp = m_fiFirst.strServ.GetString();
		strUser = m_fiFirst.strUser.GetString();
		strPwd = m_fiFirst.strPwd.GetString();
		bRlt = m_ftpFirst.Start(strIp, strUser, strPwd, m_fiFirst.nPort, strDir);
		if(bRlt)
		{
			RegCB cb;
			cb.tfCB = FtpFirstTransFileCB;
			cb.ttNotify = Ftp1TransMsgCB;

			m_ftpFirst.Register(cb);
			m_ftpFirst.ServiceRun();
		}
		m_bFtpValid |= bRlt; 
	}

	//二级FTP服务
	if(m_fiSecond.bEnable)
	{
		strIp = m_fiSecond.strServ.GetString();
		strUser = m_fiSecond.strUser.GetString();
		strPwd = m_fiSecond.strPwd.GetString();
		bRlt = m_ftpSecond.Start(strIp, strUser, strPwd, m_fiSecond.nPort, strDir);
		if(bRlt)
		{
			RegCB cb;
			cb.tfCB = FtpSecondTransFileCB;
			cb.ttNotify = Ftp2TransMsgCB;

			m_ftpSecond.Register(cb);
			m_ftpSecond.ServiceRun();
		}
		m_bFtpValid |= bRlt;
	}
#endif

	return m_bFtpValid;
}

void CFtpMgr::GetTransInfo()
{
	if(!m_bFtpValid)
	{
		m_transInfo(_T(""), _T("消息提示"), 0);
		return;
	}

	CFtpHelper& ftp = GetCurWorkFtp();

	//检查FTP传输百分比
	int nPrecent = ftp.GetTransPrecent() * 100;
	wstring strPutFile = ftp.GetPutFile();
	CString strInfo;
	
	if(!strPutFile.empty())
	{
		if(ftp == m_ftpOne)
			strPutFile = _T("[单机FTP]上传文件：") + strPutFile;
		else if(ftp == m_ftpFirst)
			strPutFile = _T("[一级FTP]上传文件：") + strPutFile;
		else if(ftp == m_ftpSecond)
			strPutFile = _T("[二级FTP]上传文件：") + strPutFile;
		strInfo.Format(_T("完成:%d%% %s"), nPrecent, ftp.GetTransSpeed().c_str());
	}
	else
	{
		strInfo = _T("消息提示");
		nPrecent = 0;
	}
	m_transInfo(strPutFile, strInfo.GetString(), nPrecent);
}

//////////////////////////////////////////////////////////////////////////
int __stdcall FtpOneTransFileCB(const wstring& strCurTransFile)
{
	return FTP_CLIENT.FtpOneTransFileFunc(strCurTransFile);
}

int __stdcall FtpFirstTransFileCB(const wstring& strCurTransFile)
{
	return FTP_CLIENT.FtpFirstTransFileFunc(strCurTransFile);
}

int __stdcall FtpSecondTransFileCB(const wstring& strCurTransFile)
{
	return FTP_CLIENT.FtpSecondTransFileFunc(strCurTransFile);
}

int __stdcall FtpTransMsgCB(EM_MSG_TYPE type)
{
	return FTP_CLIENT.FtpTransMsgFunc(type);
}

int __stdcall Ftp1TransMsgCB(EM_MSG_TYPE type)
{
	return FTP_CLIENT.Ftp1TransMsgFunc(type);
}

int __stdcall Ftp2TransMsgCB(EM_MSG_TYPE type)
{
	return FTP_CLIENT.Ftp2TransMsgFunc(type);
}

//////////////////////////////////////////////////////////////////////////

int CFtpMgr::FtpOneTransFileFunc(const wstring& strCurTransFile)
{
	int nRlt = IsContinueTrans(strCurTransFile, m_fiOne);
	if(nRlt == TRANS_CONTUNE)
	{
		//单机上传完成后删除文件
		return TRANS_DELETE;
	}
	return nRlt;
}

int CFtpMgr::FtpFirstTransFileFunc(const wstring& strCurTransFile)
{	
	return IsContinueTrans(strCurTransFile, m_fiFirst);
}

int CFtpMgr::FtpSecondTransFileFunc(const wstring& strCurTransFile)
{
	return IsContinueTrans(strCurTransFile, m_fiSecond);
}

int CFtpMgr::IsContinueTrans(const wstring& strFile, const FTPInfo& ftpIf)
{
	int nRlt = TRANS_SKIP;

	//视频文件处理
	if(IsVideoFile(strFile))
	{
		//传输重点视频
		if(ftpIf.bTransIMP && IsIMPVideo(strFile))
			nRlt = TRANS_CONTUNE;

		//传送高清视频
		if(ftpIf.bTransHD && IsHDVideo(strFile))
			nRlt = TRANS_CONTUNE;

		//传送标清视频
		if(ftpIf.bTransSD)
			nRlt = TRANS_CONTUNE;
	}
	
	if(nRlt == TRANS_CONTUNE)
		GetTransInfo();

	return nRlt;
}

bool CFtpMgr::IsVideoFile(const wstring& strFile)
{
	return ( strFile.rfind(_T(".AVI")) != wstring::npos || strFile.rfind(_T(".avi")) != wstring::npos );
}

bool CFtpMgr::IsIMPVideo(const wstring& strFile)
{
	return ( strFile.rfind(m_strFlagIMP) != wstring::npos );
}

bool CFtpMgr::IsHDVideo(const wstring& strFile)
{
	int width = 0;
	int height = 0;
	if( !CAviHelper::AVI_resolution(strFile, width, height) )
		return false;

	return IsHD(width, height);
}

bool CFtpMgr::IsHD(int width, int height)
{
	Resolution &rl = g_resolution[m_nHDDef];
	return (width >= rl.w && height >= rl.h);
}

int CFtpMgr::FtpTransMsgFunc(EM_MSG_TYPE type)
{
	int nRlt;
	switch(type)
	{
	case TRANS_BEGIN:

		while(IsWait(SEC_FTP_ONE))
		{
			Sleep(10);
		}

		m_transInfo(_T(""), _T("[单机FTP]开始传输!"), 0);
		Sleep(1000);

		nRlt = TRANS_CONTUNE;
		break;
	case TRANS_END:

		m_transInfo( _T(""), _T("[单机FTP]传输完成!"),0);
		
		m_cs.Lock();
		m_qLevel.pop();
		m_qLevel.push(&m_fiOne);
		m_cs.Unlock();

		//单机删除空文件夹
		nRlt = TRANS_DELETE;
		break;
	default:
		nRlt = TRANS_CONTUNE;
	}

	return nRlt;
}

int CFtpMgr::Ftp1TransMsgFunc(EM_MSG_TYPE type)
{
	int nRlt;
	switch(type)
	{
	case TRANS_BEGIN:
		while(IsWait(SEC_FTP_FIRST))
		{
			Sleep(10);
		}
		m_transInfo(_T(""), _T("[一级FTP]开始传输!"), 0);
		Sleep(1000);

		nRlt = TRANS_CONTUNE;
		break;
	case TRANS_END:
		m_transInfo(_T(""), _T("[一级FTP]传输完成!"), 0);

		m_cs.Lock();
		m_qLevel.pop();
		m_qLevel.push(&m_fiFirst);
		m_cs.Unlock();

		nRlt = TRANS_DELETE;
		break;
	default:
		nRlt = TRANS_CONTUNE;
	}

	return nRlt;
}

int CFtpMgr::Ftp2TransMsgFunc(EM_MSG_TYPE type)
{
	int nRlt;
	switch(type)
	{
	case TRANS_BEGIN:
		while(IsWait(SEC_FTP_SECOND))
		{
			Sleep(10);
		}

		m_transInfo(_T(""), _T("[二级FTP]开始传输!"), 0);
		Sleep(1000);

		nRlt = TRANS_CONTUNE;
		break;
	case TRANS_END:
		m_transInfo(_T(""), _T("[二级FTP]传输完成!"), 0);

		m_cs.Lock();
		m_qLevel.pop();
		m_qLevel.push(&m_fiSecond);
		m_cs.Unlock();

		nRlt = TRANS_DELETE;
		break;
	default:
		nRlt = TRANS_CONTUNE;
	}

	return nRlt;
}


//////////////////////////////////////////////////////////////////////////
//当前工作的FTP（和优先级有关系）
//
//////////////////////////////////////////////////////////////////////////
CFtpHelper& CFtpMgr::GetCurWorkFtp()
{
	FTPInfo* p = m_qLevel.front();
	if(p == &m_fiOne)
		return m_ftpOne;
	else if( p == &m_fiFirst )
		return m_ftpFirst;
	else if( p == &m_fiSecond )
		return m_ftpSecond;
}

//////////////////////////////////////////////////////////////////////////
//功能：判断指定的级别是否需要等待
//		1. 当前级别是否在队列的头部
//			如果不是就等待，如果是则无需等待
//		2. 当传完一次后出列，再入队
//参数：
//		level [IN]	--	级别["FTP","FTP1","FTP2"]
//返回：
//		true: 需要等待
//		false: 无需等待
//////////////////////////////////////////////////////////////////////////
bool CFtpMgr::IsWait(const wstring& level)
{
	m_cs.Lock();
	bool bRlt = false;
	if(level == SEC_FTP_ONE)
	{
		if(m_qLevel.front() != &m_fiOne)
			bRlt = true;
	}
	else if(level == SEC_FTP_FIRST)
	{
		if(m_qLevel.front() != &m_fiFirst)
			bRlt = true;
	}
	else if(level == SEC_FTP_SECOND)
	{
		if(m_qLevel.front() != &m_fiSecond)
			bRlt = true;
	}
	m_cs.Unlock();
	return bRlt;
}

//初始化级别扩展数据
void CFtpMgr::InitLevelEx()
{
	m_cs.Lock();
	for (int i = 0; i < m_vecLevel.size(); ++i)
	{
#ifdef ONE_DVR
		if(m_vecLevel[i] == SEC_FTP_ONE)
		{
			if(m_fiOne.bEnable)
				m_qLevel.push(&m_fiOne);
		}
#else
		if(m_vecLevel[i] == SEC_FTP_FIRST)
		{
			if(m_fiFirst.bEnable)
				m_qLevel.push(&m_fiFirst);
		}
		else 
		{
			if(m_fiSecond.bEnable)
				m_qLevel.push(&m_fiSecond);
		}
#endif

	}
	m_cs.Unlock();
}
