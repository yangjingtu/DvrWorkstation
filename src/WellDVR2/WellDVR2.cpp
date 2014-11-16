// App.cpp : Defines the entry point for the application.
//
#include "stdafx.h"

#ifdef DEBUG
#include "MiniDumper.h"
CMiniDumper g_miniDumper( true );
#endif

#include "UI/CMainFrameWnd.h"
#include "ShareData.h"
#include "chmzc.h"
#include "ftp/FtpHelper.h"
#include "network/SockInit.h"
#include "UI/UIHelper.h"


#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

//检测内存泄露
void DetectorMemoryLeak()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}


static void ParseCmdLine(LPSTR lpCmdLine);
CString g_strFingerPath;

CString GetAppPath()
{
	CString path;   
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH),MAX_PATH);   
	int pos = path.ReverseFind('\\');
	path = path.Mid(0, pos);
	return path;
}

void InitFingerPath()
{
	CString str = GetAppPath();
	str += "\\FingerImage";
	g_strFingerPath = str;
	BOOL b = CreateDirectory(g_strFingerPath, NULL);

	SYSTEMTIME st = {0};
	GetLocalTime(&st);

	CString strCurFingerPath = g_strFingerPath;
	str.Format(_T("%04d%02d%02d"), st.wYear, st.wMonth, st.wDay);
	strCurFingerPath += _T("\\");
	strCurFingerPath += str;
	b = CreateDirectory(strCurFingerPath, NULL);
}

CString GetCurFingerPath()
{
	CString str;
	CString strCurFingerPath = g_strFingerPath;

	SYSTEMTIME st = {0};
	GetLocalTime(&st);

	str.Format(_T("%04d%02d%02d"), st.wYear, st.wMonth, st.wDay);
	strCurFingerPath += _T("\\");
	strCurFingerPath += str;
	BOOL b = CreateDirectory(strCurFingerPath, NULL);

	return strCurFingerPath;
}

//检查只有一个实例运行
BOOL CheckOneInstance()
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, DVR_INSTANCE);
	if(hMutex != NULL)
	{
		if(GetLastError() == ERROR_ALREADY_EXISTS)
		{
			//关闭进程互斥体
			CloseHandle(hMutex);
			hMutex = NULL;
			return FALSE;
		}
	}
	return TRUE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if(!CheckOneInstance())
		return 0;

	DetectorMemoryLeak();

    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
 //   CPaintManagerUI::SetResourceZip(_T("skin.zip"));

	LOGS(_T("************检查系统注册信息****************"));
	//检查注册
	while(!IsRegister())
	{
		if(!WELLUI.Register())
		{
			LOGS(_T("系统未合法注册"));
			return 0;
		}
	}
	LOGS(_T("系统合法注册，启动系统..."));

	SOCKSUPPORT;

    HRESULT Hr = ::CoInitialize(NULL);
    if( FAILED(Hr) ) 
		return 0;

#if FINGER_ENABLE
	InitFingerPath();
#endif

	ParseCmdLine(lpCmdLine);

    CMainFrameWnd* pFrame = new CMainFrameWnd();
    if( pFrame == NULL ) return 0;
	pFrame->SetInstance(hInstance);
    pFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, 0L, 0, 0, 1280, 1024);
    pFrame->CenterWindow();
//	pFrame->ShowWindow(true);
    ::ShowWindow(*pFrame, SW_SHOWMAXIMIZED);

    CPaintManagerUI::MessageLoop();

    ::CoUninitialize();
    return 0;
}

//解析参数，如果是-d就进入定位模式
static void ParseCmdLine(LPSTR lpCmdLine)
{
	SHAREDATA.g_dbgLevel = WORKING;
	if(lpCmdLine == NULL)
	{
		LOGS(_T("进入工作模式"));
		return;
	}

	// Process command line
	int cmdLen  = strlen(lpCmdLine);
	if( cmdLen > 0 && cmdLen < 3 )
	{
		if( lpCmdLine[0] == _T('/') || lpCmdLine[0] == _T('-') )
		{
			if( lpCmdLine[1] == _T('d') || lpCmdLine[1] == _T('D') )
			{
				SHAREDATA.g_dbgLevel = LOCATION;
				LOGS(_T("进入定位模式"));
				//删除PORT信息
				WritePrivateProfileString(_T("PORT"),NULL,NULL,GetAppPath() + gc_Config);
				return;
			}
		}
	}
	LOGS(_T("进入工作模式"));
}