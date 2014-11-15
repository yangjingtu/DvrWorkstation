//////////////////////////////////////////////////////////////////////////
//Describe： 定位配置文件 
//Date: create by yjt 2014-7-2
//History:
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "ConfigBase.h"

#include "../WellCommon/XmlHelper.h"

#define LOCATIONCONF CLocationConfig::Instance()

class CLocationConfig : public ConfigBase
{
private:
	CLocationConfig(void);
	~CLocationConfig(void);

public:
	static CLocationConfig& Instance();

	virtual void Init();
	virtual void InitFromFile();
	virtual void SaveToFile();

	void SaveDvrPos(const wstring& port, int wndIndex);
	//根据hub口获取窗口索引
	int GetWndIndex(const wstring& port);

protected:
	virtual CString GetConfigPath();
	virtual CString GetConfigBackUpPath();
private:
	CXmlHelper m_xml;
};

