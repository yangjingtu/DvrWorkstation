#include "stdafx.h"
#include "DvrFactory.h"
#include "../WellDVR2/dvr/HADvr.h"
#include "../WellDVR2/dvr/WellDvr34.h"


CDvrFactory::CDvrFactory(void)
{
}


CDvrFactory::~CDvrFactory(void)
{
}

CDevBase* CDvrFactory::GetDvr()
{
	CString strId;
	//调用二代
	CDevBase* pDev = new CA4Dvr();
	if(pDev == NULL)
		return NULL;

	BOOL bret = pDev->GetIDEx(strId);
	if(!bret || strId.IsEmpty())
	{
		//3,4代DVR
		delete pDev;
		pDev = new CWellDvr34();//CHADvr();
		if(pDev)
			bret = pDev->GetIDEx(strId);
	}
	if( !bret || strId.IsEmpty())
	{
		delete pDev;
		pDev = NULL;
	}

	return pDev;
}