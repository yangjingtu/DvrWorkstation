/********************************************************************
	created:	2012/10/26 8:46  
	filename: 	DirHelper.h
	author:		yjt
	purpose:		目录辅助类
*********************************************************************/
#pragma once

#define IVS_COMM_EXPORTS

#ifdef IVS_COMM_EXPORTS
#define IVS_COMM_API __declspec(dllexport)
#else 
#define IVS_COMM_API __declspec(dllimport)
#endif

#include <vector>
#include <string>
using namespace std;

class IVS_COMM_API CDirHelper
{
public:
	CDirHelper(void);
	~CDirHelper(void);

	//获取当前目录--应用程序
	static CString GetCurrentPath();

	//获取应用程序路径
	static string GetAppPath();

	//创建目录
	static bool CreateDir(const CString& strPath);

	//判断目录是否存在
	static bool DirExits(const CString& strDir);

	//获取目录下的指定类型的文件名列表
	static vector<string> GetPathFilesName(const CString& strPath, const CString& strFileType);
};
