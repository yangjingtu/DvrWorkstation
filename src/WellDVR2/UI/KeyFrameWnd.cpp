#include "stdafx.h"
#include "KeyFrameWnd.h"


CKeyFrameWnd::CKeyFrameWnd(const CStdString& strCheck)
	: m_strCheck(strCheck)
	, m_bOk(false)
{
}


CKeyFrameWnd::~CKeyFrameWnd(void)
{
}

LPCTSTR CKeyFrameWnd::GetWindowClassName() const 
{ 
	return _T("UIKeyFrame"); 
}

UINT CKeyFrameWnd::GetClassStyle() const 
{ 
	return UI_CLASSSTYLE_DIALOG; 
}

void CKeyFrameWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
}

void CKeyFrameWnd::Init() 
{
	m_btnClose = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnClose")));

	m_lblMsg = static_cast<CEditUI*>(m_pm.FindControl(_T("lblMsg")));
	m_edtPwd  = static_cast<CEditUI*>(m_pm.FindControl(_T("edtPwd")));
	m_btn1  = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn1")));
	m_btn2  = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn2")));
	m_btn3 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn3")));
	m_btn4 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn4")));
	m_btn5 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn5")));
	m_btn6 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn6")));
	m_btn7 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn7")));
	m_btn8 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn8")));
	m_btn9 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn9")));
	m_btn0 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn0")));
	m_btnBack = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnback")));
	m_btnOk = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnok")));
	
	m_edtPwd->SetFocus();
}

void CKeyFrameWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) 
	{
		if( msg.pSender == m_btnClose ) 
		{ 
			Close();
			return; 
		}
		else if( msg.pSender->GetName() == _T("btnok") ) 
		{ 
			return InputOk();
		}
		else if( msg.pSender->GetName() == _T("btnback") ) 
		{ 
			return InputBack();
		}else if( msg.pSender->GetName() == _T("btn0") ) 
		{ 
			return InputNumber(_T("0"));
		}else if( msg.pSender->GetName() == _T("btn1") ) 
		{ 
			return InputNumber(_T("1"));
		}else if( msg.pSender->GetName() == _T("btn2") ) 
		{ 
			return InputNumber(_T("2"));
		}else if( msg.pSender->GetName() == _T("btn3") ) 
		{ 
			return InputNumber(_T("3"));
		}else if( msg.pSender->GetName() == _T("btn4") ) 
		{ 
			return InputNumber(_T("4"));
		}else if( msg.pSender->GetName() == _T("btn5") ) 
		{ 
			return InputNumber(_T("5"));
		}else if( msg.pSender->GetName() == _T("btn6") ) 
		{ 
			return InputNumber(_T("6"));
		}else if( msg.pSender->GetName() == _T("btn7") ) 
		{ 
			return InputNumber(_T("7"));
		}else if( msg.pSender->GetName() == _T("btn8") ) 
		{ 
			return InputNumber(_T("8")); 
		}else if( msg.pSender->GetName() == _T("btn9") ) 
		{ 
			return InputNumber(_T("9")); 
		}
	}
}

LRESULT CKeyFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("key.xml"), (UINT)0, &cb, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();
	return 0;
}

LRESULT CKeyFrameWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CKeyFrameWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CKeyFrameWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CKeyFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CKeyFrameWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CKeyFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT CKeyFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
//输入数字
void CKeyFrameWnd::InputNumber(const CStdString& strNumber)
{
	CStdString strPwd = m_edtPwd->GetText();
	strPwd += strNumber;
	m_edtPwd->SetText(strPwd);
}

void CKeyFrameWnd::InputBack()
{
	CStdString strPwd = m_edtPwd->GetText();
	if(strPwd.GetLength() == 0)
		return;
	strPwd = strPwd.Left(strPwd.GetLength() - 1);
	m_edtPwd->SetText(strPwd);
}

void CKeyFrameWnd::InputOk()
{
	CStdString strPwd = m_edtPwd->GetText();
	if(strPwd.IsEmpty())
	{
		m_bOk = false;
		return;
	}

	if(strPwd == m_strCheck)
	{
		m_bOk = true;
		Close();
	}
	else
	{
		m_lblMsg->SetText(_T("校验失败，请重新输入"));
		m_edtPwd->SetFocus();
	}
}