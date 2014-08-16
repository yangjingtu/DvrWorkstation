// WellDvrTool.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WellDvrTool.h"
#include "DvrToolUI.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
    CPaintManagerUI::SetResourceZip(_T("dvrtool.zip"));
	
    HRESULT Hr = ::CoInitialize(NULL);
    if( FAILED(Hr) ) return 0;

	CDvrToolUI* pFrame = new CDvrToolUI();
    if( pFrame == NULL ) return 0;

    pFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, 0L, 0, 0, 1024, 738);
    pFrame->CenterWindow();
	
    ::ShowWindow(*pFrame, SW_SHOWNORMAL);

    CPaintManagerUI::MessageLoop();

    ::CoUninitialize();
    return 0;

}