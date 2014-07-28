#include "stdafx.h"
#include "Config.h"
#include "ShareData.h"

Config& Config::Instance()
{
	static Config conf;
	return conf;
}

Config::Config(void)
{
	Init();
}


Config::~Config(void)
{
	UnInit();
}

void Config::InitDefConfig()
{
	//路径
	CString strSec = _T("FILE");
	CString strKey = _T("Target");
	CString strDef(_T("localhost"));
	m_Ini.WriteString(strSec, strKey, strDef);

	strKey = _T("Path");
	strDef = _T("d://well-data");
	m_Ini.ReadString(strSec, strKey, strDef);

	strSec = _T("PORT");
	strKey = _T("PortNum");
	int nDef = 0;
	m_Ini.WriteInt(strSec, strKey, nDef);

	//DB
	strSec = _T("DB");
	strKey = _T("host");
	strDef.Empty();
	m_Ini.WriteString(strSec, strKey, strDef);
	strDef = _T("1521");
	strKey = _T("port");
	m_Ini.WriteString(strSec, strKey, strDef);
	strKey = _T("sid");
	strDef = _T("orcl");
	m_Ini.WriteString(strSec, strKey, strDef);
	strKey = _T("uid");
	m_Ini.WriteString(strSec, strKey, strDef);
	strKey = _T("pwd");
	m_Ini.WriteString(strSec, strKey, strDef);
	strKey = _T("ConnectTime");
	strDef = _T("6");
	m_Ini.WriteString(strSec, strKey, strDef);
	strKey = _T("enable");
	strDef = _T("1");
	m_Ini.WriteString(strSec, strKey, strDef);

	//FTP
	WriteDefaultFtp(SEC_FTP_ONE, 1);
	WriteDefaultFtp(SEC_FTP_FIRST);
	WriteDefaultFtp(SEC_FTP_SECOND);

	//Trans Setting
	strSec = _T("TransSetting");
	strKey = _T("resolution");
	m_Ini.WriteString(strSec, strKey, _T("3"));
	strKey = _T("flag");
	m_Ini.WriteString(strSec, strKey, _T("IMP"));

	//////////////////////////////////////////////////////////////////////////
	//设备信息
	//////////////////////////////////////////////////////////////////////////
	//设备ID
	strSec = _T("DeviceInfo");
	strKey = _T("DeviceId");
	m_Ini.WriteString(strSec, strKey, _T("000000000000000001"));
}

void Config::Init()
{
	CString strFile(GetAppPath() + gc_Config);
	m_Ini.SetIniPathName(strFile);

	//恢复配置文件
	if(SHAREDATA.g_dbgLevel != LOCATION && !Restore())
	{
		InitDefConfig();
	}

	CFile theFile;
	CFileStatus status; 
	if( !CFile::GetStatus( strFile, status ) ) 
	{   
		InitDefConfig();
	} 
	
#ifdef ONE_DVR
//	m_Ini.WriteString(_T("FTP"), _T("enable"), _T("1"));
	m_Ini.WriteString(_T("FTP1"), _T("enable"), _T("0"));
	m_Ini.WriteString(_T("FTP2"), _T("enable"), _T("0"));
#else
	m_Ini.WriteString(_T("FTP"), _T("enable"), _T("0"));
//	m_Ini.WriteString(_T("FTP1"), _T("enable"), _T("1"));
//	m_Ini.WriteString(_T("FTP2"), _T("enable"), _T("1"));
#endif
}

void Config::UnInit()
{

}

bool Config::InitFromConfig()
{
	CString strSec, strKey, strDst, strDef;
	int nDef = 0;
	long lConnectTime = 0;
	int num = 0;

	strSec = _T("FILE");
	strKey = _T("Target");
	SHAREDATA.g_strFileTarget = m_Ini.ReadString(strSec, strKey, strDef);
	if( SHAREDATA.g_strFileTarget.IsEmpty() )
		SHAREDATA.g_strFileTarget = _T("localhost");
	strKey = _T("Path");
	SHAREDATA.g_strFilePath = m_Ini.ReadString(strSec, strKey, strDef);
	if( SHAREDATA.g_strFilePath.IsEmpty() )
	{
		SHAREDATA.g_strFilePath = gc_DefaultSavePath;
	}	

	DeviceInfo di = GetDeviceInfo();
	SHAREDATA.g_strDeviceId = di.strId;

	WebInfo wi = GetWebInfo();
	SHAREDATA.g_strWebIp = wi.strIp;
	SHAREDATA.g_nWebPort = wi.nPort;

	return true;
}

DBInfo Config::GetDBInfo()
{
	DBInfo dbi;

	CString strSec, strKey, strDef;
	int nDef = 0;

	// Connect to local db
	strSec = _T("DB");
	strKey = _T("ConnectTime");
	dbi.lConnTime = m_Ini.ReadInt(strSec, strKey, nDef);

	strKey = _T("pwd");
	dbi.strPwd = m_Ini.ReadString(strSec, strKey, strDef);

	strKey = _T("uid");
	dbi.strUser = m_Ini.ReadString(strSec, strKey, strDef);

	strKey = _T("host");
	dbi.strHost = m_Ini.ReadString(strSec, strKey, strDef);

	strKey = _T("port");
	nDef = 1521;
	dbi.nPort = m_Ini.ReadInt(strSec, strKey, nDef);

	strKey = _T("sid");
	strDef = _T("orcl");
	dbi.strSid = m_Ini.ReadString(strSec, strKey, strDef);

	strKey = _T("enable");
	dbi.bEnable = m_Ini.ReadInt(strSec, strKey, 0);

	return dbi;
}

FTPInfo Config::GetFTPInfo(const CString& strSec)
{
	FTPInfo ftpi;

	ftpi.bEnable = m_Ini.ReadInt(strSec, _T("enable"), 0);
	ftpi.strServ = m_Ini.ReadString(strSec, _T("serv"), _T(""));
	ftpi.nPort = m_Ini.ReadInt(strSec, _T("port"), 21);
	ftpi.strUser = m_Ini.ReadString(strSec, _T("user"), _T(""));
	ftpi.strPwd = m_Ini.ReadString(strSec, _T("pwd"), _T(""));
	ftpi.bTransIMP = m_Ini.ReadInt(strSec, _T("transimp"), 0);
	ftpi.bTransHD = m_Ini.ReadInt(strSec, _T("transhd"), 0);
	ftpi.bTransSD = m_Ini.ReadInt(strSec, _T("transsd"), 0);
	
	return ftpi;
}

DeviceInfo Config::GetDeviceInfo()
{
	DeviceInfo info;

	CString strSec(_T("DeviceInfo"));
	CString strKey(_T("DeviceId"));

	info.strId = m_Ini.ReadString(strSec, strKey, _T("000000000000000001"));
	return info;
}

WebInfo Config::GetWebInfo()
{
	WebInfo wi;
	CString strSec(_T("WEB"));
	CString strKey(_T("ip"));
	wi.strIp = m_Ini.ReadString(strSec, strKey, _T("127.0.0.1"));
	strKey = _T("port");
	wi.nPort = m_Ini.ReadInt(strSec, strKey, 0);

	return wi;
}

void Config::WriteDefaultFtp(const CString& strSec, int type)
{
	m_Ini.WriteString(strSec, _T("serv"), _T(""));
	m_Ini.WriteString(strSec, _T("user"), _T(""));
	m_Ini.WriteString(strSec, _T("pwd"), _T(""));
	m_Ini.WriteString(strSec, _T("port"), _T("21"));	
	if(type != 0) //单机
	{
#ifdef ONE_DVR
	m_Ini.WriteString(strSec, _T("enable"), _T("1"));
	m_Ini.WriteString(strSec, _T("transimp"), _T("1"));
	m_Ini.WriteString(strSec, _T("transihd"), _T("1"));
	m_Ini.WriteString(strSec, _T("transisd"), _T("1"));
#else
	m_Ini.WriteString(strSec, _T("enable"), _T("0"));
	m_Ini.WriteString(strSec, _T("transimp"), _T("0"));
	m_Ini.WriteString(strSec, _T("transhd"), _T("0"));
	m_Ini.WriteString(strSec, _T("transsd"), _T("0"));
#endif
	}
	else
	{
		m_Ini.WriteString(strSec, _T("enable"), _T("0"));
		m_Ini.WriteString(strSec, _T("transimp"), _T("0"));
		m_Ini.WriteString(strSec, _T("transhd"), _T("0"));
		m_Ini.WriteString(strSec, _T("transsd"), _T("0"));
	}
}

void Config::GetFtpSetting(CString& strImp, int& nHDDef)
{
	CString strKey = _T("resolution");
	nHDDef = m_Ini.ReadInt(_T("TransSetting"), strKey, 3);
	strKey = _T("flag");
	strImp = m_Ini.ReadString(_T("TransSetting"), strKey, _T("IMP"));
}

vector<wstring> Config::GetFtpLevel()
{
	vector<wstring> vec;
	CString strImp = m_Ini.ReadString(_T("TransSetting"), _T("level1"), _T("FTP"));
	vec.push_back(strImp.GetString());
	strImp = m_Ini.ReadString(_T("TransSetting"), _T("level2"), _T("FTP1"));
	vec.push_back(strImp.GetString());
	strImp = m_Ini.ReadString(_T("TransSetting"), _T("level3"), _T("FTP2"));
	vec.push_back(strImp.GetString());
	return vec;
}

CString Config::GetConfigPath()
{
	return GetAppPath() + gc_Config;
}

CString Config::GetConfigBackUpPath()
{
	return GetAppPath() + gc_Config_BackUp;
}