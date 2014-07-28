#pragma once
#include "netbase.h"

#include <string>
using namespace std;

class CNetClient : public CNetBase
{
public:
	CNetClient(void);
	virtual ~CNetClient(void);

	//Á¬½Ó
	virtual bool Connect(const string& strIp, int nPort);

	virtual bool Init();

	virtual void UnInit();
};

