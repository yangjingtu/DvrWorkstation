#include "stdafx.h"
#include "ControlEx.h"

#include "MsgWnd.h"


CMsgWnd::CMsgWnd(void)
{
	m_bOk = false;
}

LPCTSTR CMsgWnd::GetWindowClassName() const 
{ 
	return _T("UIMsgFrame"); 
}

UINT CMsgWnd::GetClassStyle() const 
{ 
	return UI_CLASSSTYLE_DIALOG; 
}

void CMsgWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	//delete this;
}

void CMsgWnd::Init() 
{
	m_plblTitle = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblTitle")));
	m_pImg = static_cast<CButtonUI*>(m_pm.FindControl(_T("img")));
	m_pTxtMsg = static_cast<CTextUI*>(m_pm.FindControl(_T("lblMsg")));

}

void CMsgWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) 
	{
		if( msg.pSender->GetName() == _T("closebtn") ) 
		{ 
			m_bOk = false;
			Close(); 
			return; 
		}
		else if( msg.pSender->GetName() == _T("okBtn") ) 
		{ 
			m_bOk = true;
			Close();
			return; 
		}
		else if( msg.pSender->GetName() == _T("cancleBtn"))
		{
			m_bOk = false;
			Close();
			return;
		}
	}
}

LRESULT CMsgWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("msg.xml"), (UINT)0, &cb, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();
	return 0;
}

LRESULT CMsgWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CMsgWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CMsgWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CMsgWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	RECT rcCaption = m_pm.GetCaptionRect();
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
			if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 )
				return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT CMsgWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
		DuiLib::CRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CMsgWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg ) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMsgWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if( uMsg == WM_KEYDOWN ) 
	{
		if( wParam == VK_RETURN ) 
		{
			CEditUI* pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("accountedit")));
			if( pEdit->GetText().IsEmpty() ) pEdit->SetFocus();
			else 
			{
				pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("pwdedit")));
				if( pEdit->GetText().IsEmpty() ) 
					pEdit->SetFocus();
				else 
				{
					Close();
					m_bOk = false;
				}
			}
			return true;
		}
		else if( wParam == VK_ESCAPE ) 
		{
			//PostQuitMessage(0);
			Close();
			m_bOk = false;
			return true;
		}

	}
	return false;
}

void CMsgWnd::SetMsg(const CString& msg, const CString& title, const CString& img)
{
	m_pTxtMsg->SetText((LPCTSTR)msg);
	if(title.IsEmpty())
	{
		m_plblTitle->SetText(_T("消息提示"));
	}else
	{
		m_plblTitle->SetText((LPCTSTR)title); 
	}
	if(img.IsEmpty())
	{
		m_pImg->SetBkImage(_T("info1.png"));
	}
	else
	{
		m_pImg->SetBkImage((LPCTSTR)img);
	}
}