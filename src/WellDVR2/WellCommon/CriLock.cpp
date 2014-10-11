#include "stdafx.h"
#include "CriLock.h"


CCriLock::CCriLock(CRITICAL_SECTION& rcri)
	: m_rcri(rcri)
{
	EnterCriticalSection(&m_rcri);
}


CCriLock::~CCriLock(void)
{
	LeaveCriticalSection(&m_rcri);
}
