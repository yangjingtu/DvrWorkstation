#pragma once
#include "NetClient.h"

class CNetUdp :
	public CNetClient
{
public:
	CNetUdp(void);
	virtual ~CNetUdp(void);

	//发送数据
	virtual int Send(const char* buf, int nLen);

	//接收数据
	virtual int Recv(char* buf, int nLen);
};

