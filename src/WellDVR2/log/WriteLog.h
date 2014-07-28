#pragma once

#include "stdafx.h"
#include <time.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>

#define _LOG_WRITE_STATE_ 1            /* 条件编译开关，1：写日志，0：不写日志 */

#define LOG_SUCCESS (0)
#define LOG_FAILED (-1)

#define LOG_BOOL_TRUE (1)
#define LOG_BOOL_FALSE (0)

#define DWORD_NULL (0xFFFFFFFF)

#define MAX_LOGTEXT_LEN (2048)         /* 每行日志的最大长度*/
#define MAX_FILE_PATH (255)            /* 日志文件路径的最大长度*/
#define MAX_LOG_FILE_SIZE (512 * 1024) /* 日志文件内容的最大长度*/
#define MAX_LOG_FILE_NAME_LEN (256)    /* 日志文件名的最大长度*/
#define LOG_TYPE_INFO    0             /* 日志类型: 信息类型*/

#define LOG_TYPE_ERROR   1             /* 日志类型: 错误类型*/

#define LOG_TYPE_SYSTEM 2             /* 日志类型: 系统类型*/

#define TEST_CASE_MAX_FILE_LEN (1024)   /* 测试函数中文件内容最大长度*/

const TCHAR g_LogRootPath[] = _T(".//LOG"); /*日志文件根路径，由用户指定*/

#pragma pack(push, 1)

typedef struct tagLOG_DATA             /* 日志内容结构体*/
{
	TCHAR             strDate[11];   /* 日期:格式为如:2009-10-11*/
	TCHAR             strTime[9];    /* 时间:格式为如:16:10:57*/
	unsigned int iType;         /* 日志类型:3种:INFO(0)/ERROR(1)/SYSTEM(2)*/
	TCHAR             strText[MAX_LOGTEXT_LEN]; /*日志内容*/
	TCHAR			  strModel[20];	/*模块名*/			
	TCHAR			  strFile[50];		/*文件名*/
	unsigned int iLine;					/*行号*/
}LOG_DATA, *LPLOG_DATA;

#pragma pack(pop)

#define LOG(fmt, ...) CWriteLog::Instance().Write_Log(LOG_TYPE_INFO, _T("[WELLDVR          ]"), __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) CWriteLog::Instance().Write_Log(LOG_TYPE_ERROR, _T("[WELLDVR          ]"), __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOGS(fmt, ...) CWriteLog::Instance().Write_Log(LOG_TYPE_SYSTEM, _T("[WELLDVR          ]"), __FILE__, __LINE__, fmt, ##__VA_ARGS__)

class CWriteLog
{
private:
	CWriteLog(void);
	~CWriteLog(void);

	int Create_LogDir(const TCHAR *pStrPath);
	int Create_LogFile(const TCHAR *pStrFile, int iPos);
	int IsFileExist(const TCHAR *pStrFile);
	int GetLogPath(TCHAR *pStrPath);
	DWORD GetFileLenth(const TCHAR *pFile);
	int Write_Log_Text(LPLOG_DATA lpLogData);

public:
	static CWriteLog& Instance();

	void Write_Log(unsigned int uiLogType, TCHAR *pstrFmt, ...);
	void Write_Log(unsigned int uiLogType, TCHAR* pStrModel, TCHAR* pStrFile, unsigned int iLine, TCHAR *pstrFmt, ...);
	void Write_Log(unsigned int uiLogType, TCHAR* pStrModel, char* pStrFile, unsigned int iLine, TCHAR *pstrFmt, ...);
	void TestLogCase_One();

private:
	int GetLogFileName(int iLogType, const TCHAR *pStrPath, TCHAR *pStrName);
};

