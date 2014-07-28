#include "stdafx.h"
#include "SockInit.h"

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")


CSockInit::CSockInit(void)
{
	Init();
}


CSockInit::~CSockInit(void)
{
	UnInit();
}

CSockInit& CSockInit::Instance()
{
	static CSockInit sock;
	return sock;
}

bool CSockInit::Init()
{
	WORD wVersionRequested;	
	WSADATA wsaData;	
	int err;
	wVersionRequested = MAKEWORD(1,1);
	err = WSAStartup(wVersionRequested,&wsaData);
	if(err != 0)//返回0表示成功
	{
		return false;
	}

	//高位字节指出副版本(修正)号，低位字节指明主版本号。/* Confirm that the Windows Sockets DLL supports 1.1.*/ 
	if(LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		/* Tell the user that we couldn't find a useable  winsock.dll. */ 
		WSACleanup();//终止Winsock 2 DLL (Ws2_32.dll) 的使用.
		return false;
	}
	return true;
}

void CSockInit::UnInit()
{
	WSACleanup();
}