#include "stdafx.h"
#include "ConfigBase.h"
#include "FileBackUp.h"

ConfigBase::ConfigBase(void)
{
}


ConfigBase::~ConfigBase(void)
{
}

CString ConfigBase::GetAppPath()
{
	CString path;   
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH),MAX_PATH);   
	int pos = path.ReverseFind('\\');
	path = path.Mid(0, pos);
	return path;
}

CString ConfigBase::GetConfigPath()
{
	return _T("");
}

CString ConfigBase::GetConfigBackUpPath()
{
	return _T("");
}

void ConfigBase::Init()
{

}

void ConfigBase::InitFromFile()
{

}

void ConfigBase::SaveToFile()
{

}


//////////////////////////////////////////////////////////////////////////
//在定位完成后，备份数据配置文件
//关闭软件时备份一下（设置后不会生效）
//////////////////////////////////////////////////////////////////////////
bool ConfigBase::BackUp()
{
	CString strFile(GetConfigPath());
	CString strFileBack(GetConfigBackUpPath());
	SetFileAttributes(strFileBack,FILE_ATTRIBUTE_NORMAL);
	bool bRlt = CFileBackUp::BackUp(strFile.GetString(), strFileBack.GetString());
	DWORD dw = 0;
	if(bRlt)
		//设置备份文件隐藏
		SetFileAttributes(strFileBack,FILE_ATTRIBUTE_HIDDEN);
	else
		dw = GetLastError();
	return bRlt;
}

//////////////////////////////////////////////////////////////////////////
//每次启动完成后恢复配置文件
//////////////////////////////////////////////////////////////////////////
bool ConfigBase::Restore()
{
	CString strFile(GetConfigPath());
	CString strFileBack(GetConfigBackUpPath());
	SetFileAttributes(strFileBack,FILE_ATTRIBUTE_NORMAL);
	wstring sf = strFile.GetBuffer();
	wstring sfb = strFileBack.GetBuffer();
	bool bRtl = CFileBackUp::BackUp( sfb, sf);
	SetFileAttributes(strFileBack,FILE_ATTRIBUTE_HIDDEN);
	return bRtl;
}