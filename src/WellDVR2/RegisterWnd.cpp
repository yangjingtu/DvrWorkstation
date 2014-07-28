#include "stdafx.h"
#include "RegisterWnd.h"

#include "WellCommon/CharSetHelper.h"

#include "chmzc.h"
#pragma comment(lib, "Register.lib")

CRegisterWnd::CRegisterWnd(void)
{
	m_bRegister = false;
}

LPCTSTR CRegisterWnd::GetWindowClassName() const 
{ 
	return _T("UIRegisterFrame"); 
}

UINT CRegisterWnd::GetClassStyle() const 
{ 
	return UI_CLASSSTYLE_DIALOG; 
}

void CRegisterWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}

void CRegisterWnd::Init() 
{

	CButtonUI* m_pCancel = static_cast<CButtonUI*>(m_pm.FindControl(_T("cancelBtn")));
	CButtonUI* m_pReg = static_cast<CButtonUI*>(m_pm.FindControl(_T("regBtn")));
	CEditUI* m_pText = static_cast<CEditUI*>(m_pm.FindControl(_T("regCodeTxt")));
	m_pText->SetFocus();
	m_pText->GetText();
}

void CRegisterWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) {
		if( msg.pSender->GetName() == _T("closebtn") ) 
		{ 
			PostQuitMessage(0); return; 
		}
		else if( msg.pSender->GetName() == _T("cancelBtn") ) 
		{ 
			m_bRegister = false;
			Close(); 
			return; 
		}
		else if( msg.pSender->GetName() == _T("regBtn") ) 
		{ 
			m_bRegister = OnRegister();
			if(m_bRegister)
			{
				CRichEditUI* pText = static_cast<CRichEditUI*>(m_pm.FindControl(_T("regCodeTxt")));
				if(pText == NULL)
					return;
				pText->SetText(_T("×¢²á³É¹¦"));
				Sleep(1000);
				Close();
			}
			else
			{
				CRichEditUI* pText = static_cast<CRichEditUI*>(m_pm.FindControl(_T("regCodeTxt")));
				if(pText == NULL)
					return;
				pText->SetText(_T("×¢²áÊ§°Ü£¬×¢²áÂë²»ºÏ·¨!"));
				pText->SetFocus();
			}
			return; 
		}
	}
}

LRESULT CRegisterWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("register.xml"), (UINT)0, &cb, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();
	return 0;
}

LRESULT CRegisterWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CRegisterWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CRegisterWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CRegisterWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CRegisterWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CRegisterWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT CRegisterWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if( uMsg == WM_KEYDOWN ) {
		if( wParam == VK_RETURN ) 
		{
			if( m_pText->GetText().IsEmpty() ) 
				m_pText->SetFocus();
			return true;
		}
		else if( wParam == VK_ESCAPE ) {
			PostQuitMessage(0);
			return true;
		}

	}
	return false;
}

bool CRegisterWnd::OnRegister()
{
	CRichEditUI* pText = static_cast<CRichEditUI*>(m_pm.FindControl(_T("regCodeTxt")));
	if(pText == NULL)
		return false;
	CStdString strCode = pText->GetText();
	if(strCode.IsEmpty())
	{
		pText->SetFocus();
		return false;
	}
	
	string sCode = WS2S(strCode.GetData());
	return Register(sCode);
}