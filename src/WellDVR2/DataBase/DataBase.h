/************************************************************************/
/* 数据库操作类                                                                     */
/************************************************************************/
#pragma once

#include <vector>
using namespace std;

#include "DBHelper.h"

#include "../DataDef.h"
#include <map>
using namespace std;

typedef map<CString, CString> MapDvrIdName;
typedef MapDvrIdName::iterator MapDvrIdNameItor;

#define DB CDataBase::Instance()

class CDataBase
{
private:
	CDataBase(void);
	~CDataBase(void);

public:
	static CDataBase& Instance();

	//通过警员ID获取名称
	CString GetNameFormID(const CString& id);
	//通过id去查名称(实时更新)
	CString QueryNameFormID(const CString& id);

	//插入媒体数据
	BOOL InsertMediaInfo(const DVRMEDIA_INFO& info);

	BOOL InsertDvrLog(const DVR_DEVICE_LOG& ddlog);

	BOOL InsertLog(const TERMINAL_DEV_LOG& telog);

	BOOL InsertStatus(const TERMINAL_STATE& ts);

	BOOL QueryIpPortByDevId(const wstring& devId,  wstring& ftpip, wstring& ftpport, wstring& iisIp, wstring& iisPort);

private:
	BOOL Init();
	void UnInit();
	
	//用户列表
	void InitUserRec();
	void FillUserVector(_RecordsetPtr record);



private:
	CDBHelper m_db;

	MapDvrIdName mapDvr;
};

