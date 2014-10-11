#pragma once
#include "../stdafx.h"

#define DECLARE_LOCK CRITICAL_SECTION m_cri;
#define INIT_LOCK InitializeCriticalSection(&m_cri)
#define UNINIT_LOCK DeleteCriticalSection(&m_cri)
#define LOCK CCriLock lock(m_cri)

class CCriLock
{
public:
	CCriLock(CRITICAL_SECTION &rcri);
	~CCriLock(void);

	CRITICAL_SECTION &m_rcri;
};

