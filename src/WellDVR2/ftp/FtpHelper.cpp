#include "stdafx.h"
#include "FtpHelper.h"
#include "../WellCommon/CharSetHelper.h"

MapTimer CFtpHelper::m_mapTimerObjs;

CFtpHelper::CFtpHelper()
	: m_pInetSession(NULL)
	, m_pFtpConnection(NULL)
	, m_nPort(21)
	, m_hEvent(NULL)
	, m_hThread(NULL)
	, m_bExit(false)
	, m_nPutStatus(EM_PUT_UNKNOW)
	, m_bForceStop(false)
{
	Init();
}


CFtpHelper::~CFtpHelper()
{
	Unit();
}

bool CFtpHelper::Init()
{
	m_regCB.tfCB = NULL;
	m_regCB.ttNotify = NULL;

	m_nBufSize = 2000000;
	m_pBuffer = new char[m_nBufSize];
	ReSetTrans();

	//拷贝定时器
	//第二个参数为0，会自动分配一个id号
	m_putTimerId = ::SetTimer(NULL, 0, 1000, (TIMERPROC)CFtpHelper::PutTimerProc);

	//存储
	m_mapTimerObjs[m_putTimerId] = this;

	return true;
}

void CFtpHelper::Unit()
{
	ReSetTrans();
	::KillTimer(NULL, m_putTimerId);
	//删除项
	m_mapTimerObjs.erase(m_mapTimerObjs.find(m_putTimerId));

	if( m_hThread )
	{
		WaitForSingleObject(m_hThread, 2000);
		m_hThread = NULL;
	}

	if( m_hEvent )
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}

	if(m_pFtpConnection)
	{
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
		m_pFtpConnection = NULL;
	}

	if(m_pInetSession)
	{
		m_pInetSession->Close();
		delete m_pInetSession;
		m_pInetSession = NULL;
	}

	if(m_pBuffer)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}

bool CFtpHelper::_Start( const wstring& addr, const wstring& strUser, const wstring& strPwd, UINT nPort)
{
	m_strServAddr = addr;
	m_strUser = strUser;
	m_strPwd = strPwd;
	m_nPort = nPort;

	if(Start())
	{
		//m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		//m_hThread = AfxBeginThread(PutFileProc, this);
		return true;
	}

	return false;
}

bool CFtpHelper::Start()
{
	if(m_pInetSession)
	{
		m_pInetSession->Close();
		delete m_pInetSession;
	}

	m_pInetSession = new CInternetSession(_T("welldvr"), 1, PRE_CONFIG_INTERNET_ACCESS);
	try
	{
		if(m_pFtpConnection)
		{
			m_pFtpConnection->Close();
			delete m_pFtpConnection;
			m_pFtpConnection = NULL;
		}
		//最后一个参数要为TRUE, 不然在执行到FindFile的时候,程序就卡住了（CFtpHelperFindfile)
		m_pFtpConnection = m_pInetSession-> GetFtpConnection(m_strServAddr.c_str(), m_strUser.c_str(), m_strPwd.c_str(), m_nPort,TRUE);
	}
	catch(CInternetException *pEx)
	{
		//若登陆不成功则抛出异常，以下是针对异常的处理
		TCHAR szError[1024] = {0};
		if(pEx->GetErrorMessage(szError,1024))
		{
			CString strError;
			strError.Format(_T("连接FTP服务器错误：%s\r\n请检查配置文件中的ftp服务器信息!"), szError);
			AfxMessageBox(strError);
		}
		else
			AfxMessageBox(_T("There was an exception"));
		pEx->Delete();
		m_pFtpConnection = NULL;
		return false;
	}
	return true;
}

void CFtpHelper::Stop()
{
	if(m_pFtpConnection)
	{
		m_pFtpConnection->Close();
		delete m_pFtpConnection;
		m_pFtpConnection = NULL;
	}

	if(m_pInetSession)
	{
		m_pInetSession->Close();
		delete m_pInetSession;
		m_pInetSession = NULL;
	}
}

UINT PutFileProc(LPVOID pFtp)
{
	CFtpHelper* p = static_cast<CFtpHelper*>(pFtp);
	if(p)
	{
		return p->PutFile();
	}
	return 0;
}

UINT CFtpHelper::PutFile()
{
	while( ::WaitForSingleObject(m_hEvent, INFINITE) == WAIT_OBJECT_0 )
	{
		if(m_bExit )
			break;

		if(m_strPutFile.empty() || m_strSaveFile.empty())
			continue;
		
		//第一个参数为本地文件的地址，第二个为服务器端文件的地址
		if(m_pFtpConnection->PutFile(m_strPutFile.c_str(), m_strSaveFile.c_str()))
		{
			m_strPutFile.clear();
			m_strSaveFile.clear();
			m_nPutStatus = EM_PUT_OK;
		}
		else
		{			
			m_nPutStatus = EM_PUT_FAIL;
			DWORD dw = GetLastError();
			CString strErr;
			strErr.Format(_T("FTP上传失败！[%d]\r\n文件：%s"), dw, m_strSaveFile);
			//SHAREDATA.g_pMainFrame->Alert(strErr);
		}

		ResetEvent(m_hEvent);
	}

	return 1;
}

UINT CFtpHelper::_PutFile(const wstring& strFileName, const wstring& saveFile)
{
	if(strFileName.empty() || saveFile.empty())
	{
		return 0;
	}

	m_nPutStatus = EM_PUT_UNKNOW;

	m_strSaveFile = saveFile;
	m_strPutFile = strFileName;

	SetEvent(m_hEvent);	
	while(m_nPutStatus == EM_PUT_UNKNOW)
	{
		Sleep(10);
	}

	return m_nPutStatus == EM_PUT_OK ? 1 : 0;
}

bool CFtpHelper::_CreateDirctory(const wstring& strPath)
{
	if(strPath.empty())
		return false;

	bool bError = false;

	if( !m_pFtpConnection->CreateDirectory(strPath.c_str()) )
	{
		DWORD err = GetLastError();
		if(err == ERROR_INTERNET_EXTENDED_ERROR)
		{
			DWORD dwError;
			TCHAR buf[200];
			DWORD size=200;	
			InternetGetLastResponseInfo(&dwError,buf,&size);
			CString strError(buf);
			if(strError.Left(3) == _T("550") )
				bError = false;  //目录如果已经存在，则认为没有错误
			else
				bError = true;
		}
	}

	return !bError;
}

void CFtpHelper::ServiceRun()
{
	//FTP后台线程
	AfxBeginThread((AFX_THREADPROC)FtpThrProc, this);
}

DWORD WINAPI FtpThrProc(LPVOID param)
{
	CFtpHelper* p = (CFtpHelper*)param;
	if(p)
	{
		p->Service();
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//功能：递归删除空文件夹
//参数：
//		strFolde [IN]	--	本地文件夹路径，发E:\\test-ftp
//返回：文件夹的文件个数
//
//////////////////////////////////////////////////////////////////////////
int CFtpHelper::DelEmptyFolder(const wstring& strFolder)
{
	CFileFind tempFind; 
	BOOL bFound; //判断是否成功找到文件
	bFound = tempFind.FindFile(wstring(strFolder + _T("\\*.*")).c_str());

	int fileCount = 0;

	CString strTmp;   //如果找到的是文件夹 存放文件夹路径
	while(bFound)     //遍历所有文件
	{ 
		bFound = tempFind.FindNextFile(); //第一次执行FindNextFile是选择到第一个文件，以后执行为选择

		if(tempFind.IsDots()) 
			continue;
		if(tempFind.IsDirectory())   //找到的是文件夹，则遍历该文件夹下的文件
		{ 
			strTmp = tempFind.GetFilePath();
			CString strF = tempFind.GetFileName();
				
			int fileCount = DelEmptyFolder(strTmp.GetString()); 

			if(fileCount == 0)
			{	
				//删除空文件夹
				RemoveDirectory(strTmp); 
			} 
		}
		else 
		{ 
			fileCount++;
		}
	} 
	tempFind.Close();
	return fileCount;
}


void CFtpHelper::Service()
{
	//不停的从本地目录中上传到ftp服务器上
	if(m_strLocalDir.empty())
		return;

	int nRlt = TRANS_CONTUNE;
	while(true)
	{
		nRlt = TRANS_CONTUNE;
		//开始之前通知客户
		if(m_regCB.ttNotify)
			nRlt = m_regCB.ttNotify(TRANS_BEGIN);

		if(nRlt == TRANS_CONTUNE)
		{
			_TransFolder(m_strLocalDir, _T(""));
		}

		//删除文件可能需要一小段时间，睡一会再调删除空文件夹		
		Sleep(5000);
		

		nRlt = TRANS_SKIP;
		//传输结束后通知客户
		if(m_regCB.ttNotify)
			nRlt = m_regCB.ttNotify(TRANS_END);
		if(nRlt == TRANS_DELETE)
		{
			//删除空文件夹
			DelEmptyFolder(m_strLocalDir);
		}

		Sleep(2000);
	}
}

//判断ftp服务器是否存在此文件
//如果存在返回文件的大小
LONGLONG CFtpHelper::IsFileExit(const wstring& strFile)
{
	CFtpFileFind ftpff(m_pFtpConnection);
	LONGLONG filelen = 0;
	if(ftpff.FindFile(strFile.c_str())) 
	{ 
		ftpff.FindNextFile(); 
		filelen = ftpff.GetLength(); 
	} 
	ftpff.Close();

	return filelen;
}

bool CFtpHelper::_TransFolder(const wstring& strFoldername, const wstring& strDst)
{
	CInternetFile *pInetFile = NULL;
	try
	{
		CFileFind tempFind; 
		BOOL bFound; //判断是否成功找到文件
		bFound = tempFind.FindFile(wstring(strFoldername + _T("\\*.*")).c_str());

		if(!strDst.empty()  && !_CreateDirctory(strDst))
		{
			return false;
		}

		CString strTmp;
		while(bFound)
		{ 
			//第一次执行FindNextFile是选择到第一个文件，以后执行为选择
			bFound = tempFind.FindNextFile(); 

			if(tempFind.IsDots()) 
				continue;
			if(tempFind.IsDirectory())
			{ 
				//找到的是文件夹，则遍历该文件夹下的文件
				strTmp = tempFind.GetFilePath();
				CString strF = tempFind.GetFileName();

				_TransFolder(strTmp.GetString(), strDst + _T("\\") + strF.GetString());
			} 
			else 
			{ 
				m_bForceStop = false;

				CFile localFile;
				strTmp = tempFind.GetFilePath();//保存文件名，包括后缀名

				int nRlt = TRANS_CONTUNE;
				//add by yjt 2014-06-13	回调上传文件，由客户决定是否上传
				if(m_regCB.tfCB != NULL && TRANS_SKIP == (nRlt = m_regCB.tfCB(strTmp.GetString())) )
				{
					continue;
				}

				if(!localFile.Open(strTmp, CFile::modeRead|CFile::shareDenyNone))
				{
					m_llFileSize = 0;
					m_llTransSize = 0;
					Sleep(10);
					continue;
				}

				//远程目录要从根目录开始
				CString strReoveFie;
				strReoveFie.Format(_T("%s\\%s"), strDst.c_str() ,tempFind.GetFileName());
				
				m_llFileSize = localFile.GetLength();
				m_llTransSize = IsFileExit(strReoveFie.GetString());
				//如果文件已存在，且大小一样, 说明已传过
				if(m_llTransSize == m_llFileSize)
				{
					localFile.Close();
					continue;
				}

				if(m_llTransSize > 0)
				{
					//断点续传
					try
					{
						localFile.Seek(m_llTransSize, CFile::begin);
						pInetFile = m_pFtpConnection->Command(_T("APPE ") + strReoveFie, CFtpConnection::CmdRespWrite);
						TRACE("begin %lld/%lld!!!\n", m_llTransSize, m_llFileSize);
						//续传时,传输大小清0，否则速度不对
						m_llTransSize = 0;
					}
					catch (CInternetException* e)
					{
						pInetFile = m_pFtpConnection->OpenFile(strReoveFie, GENERIC_WRITE);	
					}
				}
				else
				{
					pInetFile = m_pFtpConnection->OpenFile(strReoveFie, GENERIC_WRITE);
				}

				m_strPutFile = tempFind.GetFileName(); 
				int len = 0;
				while( len = localFile.Read(m_pBuffer,m_nBufSize))
				{
					pInetFile->Write(m_pBuffer,len);
					m_cs.Lock();
					m_llTransSize += len;
					m_cs.Unlock();

					TRACE("trans %lld/%lld!!!!\n" , m_llTransSize, m_llFileSize);
					//是否停止传输
					if(m_bForceStop)
					{
						localFile.Close();
						if(pInetFile)
						{
							pInetFile->Close();
							delete pInetFile;
						}
						break;
					}
				}
				TRACE("end %lld/%lld!!!!\n" , m_llTransSize, m_llFileSize);
				localFile.Close();
				pInetFile->Close();
				ReSetTrans();

				if(pInetFile)
				{
					pInetFile->Close();
					delete pInetFile;
					pInetFile = NULL;
				}

				if(!m_bForceStop)
				{	
					if(nRlt == TRANS_DELETE)
					{
						//删除文件
						DeleteFile(strTmp);
					}
				}
			} 
		} 
		tempFind.Close();
		ReSetTrans();
		return true;
	}
	catch(CInternetException *e)
	{
		if(pInetFile)
		{
			pInetFile->Close();
		}
		e->Delete();
	}
	catch(CFileException *e)
	{
		e->Delete();
		DWORD error = GetLastError();
	}
	if(pInetFile)
	{
		delete pInetFile;
		pInetFile = NULL;
	}

	//重连
	ReStart();

	return false;
}

bool CFtpHelper::ReStart()
{
	Stop();
	Sleep(1000);

	ReSetTrans();

	return Start();
}

void CFtpHelper::ReSetTrans()
{	
	m_cs.Lock();
	m_llFileSize = 0;
	m_llTransSize = 0;
	m_nTotalTanstime = 0;
	m_strPutFile.clear();
	m_strSpeed.clear();
	m_cs.Unlock();
}

//获取传送百分比
float CFtpHelper::GetTransPrecent()
{ 
	float fPrecent = 0;
	if(m_llFileSize > 0)
	{
		m_cs.Lock();
		fPrecent = (float)m_llTransSize / m_llFileSize; 
		if(fPrecent > 1)
			fPrecent = 1;
		if(fPrecent < 0)
			fPrecent = 0;
		m_cs.Unlock();

	}
	return fPrecent;
}

//获取传送速度
wstring CFtpHelper::GetTransSpeed()
{ 
	return m_strSpeed;
}

void CFtpHelper::GetTransSpeed(wstring& strspd)
{ 
	strspd = m_strSpeed;
}

void CFtpHelper::GetPutFile(wstring& strpf)
{
	strpf = m_strPutFile;
}

wstring CFtpHelper::GetPutFile()
{
	return m_strPutFile;
}

//定时计算传输速度
void CALLBACK CFtpHelper::PutTimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime)
{
	if( m_mapTimerObjs.find(idEvent) == m_mapTimerObjs.end())
		return;

	CFtpHelper* pFtp = m_mapTimerObjs[idEvent];
	if(pFtp == NULL)
	{
		return;
	}

	if(pFtp->m_llTransSize > 100)
	{
		pFtp->m_nTotalTanstime += 1;
		float fSpeed = pFtp->m_llTransSize / pFtp->m_nTotalTanstime;   // B/s
		fSpeed = fSpeed / 1024/1024;
		CString strSd;
		strSd.Format(_T("传输速度:%.2fMB/s"), fSpeed);
		pFtp->m_strSpeed = strSd.GetString();
	}
}

//启动ftp客户端
bool CFtpHelper::Start(const string& addr, const string& strUser, const string& strPwd, UINT nPort, const string& strDir)
{
	return Start(S2WS(addr), S2WS(strUser), S2WS(strPwd), nPort, S2WS(strDir));
}

bool CFtpHelper::Start(const wstring& addr, const wstring& strUser, const wstring& strPwd, UINT nPort, const wstring& strDir)
{
	m_strLocalDir = strDir;
	return _Start(addr.c_str(), strUser.c_str(), strPwd.c_str(), nPort);
}


//创建目录
bool CFtpHelper::CreateDirctory(const wstring& strPath)
{
	return _CreateDirctory(strPath);
}

bool CFtpHelper::CreateDirctory(const string& strPath)
{
	return CreateDirctory(S2WS(strPath));
}

//上传文件
UINT CFtpHelper::PutFile(const wstring& strFile, const wstring& saveFile)
{
	return _PutFile(strFile, saveFile);
}

UINT CFtpHelper::PutFile(const string& strFile, const string& saveFile)
{
	return PutFile(S2WS(strFile), S2WS(saveFile));
}

//上传文件夹
bool CFtpHelper::TransFolder(const wstring& strFoldername, const wstring& strDst)
{
	return  _TransFolder(strFoldername, strDst);
}

bool CFtpHelper::TransFolder(const string& strFoldername, const string& strDst)
{
	return TransFolder(S2WS(strFoldername), S2WS(strDst));
}

void CFtpHelper::Register(const RegCB& cb)
{
	m_regCB = cb;
}

bool CFtpHelper::operator==(const CFtpHelper& ftp)
{
	return (this == &ftp);
}