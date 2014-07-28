#include "stdafx.h"
#include "LocationConfig.h"
#include "USBCtrl/UsbHelper.h"
#include "DataDef.h"

#include <sstream>
using namespace std;

CLocationConfig::CLocationConfig(void)
{
}


CLocationConfig::~CLocationConfig(void)
{
}

CLocationConfig& CLocationConfig::Instance()
{
	static CLocationConfig lc;
	return lc;
}

//初始时把hub信息写到配置文件中
void CLocationConfig::Init()
{
	bool bLoad = m_xml.Load((GetAppPath() + gc_LocationConfig).GetString(), true);
	if(!bLoad)
	{
		return;
	}

	wstring strNodePath(_T("root\\location\\"));

	MapUsb mapUsb = USBHUB.GetUsbPort_DiskName();
	MapUsbItor it = mapUsb.begin();
	for( ; it != mapUsb.end(); ++it)
	{
		m_xml.SetNodeValue(strNodePath + (*it).first, _T(""));
	}

	m_xml.Save((GetAppPath() + gc_LocationConfig).GetString());
}

void CLocationConfig::InitFromFile()
{
	m_xml.Load((GetAppPath() + gc_LocationConfig).GetString(), true);
}

void CLocationConfig::SaveToFile()
{
	m_xml.Save(_T(""));
}

void CLocationConfig::SaveDvrPos(const wstring& port, int wndIndex)
{
	wstring strNodePath(_T("root\\location\\"));
	wstringstream str;
	str << wndIndex;
	m_xml.SetNodeValue(strNodePath + port, str.str());

	m_xml.Save(_T(""));
}

int CLocationConfig::GetWndIndex(const wstring& port)
{
	wstring strNodePath(_T("root\\location\\") + port);
	wstring strWndIndex = m_xml.GetNodeValue(strNodePath);
	if(strWndIndex.empty())
		return -1;

	wistringstream is(strWndIndex);
	int nIndex = 0;
	is >> nIndex;

	return nIndex;
}


CString CLocationConfig::GetConfigPath()
{
	return GetAppPath() + gc_LocationConfig;
}

CString CLocationConfig::GetConfigBackUpPath()
{
	return GetAppPath() + gc_LocationConfig_BackUp;
}