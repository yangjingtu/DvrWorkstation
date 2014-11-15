/************************************************************************/
//Describe: 配置文件类
//DateTime: created by yjt 2014-05-13
//Note:
//		1. 检查配置文件是否存在
//			1.1 不存在则创建
//			1.2 写入默认项
//		
/************************************************************************/
#pragma once
#include "../DataDef.h"
#include "../WellCommon/IniFile.h"
#include "ConfigBase.h"

#define SEC_FTP_ONE _T("FTP")
#define SEC_FTP_FIRST _T("FTP1")
#define SEC_FTP_SECOND _T("FTP2")

#define CONF Config::Instance()

class Config : public ConfigBase
{
private:
	Config(void);
	~Config(void);
	
public:
	static Config& Instance();

	//从配置文件中初始化
	bool InitFromConfig();

	DeviceInfo GetDeviceInfo();
	WebInfo GetWebInfo();
	DBInfo GetDBInfo();
	FTPInfo GetFTPInfo(const CString& strSec);
	int GetDvrType();

	SoftWareInfo GetSWInfo();
	SettingInfo GetSettingInfo();

	void GetFtpSetting(CString& strImp, int& nHDDef);
	vector<wstring> GetFtpLevel();

protected:
	virtual CString GetConfigPath();
	virtual CString GetConfigBackUpPath();
private:
	void Init();
	void UnInit();
	void InitDefConfig();
	void InitSWInfo();
	void InitSettingInfo();

	void WriteDefaultFtp(const CString& strSec, int type = 0);

private:
	CIniFile m_Ini;
};

