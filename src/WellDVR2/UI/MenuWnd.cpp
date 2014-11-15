#include "StdAfx.h"
#include "MenuWnd.h"

CMenuWnd::CMenuWnd() 
	: m_pOwner(NULL) 
{

}

void CMenuWnd::Init(CControlUI* pOwner, POINT pt) 
{
	if( pOwner == NULL ) return;
	m_pOwner = pOwner;
	m_ptPos = pt;
	Create(pOwner->GetManager()->GetPaintWindow(), NULL, WS_POPUP, WS_EX_TOOLWINDOW);
	HWND hWndParent = m_hWnd;
	while( ::GetParent(hWndParent) != NULL ) hWndParent = ::GetParent(hWndParent);
	::ShowWindow(m_hWnd, SW_SHOW);
	::SendMessage(hWndParent, WM_NCACTIVATE, TRUE, 0L);
}

void CMenuWnd::AdjustPostion() {
	DuiLib::CDuiRect rcWnd;
	GetWindowRect(m_hWnd, &rcWnd);
	int nWidth = rcWnd.GetWidth();
	int nHeight = rcWnd.GetHeight();
	rcWnd.left = m_ptPos.x;
	rcWnd.top = m_ptPos.y;
	rcWnd.right = rcWnd.left + nWidth;
	rcWnd.bottom = rcWnd.top + nHeight;
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	DuiLib::CDuiRect rcWork = oMonitor.rcWork;

	if( rcWnd.bottom > rcWork.bottom ) {
		if( nHeight >= rcWork.GetHeight() ) {
			rcWnd.top = 0;
			rcWnd.bottom = nHeight;
		}
		else {
			rcWnd.bottom = rcWork.bottom;
			rcWnd.top = rcWnd.bottom - nHeight;
		}
	}
	if( rcWnd.right > rcWork.right ) {
		if( nWidth >= rcWork.GetWidth() ) {
			rcWnd.left = 0;
			rcWnd.right = nWidth;
		}
		else {
			rcWnd.right = rcWork.right;
			rcWnd.left = rcWnd.right - nWidth;
		}
	}
	::SetWindowPos(m_hWnd, HWND_TOPMOST, rcWnd.left, rcWnd.top, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_NOSIZE  | SWP_SHOWWINDOW);
}

LPCTSTR CMenuWnd::GetWindowClassName() const { return _T("MenuWnd"); };
void CMenuWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	delete this; 
};

void CMenuWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("itemselect") ) {
		Close();
	}
	else if( msg.sType == _T("itemclick") ) 
	{
		if( msg.pSender->GetName() == _T("menu_Quit") ) {
			if( m_pOwner ) m_pOwner->GetManager()->SendNotify(m_pOwner, _T("Quit"), 0, 0, true);
		}
		else if( msg.pSender->GetName() == _T("menu_Open") ) {
			if( m_pOwner ) m_pOwner->GetManager()->SendNotify(m_pOwner, _T("menu_Open"), 0, 0, true);
		}
		else if( msg.pSender->GetName() == _T("menu_About") ) {
			if( m_pOwner ) m_pOwner->GetManager()->SendNotify(m_pOwner, _T("menu_About"), 0, 0, true);
		}

		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_HIDEWINDOW);

		Close();
	}
}

LRESULT CMenuWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_pm.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("menu.xml"), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);
	m_pm.SetRoundCorner(3, 3);

	AdjustPostion();
	return 0;
}

LRESULT CMenuWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( m_hWnd != (HWND) wParam ) PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMenuWnd::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( wParam == VK_ESCAPE ) 
	{
		Close();
	}
	return 0;
}

LRESULT CMenuWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CMenuWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg ) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_KILLFOCUS:     lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); break;
	case WM_KEYDOWN:       lRes = OnKeyDown(uMsg, wParam, lParam, bHandled); break;
	case WM_MOUSEWHEEL:    break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	//16的消息特殊处理， 不然关闭时出错
	case 16: return lRes;
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}