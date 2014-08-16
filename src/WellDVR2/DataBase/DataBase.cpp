#include "stdafx.h"
#include "DataBase.h"
#include "../IniFile.h"
#include "../DataDef.h"
#include "../ShareData.h"
#include "../Config.h"


CDataBase::CDataBase(void)
	: m_bInit(false)
{
	if(!Init())
	{
		SHAREDATA.g_pMainFrame->Alert(m_db.GetLastError().c_str());
	}
}


CDataBase::~CDataBase(void)
{
	UnInit();
}

BOOL CDataBase::Init()
{
	DBInfo dbi = CONF.GetDBInfo();
	//add by yjt 2014-06-13 添加数据库可用性的配置
	if(!dbi.bEnable)
	{
		m_bInit = false;
		return TRUE;
	}

	CString strConnect;
	strConnect.Format(_T("Provider=OraOLEDB.Oracle.1;Password=%s;Persist Security Info=True;User ID=%s;\
					  Data Source=\"(DESCRIPTION =(ADDRESS_LIST =(ADDRESS = (PROTOCOL = TCP)(HOST = %s)(PORT = %d)) )(CONNECT_DATA = (SID = %s)))\""),
					  dbi.strPwd, dbi.strUser, dbi.strHost, dbi.nPort, dbi.strSid);

	BOOL bRlt = m_db.Init(strConnect.GetBuffer());
	strConnect.ReleaseBuffer();

	m_bInit = true;

	return bRlt;
}

void CDataBase::UnInit()
{
	m_db.UnInit();
	m_bInit = false;
}

CDataBase& CDataBase::Instance()
{
	static CDataBase db;
	return db;
}

//从缓存中获取数据，如果id不存在，则刷新缓存
//如果后台改变此DVRNUM对应的名称，则没办法刷新
CString CDataBase::GetNameFormID(const CString& id)
{
	CString str(_T(""));
	if( !m_db.IsConnect() )
		return str;

	MapDvrIdNameItor it = mapDvr.find(id);
	if(it != mapDvr.end())
	{
		return (*it).second;
	}

	InitUserRec();
	
	it = mapDvr.find(id);
	if(it != mapDvr.end())
	{
		return (*it).second;
	}
	return _T("");
}

//modified by yjt 2014-4-17 把DVR 改为 mycar.DVR
void CDataBase::InitUserRec()
{
	_RecordsetPtr record = m_db.Query(_T("select DVRNUM,REALNAME from mycar.DVR"));
	if(record)
	{
		FillUserVector(record);
	}
}


void CDataBase::FillUserVector(_RecordsetPtr record)
{
	_variant_t var;
	CString strID, strName;

	mapDvr.clear();

	try
	{
		if( !record->BOF )
			record->MoveFirst();

		while( !record->adoEOF )
		{
			var = record->GetCollect("DVRNUM");
			if( var.vt != VT_NULL )
			{
				strID = (LPCSTR)_bstr_t(var);
				strID.TrimRight();
				strID.TrimLeft();
			}			

			var = record->GetCollect("REALNAME");
			if( var.vt != VT_NULL )
			{
				strName = (LPCSTR)_bstr_t(var);
				strName.TrimRight();
				strName.TrimLeft();
			}			

			mapDvr[strID] = strName;

			record->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		SHAREDATA.g_pMainFrame->Alert(e->ErrorMessage());
	}
}

//根据ID实时查询姓名
CString CDataBase::QueryNameFormID(const CString& id)
{
	if( !IsValid())
		return _T("");

	CString strSql;
	strSql.Format(_T("select DVRNUM,REALNAME from mycar.DVR where DVRNUM='%s'"), id);
	_RecordsetPtr record = m_db.Query(strSql.GetString());
	if(record == NULL)
	{
		return _T("");
	}

	CString strName(_T(""));
	try
	{
		if( !record->BOF )
			record->MoveFirst();

		_variant_t var;
		while( !record->adoEOF )
		{
			var = record->GetCollect("REALNAME");
			if( var.vt != VT_NULL )
			{
				strName = (LPCSTR)_bstr_t(var);
				strName.TrimRight();
				strName.TrimLeft();
			}			
			record->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		SHAREDATA.g_pMainFrame->Alert(e->ErrorMessage());
	}

	mapDvr[id] = strName;

	return strName;
}

//////////////////////////////////////////////////////////////////////////
//描述：插入视频（媒体信息)
//时间：created by yjt 2014-07-03
//存储过程如下：
// 			P_INSERT_DVRMEDIA_INFO (
// 				iDvrNumber in varchar2, -- DVR编号
// 				iFileName in varchar2, --文件名
// 				iFileSize in number, --文件大小
// 				iViewWidth in number, -- 宽
// 				iViewHeight in number, -- 高
// 				iMediaDuration in number, --时长
// 				iFrameRate in varchar2, --帧率
// 				iDataUploadTime in date, --上传时间
// 				iMediaStartTime in date, --开始时间
// 				iMediaEndTime in date, --结束时间
// 				iRecordTime in date, -- 录像时间
// 				iFileType in varchar2, -- 文件类型
// 				iVideoType in varchar2, -- 重点/高清/标清
// 				iLocateFilePath in varchar2, --本地文件路径
// 				iFtpFileUrl in varchar2, --ftp文件路径
// 				iIISFileUrl in varchar2, --iis文件路径
// 				iDataIp in varchar2, --数据存储ip
// 				iRemark in varchar2 --备注
// 				)
//////////////////////////////////////////////////////////////////////////
BOOL CDataBase::InsertMediaInfo(const DVRMEDIA_INFO& info)
{
	if(!IsValid())
	{
		return FALSE;
	}

	wstring strProcName(_T("P_INSERT_DVRMEDIA_INFO"));

	_ParameterPtr param;
	//参数
	VecParams mapParams;
	FieldInfo fi;
	fi.strValue = info.strDvrNumber; //_T("000000000000010001");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDvrNumber");
	mapParams.push_back(fi);

	fi.strValue = info.strFileName; //_T("00000001_20140706.AVI");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iFileName");
	mapParams.push_back(fi);

	fi.strValue = info.strFileSize; //_T("2343243");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iFileSize");
	mapParams.push_back(fi);

	fi.strValue = info.strViewWidth; //_T("1080");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iViewWidth");
	mapParams.push_back(fi);

	fi.strValue = info.strViewHeight;	//_T("720");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iViewHeight");
	mapParams.push_back(fi);

	fi.strValue = info.strMediaDuration; //_T("69");
	fi.nLen = fi.strValue.length();
	fi.emType = adInteger;
	fi.strName = _T("iMediaDuration");
	mapParams.push_back(fi);

	fi.strValue = info.strFrameRate; //_T("30");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iFrameRate");
	mapParams.push_back(fi);

	fi.strValue = info.strDataUploadTime; //_T("2014-07-03 09:10:10");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDataUploadTime");
	mapParams.push_back(fi);

	fi.strValue = info.strMediaStartTime; //_T("2014-07-03 09:10:10");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iMediaStartTime");
	mapParams.push_back(fi);

	fi.strValue = info.strMediaEndTime; //_T("2014-07-03 09:10:10");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iMediaEndTime");
	mapParams.push_back(fi);
	
	fi.strValue = info.strRecordTime; //_T("2014-07-03 09:10:10");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iRecordTime");
	mapParams.push_back(fi);

	fi.strValue = info.strFileType; //_T("AVI");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iFileType");
	mapParams.push_back(fi);

	fi.strValue = info.strVideoType; //_T("IPM");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iVideoType");
	mapParams.push_back(fi);

	fi.strValue = info.strLocateFilePath; //_T("0000001/DCIM/RECORD/00000001_20140706.AVI");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iLocateFilePath");
	mapParams.push_back(fi);

	fi.strValue = info.strFtpFileUrl; //_T("ftp://192.168.1.1:21/0000001/DCIM/RECORD/00000001_20140706.AVI");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iFtpFileUrl");
	mapParams.push_back(fi);

	fi.strValue = info.strIISFileUrl; //_T("http://192.168.1.1:80/0000001/DCIM/RECORD/00000001_20140706.AVI");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iIISFileUrl");
	mapParams.push_back(fi);

	fi.strValue = info.strDataIp;	//_T("192.168.1.1");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDataIp");
	mapParams.push_back(fi);	

	fi.strValue = info.strRemark;	//_T(" ");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iRemark");
	mapParams.push_back(fi);

	return m_db.ExecProc(strProcName, mapParams);
}

//////////////////////////////////////////////////////////////////////////
//描述：插入DVR日志
//时间：created by yjt 2014-07-03
//存储过程如下：
// 			P_INSERT_DVR_DEVICE_LOG (iDvrNumber in varchar2, --dvr编号
// 				iDeviceInsertTime in date, --设备插入时间
// 				iDeviceOperTime in date, --设备操作时间
// 				iDeviceOperUser in varchar2, --设备操作用户
// 				iLogContent in varchar2, --日志内容
// 				iRemark in varchar2 --备注
// 				)
//////////////////////////////////////////////////////////////////////////
BOOL CDataBase::InsertDvrLog(const DVR_DEVICE_LOG& ddLog)
{
	if(!IsValid())
	{
		return FALSE;
	}

	wstring strProcName(_T("P_INSERT_DVR_DEVICE_LOG"));
	//参数
	VecParams mapParams;
	FieldInfo fi;
	fi.strValue = ddLog.strDvrNumber;	//_T("000000000000010001");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDvrNumber");
	mapParams.push_back(fi);

	fi.strValue = ddLog.strDeviceInsertTime;	//_T("2014-07-03 09:10:10");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDeviceInsertTime");
	mapParams.push_back(fi);

	fi.strValue = ddLog.strDeviceOperTime;	//_T("2014-07-03 09:10:10");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDeviceOperTime");
	mapParams.push_back(fi);

	fi.strValue = ddLog.strDeviceOperUser;	//_T("Administrator");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDeviceOperUser");
	mapParams.push_back(fi);

	fi.strValue = ddLog.strLogContent;	//_T("采集终端还活着");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iLogContent");
	mapParams.push_back(fi);

	fi.strValue = ddLog.strRemark;	//_T(" ");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iRemark");
	mapParams.push_back(fi);


	return m_db.ExecProc(strProcName, mapParams);
}

//////////////////////////////////////////////////////////////////////////
//描述：插入终端日志
//时间：created by yjt 2014-07-03
//存储过程如下：
// 			//终端日志
// 			P_INSERT_TERMINAL_DEV_LOG (
// 				iDeviceNumber IN VARCHAR2, --设备号
// 				iHarewareVersion IN VARCHAR2, --硬件版本
// 				iSoftwareVersion IN VARCHAR2, --软件版本
// 				iDiskSpace IN NUMBER, --磁盘空间
// 				iTerminalIp IN VARCHAR2, --IP
// 				iIsusing IN VARCHAR2, --是否启用 -Y是 -N否
// 				iDetachment IN VARCHAR2, --支队
// 				iBattalion IN VARCHAR2, --大队
// 				iSquadron IN VARCHAR2, --中队
// 				iDescribe IN VARCHAR2, --描述
// 				iRemark IN VARCHAR2 --备注
// 				)
//////////////////////////////////////////////////////////////////////////
BOOL CDataBase::InsertLog(const TERMINAL_DEV_LOG& tdLog)
{
	if(!IsValid())
	{
		return FALSE;
	}

	wstring strProcName(_T("P_INSERT_TERMINAL_DEV_LOG"));
	//参数
	VecParams mapParams;

	FieldInfo fi;
	fi.strValue = tdLog.strDeviceNumber;	//_T("000000000000020001");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDeviceNumber");
	mapParams.push_back(fi);

	fi.strValue = tdLog.strHarewareVersion;	//_T("V1.0.0");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iHarewareVersion");
	mapParams.push_back(fi);

	fi.strValue = tdLog.strSoftwareVersion;	//_T("V1.0.0.5");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iSoftwareVersion");
	mapParams.push_back(fi);

	fi.strValue = tdLog.strDiskSpace;	//_T("2000000");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDiskSpace");
	mapParams.push_back(fi);

	fi.strValue = tdLog.strTerminalIp;	//_T("192.168.1.2");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iTerminalIp");
	mapParams.push_back(fi);

	fi.strValue = tdLog.strIsusing;		//_T("1");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iIsusing");
	mapParams.push_back(fi);

	fi.strValue = tdLog.strDetachment;	//_T("支队");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDetachment");
	mapParams.push_back(fi);

	fi.strValue = tdLog.strBattalion;	//_T("大队");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iBattalion");
	mapParams.push_back(fi);

	fi.strValue = tdLog.strSquadron;	//_T("中队");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iSquadron");
	mapParams.push_back(fi);

	fi.strValue = tdLog.strDescribe;	//_T("正常工作中");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iDescribe");
	mapParams.push_back(fi);

	fi.strValue = tdLog.strRemark;		//_T(" ");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.strName = _T("iRemark");
	mapParams.push_back(fi);

	return m_db.ExecProc(strProcName, mapParams);
}

//////////////////////////////////////////////////////////////////////////
//描述：上报终端状态
//时间：created by yjt 2014-07-03
//存储过程如下：
//终端状态
// P_INSERT_TERMINAL_STATE (
// 	iDeviceNumber IN VARCHAR2, --设备号
// 	iReportTime IN date, --报告时间
// 	iDeviceState IN VARCHAR2, --设备状态
// 	iRemark IN VARCHAR2 --备注
// 	)
//////////////////////////////////////////////////////////////////////////
BOOL CDataBase::InsertStatus(const TERMINAL_STATE& ts)
{
	if(!IsValid())
	{
		return FALSE;
	}

	wstring strProcName(_T("P_INSERT_TERMINAL_STATE"));
	
	//参数
	VecParams mapParams;
	FieldInfo fi;
	fi.strValue = ts.strDeviceNumber;	//_T("df");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.pType = adParamInput;
	fi.strName = _T("iDeviceNumber");
	mapParams.push_back(fi);

	fi.strValue = ts.strReportTime;	//_T("2014-07-03 12:11:12");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarWChar;
	fi.pType = adParamInput;
	fi.strName = _T("iReportTime");
	mapParams.push_back(fi);

	fi.strValue = ts.strDeviceState;	//_T("正常工作中");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.pType = adParamInput;
	fi.strName = _T("iDeviceState");
	mapParams.push_back(fi);

	fi.strValue = ts.strRemark;			//_T(" ");
	fi.nLen = fi.strValue.length();
	fi.emType = adVarChar;
	fi.pType = adParamInput;
	fi.strName = _T("iRemark");
	mapParams.push_back(fi);

	return m_db.ExecProc(strProcName, mapParams);
}

////根据设备号获取ip和端口
//select t.ftpip, t.ftpport, t.iisip, t.iisport from TERMINALIPCONF t where t.terminalsn = ?
BOOL CDataBase::QueryIpPortByDevId(const wstring& devId, wstring& ftpip, wstring& ftpport, wstring& iisIp, wstring& iisPort)
{
	if( !IsValid() )
		return FALSE;

	CString strSql;
	strSql.Format(_T("select t.ftpip, t.ftpport, t.iisip, t.iisport from TERMINALIPCONF t where t.terminalsn = '%s'"), devId.c_str());
	_RecordsetPtr record = m_db.Query(strSql.GetString());
	if(record == NULL)
	{
		return FALSE;
	}

	try
	{
		if( !record->BOF )
			record->MoveFirst();

		_variant_t var;
		while( !record->adoEOF )
		{
			var = record->GetCollect("FTPIP");
			if( var.vt != VT_NULL )
			{
				ftpip = (wchar_t*)_bstr_t(var);
			}			
			var = record->GetCollect("FTPPORT");
			if( var.vt != VT_NULL )
			{
				ftpport = (wchar_t*)_bstr_t(var);
			}
			var = record->GetCollect("IISIP");
			if( var.vt != VT_NULL )
			{
				iisIp = (wchar_t*)_bstr_t(var);
			}
			var = record->GetCollect("IISPORT");
			if( var.vt != VT_NULL )
			{
				iisPort = (wchar_t*)_bstr_t(var);
			}
			record->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		//SHAREDATA.g_pMainFrame->Alert(e->ErrorMessage());
		return FALSE;
	}

	return TRUE;
}