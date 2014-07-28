#pragma once
#include "threadbase.h"
#include <afxmt.h>
#include <afxinet.h> 

class CFtpHelper;

class CFtpDownloadThread :
	public CThreadBase
{
public:
	CFtpDownloadThread(void);
	~CFtpDownloadThread(void);
	CCriticalSection m_cs;
	CString m_strFtpFile,m_strLocalFolder; //源目标文件，本地目录
	CString m_strRename; //下载重命名
	CString m_strFileName,m_strFileTitle;  //文件名，文件标题
	CString m_ftpIp,m_ftpUser,m_ftpPwd;
	bool m_bFailed;
	UINT m_ftpPort;
	CEvent *m_pEvent;
	LONGLONG m_nFileTransSize ;
	LONGLONG m_nFileSize ;
	CFtpHelper *m_ctrl;   //控件指针
	bool m_bTransOver ; //指示传送是否完毕


	void SetFtpInfo(CString ip, UINT port, CString user, CString pwd);
	UINT DoWork(void);
	bool DownloadProc(void);
	
	void DownloadFile(CString ftpPath, CString localFolder,CString rename,CEvent *pEvent);
protected:
	char *buffer;
	int nBufSize;
public:
	LONGLONG GetFtpFileSize(CFtpConnection* pFtpCon, CString strFtpFile);
	bool IsFailed(void);
	bool IsTransOver(void);
	void SetTransOverFlag(bool value);
	CString GetAudioFileName(CFtpConnection* pFtpCon,CString strVideo);
	CString GetPureName(CString fullname);
	int ParsePasv( char *buf );
};
