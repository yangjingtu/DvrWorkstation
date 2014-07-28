#include "StdAfx.h"
#include "ThreadBase.h"

CThreadBase::CThreadBase(void)
{
	m_bRunning = false;
	m_bAutoRelease = false;
	m_bForceStop =  false;
}

CThreadBase::~CThreadBase(void)
{
}

void CThreadBase::Begin()
{
	m_pThread = AfxBeginThread((AFX_THREADPROC)ThreadProc,this);
}
void CThreadBase::Stop()
{
	if(m_bRunning)
		TerminateThread(m_pThread->m_hThread,0);
}

UINT CThreadBase::ThreadProc(LPVOID pParam)
{
	
	CThreadBase *pThread = (CThreadBase*) pParam;
	pThread->m_bRunning = true;
	UINT ret;
	ret = pThread->DoWork();
	pThread->m_bRunning = false;
	if(pThread->m_bAutoRelease)
		delete pThread;
	return ret;
}
UINT CThreadBase::ThreadProcContiue(LPVOID pParam)
{

	CThreadBase *pThread = (CThreadBase*) pParam;
	pThread->m_bRunning = true;
	UINT ret;
	ret = pThread->DoWork();
	pThread->m_bRunning = false;
	if(pThread->m_bAutoRelease)
		delete pThread;
	return ret;
}
bool CThreadBase::IsRunning(void)
{
	return m_bRunning;
}

void CThreadBase::SetAutoRelease(bool value)
{
	m_bAutoRelease = value;
}

void CThreadBase::SoftStop(void) //»ÌÕ£÷π
{
	m_bForceStop = true;
}
