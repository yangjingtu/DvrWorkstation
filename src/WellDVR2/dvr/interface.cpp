#include"stdafx.h"
#include "I43_Api.h"
#include "../DataDef.h"
#include "interface.h"

#define PP_USE

CDevBase::CDevBase() 
	: m_bMass(false)
	, m_bSetTime(false)
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

void CDevBase::ClearInfo()
{
	m_bSetTime = false;
	m_bMass = false;
}