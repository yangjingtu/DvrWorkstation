#include "stdafx.h"
#include "WriteLog.h"


CWriteLog::CWriteLog(void)
{
}


CWriteLog::~CWriteLog(void)
{
}

CWriteLog& CWriteLog::Instance()
{
	static CWriteLog log;
	return log;
}

// 
// int main(int argc, char* argv[])
// {
// 	Write_Log(LOG_TYPE_SYSTEM, "Program begin.");
// 	TestLogCase_One();
// 	Write_Log(LOG_TYPE_SYSTEM, "Program end.");
// 
// 	return 0;
// }

/*********************************************************************
* 函数名称:void TestLogCase_One()
* 说明:简单的测试函数，读文件
* 调用者：main
* 输入参数:
* 无
* 输出参数：
* 无
* 返回值:
* void --
*********************************************************************/
void CWriteLog::TestLogCase_One()
{
	FILE *pFile = NULL;
	TCHAR *pFieldContent = NULL;
	TCHAR szFileName[] = _T("test_case.txt");

	pFieldContent = (TCHAR *)malloc(TEST_CASE_MAX_FILE_LEN);
	if(NULL == pFieldContent)
	{
		Write_Log(LOG_TYPE_ERROR, _T("malloc memory failed,program exit!"));
		return;
	}

	memset(pFieldContent, 0, TEST_CASE_MAX_FILE_LEN);

	Write_Log(LOG_TYPE_INFO, _T("malloc memory for pFiled successful,memory size is: %ld"),
		TEST_CASE_MAX_FILE_LEN);

	Write_Log(LOG_TYPE_INFO, _T("测试中文写入"),
		TEST_CASE_MAX_FILE_LEN);

	pFile = _tfopen(szFileName, _T("r"));
	if(NULL == pFile)
	{
		fprintf(stderr, "open file failed.");
		Write_Log(LOG_TYPE_ERROR, _T("Open file %s failed. program exit!"), szFileName);
		return;
	}

	Write_Log(LOG_TYPE_INFO, _T("Open file %s successful."), szFileName);

	fread(pFieldContent, 1, TEST_CASE_MAX_FILE_LEN, pFile);
	pFieldContent[TEST_CASE_MAX_FILE_LEN -1] = '\0';

	fclose(pFile);
	printf("The file %s content is: \n%s\n", szFileName, pFieldContent);
	Write_Log(LOG_TYPE_INFO, _T("The file %s content is: \n%s\n"), szFileName, pFieldContent);

}

/*********************************************************************
* 函数名称:void Write_Log(unsigned int uiLogType, char *pstrFmt, ...)
* 说明:日志写函数，支持变长参数
* 调用者：任何需要写日志的地方
* 输入参数:
* unsigned iType -- 日志类别
* char *pstrFmt -- 日志内容
* ...            -- 变长参数
* 输出参数：
* 无
* 返回值:
* void --
*********************************************************************/
void CWriteLog::Write_Log(unsigned int uiLogType, TCHAR *pstrFmt, ...)
{
#if _LOG_WRITE_STATE_   /* 写日志与否的编译开关*/

	LOG_DATA data;

	time_t curTime;
	struct tm *mt;
	va_list v1;
	memset(&data, 0, sizeof(LOG_DATA));
	va_start(v1, pstrFmt);
	_vsntprintf(data.strText, MAX_LOGTEXT_LEN, pstrFmt, v1);
	va_end(v1);
	data.iType = uiLogType;
	curTime = time(NULL);
	mt = localtime(&curTime);
	_tcsftime(data.strDate, sizeof(data.strDate), _T("%Y-%m-%d"), mt);
	_tcsftime(data.strTime, sizeof(data.strTime), _T("%H:%M:%S"), mt);
	Write_Log_Text(&data);
#endif _LOG_WRITE_STATE_
}


void CWriteLog::Write_Log(unsigned int uiLogType, TCHAR* pStrModel, TCHAR* pStrFile, unsigned int iLine, TCHAR *pstrFmt, ...)
{
#if _LOG_WRITE_STATE_   /* 写日志与否的编译开关*/

	LOG_DATA data;

	time_t curTime;
	struct tm *mt;
	va_list v1;
	memset(&data, 0, sizeof(LOG_DATA));
	va_start(v1, pstrFmt);
	_vsntprintf(data.strText, MAX_LOGTEXT_LEN, pstrFmt, v1);
	va_end(v1);
	data.iType = uiLogType;
	curTime = time(NULL);
	mt = localtime(&curTime);
	_tcsftime(data.strDate, sizeof(data.strDate), _T("%Y-%m-%d"), mt);
	_tcsftime(data.strTime, sizeof(data.strTime), _T("%H:%M:%S"), mt);

	_tcscat(data.strModel, pStrModel);
	_tcscat(data.strFile, pStrFile);
	data.iLine = iLine;
	
	Write_Log_Text(&data);
#endif _LOG_WRITE_STATE_
}


void CWriteLog::Write_Log(unsigned int uiLogType, TCHAR* pStrModel, char* pStrFile, unsigned int iLine, TCHAR *pstrFmt, ...)
{
#if _LOG_WRITE_STATE_   /* 写日志与否的编译开关*/

	LOG_DATA data;

	time_t curTime;
	struct tm *mt;
	va_list v1;
	memset(&data, 0, sizeof(LOG_DATA));
	va_start(v1, pstrFmt);
	_vsntprintf(data.strText, MAX_LOGTEXT_LEN, pstrFmt, v1);
	va_end(v1);
	data.iType = uiLogType;
	curTime = time(NULL);
	mt = localtime(&curTime);
	_tcsftime(data.strDate, sizeof(data.strDate), _T("%Y-%m-%d"), mt);
	_tcsftime(data.strTime, sizeof(data.strTime), _T("%H:%M:%S"), mt);

	_tcscat(data.strModel, pStrModel);

	//转成TCHAR
	int len = strlen(pStrFile);
	wchar_t * pUnicode = new  wchar_t[ len + 1];  
	memset(pUnicode,0,(len +1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_ACP, 0, pStrFile, -1, (LPWSTR)pUnicode, len );  
	_tcscat(data.strFile, pUnicode);
	delete[] pUnicode;
	pUnicode = NULL;

	data.iLine = iLine;

	Write_Log_Text(&data);
#endif _LOG_WRITE_STATE_
}

/*********************************************************************
* 函数名称:int GetLogPath(char *pStrPath)
* 说明:获取日志文件路径
* 调用者：Write_Log_Text
* 输入参数:
* 无
* 输出参数：
* char *pStrPath
* 返回值:
* int -- LOG_FAILED: 失败
*      -- LOG_SUCCESS: 成功
*********************************************************************/
int CWriteLog::GetLogPath(TCHAR *pStrPath)
{
	if(NULL == pStrPath)
	{
		return LOG_FAILED;
	}
	int iRet = 0;
	time_t curTime = time(NULL);
	struct tm *mt = localtime(&curTime);
	/* 根据日期组成文件夹名称*/
	_stprintf(pStrPath, _T("%s\\%s\\%d%02d%02d"), GetAppPath(), g_LogRootPath, mt->tm_year + 1900, mt->tm_mon + 1, mt->tm_mday);
	iRet = Create_LogDir(pStrPath);

	return iRet;
}

/*********************************************************************
* 函数名称:int GetLogFileName(int iLogType, const char *pStrPath, char *pStrName)
* 说明:获取日志文件名
* 调用者：Write_Log_Text
* 输入参数:
* int iLogType         -- 日志类型 3种:INFO(0)/ERROR(1)/SYSTEM(2)
* const char *pStrPath -- 日志路径 由GetLogPath得到
* 输出参数：
* char *pStrName       -- 日志文件名
* 返回值:
* int -- LOG_FAILED: 失败
*      -- LOG_SUCCESS: 成功
*********************************************************************/
int CWriteLog::GetLogFileName(int iLogType, const TCHAR *pStrPath, TCHAR *pStrName)
{
	if(NULL == pStrPath)
	{
		return LOG_FAILED;
	}
	TCHAR szLogName[MAX_FILE_PATH];
	FILE *pFile = NULL;
	memset(szLogName, 0, MAX_FILE_PATH);
	switch (iLogType)
	{
	case LOG_TYPE_INFO:
		_stprintf(szLogName, _T("%s\\app_info"), pStrPath);
		break;
	case LOG_TYPE_ERROR:
		_stprintf(szLogName, _T("%s\\app_error"), pStrPath);
		break;
	case LOG_TYPE_SYSTEM:
		_stprintf(szLogName, _T("%s\\app_system"), pStrPath);
		break;
	default:
		return LOG_FAILED;
		break;
	}
	_tcscat(szLogName, _T(".log"));
	if(IsFileExist(szLogName))
	{
		/* 如果文件长度大于指定的最大长度，重新创建一文件，覆盖原文件*/
		if((int)GetFileLenth(szLogName) + 256 >= MAX_LOG_FILE_SIZE)
		{
			Create_LogFile(szLogName, 0);
		}
	}
	else
	{
		Create_LogFile(szLogName, 0);
	}
	_stprintf(pStrName, _T("%s"), szLogName);
	return LOG_SUCCESS;
}

/*********************************************************************
* 函数名称:int Create_LogDir(const char *pStrPath)
* 说明:创建日志存放路径
* 调用者：GetLogPath
* 输入参数:
* const char *pStrPath --用户指定的根路径
* 输出参数：
* 无
* 返回值:
* int -- LOG_FAILED: 失败
*      -- LOG_SUCCESS: 成功
*********************************************************************/
int CWriteLog::Create_LogDir(const TCHAR *pStrPath)
{
	if(NULL == pStrPath)
	{
		return LOG_FAILED;
	}
	int iRet = 0;
	TCHAR szSub[MAX_FILE_PATH];
	TCHAR *pSub = NULL;
	int iIndex = 0;
	int iLen = 0;
	int bFind = 0;
	memset(szSub, 0, sizeof(MAX_FILE_PATH));
	/* 逐层创建目录*/
	while(1)
	{
		pSub = (TCHAR*)_tcschr(pStrPath + iLen, _T('\\'));
		if(NULL == pSub)
		{
			if(iLen == 0)
			{
				return LOG_FAILED;
			}
			iRet = CreateDirectory(pStrPath, NULL);
			if(0 == iRet)
			{
				iRet = GetLastError();
				if(ERROR_ALREADY_EXISTS == iRet)
				{
					return LOG_SUCCESS;
				}
				return LOG_FAILED;
			}
			return LOG_SUCCESS;
		}
		else
		{
			if (!bFind)
			{
				bFind = 1;
			}
			else
			{
				memset(szSub, 0, sizeof(szSub));
				_tcsncpy(szSub, pStrPath, pSub - pStrPath);
				CreateDirectory(szSub, NULL);
			}
			iLen = pSub - pStrPath + 1;
		}
	}
	return LOG_SUCCESS;
}

/*********************************************************************
* 函数名称:int Create_LogFile(const char *pStrFile, int iPos)
* 说明:创建日志文件
* 调用者：GetLogFileName
* 输入参数:
* const char *pStrFile --文件名
* int iPos             --文件指针位置
* 输出参数：
* 无
* 返回值:
* int -- LOG_FAILED: 失败
*      -- LOG_SUCCESS: 成功
*********************************************************************/
int CWriteLog::Create_LogFile(const TCHAR *pStrFile, int iPos)
{
	HANDLE hd = 0;
	int iRet = 0;
	if(NULL == pStrFile)
	{
		return LOG_FAILED;
	}
	hd = CreateFile(pStrFile,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(INVALID_HANDLE_VALUE == hd)
	{
		return LOG_FAILED;
	}
	if(DWORD_NULL == SetFilePointer(hd, iPos, NULL, FILE_BEGIN))
	{
		return LOG_FAILED;
	}
	iRet = SetEndOfFile(hd);
	CloseHandle(hd);
	return iRet;
}

/*********************************************************************
* 函数名称:int IsFileExist(const char *pStrFile)
* 说明:判断指定的文件是否存在
* 调用者：GetLogFileName
* 输入参数:
* const char *pStrFile --文件名
* 输出参数：
* 无
* 返回值:
* int -- LOG_BOOL_FALSE: 不存在
*      -- LOG_BOOL_TRUE: 存在
*********************************************************************/
int CWriteLog::IsFileExist(const TCHAR *pStrFile)
{
	int iLen = 0;
	WIN32_FIND_DATA finddata;
	memset(&finddata, 0, sizeof(WIN32_FIND_DATA));
	HANDLE hd = FindFirstFile(pStrFile, &finddata);
	if(INVALID_HANDLE_VALUE == hd)
	{
		DWORD dwRet = GetLastError();
		if(ERROR_FILE_NOT_FOUND == dwRet || ERROR_PATH_NOT_FOUND == dwRet)
		{
			return LOG_BOOL_FALSE;
		}
	}
	FindClose(hd);
	return LOG_BOOL_TRUE;
}

/*********************************************************************
* 函数名称:DWORD GetFileLenth(const char *pFile)
* 说明:判断指定的文件大小
* 调用者：GetLogFileName
* 输入参数:
* const char *pFile --文件名
* 输出参数：
* 无
* 返回值:
* DWORD -- 文件大小
*********************************************************************/
DWORD CWriteLog::GetFileLenth(const TCHAR *pFile)
{
	WIN32_FIND_DATA buff;
	HANDLE hd = NULL;
	memset(&buff, 0, sizeof(WIN32_FIND_DATA));
	hd = FindFirstFile(pFile, &buff);
	FindClose(hd);
	return (buff.nFileSizeHigh * MAXDWORD) + buff.nFileSizeLow;
}

/*********************************************************************
* 函数名称:int Write_Log_Text(LPLOG_DATA lpLogData)
* 说明:写日志内容
* 调用者：Write_Log
* 输入参数:
* LPLOG_DATA lpLogData --日志内容结构体量
* 输出参数：
* 无
* 返回值:
* int -- LOG_FAILED: 失败
*      -- LOG_SUCCESS: 成功
*********************************************************************/
int CWriteLog::Write_Log_Text(LPLOG_DATA lpLogData)
{
	TCHAR szFilePath[MAX_FILE_PATH];
	TCHAR szFileName[MAX_LOG_FILE_NAME_LEN];
	FILE *pFile = NULL;
	TCHAR szLogText[MAX_LOGTEXT_LEN];
	memset(szFilePath, 0, MAX_FILE_PATH);
	memset(szFileName, 0, MAX_LOG_FILE_NAME_LEN);
	memset(szLogText, 0, MAX_LOGTEXT_LEN);
	GetLogPath(szFilePath);
	GetLogFileName(lpLogData->iType, szFilePath, szFileName);
	pFile = _tfopen(szFileName, _T("a+"));
	if(NULL == pFile)
	{
		return LOG_FAILED;
	}
	_stprintf(szLogText, _T("%s[%s %s] %s   -----  [%s][%d]\n"), lpLogData->strModel, lpLogData->strDate, lpLogData->strTime, lpLogData->strText, lpLogData->strFile, lpLogData->iLine);

	//fwrite(szLogText, 1, _tcslen(szLogText), pFile);
	//acsii 的方式， unicode写入乱码
	int len = _tcslen(szLogText);
	char* pchBuffer = new char[len * 2 + 1];
	int a = WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)szLogText, -1, LPSTR(pchBuffer), len*2 + 1, NULL, FALSE);//Unicode转换为ANSI，a的值包括了字符串最后的0
	fwrite(pchBuffer, 1, a - 1, pFile);
	delete[] pchBuffer;
	pchBuffer = NULL;

	fclose(pFile);
	return LOG_SUCCESS;
}