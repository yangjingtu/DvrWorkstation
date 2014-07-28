#pragma once

class CThreadBase
{
public:
	CThreadBase(void);
public:
	virtual ~CThreadBase(void);
	 void Begin();
	 void Stop();
	virtual UINT DoWork()=0;
protected:
	CWinThread *m_pThread;
	bool m_bRunning; //线程是否在运行
	static UINT ThreadProc(LPVOID pParam);
	static UINT ThreadProcContiue(LPVOID pParam);
	bool m_bAutoRelease;
	bool m_bForceStop;  //停止标志位
	bool m_isContiue;

public:
	bool IsRunning(void);
	void SetAutoRelease(bool value);
	void SoftStop(void);
};
