#include "stdafx.h"
#include "ShareData.h"
#include "config/Config.h"

CShareData::CShareData(void)
{
	Init();
}


CShareData::~CShareData(void)
{
	UnInit();
}

CShareData& CShareData::Instance()
{
	static CShareData sd;
	return sd;
}

void CShareData::Init()
{
	g_dvrProp.numDvr = DVR_TOTAL_NUM;
	g_dvrProp.numRow = ROWS;
	g_dvrProp.numCol = COLS;

#ifndef ONE_DVR
	g_dvrProp = CONF.GetSettingInfo().dvrProp;
#endif

	g_dwFreeSpace = -1;
	g_dwTotalSpace = -1;

	g_dbgLevel = WORKING;

	g_strDeviceId.Empty();
	
	g_nDvrType = DVR_TYPE_WELL_34;
}

void CShareData::UnInit()
{
	g_dbgLevel = WORKING;

	g_strDeviceId.Empty();
}