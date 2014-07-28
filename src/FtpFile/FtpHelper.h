#pragma once

#include <afxmt.h>

#define WM_UPLOADCOMPLETE WM_USER+1
#define WM_DOWNLOADCOMPLETE WM_USER+2

class CFtpTransThread;
class CFtpDownloadThread;

class AFX_EXT_CLASS CFtpHelper
{
public:
	CFtpHelper(void);
	~CFtpHelper(void);

public:

	void AddServerPath(LPCTSTR ftpPath, BOOL virtualPath, LPCTSTR ip, UINT port, LPCTSTR user, LPCTSTR pwd);
	void ClearServerPath(void);

	LPCTSTR Upload(LPCTSTR localFile, LPCTSTR newDir, LPCTSTR rename, SHORT type);
	SHORT GetUploadPercent(void);
	LPCTSTR UploadContiue(LPCTSTR localFile, LPCTSTR remoteFile, BOOL isContiue);

	void DownloadFile(LPCTSTR RemoteFile, LPCTSTR localFolder,LPCTSTR rename);
	SHORT GetDownloadPercent(void);
	void DownloadFileContiue(LPCTSTR RemoteFile, LPCTSTR localFolder,LPCTSTR rename, BOOL isContiue);

	
	SHORT DelFtpFile(LPCTSTR ftpIp, LPCTSTR ftpUsr, LPCTSTR ftpPwd, SHORT ftpPort, LPCTSTR path);
	
	LPCTSTR StopTrans(BOOL isUp);

	void CheckComplete(void);

private:
	CString CreateGuid(void);
	static UINT CompleteMonitorThread(LPVOID pParam);
	CString ConverShareToFtp(CString sharepath, bool virtualPath);

	CString GetSharePath(const CString& path,bool virtualPath);

	void OnDownloadComplete(BOOL success);
	void OnUploadComplete(SHORT success, SHORT failed);

protected:
	//	void OnFailedListChanged(void);
	VARIANT m_FailedList;

	//	void OnFileListChanged(void);
	VARIANT m_FileList;

private:
	CWinThread *m_pCompleteMonitorThread;   //监视传送完成的线程
	CEvent m_eventComplete;
	struct FtpServerInfo  //Ftp服务器信息
	{
		CString ftpPath;
		CString ip;
		CString user;
		short port;
		CString pwd;
		bool virtualPath; //是否是虚拟路径
	};

	CArray<FtpServerInfo,FtpServerInfo&> m_arFtpServer; //FTP目录列表
	CArray<CFtpTransThread*,CFtpTransThread*> m_arFtpThreads; //单个服务器上传线程
	CArray<CFtpDownloadThread*,CFtpDownloadThread*> m_arFtpDownloadThread; //单个服务器下载线程
	bool m_bUploadCompleted; //上载已经触发
	bool m_bDownloadCompleted; //下载已经触发
	CCriticalSection m_csCompleteState; 

	CString m_date;
	CString strFtpPath;
};

