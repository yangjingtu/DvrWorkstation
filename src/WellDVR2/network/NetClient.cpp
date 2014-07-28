#include "stdafx.h"
#include "NetClient.h"


CNetClient::CNetClient(void)
{
}


CNetClient::~CNetClient(void)
{

}

bool CNetClient::Connect(const string& strIp, int nPort)
{
	if(m_sock == INVALID_SOCKET)
		return false;

	SOCKADDR_IN addrSrv;//socketAddress socket端口
	//服务器端口配置
	addrSrv.sin_addr.S_un.S_addr = inet_addr(strIp.c_str());
	//作为客户端，你要连接【connect】到远端的服务器，也是要指定远端服务器的（ip, port）对。
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(nPort);

	if(SOCKET_ERROR == connect(m_sock,(SOCKADDR *) &addrSrv,sizeof(SOCKADDR)))
	{
		DWORD dwErr = GetLastError();
		return false;
	}

	return true;
}

bool CNetClient::Init()
{
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(m_sock == SOCKET_ERROR)
	{
		m_sock = NULL;
		return false;
	}
	return true;
}

void CNetClient::UnInit()
{
	if(m_sock)
		closesocket(m_sock);
	m_sock = NULL;
}