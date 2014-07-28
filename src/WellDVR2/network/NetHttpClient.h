#pragma once
#include "NetTcpClient.h"

class CNetHttpClient :
	public CNetTcpClient
{
public:
	CNetHttpClient(void);
	virtual ~CNetHttpClient(void);

	//发送数据
	virtual int Send(const char* buf, int nLen);

	//接收数据
	virtual int Recv(char* buf, int nLen);

private:
	string POSTString(const char* hostName, const char* api, const char* parameters);
	string HttpString(const char* parames, int type);
};

