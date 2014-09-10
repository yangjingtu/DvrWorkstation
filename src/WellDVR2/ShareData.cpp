#include "stdafx.h"
#include "ShareData.h"

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