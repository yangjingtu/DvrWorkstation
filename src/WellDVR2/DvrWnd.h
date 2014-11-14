/************************************************************************/
/* 描述：DVR设备类
   时间：created by yjt 2014-4-12
   历史：
*/
/************************************************************************/
#pragma once

#include "DataDef.h"
#include <map>
#include <afxmt.h>
using namespace std;

UINT CopyProc(LPVOID param);

class CDevBase;
class CDvrWnd;
typedef map<int, CDvrWnd*> MapDvrTimer;
typedef MapDvrTimer::iterator MapDvrTimerItor;

class CDvrWnd
{
	friend UINT CopyProc(LPVOID param);
public:
	CDvrWnd(void);
	CDvrWnd(bool empty);
	~CDvrWnd(void);

	CDvrWnd& operator=(const CDvrWnd& dvr);

	void SetStatus(DVRSTATUS ds) { m_status = ds; }
	DVRSTATUS GetStatus() const { return m_status; }

	void SetPos(int x, int y) { m_x = x; m_y = y; }
	int GetRow() const { return m_x; }
	int GetColumn() const { return m_y; }

	void SetId(const CString& strId) { m_strId = strId; }
	CString GetId() const { return m_strId; }
	
	void SetName(const CString& strName) { m_strName = strName; }
	CString GetName() const { return m_strName; }

	void SetFile(const CString& strFile) { m_strFile = strFile; }
	CString GetFile() const { return m_strFile; }

	void SetDisk(const CString& strDisk) { m_strDisk = strDisk; }
	CString GetDisk() const { return m_strDisk; }

	int GetProgressMax() const { return m_proRange; }
	int GetProgressValue() const { return m_proValue; }

	void SetStatusStr(const CString& strInfo) { m_strStatus = strInfo; }
	CString& GetStatusStr() { return m_strStatus; }

	CString& GetSpeedStr() { return m_strSpeed; }

	void SetCopyStatus(int nStatus);

	//清空所有信息
	void ClearInfo();

	//拷贝目录
	void CopyDir(const CString& strDrive);

	//设置和获取 指向设备的对象
	CDevBase* GetDevPtr() const { return m_pDev; }
	void SetDevPtr(CDevBase* pDev);
	void RemoveDevPtr();

	void SyncTime();
	//枚举设备
	void MassDev();
	BOOL IsCopying() { return m_bIsCopying; }
	void SetCopying(bool isCopying) { m_bIsCopying = isCopying; }

protected:

	bool IsLogFile(const CString& strFileName);
	//拷贝日志文件（追加拷贝)
	bool CopyLogFile(const TCHAR* strFileSrc, const TCHAR* strDst);

private:
	void Init(bool empty);
	void UnInit();

	//CopyFileEx的回调函数，在此函数中实现文件复制过程的控制。
	static DWORD CALLBACK CopyProgressRoutine(
		LARGE_INTEGER TotalFileSize,
		LARGE_INTEGER TotalBytesTransferred,
		LARGE_INTEGER StreamSize,
		LARGE_INTEGER StreamBytesTransferred,
		DWORD dwStreamNumber,
		DWORD dwCallbackReason,
		HANDLE hSourceFile,
		HANDLE hDestinationFile,
		LPVOID lpData
		);

private:
	UINT CopyDirProc();
	void CopyDir(const TCHAR *src, const TCHAR *dst, LPBOOL bCancelCopy);

	void RecursiveFindFile(const CString& strPath);

	BOOL CreateDeepDirectory(const CString& strPath,        //directory name
		LPSECURITY_ATTRIBUTES lpSecurityAttributes  // SD
		);

	void InitSpeed();
	void UnInitSpeed();
	void ClearSpeed();

	void ResetTransSize() { 
		m_nTotalTanstime = 0;
		m_llTransSize = 0;
	}

	void SpaceLessAlarm();

	//定时器回调， 必须在头文件中定义(全局函数也是，同时要加static)
	static void CALLBACK CopyTimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);

private:
	CString m_strId;			//ID
	CString m_strName;			//NAME
	CString m_strDisk;			//盘符
	CString m_intPocess;		//进度
	DVRSTATUS m_status;			//状态
	CString m_strFile;

	////////////////////////////////////////////////////
	//拷贝速度
	CString m_strSpeed;			//拷贝速度

	//拷贝速度定时器
	UINT_PTR m_cpTimerId;
	int m_nTotalTanstime;		//总传输时间(秒)
	LONGLONG m_llTransSize;		//传输的大小(每个文件)
	static MapDvrTimer m_mapTimer;
	////////////////////////////////////////////////////


	//对应窗口的位置
	int m_x;
	int m_y;	

	int m_proRange;				//进度条的范围
	int m_proValue;				//进度条当前值
	
	//状态显示字符串
	CString m_strStatus;

private:

	HANDLE m_hCopyEvent;
	HANDLE m_hCopyThread;

	BOOL m_bExit;
	volatile int m_CopyStatus;
	//此变量和m_CopyStatus相对应
	//m_bStopCopy = true时，中止拷贝  
	BOOL m_bStopCopy;			

	CString m_strDstPath;
	CString m_strSrcPath;
	volatile int m_filecnt;

	//对应的DVR对象
	CDevBase* m_pDev;
	CCriticalSection m_cs;
	BOOL m_bIsCopying;		//是否正在拷贝

	//读取文件的次数, U盘多了之后，刚开始可能读到不到文件，一会准备好之后可以读到文件
	short m_nReadFileCount;		
};