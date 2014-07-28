#include "stdafx.h"
#include "NetBase.h"


CNetBase::CNetBase(void)
	: m_sock(NULL)
{
}


CNetBase::~CNetBase(void)
{
}

int CNetBase::Send(const char* buf, int nLen)
{
	return send(m_sock, buf, nLen, 0);
}

int CNetBase::Recv(char* buf, int nLen)
{
	return recv(m_sock, buf, nLen, 0);
}