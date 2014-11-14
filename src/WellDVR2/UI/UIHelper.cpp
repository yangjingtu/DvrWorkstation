#include "stdafx.h"
#include "UIHelper.h"
#include "KeyFrameWnd.h"
#include "RegisterWnd.h"
#include "CLoginFrameWnd.h"
#include "MenuWnd.h"
#include "AboutWnd.h"
#include "MsgWnd.h"

CUIHelper::CUIHelper(void)
{
}


CUIHelper::~CUIHelper(void)
{

}

CUIHelper& CUIHelper::Instance()
{
	static CUIHelper uh;
	return uh;
}

bool CUIHelper::Check(const CStdString& strCheck, HWND hPWnd)
{
	CKeyFrameWnd* pKeyFW = new CKeyFrameWnd(strCheck);
	pKeyFW->Create(hPWnd, _T(""), UI_WNDSTYLE_DIALOG, 0,0,0,0,0, NULL);
	pKeyFW->CenterWindow();
	pKeyFW->ShowModal();
	bool bCheck = pKeyFW->IsOk();
	if(pKeyFW)
		delete pKeyFW;
	pKeyFW = NULL;
	return bCheck;
}

bool CUIHelper::Register(HWND hPWnd)
{
	CRegisterWnd* pWnd = new CRegisterWnd;
	pWnd->Create(hPWnd, _T(""), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
	pWnd->CenterWindow();
	pWnd->ShowModal();
	bool isReg = pWnd->IsRegister();
	if(pWnd)
		delete pWnd;
	pWnd = NULL;
	return isReg;
}

bool CUIHelper::Alert(const CString& strMsg, const CString& title, const CString& img, HWND hPWnd)
{
	LOGE(strMsg.GetString());

	CMsgWnd* pMsgWnd = new CMsgWnd;
	pMsgWnd->Create(hPWnd, _T(""), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);

	pMsgWnd->SetMsg(strMsg, title, img);

	pMsgWnd->CenterWindow();
	pMsgWnd->ShowModal();
	bool bOk = pMsgWnd->IsPressOk();
	if(pMsgWnd)
		delete pMsgWnd;
	pMsgWnd = NULL;

	return bOk;
}

bool CUIHelper::Login( HWND hPWnd )
{
        CLoginFrameWnd* pLoginFrame = new CLoginFrameWnd();
        if( pLoginFrame == NULL ) 
		{ 
			return false; 
		}
        pLoginFrame->Create(hPWnd, _T(""), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
        pLoginFrame->CenterWindow();
        pLoginFrame->ShowModal();
		bool bLogin = pLoginFrame->IsLogin();
		if(pLoginFrame)
			delete pLoginFrame;
		pLoginFrame = NULL;
		return bLogin;
}

void CUIHelper::AboutWnd(HWND hPWnd )
{
	CAboutWnd* pAboutFrame = new CAboutWnd();
	if( pAboutFrame == NULL ) 
	{ 
		return; 
	}
	pAboutFrame->Create(hPWnd, _T(""), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
	pAboutFrame->CenterWindow();
	pAboutFrame->ShowModal();
}

void CUIHelper::MenuWnd(CControlUI* pOwner, POINT pt)
{
	CMenuWnd* pMenu = new CMenuWnd();
	if( pMenu == NULL ) 
	{ 
		return; 
	}
	pMenu->Init(pOwner, pt);
}