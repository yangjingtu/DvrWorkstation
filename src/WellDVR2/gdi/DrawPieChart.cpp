#include "stdafx.h"
#include "DrawPieChart.h"

const double pi = 3.1415926535;


DrawPieChart::DrawPieChart(HWND hWnd, CRect rcDraw):
	m_hWnd(hWnd),
	m_rcDraw(rcDraw)
{
	m_nStartAngle = 0;
	m_colorLine = RGB(0,0,0);
	m_colorDefault = RGB(0,0,255);

	m_rectChart.SetRect(0,0,0,0);
	
	m_strTitle = _T("");

	m_fontTitle.CreateFont(15, 0,0,0,FW_NORMAL, 0,0,0,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));

	m_fontInfo.CreateFont(13, 0,0,0,FW_NORMAL, 0,0,0,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
}


DrawPieChart::~DrawPieChart(void)
{
	Reset();
}

void DrawPieChart::Draw()
{
	if (m_rectChart.IsRectEmpty()) // First Time
		RecalcRect();

	HDC hdc = ::GetDC(m_hWnd);
	CRect clientRect(0,0, m_rcDraw.Width(), m_rcDraw.Height());
	CDC dc;
	dc.Attach(hdc);

	CBitmap *pOldMemDCBitmap = NULL;	
	CDC memDC;
	CBitmap bitmap;
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap( &dc, clientRect.Width(), clientRect.Height() );
	CBitmap *pOldmemDCBitmap = (CBitmap*)memDC.SelectObject(&bitmap);

// 	HDC hMemDC = CreateCompatibleDC(hdc);
// 	HBITMAP hBitmap = CreateCompatibleBitmap(hMemDC, clientRect.Width(), clientRect.Height() );
// 	HBITMAP* pOldMemDCBitmap = (HBITMAP*)SelectObject(hMemDC, hBitmap);

	memDC.FillSolidRect(clientRect, GetSysColor(COLOR_3DFACE));

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, m_colorLine);
	CPen* pOldPen = (CPen*)memDC.SelectStockObject(NULL_PEN);

	CBrush brush;
	brush.CreateSolidBrush(m_colorDefault);
	CBrush* pOldBrush = memDC.SelectObject(&brush);
	memDC.Ellipse(m_rectChart);

	int nCount = m_chartPieces.GetSize();
	CPieChartPiece* pItem;

	CPoint pt1, pt2;
	int nCurrectAngle = m_nStartAngle;
	int nInfo=0;
	CountPoint(nCurrectAngle, pt1);
	for (int i=0; i<nCount; i++)
	{
		pItem = m_chartPieces.GetAt(i);
		nCurrectAngle += pItem->m_nAngle;
		CountPoint(nCurrectAngle, pt2);

		memDC.SelectStockObject(NULL_PEN);
		memDC.SelectObject(&pItem->m_brushBack);

		if (pt2!=pt1)
			memDC.Pie(m_rectChart, pt2, pt1);

		//Draw line
		memDC.SelectObject(&pen);
		memDC.MoveTo(pt1);
		memDC.LineTo(m_rectChart.CenterPoint());
		memDC.LineTo(pt2);

		//Draw info
		CFont* pOldFont = memDC.SelectObject(&m_fontInfo);
		memDC.SetBkMode(TRANSPARENT);

		if (!(pItem->m_strInfo).IsEmpty())
		{
			CSize sz = memDC.GetTextExtent(pItem->m_strInfo);

			CRect rcColor(clientRect);
			rcColor.left = rcColor.right - sz.cy;
			rcColor.bottom = rcColor.top + sz.cy;
			rcColor.OffsetRect(0, nInfo*rcColor.Height());//+m_nTitleHeight);

			memDC.FillSolidRect(rcColor, pItem->m_colorBack); // i must be less than MAX_COLOR
			memDC.DrawEdge(rcColor, EDGE_SUNKEN, BF_RECT);

			memDC.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
			rcColor.right = rcColor.left - 3;
			rcColor.left = clientRect.left;
			memDC.DrawText(pItem->m_strInfo, rcColor, DT_RIGHT|DT_VCENTER);

			nInfo++;
		}

		// Draw percent
		if (pItem->m_nAngle>25)
		{
			int n = nCurrectAngle - (pItem->m_nAngle)/2;
			CPoint p;
			CountPoint(n, p, TRUE);
			CString str;
			str.Format(_T("%.0f%%"), (double)(pItem->m_nAngle)*100.0/360.0);
			CSize sz = memDC.GetTextExtent(str);
			memDC.SetTextColor(pItem->m_colorText);
			memDC.TextOut(p.x-sz.cx/2, p.y-sz.cy/2, str);
		}

		memDC.SelectObject(pOldFont);

		pt1 = pt2;
	}

	// Draw Line for the out circle
	memDC.SelectObject(&pen);
	memDC.SelectStockObject(NULL_BRUSH);
	memDC.Ellipse(m_rectChart);

	//Draw Title
	if (!m_strTitle.IsEmpty())
	{
		CFont* pOldFont = memDC.SelectObject(&m_fontTitle);
		memDC.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		memDC.SetBkMode(TRANSPARENT);
		memDC.TextOut(1, 1, m_strTitle);
		memDC.SelectObject(pOldFont);
	}

	//透明颜色绘制
	TransparentBitmap(&dc, &memDC, GetSysColor(COLOR_3DFACE));

// 	绘制到实际的位置中 -- 不透明
// 	dc.BitBlt( m_rcDraw.left, m_rcDraw.top, clientRect.Width(), clientRect.Height(), 
// 		&memDC, 0, 0, SRCCOPY );

	HGDIOBJ hTmp = memDC.SelectObject(pOldPen);
	DeleteObject(hTmp);
	hTmp = memDC.SelectObject(&pOldBrush);
	DeleteObject(hTmp);
	hTmp = memDC.SelectObject(pOldmemDCBitmap);
	DeleteObject(hTmp);

	memDC.DeleteDC();

	::ReleaseDC(m_hWnd, hdc);
}

void DrawPieChart::RecalcRect()
{
	CRect rect = m_rcDraw;
	if (!m_strTitle.IsEmpty())
	{
		CDC dc;
		dc.Attach(GetDC(m_hWnd));
//		CClientDC dc(this);
		CFont* pOldFont = dc.SelectObject(&m_fontTitle);
		CSize sz = dc.GetTextExtent(m_strTitle);
		m_nTitleHeight = sz.cy;
		rect.top += sz.cy*2;// Leave  lines.
		dc.SelectObject(pOldFont);
	}

	int nSize = (rect.Width()>rect.Height())?rect.Height():rect.Width();

// 	m_rectChart = CRect(CPoint(rect.left + (rect.Width()-nSize)/2, 
// 		rect.top + (rect.Height()-nSize)), 
// 		CSize(nSize, nSize));
	m_rectChart = CRect(CPoint(0 + (rect.Width()-nSize)/2, 
		0 + (rect.Height()-nSize)), 
		CSize(nSize, nSize));
}

BOOL DrawPieChart::AddPiece(COLORREF colorBack, COLORREF colorText,
							 int nAngle, const CString& str)
{
	CPieChartPiece* pItem = new CPieChartPiece;
	pItem -> m_colorBack = colorBack;
	pItem -> m_colorText = colorText;
	pItem -> m_brushBack.CreateSolidBrush(colorBack);
	pItem -> m_nAngle = nAngle;
	pItem -> m_strInfo = str;

	try 
	{
		m_chartPieces.Add(pItem);

		//InvalidateRect(m_hWnd, &m_rcDraw, FALSE);
		Draw();

		return TRUE;
	}
	catch (CMemoryException* e)
	{
		if (pItem !=NULL) 
			delete pItem;
		e->Delete();
		return FALSE;
	}
}

// bPercent is TRUE when counting the position for the percent info
void DrawPieChart::CountPoint(int nAngle, POINT & pt, BOOL bPercent)
{
	while (nAngle <0)
		nAngle += 360;

	while (nAngle>359)
		nAngle -= 360;

	double dAngle = ((double)nAngle)*pi/(double)180;

	double r;
	r = ((double)m_rectChart.Height())/2.0;
	if (bPercent)
		r = r*3.0/5.0;

	double dOffX = (r*sin(dAngle));
	double dOffY = 0.0 - (r*cos(dAngle));

	double dX = ((double)(m_rectChart.right+m_rectChart.left))/2.0;
	double dY = ((double)(m_rectChart.top+m_rectChart.bottom))/2.0;

	pt.x = (int)(dX + dOffX);
	pt.y = (int)(dY + dOffY);
}


void DrawPieChart::Reset()
{
	int nCount = m_chartPieces.GetSize();

	for (int i = 0; i < nCount; i++)
		delete m_chartPieces.GetAt(i);
	m_chartPieces.RemoveAll();
}

void DrawPieChart::GetItemColor(int i, COLORREF& color)
{
	int nCount = m_chartPieces.GetSize();
	if (i>=nCount)
		i=nCount-1;

	color = (m_chartPieces.GetAt(i))->m_colorBack;
}

void DrawPieChart::SetTitle(const CString & str)
{
	m_strTitle = str;
	RecalcRect();
	//InvalidateRect(m_hWnd, &m_rcDraw, FALSE);
	Draw();
}

//////////////////////////////////////////////////////////////////////////
//Function:	
//		透明位置
//Params:
//		dc [IN]		--			设备上下文（窗口)
//		srcDC[IN]	--			要透明图像选入的兼容DC
//		transparentColor [IN]	--	要透明的颜色
//Return:
//Date: [2014/11/16 yjt]
//History:
//////////////////////////////////////////////////////////////////////////
void DrawPieChart::TransparentBitmap(CDC* dc, CDC* memDC, COLORREF transparentColor)
{
	CDC maskDc;
	maskDc.CreateCompatibleDC(dc);
	CBitmap bmMask;
	bmMask.CreateBitmap(m_rcDraw.Width(), m_rcDraw.Height(), 1, 1, NULL);
	maskDc.SelectObject(bmMask);

	memDC->SetBkColor(transparentColor);

	//SRCCOPY方式将源位图以原始大小绘制到掩码DC
	maskDc.BitBlt(0,0,m_rcDraw.Width(), m_rcDraw.Height(),memDC,0,0,SRCCOPY);  
	dc->BitBlt(m_rcDraw.left, m_rcDraw.top,m_rcDraw.Width(),m_rcDraw.Height(),memDC,0,0,SRCINVERT);  
	//SRCINVERT方式将源位图拉伸绘制到窗口DC  
	dc->BitBlt(m_rcDraw.left, m_rcDraw.top,m_rcDraw.Width(),m_rcDraw.Height(),&maskDc,0,0,SRCAND);   
	//SRCAND方式将掩码位图拉伸绘制到窗口DC  
	dc->BitBlt(m_rcDraw.left, m_rcDraw.top,m_rcDraw.Width(), m_rcDraw.Height(),memDC,0,0,SRCINVERT);  
	//SRCINVERT方式将源位图拉伸绘制到窗口DC

	maskDc.DeleteDC();
}
