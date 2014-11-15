#include "StdAfx.h"
#include "CLoginFrameWnd.h"


CLoginFrameWnd::CLoginFrameWnd()
	: m_bLogin(false)
{

}

LPCTSTR CLoginFrameWnd::GetWindowClassName() const 
{ 
	return _T("UILoginFrame"); 
}

UINT CLoginFrameWnd::GetClassStyle() const 
{ 
	return UI_CLASSSTYLE_DIALOG; 
}

void CLoginFrameWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	//delete this; 
}

void CLoginFrameWnd::Init() 
{
	CComboUI* pAccountCombo = static_cast<CComboUI*>(m_pm.FindControl(_T("accountcombo")));
	CEditUI* pAccountEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("accountedit")));
	if( pAccountCombo && pAccountEdit ) pAccountEdit->SetText(pAccountCombo->GetText());
	pAccountEdit->SetFocus();
}

void CLoginFrameWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) {
		if( msg.pSender->GetName() == _T("closebtn") ) { PostQuitMessage(0); return; }
		else if( msg.pSender->GetName() == _T("loginBtn") ) { Close(); return; }
	}
	else if( msg.sType == _T("itemselect") ) {
		if( msg.pSender->GetName() == _T("accountcombo") ) {
			CEditUI* pAccountEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("accountedit")));
			if( pAccountEdit ) pAccountEdit->SetText(msg.pSender->GetText());
		}
	}
}

LRESULT CLoginFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("login.xml"), (UINT)0, &cb, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();
	return 0;
}

LRESULT CLoginFrameWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CLoginFrameWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CLoginFrameWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CLoginFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CLoginFrameWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
		DuiLib::CDuiRect rcWnd;
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

LRESULT CLoginFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT CLoginFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if( uMsg == WM_KEYDOWN ) {
		if( wParam == VK_RETURN ) {
			CEditUI* pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("accountedit")));
			if( pEdit->GetText().IsEmpty() ) pEdit->SetFocus();
			else {
				pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("pwdedit")));
				if( pEdit->GetText().IsEmpty() ) pEdit->SetFocus();
				else Close();
			}
			return true;
		}
		else if( wParam == VK_ESCAPE ) {
			PostQuitMessage(0);
			return true;
		}

	}
	return false;
}