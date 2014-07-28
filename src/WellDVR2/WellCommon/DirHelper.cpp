#include "StdAfx.h"
#include "DirHelper.h"
#include "CharSetHelper.h"
#include <io.h>

#include <shlwapi.h>//头文件

#include <list>
using namespace std;

CDirHelper::CDirHelper(void)
{
}

CDirHelper::~CDirHelper(void)
{
}

/***************************************************************************************
*描    述: 获取应用程序的当前目录
*
*参数列表:
*
*返 回 值:
*
*时间作者: created by yjt [2012/10/26 8:48]
*
*修改记录:
*
***************************************************************************************/
CString CDirHelper::GetCurrentPath()
{
	TCHAR szFilePath[MAX_PATH] = {0};
	GetModuleFileName(NULL,szFilePath,MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	return szFilePath;
}

/***************************************************************************************
*描    述: 获取应用程序目录
*
*参数列表:
*
*返 回 值:
*
*时间作者: created by yjt [2012/10/26 8:48]
*
*修改记录:
*
***************************************************************************************/
string CDirHelper::GetAppPath()
{
	wchar_t appPath[MAX_PATH] = {0};
	GetModuleFileName(NULL, appPath, MAX_PATH);
	string strAp = CCharSetHelper::w2c(appPath).c_str();
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];

	_splitpath(strAp.c_str(), drive, dir, NULL,NULL);
	strAp = drive;
	strAp += dir;
	return strAp;
}

/***************************************************************************************
*描    述:	创建目录
*				1. 已经存在返回true
*				2. 不存在，递归创建
*
*参数列表:
*
*返 回 值:
*
*时间作者: created by yjt [2012/10/26 9:06]
*
*修改记录:
*
***************************************************************************************/
bool CDirHelper::CreateDir(const CString& strPath)
{	
	CString strTmp(strPath);

	list<CString> dirs;
	dirs.push_back(strTmp);

	int i = strTmp.ReverseFind('\\');

	//查找每一级目录
	while(i > 0)
	{
		if(DirExits(strTmp))
			break;
		strTmp = strTmp.Mid(0, i);
		dirs.push_back(strTmp);
		i = strTmp.ReverseFind('\\');
	}

	try{
		//创建目录
		list<CString>::reverse_iterator itor = dirs.rbegin();
		for ( ; itor != dirs.rend(); ++itor)
		{
			::CreateDirectory((*itor), NULL);
		}
	}
	catch(...)
	{
		return false;
	}
	return true;	
}

/***************************************************************************************
*描    述: 判断目录是否存在
*
*参数列表:
*
*返 回 值:
*
*时间作者: created by yjt [2012/10/26 9:52]
*
*修改记录:
*
***************************************************************************************/
// bool CDirHelper::DirExits(const CString& strDir)
// {
// 	bool brlt = true;
// 	WIN32_FIND_DATA fd;
// 	HANDLE hd = FindFirstFile(strDir, &fd);
// 	if(hd == INVALID_HANDLE_VALUE && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
// 		brlt = false;
// 
// 	FindClose(hd);
// 	return brlt;
// }

bool CDirHelper::DirExits(const CString& strDir)
{
	if (PathFileExists(strDir))
	{
		return true;
	}
	return false;
}



/***************************************************************************************
*描    述:	获取指定路径下的所有文件名称列表
*				1. 文件夹忽略
*参数列表: strPath [IN]		--		指定路径 [d:\\test]
*				strFileType [IN]	--		文件的类型 [xml/jpg/ini ....]
*
*返 回 值:	vector<string>	--	文件名称列表
*
*时间作者: created by yjt [2012/11/28 16:49]
*
*修改记录:
*
***************************************************************************************/
vector<string> CDirHelper::GetPathFilesName(const CString& strPath, const CString& strFileType)
{
	CString strPathWid;
	strPathWid.Format(_T("%s\\*.%s"), strPath, strFileType);
	string strPW = W2C(strPathWid.GetBuffer(strPathWid.GetLength()));
	strPathWid.ReleaseBuffer();

	vector<string> vecFilesName;

	struct _finddata_t c_file;
	long hFile;
	if((hFile = _findfirst(strPW.c_str(), &c_file)) == -1L)
		return vecFilesName;
	
	do 
	{
		vecFilesName.push_back(c_file.name);
	} while (_findnext(hFile, &c_file) == 0);

	return vecFilesName;
}