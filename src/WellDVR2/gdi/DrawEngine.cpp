#include "stdafx.h"
#include "DrawEngine.h"

#define PI 3.1415926

CDrawEngine::CDrawEngine(void)
{
}


CDrawEngine::~CDrawEngine(void)
{
}

CDrawEngine& CDrawEngine::Instance()
{
	static CDrawEngine de;
	return de;
}

//////////////////////////////////////////////////////////////////////////
//Function:	绘制饼图
//Params:
//		hWnd [IN]		--		窗口句柄（在此窗口作画）
//		rcDraw [IN]	--		绘制限定区域（作画区域)
//		pieInfo [IN]	--		各个区间比例,颜色，标题, 所有值加起来要为1
//		size [IN]		--		pecent的大小
//Return:
//Date: [2014/11/15 yjt]
//History:
//////////////////////////////////////////////////////////////////////////
bool CDrawEngine::DrawPie(HWND hWnd, RECT rcDraw, PPieInfo pieInfo, int size)
{
	if(hWnd == NULL)
	{
		return false;
	}
	
	int angle = 0;
	//检查pecent的和是否为1
	if(pieInfo && size > 1)
	{
		for(int i = 0; i < size; ++i)
		{
			angle += pieInfo[i].angle;
		}
		if(angle != 360)
		{
			return false;
		}
	}

	DrawPieChart * pie = new DrawPieChart(hWnd, rcDraw);
	for (int j = 0; j < size; ++j)
	{
		pie->AddPiece(pieInfo[j].backColor, pieInfo[j].textColor, pieInfo[j].angle, pieInfo[j].title);
	}
	delete pie;
	return true;
}