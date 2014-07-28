#include "stdafx.h"
#include "DBHelper.h"
#include <sstream>
using namespace std;

CDBHelper::CDBHelper(void)
	: m_bConnectDB(FALSE)
	, m_pConnection(NULL)
	, m_pUserRecSet(NULL)
	, m_pCmd(NULL)
{

}


CDBHelper::~CDBHelper(void)
{

}

BOOL CDBHelper::Init(const wstring& strConnString)
{
	HRESULT hr = S_OK;

// 	DBInfo dbi = CONF.GetDBInfo();
// 	//add by yjt 2014-06-13 添加数据库可用性的配置
// 	if(!dbi.bEnable)
// 	{
// 		m_bConnectDB = FALSE;
// 		return FALSE;
// 	}
// 
// 	CString strConnect;
// 	strConnect.Format(_T("Provider=OraOLEDB.Oracle.1;Password=%s;Persist Security Info=True;User ID=%s;\
// 						 Data Source=\"(DESCRIPTION =(ADDRESS_LIST =(ADDRESS = (PROTOCOL = TCP)(HOST = %s)(PORT = %d)) )(CONNECT_DATA = (SID = %s)))\""),
// 						 dbi.strPwd, dbi.strUser, dbi.strHost, dbi.nPort, dbi.strSid);
	m_strConn = strConnString;

	hr = m_pConnection.CreateInstance(__uuidof(Connection));
	try
	{	
		m_pConnection->ConnectionTimeout = 6;
		hr = m_pConnection->Open((LPCTSTR)strConnString.c_str(), _T(""), _T(""), adModeUnknown);
		if(FAILED(hr))
		{
			m_strErrMsg = _T("数据库连接失败，请检查数据库!");
			return FALSE;
		}
		m_pConnection->CursorLocation =adUseClient;
	}
	catch(_com_error e)
	{		
		CString err;
		err.Format(_T("数据库连接错误！\r\n错误信息:%s:"),e.ErrorMessage());
		m_strErrMsg = err;
		m_pConnection = NULL;
		return FALSE;
	}	

	m_bConnectDB = TRUE;

	return m_bConnectDB;
}

void CDBHelper::UnInit()
{
	try
	{
		if( m_pUserRecSet )
		{
			if( m_pUserRecSet->State )
				m_pUserRecSet->Close();
			m_pUserRecSet = NULL;
		}	

		if( m_pConnection )
		{
			if( m_bConnectDB )
			{
				m_pConnection->Close();
				m_pConnection = NULL;
			}
		}
	}catch(...)
	{

	}

}

BOOL CDBHelper::IsConnect()
{	
	if(!m_bConnectDB)
		Init(m_strConn);

	return m_bConnectDB;	
}

_RecordsetPtr CDBHelper::Query(const wstring& strSql)
{
	if(!IsConnect())
	{
		return false;
	}

	if( m_pUserRecSet )
	{
		if( m_pUserRecSet->State )
			m_pUserRecSet->Close();
		m_pUserRecSet = NULL;
	}

	try
	{
		CString strT(strSql.c_str());
		_variant_t sql(strT.GetBuffer(strT.GetLength()));
		m_pUserRecSet.CreateInstance(__uuidof(Recordset));
		m_pUserRecSet->Open(sql, m_pConnection.GetInterfacePtr(), \
			adOpenDynamic, /*adOpenStatic, */
			adLockOptimistic, adCmdText);
	}
	catch(_com_error& e)
	{
		//AfxMessageBox(e.Description() + e.Source());
		return NULL;
	}
	return m_pUserRecSet;
}
//////////////////////////////////////////////////////////////////////////
//参考http://blog.csdn.net/handsomerun/article/details/1714598?P_AVPASS=PHDGBITAVPASST
//错误码： http://hi.baidu.com/uloyuu/item/166ee71220bd53f89d778a0c
// -2146824867: 参数的格式不对， date格式为 2014-07-09 11:14:00
// --2146824580: Parameter 对象定义不正确。所提供的信息不一致或不完整
//CreateParameters错误: http://yukei.blog.163.com/blog/static/112587703201121761358609/
//

_RecordsetPtr CDBHelper::ExecProcEx(const wstring& procName, const VecParams& params)
{	
	if(!IsConnect())
	{
		return NULL;
	}

	try
	{
		if(m_pCmd && m_pCmd->State) 
		{
			m_pCmd->Release();
		}

		_RecordsetPtr pRecordset = NULL;

		HRESULT hr = m_pCmd.CreateInstance(__uuidof(Command));
		if(FAILED(hr))
		{
			m_strErrMsg = _T("ExecProc() 中创建_CommandPtr对象失败");
			return pRecordset;
		}

		hr = pRecordset.CreateInstance(__uuidof(Recordset));
		if(FAILED(hr))
		{
			m_strErrMsg = _T("ExecProc() 中创建_RecordsetPtr对象失败");
			return pRecordset;
		}

		//连接数据库的对象
		m_pCmd->ActiveConnection = m_pConnection;
		m_pCmd->CommandType = adCmdStoredProc;
		//存储过程名
		m_pCmd->CommandText=_bstr_t(procName.c_str()); 

		for(int i = 0 ; i < params.size(); ++i)
		{
			_ParameterPtr param = m_pCmd->CreateParameter(_bstr_t(params[i].strName.c_str()), params[i].emType, adParamInput, params[i].nLen, _variant_t(params[i].strValue.c_str()));
			m_pCmd->Parameters->Append(param);
		}

		pRecordset = m_pCmd->Execute(NULL,NULL,adCmdStoredProc);

		// 	int   retVal = -1;
		// 	_variant_t   VretVal ; 
		// 	//GetRetVal 
		// 	VretVal = m_pCmd->Parameters->GetItem(short(0))->Value;
		// 	retVal = VretVal.lVal;
		// 	Info.Format(_T("The Return Value is : %d"),retVal);
		// 	MessageBox(Info);
		// 
		// 	//output1 
		// 	VretVal = pCmd->Parameters->GetItem(short(3))->Value; 
		// 	retVal = VretVal.lVal;
		// 	Info.Format(_T("The output1 Value is : %d"),retVal);
		// 	MessageBox(Info);
		// 
		// 
		// 	//@pout2 
		// 	VretVal = pCmd->Parameters->GetItem(short(4))->Value;
		// 	Info= (LPCTSTR)_bstr_t(VretVal);
		// 	CString info1;
		// 	info1.Format(_T("The output2 Value is : %s"),Info);
		// 	MessageBox(info1);
		// 
		//取记录集里面的内容
// 		if (pRecordset->BOF && pRecordset->adoEOF)
// 		{
// 			m_strErrMsg = _T("没有符合条件的记录存在!");
// 			if(pRecordset != NULL && pRecordset->State)
// 			{
// 				pRecordset->Close();
// 				pRecordset = NULL;  
// 			}
// 			m_pCmd.Detach();
// 			return NULL;
// 		} 
		// 
		// 	pRecordset->MoveFirst();
		// 	for(;!pRecordset->adoEOF;pRecordset->MoveNext())
		// 	{
		// 		VRectVal = pRecordset->GetCollect(_T("Name"));
		// 		StrVal = (LPCTSTR)_bstr_t(VRectVal);
		// 		m_list.AddString(StrVal);
		// 	}
		// 
		// 
		// 	if(pRecordset != NULL && pRecordset->State)
		// 	{
		// 		pRecordset->Close();
		// 		pRecordset = NULL;  
		// 	}

		return pRecordset;
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("错误描述：%s\n错误消息%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		m_strErrMsg = strMsg.GetString();
		//AfxMessageBox(strMsg);
	}
	return NULL;
}

bool CDBHelper::ExecProc(const wstring& procName, const VecParams& params)
{
	if(!IsConnect())
	{
		return NULL;
	}

	try
	{

		if(m_pCmd && m_pCmd->State) 
		{
			m_pCmd->Release();
		}

		HRESULT hr = m_pCmd.CreateInstance(__uuidof(Command));
		if(FAILED(hr))
		{
			m_strErrMsg = _T("ExecProc() 中创建_CommandPtr对象失败");
			return false;
		}

		_RecordsetPtr pRecordset = NULL;
		hr = pRecordset.CreateInstance(__uuidof(Recordset));
		if(FAILED(hr))
		{
			m_strErrMsg = _T("ExecProc() 中创建_RecordsetPtr对象失败");
			return false;
		}

		//连接数据库的对象
		m_pCmd->ActiveConnection = m_pConnection;
		m_pCmd->CommandType = adCmdStoredProc;
		//存储过程名
		m_pCmd->CommandText=_bstr_t(procName.c_str()); 

		_ParameterPtr param;
		int nTmp;
		for(int i = 0 ; i < params.size(); ++i)
		{
			if(params[i].emType == adInteger)
			{
				wistringstream is(params[i].strValue);
				is >> nTmp;
				param = m_pCmd->CreateParameter(_bstr_t(params[i].strName.c_str()), params[i].emType, adParamInput, params[i].nLen, _variant_t(nTmp));
			}
			else
			{
				param = m_pCmd->CreateParameter(_bstr_t(params[i].strName.c_str()), params[i].emType, adParamInput, params[i].nLen, _variant_t(params[i].strValue.c_str()));
			}
			m_pCmd->Parameters->Append(param);
		}


		m_pCmd->Execute(NULL,NULL,adCmdStoredProc);

		m_pCmd.Detach();
		return true;
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("错误描述：%s\n错误消息%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		m_strErrMsg = strMsg.GetString();
	}
	return false;
}