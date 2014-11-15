//////////////////////////////////////////////////////////////////////////
//Describe:
//		»æ»­ÒýÇæ
//Date: [2014/11/15 yjt]
//History:
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "DrawPieChart.h"

#define DRAWENGINE CDrawEngine::Instance()

class CDrawEngine
{
private:
	CDrawEngine(void);
	virtual ~CDrawEngine(void);
public:
	static CDrawEngine& Instance();

public:
	
	//»­±ýÍ¼
	virtual bool DrawPie(HWND hWnd, RECT rcDraw, const PPieInfo pieInfo, int size);
};

