#include"stdafx.h"
#include "I43_Api.h"
#include "interface.h"

#pragma comment(lib, "UI43API.LIB")

#define PP_USE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

CDevBase::CDevBase() 
	: m_bMass(false)
{
	InitInterface();
}

CDevBase::~CDevBase()
{
	DeinitInterface();
}


BOOL CDevBase::InitInterface()
{
	BOOL bret = FALSE;

	pSetting = new SUsbSetting;
	if( pSetting )
		bret = TRUE;
	
	return bret;
}

void CDevBase::DeinitInterface()
{
	SAFE_DELETE(pSetting);
}

BOOL CDevBase::IsDeviceReady()
{
	unsigned short uAck = 0;
	I43_ERROR_CODE rlt = I43ERR_FAIL;
	while(uAck != ACK)
	{
		I43IO_ComOpen();
		rlt = I43_GetParam(0xAD, &uAck);
		I43IO_ComClose();
	}

	return rlt == I43ERR_OK;
}