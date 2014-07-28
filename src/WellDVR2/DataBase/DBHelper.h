//////////////////////////////////////////////////////////////////////////
//Describe: 数据库操作辅助类
//			1. 封装ADO对数据库的操作
//			注：
//				a. 字段为空的" "(注意空值不能为空)，否则会出现“参数不一致或不完整"
//				b. 参数的顺序必须一致，即不能用map（自动排序)
//Date: created by yjt 2014-07-03
//History:
//////////////////////////////////////////////////////////////////////////
#pragma once

//把 msado15.dll 改为  msado60.tlb
//1. 更改了数据库创建connect时 返回 E_NOINTERFACE的问题

//2. 注意：
//		安装路径不能有英文的括号，这个和oracle有冲突，会连不上数据库
// #import "c:\program files\common files\system\ado\msado60.tlb" \
// 	no_namespace \
// 	rename ("EOF", "adoEOF")

#ifdef _WIN64
#define TLB_FILE_NAME "..\..\..\bin\msado60_x64.tlb"
#else
#define TLB_FILE_NAME "..\..\..\bin\msado60_i386.tlb"
#endif
#import TLB_FILE_NAME no_namespace rename("EOF", "adoEOF")

#include <string>
#include <map>
#include <vector>
using namespace std;

typedef struct tagFieldInfo{
	wstring strName;
	DataTypeEnum emType;
	ParameterDirectionEnum pType;
	int nLen;
	wstring strValue;
}FieldInfo, * PFieldInfo;

//存储过程参数
typedef vector<FieldInfo> VecParams;
typedef VecParams::const_iterator VecParamsItor;

class CDBHelper
{
public:
	CDBHelper(void);
	~CDBHelper(void);

	//初始化
	BOOL Init(const wstring& strConnString);
	void UnInit();

	//是否连接
	BOOL IsConnect();
	
	//获取错误信息
	wstring GetLastError() const { return m_strErrMsg; }

	//////////////////////////////////////////////////////////////////////////
	//查询sql语言
	_RecordsetPtr Query(const wstring& strSql);

	//执行存储过程 -- 这个是没有结果集的
	bool ExecProc(const wstring& procName, const VecParams& params);

	//执行存储过程 -- 这个是有结果集的
	_RecordsetPtr ExecProcEx(const wstring& procName, const VecParams& params);

	//////////////////////////////////////////////////////////////////////////
private:
	_ConnectionPtr	m_pConnection;
	_RecordsetPtr m_pUserRecSet;
	_CommandPtr m_pCmd;

	wstring m_strConn;			//连接串

	BOOL m_bConnectDB;			//是否连接

	wstring m_strErrMsg;		//错误信息
};

