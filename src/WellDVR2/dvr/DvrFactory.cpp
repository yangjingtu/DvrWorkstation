#include "stdafx.h"
#include "DvrFactory.h"
#include "../ShareData.h"
#include "WellDvr34.h"
#include "HADvr.h"

CDvrFactory::CDvrFactory(void)
{
}


CDvrFactory::~CDvrFactory(void)
{
}

CDvrFactory& CDvrFactory::Instance()
{
	static CDvrFactory df;
	return df;
}

CDevBase* CDvrFactory::GetDvr()
{
	CDevBase* pDvr = NULL;
	switch (SHAREDATA.g_nDvrType)
	{
	case DVR_TYPE_WELL_34:
		pDvr = new CWellDvr34();
		break;
	case DVR_TYPE_HA:
		pDvr = new CHADvr();
		break;
	case DVR_TYPE_SHLR_A34:
	case DVR_TYPE_SHLR_D6:
	case DVR_TYPE_SHLR_X6:
		pDvr = new CA4Dvr();
		break;
	default:
		pDvr = DetectDvr();
		break;
	}
	return pDvr;
}

//自动检测DVR
CDevBase* CDvrFactory::DetectDvr()
{
	//调用二代
	CDevBase* pDev = new CA4Dvr();
	if(pDev == NULL)
		return pDev;

	CString strId;
	BOOL bret = pDev->GetIDEx(strId);
	if(!bret || strId.IsEmpty())
	{
		//3,4代DVR
		delete pDev;
		pDev = new CWellDvr34();//CHADvr();
		if(pDev)
			bret = pDev->GetIDEx(strId);
	}
	bret = pDev->GetIDEx(strId);
	if( !bret || strId.IsEmpty())
	{
		delete pDev;
		pDev = NULL;
	}
	return pDev;
}