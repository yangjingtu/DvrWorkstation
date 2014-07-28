//////////////////////////////////////////////////////////////////////////
//Describe:	网络层基类
//Date: created by yjt 2014-07-07
//History:
//////////////////////////////////////////////////////////////////////////
#pragma once


class CNetBase
{
public:
	CNetBase(void);
	virtual ~CNetBase(void);

public:
	virtual bool Init() = 0;
	virtual void UnInit() = 0;

	//发送数据
	virtual int Send(const char* buf, int nLen);

	//接收数据
	virtual int Recv(char* buf, int nLen);

protected:
	SOCKET m_sock;
};

