#include "StdAfx.h"
#include <vector>
#include <math.h>
#include "../DataDef.h"
#include "DvrListUI.h"

#include "../ShareData.h"
#include "../DvrMgr.h"

//DVR图片的宽高比例
#define DVR_IMG_SCALE 243/401

inline double CalculateDelay(double state) {
	return pow(state, 2);
}

DvrListUI::DvrListUI()
	: m_selectRow(-1)
	, m_selectCol(-1)
{
	for(int i = 0; i < SHAREDATA.g_dvrProp.numDvr; ++i) 
	{
		CDialogBuilder builder;
		CContainerUI* pDesk = static_cast<CContainerUI*>(builder.Create(_T("dvr.xml"), (UINT)0));
		if( pDesk ) 
		{
			pDesk->SetName(_T("dvr") + i);
			this->Add(pDesk);
			
			//初始化所有控件的指针
			int row = i / SHAREDATA.g_dvrProp.numCol;
			int col = i % SHAREDATA.g_dvrProp.numCol;
			m_mapItem[i] = InitDvrItemCtrl(row, col);
		}
		else 
		{
			this->RemoveAll();
			return;
		}
	}

	ClearAllInfo();
}

void DvrListUI::DoEvent(TEventUI& event) 
{
	if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
		if( m_pParent != NULL ) m_pParent->DoEvent(event);
		else CTileLayoutUI::DoEvent(event);
		return;
	}

	if( event.Type == UIEVENT_TIMER && event.wParam == SCROLL_TIMERID )
	{
		return;
	}
	if( event.Type == UIEVENT_BUTTONDOWN && IsEnabled() )
	{
		//主框架要初始化好才可操作（解决FTP检查没成功时，点击会中断的问题）
		if(SHAREDATA.g_pMainFrame)
		{
			OnClick(event.ptMouse);
		}
		return;
	}

	if( event.Type == UIEVENT_BUTTONUP )
	{
		return;
	}
	if( event.Type == UIEVENT_SCROLLWHEEL )
	{
		return;
	}
	

	CTileLayoutUI::DoEvent(event);
}

void DvrListUI::SetPos(RECT rc)
{
	if( GetCount() > 0 ) 
	{
		//固定设为4列
		SetColumns(SHAREDATA.g_dvrProp.numCol);
	}

	CTileLayoutUI::SetPos(rc);

	SetDvrPos(rc);
}

void DvrListUI::SetDvrPos(RECT rc)
{
	//最小化到任务栏时
	if(rc.top == rc.bottom)
	{
		return;
	}

	//固定列数设置为4的方法
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	
	//行列添加间隙
	int nOffSet = 5;
	
	width = (width - nOffSet*SHAREDATA.g_dvrProp.numRow) / SHAREDATA.g_dvrProp.numCol;
	height = (height - nOffSet*SHAREDATA.g_dvrProp.numCol) / SHAREDATA.g_dvrProp.numRow;
	//值的宽度 = 单个dvr的宽度　－　标签30 - 间隔10 - 图片的宽
	int widVal = width - height * DVR_IMG_SCALE - 20;
	for( int it1 = 0; it1 < m_items.GetSize(); it1++ ) 
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_items[it1]);
		if( !pControl->IsVisible() ) 
			continue;
		if( pControl->IsFloat() ) {
			SetFloatPos(it1);
			continue;
		}

		RECT rcPos;
		rcPos.left = (it1%m_nColumns)*(width) + 5 + nOffSet/2; //4是左边距
		if(it1 % SHAREDATA.g_dvrProp.numCol < SHAREDATA.g_dvrProp.numCol)
		{
			rcPos.left += nOffSet * (it1 % SHAREDATA.g_dvrProp.numCol);
		}
		rcPos.right = rcPos.left + width;
		rcPos.top = (it1/m_nColumns)*height + 94 + nOffSet/2;  //90是标题的高度
		if(it1/SHAREDATA.g_dvrProp.numRow < SHAREDATA.g_dvrProp.numCol)
		{
			rcPos.top += nOffSet * (it1/SHAREDATA.g_dvrProp.numRow);
		}
		rcPos.bottom = rcPos.top + height;

		pControl->SetPos(rcPos);

		//注这边不能用findctrol,因为所有的dvr子控件的id是一样的，会造成只有最后一个有效
		//这里和相关的布局层数有关系
		CContainerUI* pDvr = static_cast<CContainerUI*>(pControl);

		//设置圆角
		pDvr->SetBorderSize(1);
		SIZE sz;
		sz.cx = 5;
		sz.cy = 5;
		pDvr->SetBorderRound(sz);

		CHorizontalLayoutUI* pParent = static_cast<CHorizontalLayoutUI*>(pDvr->GetItemAt(0));
		if(pParent)
		{
			CVerticalLayoutUI* pImg = static_cast<CVerticalLayoutUI*>(pParent->GetItemAt(0));
			if(pImg)
			{
				pImg->SetFixedWidth(height * DVR_IMG_SCALE);

				//设整图片的大小（占用3/4)更美观
				pImg->SetFixedHeight(height * 3/4);
				pImg->SetFixedWidth(height * 3/4 * DVR_IMG_SCALE);
  				RECT rc;
  				rc.top = height / 4 / 2;
				rc.left = rc.top * DVR_IMG_SCALE;
				rc.right = rc.bottom = 0;
  				pImg->SetPadding(rc);

			}
		}

 		DvrItemCtrl dic = m_mapItem[it1];
 		if(dic.pValue)		dic.pValue->SetFixedWidth(widVal);
		if(dic.pProgress)
		{
			RECT rcPro;
			//使进度条对齐
			rcPro.top = dic.pProgress->GetParent()->GetHeight();
			dic.pProgress->SetFixedHeight(rcPro.top * 0.8);
			rcPro.top = rcPro.bottom = rcPro.top * 0.1;
			rcPro.left = rcPro.right = 0;
			dic.pProgress->SetPadding(rcPro);
			if(dic.pProgress->GetHeight() > 30)
			{
				rcPro.top = dic.pProgress->GetHeight() * 8 / 32;
				dic.pProgress->SetTextPadding(rcPro);
			}
		}
// 		if(dic.pId)			dic.pId->SetFixedWidth(widVal);
// 		if(dic.pName)		dic.pName->SetFixedWidth(widVal);
// 		if(dic.pDisk)		dic.pDisk->SetFixedWidth(widVal);
// 		if(dic.pProgress)	dic.pProgress->SetFixedWidth(widVal);
// 		if(dic.pStatus)		dic.pStatus->SetFixedWidth(widVal);
// 		if(dic.pStop)		dic.pStop->SetFixedWidth(widVal);
	}
}

void DvrListUI::OnClick(const POINT& pt)
{
	CControlUI* pControl = HitPtInItem(pt);
	if( NULL == pControl)
	{
		return;
	}
	
//	HitItem(pControl);

	CDuiString strT;
	strT.Format(_T("当前选择的位置 %d,%d "), m_selectRow + 1, m_selectCol + 1);
	SHAREDATA.g_pMainFrame->ShowMsgInfo(strT);
}

CControlUI* DvrListUI::HitPtInItem(const POINT& pt)
{
	CControlUI* pControl = NULL;
	for( int it1 = 0; it1 < m_items.GetSize(); it1++ ) 
	{
		pControl = static_cast<CControlUI*>(m_items[it1]);
		if( !pControl->IsVisible() ) 
			continue;
		if( pControl->IsFloat() ) {
			SetFloatPos(it1);
			continue;
		}

		RECT rcPos = pControl->GetPos();

		if( pt.x > rcPos.left && pt.x < rcPos.right && pt.y > rcPos.top && pt.y < rcPos.bottom )
		{
			//选择的行列
			//modified by yjt 2014-10-09 行列不对称时，计算有问题
			m_selectRow = it1 / SHAREDATA.g_dvrProp.numCol;
			m_selectCol = it1 % SHAREDATA.g_dvrProp.numCol;

			return pControl;
		}
	}
	pControl = NULL;

	return pControl;
}

//改变点击项的边框颜色
void DvrListUI::HitItem(CControlUI* pItem)
{
	pItem->SetBorderColor(CLR_ACTIVR_BORDER);
	pItem->SetBkColor(CLR_ACTIVR_BK);

	//把其它的颜色改回蓝色
	for( int it1 = 0; it1 < m_items.GetSize(); it1++ ) 
	{
		CControlUI* pControlT = static_cast<CControlUI*>(m_items[it1]);
		if( !pControlT->IsVisible() ) 
			continue;
		if( pControlT->IsFloat() ) {
			SetFloatPos(it1);
			continue;
		}

		if(pItem != pControlT)
		{
			pControlT->SetBorderColor(CLR_DISABLE_BORDER);

			//背景色
			pControlT->SetBkColor(CLR_DISABLE_BK);
		}
	}
}

//设置背景色
void DvrListUI::BKColor(int row, int column, DWORD boderColor, DWORD bkcolor)
{
	CContainerUI* pControl = GetItem(row, column);
	if(pControl == NULL)
	{
		return;
	}
 	pControl->SetBorderColor(boderColor);
 	pControl->SetBkColor(bkcolor);
}

void DvrListUI::GetSelectPos(int& row, int& col)
{
	row = m_selectRow;
	col = m_selectCol;
}

void DvrListUI::ClearSelectPos()
{
	m_selectRow = -1;
	m_selectCol = -1;
}

CContainerUI* DvrListUI::GetItem(int row, int col)
{
	if(row < 0 || col < 0 || row >SHAREDATA.g_dvrProp.numRow || col > SHAREDATA.g_dvrProp.numCol)
	{
		return NULL;
	}

	int nIndex = nIndex = (row  * SHAREDATA.g_dvrProp.numCol) +  col;
	CContainerUI* pControl = static_cast<CContainerUI*>(m_items[nIndex]);
	if( NULL == pControl && !pControl->IsVisible())
	{
		return NULL;
	}
	return pControl;
}

void DvrListUI::ClearInfo(int row, int col)
{
	CDvrWnd dvr(false);
	SetInfo(row, col, &dvr);
}

void DvrListUI::ClearAllInfo()
{
	for( int it1 = 0; it1 < m_items.GetSize(); it1++ ) 
	{
		int row = it1 / SHAREDATA.g_dvrProp.numCol;
		int col = it1 % SHAREDATA.g_dvrProp.numCol;
		ClearInfo(row, col);
	}
}

DvrItemCtrl DvrListUI::InitDvrItemCtrl(int row, int col)
{	
	DvrItemCtrl dic;
	memset(&dic, 0, sizeof(DvrItemCtrl));
	
	CContainerUI* pControl = GetItem(row, col);
	if(pControl == NULL)
	{
		return dic;
	}

	//级数： 即item at的索引， 看dvr.xml的嵌套层数
	CHorizontalLayoutUI* pParent = static_cast<CHorizontalLayoutUI*>(pControl->GetItemAt(0));
	if(pParent == NULL)
		return dic;


	CVerticalLayoutUI* pImg = static_cast<CVerticalLayoutUI*>(pParent->GetItemAt(0));
	if(pImg)
	{
		dic.pImg = pImg;
		CVerticalLayoutUI* pImg0 = static_cast<CVerticalLayoutUI*>(pImg->GetItemAt(0));
		if(pImg0)
		{
			dic.pDev = static_cast<CLabelUI*>(pImg0->GetItemAt(1));
		}
	}

	dic.pValue = static_cast<CVerticalLayoutUI*>(pParent->GetItemAt(1));
	if(dic.pValue)
	{
		CVerticalLayoutUI* pValue = dic.pValue;

		int index = 0;
		CHorizontalLayoutUI* pItem = static_cast<CHorizontalLayoutUI*>(pValue->GetItemAt(index));
		if(pItem)
		{
			dic.pId = static_cast<CLabelUI*>(pItem->GetItemAt(1));
		}
		index+=1;
		pItem = static_cast<CHorizontalLayoutUI*>(pValue->GetItemAt(index));
		if(pItem)
		{
			dic.pName = static_cast<CLabelUI*>(pItem->GetItemAt(1));
		}
		index+=1;
		pItem = static_cast<CHorizontalLayoutUI*>(pValue->GetItemAt(index));
		if(pItem)
		{
			dic.pDisk = static_cast<CLabelUI*>(pItem->GetItemAt(1));
		}
		index+=1;
		pItem = static_cast<CHorizontalLayoutUI*>(pValue->GetItemAt(index));
		if(pItem)
		{
			dic.pProgress = static_cast<CProgressUI*>(pItem->GetItemAt(1));
		}
		index+=1;
		pItem = static_cast<CHorizontalLayoutUI*>(pValue->GetItemAt(index));
		if(pItem)
		{
			dic.pSpeed = static_cast<CLabelUI*>(pItem->GetItemAt(1));
		}
		index+=1;
		pItem = static_cast<CHorizontalLayoutUI*>(pValue->GetItemAt(index));
		if(pItem)
		{
			dic.pStatus = static_cast<CLabelUI*>(pItem->GetItemAt(1));
		}
		index+=1;
		pItem = static_cast<CHorizontalLayoutUI*>(pValue->GetItemAt(index));
		if(pItem)
		{
			dic.pFile = static_cast<CLabelUI*>(pItem->GetItemAt(1));
		}
		index+=1;
		pItem = static_cast<CHorizontalLayoutUI*>(pValue->GetItemAt(index));
		if(pItem)
		{
			dic.pStop = static_cast<CButtonUI*>(pItem->GetItemAt(1));
		}
	}
	return dic;
}

DvrItemCtrl DvrListUI::GetDvrItemCtrl(int row, int col)
{
	int index = row * SHAREDATA.g_dvrProp.numCol + col;
	return m_mapItem[index];
}


//设置相关信息并显示
void DvrListUI::SetInfo(int row, int col, CDvrWnd* dvr)
{
	DvrItemCtrl dic = GetDvrItemCtrl(row, col);
	if(dvr->GetStatus() == DVR_ACTIVE)
	{
		SetInfo_Active(dic, dvr);
		BKColor(row, col, CLR_ACTIVR_BORDER, CLR_ACTIVR_BK);
	}
	else if(dvr->GetStatus() == DVR_DERICT)
	{
		SetInfo_Direct(dic, dvr);
		BKColor(row, col, CLR_DERICT_BORDER, CLR_DERICT_BK);
	}
	else if(dvr->GetStatus() == DVR_NORMAL)
	{
		SetInfo_Nomal(dic, dvr);
		BKColor(row, col, CLR_NOMAL_BORDER, CLR_NOMAL_BK);
	}
	else if(dvr->GetStatus() == DVR_DISABLE)
	{
		SetInfo_Disable(dic, dvr);
		BKColor(row, col, CLR_DISABLE_BORDER, CLR_DISABLE_BK);
	}
	else if(dvr->GetStatus() == DVR_COPY)
	{
		SetInfo_Copy(dic, dvr);
		BKColor(row, col, CLR_COPY_BORDER, CLR_COPY_BK);
	}
	else if(dvr->GetStatus() == DVR_COPY_OK)
	{
		//传输完成
		SetInfo_Copy_OK(dic, dvr);
		BKColor(row, col, CLR_COPY_OK_BORDER, CLR_COPY_OK_BK);
	}
	else if(dvr->GetStatus() == DVR_STOP)
	{
		//文件异常
		SetInfo_Stop(dic, dvr);
		BKColor(row, col, CLR_STOP_BORDER, CLR_STOP_BK);
	}
}


void DvrListUI::SetInfo_Active(const DvrItemCtrl& dic, CDvrWnd* dvr)
{
	if(dic.pDev)		dic.pDev->SetText(_T("工作中..."));
	if(dic.pId)			dic.pId->SetText(dvr->GetId());
	if(dic.pName)		dic.pName->SetText(dvr->GetName());
	if(dic.pDisk)		dic.pDisk->SetText(dvr->GetDisk());
	if(dic.pProgress)
	{
		float v = dvr->GetProgressValue();
		int r = 0;
		if(v > 0)
		{
			CDuiString strP;
			r = dvr->GetProgressMax();
			r = (v / r) * 100;
			if(r > 100)
				r = 100;
			strP.Format(_T("完成:%d%%"), r > 0 ? r : 1);
			dic.pProgress->SetText(strP);
		}		
		dic.pProgress->SetMinValue(0);
		dic.pProgress->SetMaxValue(dvr->GetProgressMax());
		dic.pProgress->SetValue(v > r ? r : v );
	}
	if(dic.pSpeed)		dic.pSpeed->SetText(dvr->GetSpeedStr());
	if(dic.pStatus)		dic.pStatus->SetText(dvr->GetStatusStr());
	if(dic.pFile)		dic.pFile->SetText(dvr->GetFile());
	if(dic.pStop)		dic.pStop->SetVisible(false);
}

void DvrListUI::SetInfo_Disable(const DvrItemCtrl& dic, CDvrWnd* dvr)
{
	if(dic.pDev)		dic.pDev->SetText(_T("无设备"));
	if(dic.pId)			dic.pId->SetText(dvr->GetId());
	if(dic.pName)		dic.pName->SetText(dvr->GetName());
	if(dic.pDisk)		dic.pDisk->SetText(dvr->GetDisk());
	if(dic.pProgress)
	{
		dic.pProgress->SetValue(0);
		dic.pProgress->SetText(_T(""));
	}
	if(dic.pSpeed)		dic.pSpeed->SetText(_T(""));
	if(dic.pStatus)		dic.pStatus->SetText(dvr->GetStatusStr());
	if(dic.pFile)		dic.pFile->SetText(dvr->GetFile());
	if(dic.pStop)		dic.pStop->SetVisible(false);
}

void DvrListUI::SetInfo_Nomal(const DvrItemCtrl& dic, CDvrWnd* dvr)
{
	if(dic.pDev)		dic.pDev->SetText(_T("工作中..."));
	if(dic.pId)			dic.pId->SetText(dvr->GetId());
	if(dic.pName)		dic.pName->SetText(dvr->GetName());
	if(dic.pDisk)		dic.pDisk->SetText(dvr->GetDisk());
	if(dic.pProgress)
	{
		float v = dvr->GetProgressValue();
		int r = 0;
		if(v > 0)
		{
			CDuiString strP;
			r = dvr->GetProgressMax();
			r = v / r * 100;
			if(r > 100)
				r = 100;
			strP.Format(_T("完成:%d%%"), r > 0 ? r : 1);
			dic.pProgress->SetText(strP);
		}
		dic.pProgress->SetMinValue(0);
		dic.pProgress->SetValue(v > r ? r : v);
		dic.pProgress->SetMaxValue(dvr->GetProgressMax());
	}
	if(dic.pSpeed)		dic.pSpeed->SetText(dvr->GetSpeedStr());
	if(dic.pStatus)		dic.pStatus->SetText(dvr->GetStatusStr());
	if(dic.pFile)		dic.pFile->SetText(dvr->GetFile());
	if(dic.pStop)		dic.pStop->SetVisible(true);
}

void DvrListUI::SetInfo_Direct(const DvrItemCtrl& dic, CDvrWnd* dvr)
{
	SetInfo_Active(dic, dvr);
}

void DvrListUI::SetInfo_Copy(const DvrItemCtrl& dic, CDvrWnd* dvr)
{
	SetInfo_Active(dic, dvr);
}

void DvrListUI::SetInfo_Copy_OK(const DvrItemCtrl& dic, CDvrWnd* dvr)
{
	SetInfo_Active(dic, dvr);
}

void DvrListUI::SetInfo_Stop(const DvrItemCtrl& dic, CDvrWnd* dvr)
{
	SetInfo_Nomal(dic, dvr);
}

void DvrListUI::OnBtnClick(TNotifyUI& msg)
{
	CDuiString name = msg.pSender->GetName();
	if(name == _T("btnStop"))
	{
		int index = -1;
		MapDvrCtrlItor it = m_mapItem.begin();
		for( ; it != m_mapItem.end(); ++it)
		{
			if( (*it).second.pStop == msg.pSender)
			{
				index = (*it).first;
				break;
			}
		}
		
		CDvrWnd* pDvr = CDvrMgr::Instance().GetDvr(index);
		if(pDvr)
		{	
			pDvr->SetCopyStatus(COPY_STOP);
		}
	}
}