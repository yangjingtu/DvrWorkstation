//////////////////////////////////////////////////////////////////////////
//Describe:
//		绘制饼图图表
//Date: [2014/11/15 yjt]
//History:
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IDraw.h"

typedef struct tagPieInfo
{
	int angle; 
	COLORREF backColor;
	COLORREF textColor;
	CString title;
}PieInfo, *PPieInfo;

class CPieChartPiece : public CObject
{
public:
	CPieChartPiece() {;}
	~CPieChartPiece() {if (m_brushBack.m_hObject) m_brushBack.DeleteObject();}

	COLORREF m_colorBack;
	COLORREF m_colorText;
	CBrush m_brushBack;	
	int m_nAngle;
	CString m_strInfo;
};

typedef CTypedPtrArray <CObArray, CPieChartPiece*> CChartPieceArray;

class DrawPieChart : public IDraw
{
public:
	DrawPieChart(HWND hWnd, CRect rcDraw);
	~DrawPieChart(void);

public:
	void Draw();

	void SetTitle(const CString& str);
	void GetItemColor(int i, COLORREF& color);
	void Reset();
	void CountPoint(int nAngle, POINT& pt, BOOL bPercent = FALSE);
	BOOL AddPiece(COLORREF colorBack, COLORREF colorText,
		int nAngle, const CString& str = _T(""));
	void RecalcRect();

private:
	//绘制透明位图
	void TransparentBitmap(CDC* dc, CDC* memDC, COLORREF transparentColor);

private:
	int m_nStartAngle; // 0-359
	COLORREF m_colorDefault;
	COLORREF m_colorLine;

	CChartPieceArray m_chartPieces;

private:
	int m_nTitleHeight;
	CFont m_fontTitle;
	CFont m_fontInfo;
	CString m_strTitle;
	CRect m_rectChart;		//图表区域

	HWND m_hWnd;
	CRect m_rcDraw;			//整个画图区域（标题，饼图）
};

