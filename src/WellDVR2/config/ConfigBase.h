//////////////////////////////////////////////////////////////////////////
//配置文件基类
//////////////////////////////////////////////////////////////////////////
#pragma once

class ConfigBase
{
public:
	ConfigBase(void);
	virtual ~ConfigBase(void);

	virtual void Init();
	virtual void InitFromFile();

	virtual void SaveToFile();

	//备份
	bool BackUp();
	//恢复
	bool Restore();

protected:
	virtual CString GetConfigPath();
	virtual CString GetConfigBackUpPath();

protected:
	CString GetAppPath();
};

