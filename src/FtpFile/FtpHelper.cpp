#include "StdAfx.h"
#include "FtpHelper.h"

#include "FtpTransThread.h"
#include "FtpDownloadThread.h"

CFtpHelper::CFtpHelper(void)
{
	m_pCompleteMonitorThread = AfxBeginThread(CompleteMonitorThread,this);
}


CFtpHelper::~CFtpHelper(void)
{
	//关闭已经在运行的线程
	for(int i=0;i<m_arFtpThreads.GetSize();i++)
	{
		m_arFtpThreads[i]->Stop();
		delete m_arFtpThreads[i];
	}
//	m_arFtpThreads.RemoveAll();

	for(int i=0;i<m_arFtpDownloadThread.GetSize();i++)
	{
		m_arFtpDownloadThread[i]->Stop();
		delete m_arFtpDownloadThread[i];
	}
	m_arFtpDownloadThread.RemoveAll();
	if(m_pCompleteMonitorThread != NULL)
		delete m_pCompleteMonitorThread;	

}

/************************************************************************/
//功能：添加ftp服务器路径
//参数：
//	 ftpPath [IN]	--		FTP服务器的路径
//	 virtualPath [IN]	--	是否为虚拟路径
//	 ip [IN]			--	FTP服务器的IP
//	 port [IN]			--	FTP服务器的端口
//	 user [IN]			--	用户名
//	 pwd [IN]			--	密码
//备注：
//	1. 如FTP服务器（192.168.1.217) 配在d://well-ftp
//	2. 用户名test 密码test
//示例:
//	AddServerPath(L"\\", TRUE, L"192.168.1.217", 21, L"test", L"test");
/************************************************************************/
void CFtpHelper::AddServerPath(LPCTSTR ftpPath, BOOL virtualPath, LPCTSTR ip, UINT port, LPCTSTR user, LPCTSTR pwd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//检查是否记录重复
	bool repeat = false;
	for(int i=0;i<m_arFtpServer.GetSize();i++)
	{
		if(m_arFtpServer[i].ip == ip && m_arFtpServer[i].port == port && m_arFtpServer[i].ftpPath == ftpPath)
		{
			repeat = true;
			//这里对FTP记录和线程记录，文件记录中进行操作，将当前插入的FTP设为列表的最后一个	
			break;
		}
	}
	if(!repeat)
	{
		FtpServerInfo info;
		info.ip = ip;
		info.port = port;
		info.pwd = pwd;
		info.ftpPath = ftpPath;
		info.user = user;
		info.virtualPath = virtualPath;
		m_arFtpServer.Add(info);
	}
}

/************************************************************************/
//功能： 上传文件
//参数：
//		localFile [IN]	--		上传文件的完整名（路径)
//		newDir [IN]		--		ftp相应的目录中
//		rename [IN]		--		新的名称
//		type [IN]		--		
//返回值：上传后在ftp的完整名称
//示例：
//	Upload(L"E:\\01-software\\xxxxxx-Win.exe", L"",L"", 0);
//
/************************************************************************/
LPCTSTR CFtpHelper::Upload(LPCTSTR localFile, LPCTSTR newDir, LPCTSTR rename, SHORT type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	m_csCompleteState.Lock();
	m_bUploadCompleted = false;
	m_csCompleteState.Unlock();

	//关闭已经在运行的线程
	for(int i=0;i<m_arFtpThreads.GetSize();i++)
	{
		//m_arFtpThreads[i]->Stop();
		//delete m_arFtpThreads[i];
		if(!m_arFtpThreads[i]->IsTransOver())
		{
			m_arFtpThreads[i]->SoftStop();
			m_arFtpThreads[i]->SetAutoRelease(true);
		}
		else
			delete m_arFtpThreads[i];
	}
	m_arFtpThreads.RemoveAll();

	CString strSourceFile(localFile);
	CString destFile;
	//生成Ftp上的新文件名
	CString filename,title,extend;
	int index;
	CString strRename(rename);
	if(strRename == _T(""))
	{
		index = strSourceFile.ReverseFind(_T('\\'));
		if(index == -1) strResult.AllocSysString();
		filename = strSourceFile.Right(strSourceFile.GetLength()-index-1);
	}
	else
		filename = rename;
	index = filename.ReverseFind(_T('.'));
	if(index == -1) { title = filename; extend = _T("");}
	else
	{
		title = filename.Left(index);
		extend = filename.Right(filename.GetLength()-index-1);
	}
	CString folder = _T("");
	CString strNewDir(newDir);
	if(strNewDir != _T("")  )
		folder = folder + newDir+_T("/");
	if(m_date != _T(""))
		folder =folder + m_date + _T("/");
	if(type == 0) //生成Guid
	{
		CString guid = CreateGuid();
		title = title.Left(10);
		int len = title.GetLength();
		if(len<10)
		{
			for(int i=0;i<10-len;i++)
				title += _T(" ");
		}
		strFtpPath = title + guid + _T(".") + extend;
	}
	else if(type == 1)
		strFtpPath = filename;
	strResult = strFtpPath;
	//去掉strResult中间的后缀名
	index=strResult.ReverseFind(_T('.'));
	if(index != -1) strResult = strResult.Left(index);
	strFtpPath = folder + strFtpPath;

	//启动若干个线程
	for(int i=0;i<m_arFtpServer.GetSize();i++)
	{
		CFtpTransThread *pThread=new CFtpTransThread;
		pThread->SetFtpInfo(m_arFtpServer[i].ip,m_arFtpServer[i].port,m_arFtpServer[i].user,m_arFtpServer[i].pwd,ConverShareToFtp(m_arFtpServer[i].ftpPath,m_arFtpServer[i].virtualPath));
		pThread->TransFile(localFile,ConverShareToFtp(m_arFtpServer[i].ftpPath,m_arFtpServer[i].virtualPath)+_T("/")+strFtpPath,
			strNewDir,m_date,GetSharePath(m_arFtpServer[i].ftpPath,m_arFtpServer[i].virtualPath), &m_eventComplete);
		pThread->m_ctrl = this;
		m_arFtpThreads.Add(pThread);
	}
	return strFtpPath;
}

CString CFtpHelper::CreateGuid(void)
{
	CString ret;
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		ret.Format(
			_T("%08X%04X%04x%02X%02X%02X%02X%02X%02X%02X%02X")
			, guid.Data1
			, guid.Data2
			, guid.Data3
			, guid.Data4[0], guid.Data4[1]
		, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
		, guid.Data4[6], guid.Data4[7]
		);
	}
	return ret;
}

UINT CFtpHelper::CompleteMonitorThread(LPVOID pParam)
{
	CFtpHelper *pCtrl = (CFtpHelper*) pParam;
	while(::WaitForSingleObject(pCtrl->m_eventComplete.m_hObject,INFINITE)==WAIT_OBJECT_0)
	{
		pCtrl->CheckComplete();
	}
	/*while(1)
	{
	bool bUploadRunning = true,bDownloadRunning = false ;
	for(int i=0;i<pCtrl->m_ar
	}*/
	return 0;
}

void CFtpHelper::CheckComplete(void)
{
	//检查上传进度
	m_csCompleteState.Lock();
	bool bUploadComplete;
	bUploadComplete = m_bUploadCompleted;
	if(!bUploadComplete && m_arFtpThreads.GetSize()>0)
	{
		int success=0,failed=0;
		bool bStillRunning =  false;

		CArray<CString,CString&> arSuccessPath;
		CArray<CString,CString&> arFailedPath; //失败的列表，只包含传送失败时的结果

		for(int i=0;i<m_arFtpThreads.GetSize();i++)
		{
			if(m_arFtpThreads[i]->IsTransOver())
			{
				if(m_arFtpThreads[i]->IsFailed())
				{
					arSuccessPath.Add(CString(_T(""))); //上传失败，返回空值
					failed++;
					if(m_arFtpThreads[i]->m_nFileTransSize>0) //已经传送了一部分文件
					{
						if(m_arFtpThreads[i]->m_strDestFile[0]!=_T('/'))
							arFailedPath.Add(_T("./")+m_arFtpThreads[i]->m_strDestFile);
						else
							arFailedPath.Add(_T('.')+m_arFtpThreads[i]->m_strDestFile);
					}
					else
						arFailedPath.Add(CString(_T("")));
				}
				else
				{
					if(m_arFtpThreads[i]->m_strDestFile[0]!=_T('/'))
						arSuccessPath.Add(_T("./")+m_arFtpThreads[i]->m_strDestFile);
					else
						arSuccessPath.Add(_T('.')+m_arFtpThreads[i]->m_strDestFile);
					success++;
				}
			}
			else
			{
				bStillRunning = true;
				break;
			}
		}
		if(!bStillRunning)
		{
			{
				//封装SAFEARRAY
				SAFEARRAY *psa;
				SAFEARRAYBOUND rgsabound[1];
				rgsabound[0].lLbound = 0;
				rgsabound[0].cElements = arSuccessPath.GetSize();
				psa = SafeArrayCreate(VT_VARIANT,1,rgsabound);
				for(long i=0;i<arSuccessPath.GetSize();i++)
				{
					CComVariant com_v;
					com_v = arSuccessPath[i].AllocSysString();
					SafeArrayPutElement(psa,&i,&com_v);
				}
				m_FileList.vt = VT_ARRAY|VT_VARIANT;
				m_FileList.parray = psa;
			}

			{
				//封装失败的SAFEARRAY
				SAFEARRAY *psa;
				SAFEARRAYBOUND rgsabound[1];
				rgsabound[0].lLbound = 0;
				rgsabound[0].cElements = arSuccessPath.GetSize();
				psa = SafeArrayCreate(VT_VARIANT,1,rgsabound);
				for(long i=0;i<arFailedPath.GetSize();i++)
				{
					CComVariant com_v;
					com_v = arFailedPath[i].AllocSysString();
					SafeArrayPutElement(psa,&i,&com_v);
				}
				m_FailedList.vt = VT_ARRAY|VT_VARIANT;
				m_FailedList.parray = psa;
			}

			OnUploadComplete(success,failed);
			m_bUploadCompleted = true;
		}
	}

	{
		//检查下载进度
		/*bool bStillRunning = false;
		int nSuccess=0,nFailed=0;
		for(int i=0;i<m_arFtpDownloadThread.GetSize();i++)
		{
		if(!m_arFtpDownloadThread[i]->IsRunning())
		{
		if(m_arFtpDownloadThread[i]->IsFailed())
		nFailed++;
		else
		nSuccess++;
		}
		else
		bStillRunning = true;
		}
		if(!bStillRunning)
		{
		VARIANT_BOOL result;
		if(nFailed == 0 || nFailed == 1)
		result = TRUE;
		else
		result = FALSE;
		OnDownloadComplete(result);
		}*/
		//检查视频和音频
		bool bDownloadCompleted;
		bDownloadCompleted = m_bDownloadCompleted;
		if(!bDownloadCompleted && m_arFtpDownloadThread.GetSize() == 1)
		{
			if(m_arFtpDownloadThread[0]->IsTransOver() )
			{
				if(m_arFtpDownloadThread[0]->IsFailed() == false)
					OnDownloadComplete(TRUE);
				else
					OnDownloadComplete(FALSE);
				m_bDownloadCompleted = true;
				/*for(int i=0;i<m_arFtpDownloadThread.GetSize();i++)
				{
				m_arFtpDownloadThread[i]->Stop();
				delete m_arFtpDownloadThread[i];
				}
				m_arFtpDownloadThread.RemoveAll();*/
			}
		}
	}
	m_csCompleteState.Unlock();
}

SHORT CFtpHelper::GetUploadPercent(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONGLONG totalSize=0,transSize=0;
	for(int i=0;i<m_arFtpThreads.GetSize();i++)
	{
		m_arFtpThreads[i]->m_cs.Lock();
		totalSize += m_arFtpThreads[i]->m_nFileSize;
		transSize += m_arFtpThreads[i]->m_nFileTransSize;
		m_arFtpThreads[i]->m_cs.Unlock();
	}
	if(totalSize == 0)
		return 0;
	else
	{
		short ret;
		ret = (short)(transSize*100 / totalSize);
		return ret;
	}
}

CString CFtpHelper::ConverShareToFtp(CString sharepath, bool virtualPath)
{
	//首先去除机器名
	int index;
	sharepath = sharepath.Right(sharepath.GetLength() - 2);
	index = sharepath.Find(_T('\\'));
	if(index==-1) return _T("");
	sharepath =  sharepath.Right(sharepath.GetLength()-index-1);
	if(!virtualPath)
	{
		index = sharepath.Find(_T('\\'));
		if(index==-1) return _T("");
		sharepath = sharepath.Right(sharepath.GetLength() - index -1);
	}
	sharepath.Replace(_T('\\'),_T('/'));
	return sharepath;
}

//进行ftp路径截取之后剩下的部分
CString CFtpHelper::GetSharePath(const CString& path,bool virtualPath)
{
	//截取机器名
	int pos; // 目标'\'位置
	if(virtualPath)
		pos = 3;
	else
		pos = 4;
	int cutPos = 0;
	int count = 0;
	for(int i=0;i<path.GetLength();i++)
	{
		if(path[i]==_T('\\'))
		{
			count++;
			if(count == pos)
			{
				cutPos = i;
				break;
			}
		}
	}
	CString ret = path.Left(cutPos+1);
	return ret;
}

void CFtpHelper::DownloadFile(LPCTSTR RemoteFile, LPCTSTR localFolder,LPCTSTR rename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	//for test
	//dvcpro25  012C3B69256841dd9BA8FDB8B3FF9D6C-145324.wav
	//RemoteFile = _T("\\\\dell-780h\\媒资素材库A\\dvcpro50  3AEFE82B3EEC4f268D07F572F1DB85D1-90152.rar");
	//RemoteFile = _T("\\\\dell-780e\\媒资素材库B\\test      40C0CB77692545dfB0B2EC5F2210875A.rar");
	//localFolder = _T("D:\\testfolder\\");
	//rename = _T("fff");



	// TODO: Add your dispatch handler code here
	m_csCompleteState.Lock();
	m_bDownloadCompleted = false;
	m_csCompleteState.Unlock();
	//如果有搜索在继续，退出搜索

	for(int i=0;i<m_arFtpDownloadThread.GetSize();i++)
	{
		//m_arFtpDownloadThread[i]->Stop();
		//delete m_arFtpDownloadThread[i];
		if(!m_arFtpDownloadThread[i]->IsTransOver())
		{
			m_arFtpDownloadThread[i]->SoftStop();
			m_arFtpDownloadThread[i]->SetAutoRelease(true);
		}
		else
			delete m_arFtpDownloadThread[i];
	}
	m_arFtpDownloadThread.RemoveAll();

	//在服务器数据中查找
	CString strRemote(RemoteFile);
	int nServerIdx = -1;
	for(int i=0;i<m_arFtpServer.GetSize();i++)
	{
		if(strRemote.Left(m_arFtpServer[i].ftpPath.GetLength()).CompareNoCase(m_arFtpServer[i].ftpPath)==0)
		{
			nServerIdx = i;
			break;
		}
	}
	if(nServerIdx == -1)
	{
		OnDownloadComplete(FALSE);   //如果没有对应的服务器信息，出错
		return ;
	}
	//设置ftp服务器信息
	CFtpDownloadThread *pVideoThread = new CFtpDownloadThread;
	//CFtpDownloadThread *pAudioThread = new CFtpDownloadThread;
	CString ftpPath = ConverShareToFtp(strRemote,m_arFtpServer[nServerIdx].virtualPath);
	//ftpPath = _T("/") + ftpPath;
	CString ip,user,pwd;
	UINT port;
	ip = m_arFtpServer[nServerIdx].ip;
	user = m_arFtpServer[nServerIdx].user;
	pwd = m_arFtpServer[nServerIdx].pwd;
	port = m_arFtpServer[nServerIdx].port;
	pVideoThread->SetFtpInfo(ip,port,user,pwd);
	pVideoThread->DownloadFile(ftpPath,localFolder,rename,&m_eventComplete);

	pVideoThread->m_ctrl = this;
	m_arFtpDownloadThread.Add(pVideoThread);


	////添加音频下载线程
	//pAudioThread->SetFtpInfo(ip,port,user,pwd);
	//CString audioFile = ftpPath;
	//int index = ftpPath.ReverseFind(_T('.'));
	//if(index != -1)
	//{
	//	audioFile = ftpPath.Left(index+1);
	//}
	//audioFile = audioFile + _T("wav");
	//if(audioFile.CompareNoCase(ftpPath)!=0)
	//	pAudioThread->DownloadFile(audioFile,localFolder,&m_eventComplete);
	//pAudioThread->m_ctrl = this;
	//m_arFtpDownloadThread.Add(pAudioThread);


}

SHORT CFtpHelper::GetDownloadPercent(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	LONGLONG totalSize=0,transSize=0;
	for(int i=0;i<m_arFtpDownloadThread.GetSize();i++)
	{
		m_arFtpDownloadThread[i]->m_cs.Lock();
		totalSize += m_arFtpDownloadThread[i]->m_nFileSize;
		transSize += m_arFtpDownloadThread[i]->m_nFileTransSize;
		m_arFtpDownloadThread[i]->m_cs.Unlock();
	}
	if(totalSize == 0)
		return 0;
	else
	{
		short ret;
		ret = (short)(transSize*100 / totalSize);
		return ret;
	}
}

void CFtpHelper::ClearServerPath(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	m_arFtpServer.RemoveAll();

}

SHORT CFtpHelper::DelFtpFile(LPCTSTR ftpIp, LPCTSTR ftpUsr, LPCTSTR ftpPwd, SHORT ftpPort, LPCTSTR path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	CInternetSession session;
	CFtpConnection *pFtpCon = NULL;
	SHORT ret;
	try
	{
		pFtpCon = session.GetFtpConnection(ftpIp,ftpUsr,
			ftpPwd,ftpPort,true);
		if(pFtpCon->Remove(path))
			ret = 0;
		else
		{
			HRESULT hr = GetLastError();
			if(hr == ERROR_INTERNET_EXTENDED_ERROR)
			{
				DWORD dwError;
				TCHAR buf[200];
				DWORD size=200;	
				InternetGetLastResponseInfo(&dwError,buf,&size);
				CString strError(buf);
				//CString strErrorCode;
				//strErrorCode = strError.Left(3);
				//ret = _wtoi(strErrorCode);
				if(strError.Left(3) == _T("550"))
				{
					if(strError.Find(_T("file"))!=-1) //文件找不到
						ret = 0;
					else
						ret = -1003;  //路径找不到
				}
			}
			else
				ret = -1004;
		}

	}
	catch(CInternetException *e)
	{
		if(e->m_dwError == ERROR_INTERNET_INCORRECT_PASSWORD )
			ret = -1002;
		else
			ret= -1001;
		e->Delete();
	}
	if(pFtpCon != NULL ) delete pFtpCon;
	return ret;
}

/************************************************************************/
//功能： 断点上传
//参数:
//		localFile [IN]	--	要上传的文件（完整路径）
//		remoteFile [IN]	--	远程路径
//		isCoutinue [IN]	--	是否续传
//返回：
//示例：
//	localFile = _T("F:\\testfolder\\test.rar");
//	remoteFile=strFtpPath;
//	isContiue=TRUE;
/************************************************************************/
LPCTSTR CFtpHelper::UploadContiue(LPCTSTR localFile, LPCTSTR remoteFile, BOOL isContiue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;


	m_csCompleteState.Lock();
	m_bUploadCompleted = false;
	m_csCompleteState.Unlock();
	//关闭已经在运行的线程

	//关闭已经在运行的线程
	for(int i=0;i<m_arFtpThreads.GetSize();i++)
	{
		//m_arFtpThreads[i]->Stop();
		//delete m_arFtpThreads[i];
		if(!m_arFtpThreads[i]->IsTransOver())
		{
			m_arFtpThreads[i]->SoftStop();
			m_arFtpThreads[i]->SetAutoRelease(true);
		}
		else
			delete m_arFtpThreads[i];
	}
	m_arFtpThreads.RemoveAll();


	//启动若干个线程
	for(int i=0;i<m_arFtpServer.GetSize();i++)
	{
		CFtpTransThread *pThread=new CFtpTransThread;
		pThread->SetFtpInfo(m_arFtpServer[i].ip,m_arFtpServer[i].port,m_arFtpServer[i].user,m_arFtpServer[i].pwd,ConverShareToFtp(m_arFtpServer[i].ftpPath,m_arFtpServer[i].virtualPath));
		pThread->TransFileContiue(localFile,remoteFile, &m_eventComplete,true);
		pThread->m_ctrl = this;
		m_arFtpThreads.Add(pThread);
	}

	return strResult;
}


// RemoteFile = _T("\\\\dell-780e\\媒资素材库B\\test      40C0CB77692545dfB0B2EC5F2210875A.rar");
// localFolder = _T("D:\\testfolder\\");
// rename = _T("fff");
void CFtpHelper::DownloadFileContiue(LPCTSTR RemoteFile, LPCTSTR localFolder,LPCTSTR rename, BOOL isContiue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	// TODO: Add your dispatch handler code here
	m_csCompleteState.Lock();
	m_bDownloadCompleted = false;
	m_csCompleteState.Unlock();
	//如果有搜索在继续，退出搜索

	for(int i=0;i<m_arFtpDownloadThread.GetSize();i++)
	{
		//m_arFtpDownloadThread[i]->Stop();
		//delete m_arFtpDownloadThread[i];
		if(!m_arFtpDownloadThread[i]->IsTransOver())
		{
			m_arFtpDownloadThread[i]->SoftStop();
			m_arFtpDownloadThread[i]->SetAutoRelease(true);
		}
		else
			delete m_arFtpDownloadThread[i];
	}
	m_arFtpDownloadThread.RemoveAll();

	//在服务器数据中查找
	CString strRemote(RemoteFile);
	int nServerIdx = -1;
	for(int i=0;i<m_arFtpServer.GetSize();i++)
	{
		if(strRemote.Left(m_arFtpServer[i].ftpPath.GetLength()).CompareNoCase(m_arFtpServer[i].ftpPath)==0)
		{
			nServerIdx = i;
			break;
		}
	}
	if(nServerIdx == -1)
	{
		OnDownloadComplete(FALSE);   //如果没有对应的服务器信息，出错
		return ;
	}
	//设置ftp服务器信息
	CFtpDownloadThread *pVideoThread = new CFtpDownloadThread;
	//CFtpDownloadThread *pAudioThread = new CFtpDownloadThread;
	CString ftpPath = ConverShareToFtp(strRemote,m_arFtpServer[nServerIdx].virtualPath);
	//ftpPath = _T("/") + ftpPath;
	CString ip,user,pwd;
	UINT port;
	ip = m_arFtpServer[nServerIdx].ip;
	user = m_arFtpServer[nServerIdx].user;
	pwd = m_arFtpServer[nServerIdx].pwd;
	port = m_arFtpServer[nServerIdx].port;
	pVideoThread->SetFtpInfo(ip,port,user,pwd);
	pVideoThread->DownloadFile(ftpPath,localFolder,rename,&m_eventComplete);

	pVideoThread->m_ctrl = this;
	m_arFtpDownloadThread.Add(pVideoThread);

	////添加音频下载线程
	//pAudioThread->SetFtpInfo(ip,port,user,pwd);
	//CString audioFile = ftpPath;
	//int index = ftpPath.ReverseFind(_T('.'));
	//if(index != -1)
	//{
	//	audioFile = ftpPath.Left(index+1);
	//}
	//audioFile = audioFile + _T("wav");
	//if(audioFile.CompareNoCase(ftpPath)!=0)
	//	pAudioThread->DownloadFile(audioFile,localFolder,&m_eventComplete);
	//pAudioThread->m_ctrl = this;
	//m_arFtpDownloadThread.Add(pAudioThread);


}
LPCTSTR CFtpHelper::StopTrans(BOOL isUp)
{
	
	
CString remoteFileTemp;
	//检查是存在该服务点

			if(isUp)
			{

				//关闭已经在运行的线程
				for(int i=0;i<m_arFtpThreads.GetSize();i++)
				{
					//m_arFtpThreads[i]->Stop();
					//delete m_arFtpThreads[i];
					if(!m_arFtpThreads[i]->IsTransOver())
					{
						m_arFtpThreads[i]->SoftStop();
						m_arFtpThreads[i]->SetAutoRelease(true);
					}
					else
						delete m_arFtpThreads[i];

				}
				m_arFtpThreads.RemoveAll();
				remoteFileTemp=strFtpPath;

			}
			else
			{
				//如果有搜索在继续，退出搜索

				for(int i=0;i<m_arFtpDownloadThread.GetSize();i++)
				{
					//m_arFtpDownloadThread[i]->Stop();
					//delete m_arFtpDownloadThread[i];
					if(!m_arFtpDownloadThread[i]->IsTransOver())
					{
						m_arFtpDownloadThread[i]->SoftStop();
						m_arFtpDownloadThread[i]->SetAutoRelease(true);
					}
					else
						delete m_arFtpDownloadThread[i];
				}
				m_arFtpDownloadThread.RemoveAll();
			}


	return remoteFileTemp;
}

void CFtpHelper::OnDownloadComplete(BOOL success)
{
	//FireEvent(eventidOnDownloadComplete, EVENT_PARAM(VTS_BOOL), success);
	::PostMessage(NULL, WM_DOWNLOADCOMPLETE,success,0);
}
void CFtpHelper::OnUploadComplete(SHORT success, SHORT failed)
{
	//FireEvent(eventidOnUploadComplete, EVENT_PARAM(VTS_I2 VTS_I2), success, failed);
	::PostMessage(NULL, WM_UPLOADCOMPLETE,success,failed);
}