#pragma once
#include "threadbase.h"
#include <afxmt.h>
#include <afxinet.h>

class CFtpHelper;

//Ftp的文件传送类
class CFtpTransThread :
	public CThreadBase
{
public:
	CFtpTransThread(void);
public:
	~CFtpTransThread(void);
public:
	//传送的信息
	LONGLONG m_nFileSize; //文件大小
	LONGLONG m_nFileTransSize;  //文件已经传送的大小
	CString m_strSourceFile; //源文件
	CString m_strDestFile;   //目标文件
	CString m_ftpIp,m_ftpUser,m_ftpPwd,m_ftpPath; //ftp信息
	CString m_strNewDir,m_strDate,m_strSharePath; //sharepath: ftp目录的共享路径
	UINT m_ftpPort;    //ftp端口
	bool m_bFailed; //是否传送失败
	CCriticalSection m_cs;  //CriticalSection,用来同步faled和transSize
	virtual UINT DoWork();
	CEvent *m_pCompleteEvent;
	CFtpHelper *m_ctrl;   //控件指针
	bool m_bTransOver ; //指示传送是否完毕
	bool IsTransOver(void);
	void SetTransOverFlag(bool value);
public:
	bool FtpTransProc(void);
	
public:
	void SetFtpInfo(CString ip, UINT port,CString user, CString pwd,CString path);
public:
	void TransFile(CString srcFile, CString destFile,CString newDir,CString date,CString sharepath,CEvent *pCompleteEvent);
	void TransFileContiue(CString srcFile, CString remoteFile,CEvent *pCompleteEvent,BOOL isContiue);
public:
	bool IsFailed(void);
protected:
	char *buffer;
	int nBufSize;
	 LONGLONG GetFtpFileSize(CFtpConnection* pFtpCon, CString strFtpFile);

	 //创建多级目录
	 BOOL CreateFTPDirectory(CFtpConnection* pFtpCon, const CString& strPath);
};
