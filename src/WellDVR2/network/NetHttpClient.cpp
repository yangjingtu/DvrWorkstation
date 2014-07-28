#include "stdafx.h"
#include "NetHttpClient.h"
#include "../ShareData.h"
#include "../WellCommon/CharSetHelper.h"

#include <sstream>
using namespace std;


CNetHttpClient::CNetHttpClient(void)
{
}


CNetHttpClient::~CNetHttpClient(void)
{
}

//发送数据
int CNetHttpClient::Send(const char* buf, int nLen)
{
	if(!Init())
		return -1;

	if( !Connect(WS2S(SHAREDATA.g_strWebIp.GetString()), SHAREDATA.g_nWebPort))
	{
		UnInit();
		return -1;
	}
	
	ostringstream os;
	os << WS2S(SHAREDATA.g_strWebIp.GetString()) << ":" << SHAREDATA.g_nWebPort;
	string strPostString = POSTString(os.str().c_str(), buf, "keep-alive");

	int nSend = CNetTcpClient::Send(strPostString.c_str(), strPostString.length());

//	char bufRecv[200] = {0};
//	nSend = Recv(bufRecv, 200);


	UnInit();
	return nSend;
}

//接收数据
int CNetHttpClient::Recv(char* buf, int nLen)
{
	return CNetTcpClient::Recv(buf, nLen);
}

//////////////////////////////////////////////////////////////////////////
//成功会返回
//HTTP/1.1 200 OK
//Server: Apache-Coyote/1.1
//		Transfer-Encoding: chunked
//Date: Mon, 07 Jul 2014 07:50:52 GMT

//  7
//  success
//  0
//////////////////////////////////////////////////////////////////////////
string CNetHttpClient::POSTString(const char* hostName, const char* api, const char* parameters)
{
	ostringstream os;

	//初始化发送信息
    //头信息
	os << "POST " << api << " HTTP/1.1\r\n"
		<< "Host: " << hostName << "\r\n"
		<< "Connection: keep-alive\r\n"
		<< "Content-Length: " << strlen(parameters) << "\r\n"
		<< "Cache-Control: max-age=0\r\n"
		<< "Origin: http://www.glwell-co.com/html/main.asp\r\n"
		<< "User-Agent: Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/15.0.849.0 Safari/535.1\r\n"
		<< "Content-Type: application/x-www-form-urlencoded\r\n"
		<< "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
		<< "Accept-Encoding: gzip,deflate,sdch\r\n"
		<< "Accept-Language: zh-CN,zh;q=0.8\r\n";

    //内容信息
    os << "\r\n"
		<< parameters;

	return os.str();
}