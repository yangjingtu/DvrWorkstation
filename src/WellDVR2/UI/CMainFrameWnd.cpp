#include "stdafx.h"

#include "../DataDef.h"
#include "CMainFrameWnd.h"
#include "../resource.h"

#include <exdisp.h>
#include <comdef.h>

#include <dbt.h>

#include "UIHelper.h"
#include "../dvr/interface.h"
#include "../WellCommon/IniFile.h"
#include "../ShareData.h"
#include "../DvrMgr.h"
#include "DvrListUI.h"
#include "../DataBase/DataBase.h"
#include "../ftp/FtpMgr.h"
#include "../config/Config.h"
#include "../DvrLocation.h"

#include "../USBCtrl/UsbHelper.h"
#include "../config/LocationConfig.h"
#include "../WellCommon/CharSetHelper.h"

#include "../USBCtrl/UsbHelper.h"

#include "../ConvertVideo/Avi2Flv.h"
#include "../network/NetHttpClient.h"
#include "../gdi/DrawEngine.h"
#include "../network/NetUtil.h"

#include <sstream>
using namespace std;

extern CString GetAppPath();

CMainFrameWnd::CMainFrameWnd()
	: m_hInstance(NULL)
	, m_bMass(FALSE)
	, m_cntMass(0)
{
#ifdef ONE_DVR
	m_bTopWnd = FALSE;
#else
	m_bTopWnd = TRUE;
#endif

	m_pHttpClient = new CNetHttpClient();
	//m_pHttpClient->Connect(WS2S(SHAREDATA.g_strWebIp.GetString()), SHAREDATA.g_nWebPort);
}

CMainFrameWnd::~CMainFrameWnd()
{
	if(m_pHttpClient)
	{
		delete m_pHttpClient;
		m_pHttpClient = NULL;
	}
}

LPCTSTR CMainFrameWnd::GetWindowClassName() const 
{ 
	return _T("UIMainFrame"); 
}
	
UINT  CMainFrameWnd::GetClassStyle() const 
{ 
	return CS_DBLCLKS; 
	//return UI_CLASSSTYLE_DIALOG;
}
	
void  CMainFrameWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	m_pm.RemovePreMessageFilter(this);
	delete this; 
}

void  CMainFrameWnd::Init() 
{
	m_pLogoBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("logobtn")));
	m_pCaptionTxt = static_cast<CTextUI*>(m_pm.FindControl(_T("txtCaption")));
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));
	m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
	
	m_pMsgLbl = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblmsg")));

	m_pNetConnLbl = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblNet")));
	m_pNetstatusLbl = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblnetstatus")));
	m_pIpLbl = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblip")));

	m_pCompanyLbl = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblcompany")));
	m_pVersionLbl = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblversion")));
	m_pDateTimeLbl = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbldt")));

	m_pFreeSpace = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblfreespace")));
	m_pUsedSpace = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblusedspace")));
	m_pTotalSpace = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbltotalspace")));
	m_pUsedPecent = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblusedpecent")));

	m_pDrawLbl = static_cast<CLabelUI*>(m_pm.FindControl(_T("lbldraw")));

	m_pPhoneLbl = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblphone")));

	m_pDvrListUI = static_cast<DvrListUI*>(m_pm.FindControl(_T("dvrlist")));

	if(m_pCaptionTxt)
	{
		m_pCaptionTxt->SetText(gc_AppName);
	}

	m_pFtpPro = static_cast<CProgressUI*>(m_pm.FindControl(_T("proFtp")));
	if(m_pFtpPro)
	{
		RECT rcText;
		rcText.top = 8;
		rcText.left = rcText.right = rcText.bottom = 0;
		m_pFtpPro->SetTextPadding(rcText);
	}
}

void  CMainFrameWnd::OnPrepare() 
{ 
	//��¼��Ϣ
	//WELLUI.Login();

	SHAREDATA.g_pMainFrame = this;

	ShowDateTime();
	ShowNetwork();
	ShowCompanyAndVersion();

	if(!InitSystem())
	{
		exit(0);
	}

	//����ϵͳ����ͼ��
	CreateNotifyIcon();

	RegisgerDvr();

	SetTimer(m_hWnd, CHECKDEV_STATUS_TIMERID, 500, NULL);

	SetTimer(m_hWnd, SHOWTIME_TIMERID, 1000, NULL);

	SetTimer(m_hWnd, CHECKDEV_DATA_TIMERID, 5000, NULL);

	SetTimer(m_hWnd, CHECKFTP_TIMERID, 3000, NULL);

	SetTimer(m_hWnd, CHECKUSB_TIMERID, 1500, NULL);
}

void  CMainFrameWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("windowinit") ) OnPrepare();
	else if( msg.sType == _T("click") ) 
	{
		if( msg.pSender == m_pMinBtn ) { SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); 
			return; }
		else if( msg.pSender == m_pMaxBtn ) { SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
		else if( msg.pSender == m_pRestoreBtn ) { SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
		else if( msg.pSender == m_pCloseBtn ) 
		{ 
			if(SHAREDATA.g_dbgLevel == LOCATION)
			{
				CONF.BackUp();
				Close(); //PostQuitMessage(0); // ��Ϊactivex��ԭ��ʹ��close���ܻ���ִ���
			}
			else
			{
				CloseWnd();
			}
			return; 
		}

		CDuiString name = msg.pSender->GetName();
		if( name == _T("quitbtn") ) 
		{
			CloseWnd();
			return;
		}

		//ֹͣ����
		m_pDvrListUI->OnBtnClick(msg);
	}
	else if( msg.sType == _T("Quit"))
	{
		CloseWnd();
		return;
	}
	else if( msg.sType == _T("menu_Open"))
	{
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); 
		return;
	}
	else if( msg.sType == _T("menu_About"))
	{
		WELLUI.AboutWnd();        
	}
}


LRESULT  CMainFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	m_pm.AddPreMessageFilter(this);
	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("mainframe.xml"), (UINT)0, &cb, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();
	return 0;
}

LRESULT  CMainFrameWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	AVI2FLV.Stop();
//	LOGS(_T("ֹͣת�����"));

	//�ڶ�λģʽ�£����������ļ�
	//if(SHAREDATA.g_dbgLevel == LOCATION)
	{
		CONF.BackUp();
		LOGS(_T("���������ļ�"));
	}

	WSACleanup();
	Sleep(100);

	LOGS(_T("ϵͳ�����ر�"));
	bHandled = FALSE;
	return 0;
}

LRESULT  CMainFrameWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	KillTimer(m_hWnd, SHOWTIME_TIMERID);
	KillTimer(m_hWnd, CHECKDEV_STATUS_TIMERID);
	KillTimer(m_hWnd, CHECKDEV_DATA_TIMERID);
	KillTimer(m_hWnd, CHECKFTP_TIMERID);
	KillTimer(m_hWnd, CHECKUSB_TIMERID);
	LOGS(_T("�رն�ʱ��"));

	CONF.BackUp();
	::PostQuitMessage(0L);

	bHandled = FALSE;
	return 0;
}

LRESULT  CMainFrameWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT  CMainFrameWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT  CMainFrameWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT  CMainFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if( !::IsZoomed(*this) ) {
		RECT rcSizeBox = m_pm.GetSizeBox();
		if( pt.y < rcClient.top + rcSizeBox.top ) {
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
			return HTTOP;
		}
		else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) {
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
		if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
	}

	RECT rcCaption = m_pm.GetCaptionRect();
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
			if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
				_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
				_tcscmp(pControl->GetClass(), _T("TextUI")) != 0 )
				return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT  CMainFrameWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT  CMainFrameWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	DuiLib::CDuiRect rcWork = oMonitor.rcWork;
	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;

// 	lpMMI->ptMaxPosition.x = rcWork.left;
// 	lpMMI->ptMaxPosition.y = rcWork.top;
// 	lpMMI->ptMaxSize.x = rcWork.right - rcWork.left;
// 	lpMMI->ptMaxSize.y = rcWork.bottom - rcWork.top;

	//ʵ��ȫ��
	int  nFullWidth=GetSystemMetrics(SM_CXSCREEN);
	int  nFullHeight=GetSystemMetrics(SM_CYSCREEN);
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;
	lpMMI->ptMaxSize.x = nFullWidth;
	lpMMI->ptMaxSize.y = nFullHeight;
	lpMMI->ptMaxTrackSize.x = nFullWidth;
	lpMMI->ptMaxTrackSize.y = nFullHeight;
	
	bHandled = FALSE;
	return 0;
}

LRESULT  CMainFrameWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
	if( wParam == SC_CLOSE ) {
		CONF.BackUp();
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	if( wParam == SC_MINIMIZE)
	{
		//���㴰�ڣ��رհ�ť�ᷢ��SC_MAXIMIZE��
		if(m_bTopWnd)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			return 0;
		}
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if( ::IsZoomed(*this) != bZoomed ) {
// 		if( !bZoomed ) {
// 			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
// 			if( pControl ) pControl->SetVisible(false);
// 			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
// 			if( pControl ) pControl->SetVisible(true);
// 		}
// 		else {
// 			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
// 			if( pControl ) pControl->SetVisible(true);
// 			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
// 			if( pControl ) pControl->SetVisible(false);
// 		}
	}
	return lRes;
}

LRESULT  CMainFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg ) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:		   lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	case WM_TIMER:		   lRes = OnTimer(uMsg, wParam, lParam); break;
	case WM_DEVICECHANGE:  lRes = OnMyDeviceChange(wParam, lParam); break;
	case WM_NOTIFYDATA:	   lRes = OnNotifyData(wParam, lParam); break;
	case WM_SYSCHAR:	   lRes = OnSysKeyHandle(wParam, lParam); break;
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMainFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	return S_OK;
}


//Alt��ݼ�����
//1. Alt + shift + C  �������ù���
//2. Alt + shift + Q  �˳�����
//3. Alt + shift + M  ��ȡע����
//4. Alt + shift + R  ע�ᴰ��
//5. Alt + t		  ȡ�����ö��㴰��
LRESULT CMainFrameWnd::OnSysKeyHandle(WPARAM wParam, LPARAM lParam)
{
	// Handle ALT-shortcut key-combinations  
	CString strPath = GetAppPath();
	char nChar = wParam;
	if(nChar == 'C')
	{
		LOGS(_T("��ݼ� �������ù��߳���"));
#ifdef ONE_DVR
		ShellExecute(m_hWnd,_T("open"),strPath + gc_configApp, _T("one"), NULL,SW_SHOWNORMAL);		
#else
		ShellExecute(m_hWnd,_T("open"),strPath + gc_configApp, _T("more"),NULL,SW_SHOWNORMAL);	
#endif
	}
	else if(nChar == 'Q')
	{
		CloseWnd();
	}
	else if(nChar == 'M')
	{
		LOGS(_T("��ݼ� ���û�ȡ���������"));
		ShellExecute(m_hWnd,_T("open"),strPath + gc_GetMachineApp,NULL,NULL,SW_SHOWNORMAL);	
	}
	else if(nChar == 'R')
	{
		LOGS(_T("��ݼ� ����ע�������"));
		ShellExecute(m_hWnd,_T("open"),strPath + gc_RegisterApp,NULL,NULL,SW_SHOWNORMAL);	
	}
#ifndef ONE_DVR
	else if(nChar == 't')
	{
		LOGS(_T("��ݼ� ��ȡ�����ռ[%d]"), m_bTopWnd);
		m_bTopWnd = !m_bTopWnd;
	}
#endif

	return S_OK;
}

LRESULT CMainFrameWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case SHOWTIME_TIMERID:
		ShowDateTime();
		ShowFreeSpace();
		SetTopWnd();
		break;
	case CHECKFTP_TIMERID:
		if(FTP_CLIENT.IsFtpValid())
		{
			//ShowFtpInfo();
			FTP_CLIENT.GetTransInfo();
			m_pFtpPro->SetVisible(true);
		}
		else
		{
			m_pFtpPro->SetVisible(false);
		}
		break;
	case CHECKUSB_TIMERID:
		CheckUsbHub();
		break;
	case CHECKDEV_STATUS_TIMERID:
		CheckDeviceStatusTimer();
		break;
	case CHECKDEV_DATA_TIMERID:
		//�ȽϷ�ʱ�����Կ������߳�
		CheckDeviceDataTimer();
		break;
	default:
		//���ඨʱ������ϵͳ����
		LRESULT lRes = 0;
		if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}

	return 0;	
}

void CMainFrameWnd::ShowMsgInfo(const CDuiString& msg)
{
	m_pMsgLbl->SetText(msg);
}

void CMainFrameWnd::ShowDateTime()
{
	//��ʾʱ��
	SYSTEMTIME   st;   
	::GetSystemTime(&st);

	CDuiString str;
	str.Format(_T("%d-%d-%d %02d:%02d:%02d"),st.wYear, st.wMonth,st.wDay,st.wHour+8 > 24 ? st.wHour - 16 : st.wHour + 8,st.wMinute,st.wSecond);

	m_pDateTimeLbl->SetText(str.GetData());
}

void CMainFrameWnd::ShowCompanyAndVersion()
{
	SoftWareInfo swi = CONF.GetSWInfo();
// 	CDuiString str;
// 	str.Format(_T("%s"), COMPANY, SOFT_VERSION);
	m_pCompanyLbl->SetText(swi.strCpy);
//	str.Format(_T("%s"), SOFT_VERSION);
	m_pVersionLbl->SetText(swi.strVersion);
	m_pPhoneLbl->SetText(swi.strPhone);
}

void CMainFrameWnd::ShowNetwork()
{
	wstring strIp;
	if(GetIpAddr(strIp))
	{
		m_pIpLbl->SetText(strIp.c_str());
		m_pNetstatusLbl->SetText(_T("������������"));
		m_pNetConnLbl->SetBkImage(_T("net-connect.png"));
	}
	else
	{
		m_pIpLbl->SetText(strIp.c_str());
		m_pNetstatusLbl->SetText(_T("���������쳣"));
		m_pNetConnLbl->SetBkImage(_T("net-disconnect.png"));
	}
}

BOOL CMainFrameWnd::InitSystem()
{
	// Initialize winsock communication
	WSADATA wsa;
	int ret = WSAStartup(0x0101, &wsa);
	if( ret != 0 )
	{
		Alert(_T("Initialize winsock failed!"));
		return FALSE;
	}

	if(SHAREDATA.g_strDeviceId.IsEmpty())
	{
		SHAREDATA.g_strDeviceId = CONF.GetDeviceInfo().strId;
		if(SHAREDATA.g_strDeviceId.IsEmpty())
		{
			Alert(_T("��Ϊ�豸����Ψһ���豸���!"));
		}
	}

	//////////////////////////////////////////////////////////////////////////
	USBHUB.GetUsbPort_DiskName();

	if(SHAREDATA.g_dbgLevel == LOCATION)
	{
		LOCATIONCONF.Init();
	}
	else
	{
		LOCATIONCONF.InitFromFile();

		//�������ļ��г�ʼ��
		CONF.InitFromConfig();
	}
	LOGS(_T("�������ļ��г�ʼ�����!"));

	FTP_CLIENT.Register(CMainFrameWnd::ShowFtpInfo);
	//����FTP����
	bool bRun = FTP_CLIENT.Run();

#ifdef ONE_DVR
	if(!bRun)
	{
		LOGS(_T("������������ ����FTP����ʧ��"));
		return FALSE;
	}
#endif
	LOGS(bRun ? _T("����FTP����ɹ�") : _T("����FTP����ʧ��"));

	//����ת�����
//	wstring strFlvPath = SHAREDATA.g_strFilePath.GetString();
//	strFlvPath += _T("\\WebVideo\\");
//	AVI2FLV.Run(strFlvPath);

//	LOGS(_T("����ת�����"));
//	LOGS(_T("ϵͳ��������"));

	return TRUE;
}

void CMainFrameWnd::SetInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}

void CMainFrameWnd::CreateNotifyIcon()
{
	CDuiString strPath = CPaintManagerUI::GetResourcePath() + _T("..\\ico\\logo.ico");
	//����SetIcon
	HICON hIcon = (HICON)LoadImage(NULL, strPath.GetData() ,IMAGE_ICON,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	::SendMessage(m_hWnd, WM_SETICON, (WPARAM) FALSE, (LPARAM) hIcon); 

	BOOL bt = TRUE;
	m_NotifyData.cbSize = sizeof(NOTIFYICONDATA);
	m_NotifyData.hIcon = hIcon; //::LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_LOGO));
	m_NotifyData.hWnd = this->m_hWnd;	
	_tcscpy(m_NotifyData.szTip, gc_AppName);
	m_NotifyData.uCallbackMessage = WM_NOTIFYDATA;
	m_NotifyData.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
	m_NotifyData.uID = WM_NOTIFYID;	
	VERIFY(bt = Shell_NotifyIcon(NIM_ADD, &m_NotifyData));

	//-------------------------------------------------------------------
	HDEVNOTIFY hDevNotify = NULL;
	DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
	ZeroMemory(&NotificationFilter, sizeof(NotificationFilter));
	NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

	LOGS(_T("��������ͼ�����"));

	//this->SetIcon(IDI_LOGO);
	if(m_pLogoBtn)
	{
		LPCTSTR strImg = m_pLogoBtn->GetNormalImage();
		m_pLogoBtn->SetNormalImage(_T("file='logo.png' mask='0xffffffff'"));
		m_pLogoBtn->SetPushedImage(_T("file='logo.png' mask='0xffffffff'"));
		m_pLogoBtn->SetHotImage(_T("file='logo.png' mask='0xffffffff'"));
	}
}

void CMainFrameWnd::ShowFtpInfo(const wstring& file, const wstring& info, int precent)
{
	if(info == _T("��Ϣ��ʾ"))
		return;
	static int count = 0;
	if(file.empty() && count == 0)
	{
		count = 1;
		SHAREDATA.g_pMainFrame->m_pMsgLbl->SetText(_T("��ʾ��Ϣ"));
	}
	else if(!file.empty())
	{
		count = 0;
		SHAREDATA.g_pMainFrame->m_pMsgLbl->SetText(file.c_str());
	}

	SHAREDATA.g_pMainFrame->m_pFtpPro->SetText(info.c_str());
	SHAREDATA.g_pMainFrame->m_pFtpPro->SetValue(precent);
}

//����--���̨�����豸״̬
void CMainFrameWnd::CheckDeviceDataTimer()
{	
	if(!DB.IsValid())
		return;

	//������������̨
	//1. ���ô洢����
	static TERMINAL_STATE status;
	status.strDeviceNumber = SHAREDATA.g_strDeviceId;
	status.strRemark = _T(" ");
	status.strDeviceState = _T("ok");

	CTime tm = CTime::GetCurrentTime();
	status.strReportTime = tm.Format(_T("%Y-%m-%d %H:%M:%S"));

	DB.InsertStatus(status);

	//2. HTTP�ķ�ʽ��������
	if(m_pHttpClient)
	{
		//http://192.168.1.90:9090/hdvr/devHealthMonitor?deviceNumber=000001111&storeSpace=200&freeSpace=2000&runningState=normal&accessToken=B76269AC8F66BE563332ED094ED17AEB&actionType=reportHealth
		ostringstream os;
		os << "/hdvr/devHealthMonitor?deviceNumber=" << WS2S(SHAREDATA.g_strDeviceId.GetString())
			<< "&storeSpace=" << SHAREDATA.g_dwTotalSpace
			<< "&freeSpace=" << SHAREDATA.g_dwFreeSpace
			<< "&runningState=" << "normal"
			<< "&accessToken=B76269AC8F66BE563332ED094ED17AEB" 
			<< "&actionType=reportHealth";

		m_pHttpClient->Send(os.str().c_str(), os.str().length());

		LOG(_T("���̨����http״̬"));
	}

	
	//�����ն���־
	static int nCount = 0;
	//500�����һ��
	if(nCount++ == 100)
	{
		TERMINAL_DEV_LOG tdLog;
		tdLog.strDeviceNumber = SHAREDATA.g_strDeviceId;
		CString strT;
		strT.Format(_T("%lf"), SHAREDATA.g_dwFreeSpace);
		tdLog.strDiskSpace = strT;
		tdLog.strHarewareVersion = _T(" ");
		tdLog.strSoftwareVersion = SOFT_VERSION;
		tdLog.strIsusing = _T("Y");
		tdLog.strRemark = _T(" ");
		tdLog.strBattalion = _T(" ");
		tdLog.strSquadron = _T(" ");
		tdLog.strDetachment = _T(" ");
		wstring strIp;
		if(GetIpAddr(strIp))
		{
			tdLog.strTerminalIp = strIp.c_str();
			tdLog.strDescribe = _T("�ɼ��ն���������");
		}
		else
		{
			tdLog.strTerminalIp = strIp.c_str();
			tdLog.strDescribe = _T("�ɼ������쳣");
		}

		DB.InsertLog(tdLog);
		LOG(_T("���̨д���ն���־"));
		nCount = 0;
	}
}

LRESULT CMainFrameWnd::OnMyDeviceChange(WPARAM wParam, LPARAM lParam)
{

	if ( DBT_DEVICEARRIVAL == wParam || DBT_DEVICEREMOVECOMPLETE == wParam ) 
	{
		PDEV_BROADCAST_HDR pHdr = (PDEV_BROADCAST_HDR)lParam;
		PDEV_BROADCAST_DEVICEINTERFACE pDevInf;
		PDEV_BROADCAST_HANDLE pDevHnd;
		PDEV_BROADCAST_OEM pDevOem;
		PDEV_BROADCAST_PORT pDevPort;
		PDEV_BROADCAST_VOLUME pDevVolume;

		switch( pHdr->dbch_devicetype ) 
		{
		case DBT_DEVTYP_DEVICEINTERFACE:
			pDevInf = (PDEV_BROADCAST_DEVICEINTERFACE)pHdr;
			if( wParam == DBT_DEVICEARRIVAL ) // add device
			{
				AddUsbDevice(pDevInf->dbcc_name);
			}
			else if( wParam == DBT_DEVICEREMOVECOMPLETE ) // remove device
			{
				RemoveUsbDevice(pDevInf->dbcc_name);
			}
			break;
		case DBT_DEVTYP_HANDLE:
			pDevHnd = (PDEV_BROADCAST_HANDLE)pHdr;

			break;
		case DBT_DEVTYP_OEM:
			pDevOem = (PDEV_BROADCAST_OEM)pHdr;

			break;
		case DBT_DEVTYP_PORT:
			pDevPort = (PDEV_BROADCAST_PORT)pHdr;

			break;
		case DBT_DEVTYP_VOLUME:
			pDevVolume = (PDEV_BROADCAST_VOLUME)pHdr;

			break;
		}
	}
	return S_OK;
}
// Copy from HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\DeviceClasses
static const GUID GUID_DEVINTERFACE_LIST[] = 
{
	// GUID_DEVINTERFACE_USB_DEVICE
	{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },

	// GUID_DEVINTERFACE_DISK
	//{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },

	// GUID_DEVINTERFACE_HID, 
	//{ 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },

	// GUID_NDIS_LAN_CLASS
	//{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }

	// GUID_DEVINTERFACE_COMPORT
	//{ 0x86e0d1e0, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },

	// GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR
	//{ 0x4D36E978, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } },

	// GUID_DEVINTERFACE_PARALLEL
	//{ 0x97F76EF0, 0xF883, 0x11D0, { 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C } },

	// GUID_DEVINTERFACE_PARCLASS
	//{ 0x811FC6A5, 0xF728, 0x11D0, { 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1 } }
};

static int DEVICE_LIST_LENGTH = sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID);

void CMainFrameWnd::RegisgerDvr()
{
	HDEVNOTIFY hDevNotify = NULL;
	DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
	ZeroMemory(&NotificationFilter, sizeof(NotificationFilter));
	NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

	for( int i = 0; i < DEVICE_LIST_LENGTH; i++ ) 
	{
		NotificationFilter.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];

		hDevNotify = RegisterDeviceNotification(this->m_hWnd, &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);
		if( !hDevNotify ) 
		{
			TRACE("\nCan't register device notification\n");
		}
	}
}

//����豸״̬��ʱ��
void CMainFrameWnd::CheckDeviceStatusTimer()
{
	CDvrWnd* pDvr = NULL;
	//����豸�б��е�DVR״̬���ı���ʾ����ɫ�������Ϣ
	for (int i = 0 ; i < SHAREDATA.g_dvrProp.numDvr; ++i)
	{
		if(SHAREDATA.g_dbgLevel == LOCATION)
		{
			pDvr = CDvrLocation::Instance().GetDvr(i);
		}
		else
		{
			pDvr = CDvrMgr::Instance().GetDvr(i);
		}
	
		m_pDvrListUI->SetInfo(pDvr->GetRow(), pDvr->GetColumn(), pDvr);
	}
}

//��ȡѡ���λ����Ϣ���У��У�
void CMainFrameWnd::GetSelectPos(int& row, int& col)
{
	m_pDvrListUI->GetSelectPos(row, col);
	m_pDvrListUI->ClearSelectPos();
}

LRESULT CMainFrameWnd::OnNotifyData(WPARAM wParam, LPARAM lParam)
{
	if(WM_NOTIFYID == wParam && WM_RBUTTONDOWN == lParam)
	{
		DuiLib::CPoint CursorPos;
		GetCursorPos(&CursorPos);
		POINT pt = {CursorPos.x, CursorPos.y};
		//�����˵�
		WELLUI.MenuWnd(m_pDvrListUI, pt);
	}
	else if(WM_NOTIFYID == wParam && WM_LBUTTONDBLCLK == lParam)
	{
		ShowWindow(SW_SHOW);
	}
	return S_OK;
}

bool CMainFrameWnd::Alert(const CString& strMsg, const CString& title, const CString& img)
{
	return WELLUI.Alert(strMsg, title, img);
}

void CMainFrameWnd::ShowFreeSpace()
{
	static CString strDriver = SHAREDATA.g_strFilePath.Left(3);

	ULARGE_INTEGER   FreeAv,TotalBytes,FreeBytes;   
	if(GetDiskFreeSpaceEx(strDriver,&FreeAv,&TotalBytes,&FreeBytes))   
	{   
		//��ʽ����Ϣ������ʾ����   
		CString   strInfo;
		double dFree = FreeBytes.QuadPart/1024.0/1024.0;
		if(dFree / 1024.0 > 1)
		{
			strInfo.Format(_T("%.0fGB"), dFree/1024.0); 
		}
		else
		{
			if(dFree < gc_MinSpaceLimit)
			{
				static int nCount = 1;
				if(nCount++ % 60 == 0)
				{
					//һ���ӱ���һ��
					PlaySound((LPCTSTR)IDR_WAVE2, NULL, SND_RESOURCE | SND_ASYNC);
					nCount = 1;
				}
				CDuiString strMsg;
				strMsg.Format(_T("ʣ��ռ䲻��%.dMB,Ϊ��֤���ݰ�ȫ�������κβ�����"),gc_MinSpaceLimit); 
				ShowMsgInfo(strMsg);
			}
			strInfo.Format(_T("%.0fMB"),dFree); 
		}
		SHAREDATA.g_dwFreeSpace = dFree;
		SHAREDATA.g_dwTotalSpace = TotalBytes.QuadPart/1024.0/1024.0;
		m_pFreeSpace->SetText(strInfo);

		strInfo.Format(_T("%.0fGB"), double(TotalBytes.QuadPart)/1024.0/1024.0/1024.0);
		m_pTotalSpace->SetText(strInfo);
		strInfo.Format(_T("%.0fGB"), (TotalBytes.QuadPart - FreeBytes.QuadPart) /1024.0/1024.0/1024.0);
		m_pUsedSpace->SetText(strInfo);
		float fUsed = (double)(TotalBytes.QuadPart - FreeBytes.QuadPart) /(double)TotalBytes.QuadPart;
		strInfo.Format(_T("%.0f%%"), fUsed * 100);
		m_pUsedPecent->SetText(strInfo);
	
		DrawSpacePie(fUsed);
	}
}

void CMainFrameWnd::SetTopWnd()
{
	if(m_bTopWnd)
	{
		m_pMinBtn->SetEnabled(false);
		m_pMaxBtn->SetEnabled(false);
		m_pRestoreBtn->SetEnabled(false);
		//m_pCloseBtn->SetEnabled(false);

		//��С����ԭ
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	
		//����Ϊ���ϲ㴰��
		::SetForegroundWindow(m_hWnd);
	}
	else
	{
		m_pMinBtn->SetEnabled(true);
		m_pMaxBtn->SetEnabled(true);
		m_pRestoreBtn->SetEnabled(true);
//		m_pCloseBtn->SetEnabled(true);
	}
}

//USB�豸����
void CMainFrameWnd::AddUsbDevice( const CString& strName )
{
	CString strVPID = GetVID_PIDString(strName, _T('#'));
	if( strVPID != CMD_VID_PID && strVPID != MASS_VID_PID)
	{
		//����DVR�豸�򷵻�
		return;
	}

	if( strVPID == CMD_VID_PID )
	{
		//m_pMsgLbl->SetTextColor(CLR_MSG_ADD_DEV);
		//m_pMsgLbl->SetText(_T("��⵽DVR�豸����"));

 		if(SHAREDATA.g_dbgLevel == LOCATION)
 			CDvrLocation::Instance().PutDvr();
// 		else
// 			CDvrMgr::Instance().PutDvr();
	}
	else if( strVPID == MASS_VID_PID )
	{
//		CDvrMgr::Instance().CopyDvrFile();
	}
}

void CMainFrameWnd::RemoveUsbDevice( const CString& strName )
{	
	CString strVPID = GetVID_PIDString(strName, _T('#'));
	if( strVPID != CMD_VID_PID && strVPID != MASS_VID_PID)
	{
		//����DVR�豸�򷵻�
		return;
	}

	//m_pMsgLbl->SetTextColor(CLR_MSG_DEL_DEV);
	//m_pMsgLbl->SetText(_T("��⵽DVR�豸�ε�"));

	if( strVPID == CMD_VID_PID )
	{	
 		if( SHAREDATA.g_dbgLevel == LOCATION )
 			CDvrLocation::Instance().RemoveDvr();
// 		else
// 			CDvrMgr::Instance().RemoveDvr();
	}
	else if( strVPID == MASS_VID_PID )
	{
//		CDvrMgr::Instance().RemoveDvr(true);
	}
}

//��ȡVID_PID
CString CMainFrameWnd::GetVID_PIDString(const CString &str,  wchar_t  chSplit )
{
	int pos1 = str.Find(chSplit);//str.Find(_T('#'));
	CString s1 = str.Mid(pos1+1);
	int pos2 = s1.Find(chSplit); //s1.Find(_T('#'));
	CString s2 = s1.Left(pos2);
	s2.MakeUpper();
	return s2;
}

bool CMainFrameWnd::GetIpAddr(wstring &strIp)
{
	strIp = CNetUtil::GetLocalIpAddr();
	if(strIp == _T("127.0.0.1"))
	{
		strIp = _T("�ɼ�վδ����");
		return false;
	}
	return true;
}

//���USB HUB��״̬
//����USB hub�ڵ������豸�����������ֲ���
//		1. vid-pid����ö�ٲ���
//		2. vid-pid + �̷��� �����ݿ�������
void CMainFrameWnd::CheckUsbHub()
{
	//��λģʽ�²������
	if(SHAREDATA.g_dbgLevel == LOCATION)
		return;

	static map<wstring, int> mapPort_Count;
	CDvrWnd* pDvr = NULL;
	MapUsb mUsb = USBHUB.GetMapPortName();
	MapUsb::iterator it = mUsb.begin();
	for ( ; it != mUsb.end(); ++it) 
	{
		if(it->second.empty())
		{
			int nCount = mapPort_Count[(*it).first];
			if(nCount == 0)
			{
				//��������-----�γ���3����û��״̬�����
				CDvrMgr::Instance().RemoveDvr((*it).first);
			}
			else
			{
				mapPort_Count[(*it).first] = --nCount;
			}
			continue;
		}

		CString strVPID = GetVID_PIDString(it->second.c_str(), _T('\\'));
		if( strVPID == CMD_VID_PID )
		{
			//40������
			mapPort_Count[(*it).first] = 40;
			
			pDvr = CDvrMgr::Instance().PutDvr((*it).first);
			if(pDvr)
			{
				pDvr->SyncTime();
				Sleep(200);
				//ö����
				pDvr->MassDev();
			}
		}	
		else if(strVPID == MASS_VID_PID)
		{
			//3������
			mapPort_Count[(*it).first] = 3;					//3��

			wstring diskName = (*it).second;
			diskName = diskName.substr(diskName.length() - 3);
			if( diskName.find(']') == wstring::npos)
			{
				continue;
			}
			diskName = diskName.substr(0 , 2);

			//�ָ���ʾ
// 			pDvr = CDvrMgr::Instance().GetDvr((*it).first);
// 			if(pDvr)
// 			{
// 				if(pDvr->GetId().IsEmpty())
// 				{
// 					pDvr->SetStatusStr(_T("�޷���ȷ��ȡ�豸ID,�����°β壡"));
// 				}
// 				else
// 				{
// 					pDvr->SetDisk(diskName.c_str());
					//��������
					CDvrMgr::Instance().CopyDvrFile((*it).first, diskName);
// 				}
// 				m_pDvrListUI->SetInfo(pDvr->GetRow(), pDvr->GetColumn(), pDvr);
//			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//add by yjt 2014-11-13
//���ƿռ�ȱ�ͼ
//  nUsed : ��ʹ�ðٷֱ� 0.00 - 1.00
//////////////////////////////////////////////////////////////////////////
void CMainFrameWnd::DrawSpacePie(float nUsed)
{
	//��������
	float usedPercent = nUsed + 0.005;

	PieInfo pi[2];
	pi[0].angle = usedPercent * 360;
	pi[0].backColor = RGB(249, 54, 247);
	pi[0].textColor = RGB(0,128,100);
	pi[0].title = _T("����");
	pi[1].angle = 360 - (int)(usedPercent * 360);
	pi[1].backColor = RGB(56, 244, 111);
	pi[1].textColor = RGB(255,0,100);
	pi[1].title = _T("����");

	DRAWENGINE.DrawPie(this->m_hWnd, m_pDrawLbl->GetPos(), pi, sizeof(pi) / sizeof(PieInfo));
}

bool CMainFrameWnd::KeyFrameCheck()
{
	return WELLUI.Check(_T("8"), this->m_hWnd);
}

bool CMainFrameWnd::CloseWnd()
{
	if(KeyFrameCheck())
	{
		DeleteNotifyIcon();

		CONF.BackUp();
		Close();
		return true;
	}
	return false;
}

void CMainFrameWnd::DeleteNotifyIcon()
{
	Shell_NotifyIcon(NIM_DELETE,   &m_NotifyData);
}