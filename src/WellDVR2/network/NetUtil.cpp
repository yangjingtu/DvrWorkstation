#include "stdafx.h"
#include "NetUtil.h"
#include <Afxsock.h>
#include "../WellCommon/CharSetHelper.h"


CNetUtil::CNetUtil(void)
{
}


CNetUtil::~CNetUtil(void)
{

}

wstring CNetUtil::GetLocalIpAddr()
{
	if(!AfxSocketInit()) 
	{ 
		return _T(""); 
	}

	char szHostName[MAX_PATH + 1];
	gethostname(szHostName, MAX_PATH);			//得到计算机名
	hostent *p = gethostbyname(szHostName);		//从计算机名得到主机信息
	if(p == NULL)
	{
		return _T("");
	}

	//将32位IP转化为字符串IP
	char *pIP = inet_ntoa(*(in_addr *)p->h_addr_list[0]);
	wstring wcsIp = S2WS(pIP);
	return wcsIp;
}
