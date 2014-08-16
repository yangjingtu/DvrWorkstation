#include "stdafx.h"
#include "DvrToolUI.h"

#include <dbt.h>

#include "DvrFactory.h"
#include "../WellDVR2/dvr/interface.h"
#include "resource.h"


#define CMD_VID_PID _T("VID_0595&PID_4343")
#define MASS_VID_PID _T("VID_0595&PID_2002")

CDvrToolUI::CDvrToolUI(void)
{
	m_pDvr = NULL;
}


CDvrToolUI::~CDvrToolUI(void)
{
	if(m_pDvr)
	{
		delete m_pDvr;
		m_pDvr = NULL;
	}
}


LPCTSTR CDvrToolUI::GetWindowClassName() const 
{ 
	return _T("UIMainFrame"); 
}
	
UINT  CDvrToolUI::GetClassStyle() const 
{ 
	return CS_DBLCLKS; 
}
	
void  CDvrToolUI::OnFinalMessage(HWND /*hWnd*/) 
{ 
	delete this; 
}

void  CDvrToolUI::Init() 
{
	m_btnCheck = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnCheck")));
	m_btnPwd = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnPwd")));
	m_btnDevId = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnDevId")));
	m_btnPoliceId = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnPoliceId")));
	m_btnDir = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnDir")));
	m_btnSync = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnSync")));
	m_btnClose = static_cast<CButtonUI*>(m_pm.FindControl(_T("btnClose")));

	
	m_edtPwd = static_cast<CEditUI*>(m_pm.FindControl(_T("edtPwd")));
	m_edtPwdNew = static_cast<CEditUI*>(m_pm.FindControl(_T("edtPwdNew")));
	m_edtDevId = static_cast<CEditUI*>(m_pm.FindControl(_T("edtDevId")));
	m_edtPoliceId = static_cast<CEditUI*>(m_pm.FindControl(_T("edtPoliceId")));

	m_lblMsg = static_cast<CLabelUI*>(m_pm.FindControl(_T("lblMsg")));
}

void  CDvrToolUI::OnPrepare() 
{ 
	EnableUI(false);

	RegisgerDvr();
}

void  CDvrToolUI::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("windowinit") ) 
		OnPrepare();
	else if( msg.sType == _T("click") ) 
	{
		//关闭按钮
		if(msg.pSender == m_btnClose)
		{
			Close();
		}
		else if(msg.pSender == m_btnCheck){
			OnClickBtnCheck();
		}
		else if(msg.pSender == m_btnPwd)
		{
			OnClickBtnPwd();
		}
		else if(msg.pSender == m_btnDevId){
			OnClickBtnDevId();
		}
		else if(msg.pSender == m_btnPoliceId){
			OnClickBtnPoliceId();
		}
		else if(msg.pSender == m_btnDir){
			OnClickBtnDir();
		}
		else if(msg.pSender == m_btnSync){
			OnClickBtnSync();
		}
	}
	else if( msg.sType == _T("Quit"))
	{
		PostQuitMessage(0);
		return;
	}
}


LRESULT  CDvrToolUI::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("dvrtool.xml"), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	this->SetIcon(IDI_WELLDVRTOOL);

	Init();
	return 0;
}

LRESULT  CDvrToolUI::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT  CDvrToolUI::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);

	bHandled = FALSE;
	return 0;
}

LRESULT  CDvrToolUI::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT  CDvrToolUI::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT  CDvrToolUI::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT  CDvrToolUI::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

	//判断标题区
	RECT rcCaption = m_pm.GetCaptionRect();
	if(pt.x > rcCaption.left && pt.x < rcCaption.right &&
		pt.y > rcCaption.top && pt.y < rcCaption.bottom)
	{
		return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT  CDvrToolUI::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT  CDvrToolUI::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	DuiLib::CRect rcWork = oMonitor.rcWork;
	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;

 	lpMMI->ptMaxPosition.x = rcWork.left;
 	lpMMI->ptMaxPosition.y = rcWork.top;
 	lpMMI->ptMaxSize.x = rcWork.right - rcWork.left;
 	lpMMI->ptMaxSize.y = rcWork.bottom - rcWork.top;
	lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
	
	bHandled = FALSE;
	return 0;
}

LRESULT  CDvrToolUI::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
	if( wParam == SC_CLOSE ) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	if( wParam == SC_MINIMIZE)
	{

	}
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	return lRes;
}

LRESULT  CDvrToolUI::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;

	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}


LRESULT CDvrToolUI::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	
	default:
		break;
	}

	return 0;
}


LRESULT CDvrToolUI::OnMyDeviceChange(WPARAM wParam, LPARAM lParam)
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
				AddUsbDevice(pDevInf->dbcc_name, lParam);

			}
			else if( wParam == DBT_DEVICEREMOVECOMPLETE ) // remove device
			{
				RemoveUsbDevice(pDevInf->dbcc_name);
				pHdr->dbch_devicetype == DBT_DEVTYP_VOLUME;
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

void CDvrToolUI::EnableUI(bool bEnable)
{
	DuiLib::CStdString strShow(_T("密码校验通过后可用"));
	strShow = bEnable ? _T("") : strShow;

	m_edtPwdNew->SetEnabled(bEnable);
	m_edtPwdNew->SetText(strShow);
	m_edtDevId->SetEnabled(bEnable);
	m_edtDevId->SetText(strShow);
	m_edtPoliceId->SetEnabled(bEnable);
	m_edtPoliceId->SetText(strShow);

	m_btnPwd->SetEnabled(bEnable);
	m_btnDevId->SetEnabled(bEnable);
	m_btnPoliceId->SetEnabled(bEnable);
	m_btnDir->SetEnabled(bEnable);
	m_btnSync->SetEnabled(bEnable);

	m_btnCheck->SetEnabled(!bEnable);
	m_edtPwd->SetEnabled(!bEnable);
}

void CDvrToolUI::OnClickBtnCheck()
{
	CStdString strPwd = m_edtPwd->GetText();
	if( strPwd.IsEmpty() )
	{
		EnableUI(false);
		m_lblMsg->SetText(_T("请输入密码！"));
		return;
	}

	//读取信息并显示
	if(m_pDvr == NULL)
	{
		m_pDvr = CDvrFactory::GetDvr();
		if(m_pDvr == NULL)
		{
			m_lblMsg->SetText(_T("没有检测到设备！"));
			return;
		}
	}

	CString strDevPwd;
	//修改密码
	if(! m_pDvr->GetPwd(strDevPwd))
	{
		m_lblMsg->SetText(_T("读取DVR密钥失败!"));
		return;
	}

	//密码校验
	bool bCheck = strDevPwd.Compare(strPwd) == 0;
	if(!bCheck)
	{
		m_lblMsg->SetText(_T("校验失败，请确认密码是否正确！"));
		return;
	}

	m_lblMsg->SetText(_T("密码校验通过！"));
	EnableUI(true);
	m_edtPwd->SetEnabled(false);
	m_btnCheck->SetEnabled(false);

	//读取ID
	CString strT;
	m_pDvr->GetIDEx(strT);
	m_edtDevId->SetText(strT.GetBuffer());
	m_pDvr->GetMachinID(strT);
	m_edtPoliceId->SetText(strT.GetBuffer());
}

void CDvrToolUI::OnClickBtnPwd()
{
	CStdString strPwd = m_edtPwdNew->GetText();
	if( strPwd.IsEmpty() )
	{
		m_lblMsg->SetText(_T("请输入新密码！"));
		return;
	}

	CStdString strPwdOld = m_edtPwd->GetText();
	if(strPwdOld == strPwd)
	{
		m_lblMsg->SetText(_T("新密码和原始密码一致，请确认！"));
		m_edtPwdNew->SetFocus();
		return;
	}

	if(m_pDvr)
	{
		if(m_pDvr->SetPwd(strPwd.GetData()))
		{
			m_lblMsg->SetText(_T("修改密码成功!"));
			EnableUI(false);
			m_edtPwd->SetText(_T(""));
			m_edtPwd->SetFocus();
		}
		else
		{
			m_lblMsg->SetText(_T("修改密码失败!"));
		}
	}
	else
		m_lblMsg->SetText(_T("没有设备！"));
}

void CDvrToolUI::OnClickBtnDevId()
{
	CStdString strId = m_edtDevId->GetText();
	if( strId.IsEmpty() )
	{
		m_lblMsg->SetText(_T("请输入新设备ID！"));
		return;
	}

	if(m_pDvr)
	{
		if(m_pDvr->SetIDEx(strId.GetData()))
		{
			m_lblMsg->SetText(_T("修改设备ID成功！"));
		}
		else
		{
			m_lblMsg->SetText(_T("修改设备ID失败！"));
		}
	}
	else
		m_lblMsg->SetText(_T("没有设备！"));
}

void CDvrToolUI::OnClickBtnPoliceId()
{
	CStdString strId = m_edtPoliceId->GetText();
	if( strId.IsEmpty() )
	{
		m_lblMsg->SetText(_T("请输入新警员ID！"));
		return;
	}
	if(m_pDvr)
	{
		if(m_pDvr->SetMachinID(strId.GetData()))
		{
			m_lblMsg->SetText(_T("修改警员ID成功！"));
		}
		else
		{
			m_lblMsg->SetText(_T("修改警员ID失败！"));
		}
	}
	else
		m_lblMsg->SetText(_T("没有设备！"));

}

void CDvrToolUI::OnClickBtnDir()
{
	//枚举
	if(m_pDvr == NULL)
	{
		m_lblMsg->SetText(_T("没有设备！"));
		return;
	}

	if(m_pDvr->SetMassEx())
	{
		m_lblMsg->SetText(_T("枚举设备成功！"));
	}
	else
	{
		m_lblMsg->SetText(_T("枚举设备失败！"));
	}
}

void CDvrToolUI::OnClickBtnSync()
{
	if(m_pDvr == NULL)
	{
		m_lblMsg->SetText(_T("没有设备！"));
		return;
	}

	//显示时间
	SYSTEMTIME   st;   
	::GetSystemTime(&st);

	CStdString str;
	str.Format(_T("同步时间成功：%d-%d-%d %02d:%02d:%02d"),st.wYear, st.wMonth,st.wDay,st.wHour+8 > 24 ? st.wHour - 16 : st.wHour + 8,st.wMinute,st.wSecond);
 
	if(m_pDvr->SetTimeEx())
 		m_lblMsg->SetText(str);
	else
	{
		m_lblMsg->SetText(_T("同步时间失败！"));
	}
}

// Copy from HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\DeviceClasses
static const GUID GUID_DEVINTERFACE_LIST[] = 
{
	// GUID_DEVINTERFACE_USB_DEVICE
	{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },

	//GUID_DEVINTERFACE_VOLUME
	{0x53f5630d, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b }},

	// GUID_DEVINTERFACE_DISK
	{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },

	// GUID_DEVINTERFACE_HID, 
	{ 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },

	// GUID_NDIS_LAN_CLASS
	{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }

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

void CDvrToolUI::RegisgerDvr()
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


//USB设备插入
void CDvrToolUI::AddUsbDevice( const CString& strName, LPARAM lparam)
{
	CString strVPID = GetVID_PIDString(strName, _T('#'));
	if( strVPID != CMD_VID_PID && strVPID != MASS_VID_PID)
	{
		//不是DVR设备则返回
		return;
	}

	if( strVPID == CMD_VID_PID )
	{
		m_lblMsg->SetText(_T("检测到DVR设备插入"));
		m_pDvr = CDvrFactory::GetDvr();
		if(m_pDvr == NULL)
		{
			m_lblMsg->SetText(_T("无法识别DVR设备，请重新插拔！"));
			return;
		}
		GetDiskName(lparam);
	}
	else if( strVPID == MASS_VID_PID )
	{
		Sleep(500);
		CString diskName = GetDiskName(lparam);
		m_lblMsg->SetText(_T("枚举成U盘成功！"));		
		if(!diskName.IsEmpty())
		{
			OpenDisk(diskName);
		}
	}
}

void CDvrToolUI::RemoveUsbDevice( const CString& strName )
{	
	CString strVPID = GetVID_PIDString(strName, _T('#'));
	if( strVPID != CMD_VID_PID && strVPID != MASS_VID_PID)
	{
		//不是DVR设备则返回
		return;
	}

	if(m_pDvr)
	{
		delete m_pDvr;
		m_pDvr = NULL;
	}

	if( strVPID == CMD_VID_PID )
	{	
		m_lblMsg->SetText(_T("检测到DVR设备拔掉"));
	}
	else if( strVPID == MASS_VID_PID )
	{
		m_lblMsg->SetText(_T("检测到存储设备拔掉"));
	}
	EnableUI(false);
}

//获取VID_PID
CString CDvrToolUI::GetVID_PIDString(const CString &str,  wchar_t  chSplit )
{
	int pos1 = str.Find(chSplit);//str.Find(_T('#'));
	CString s1 = str.Mid(pos1+1);
	int pos2 = s1.Find(chSplit); //s1.Find(_T('#'));
	CString s2 = s1.Left(pos2);
	s2.MakeUpper();
	return s2;
}

// 驱动器类型检查函数--判断是否是移动存储
BOOL CDvrToolUI::IsFlashMemory(char chDisk)
{
	CString strDisk(_T("Z:\\"));
	strDisk.SetAt(0, chDisk);

	UINT unType =  GetDriveType(strDisk);

	if (DRIVE_REMOVABLE == unType)
	{
		return 1;  // 是移动存储
	}  
	else
	{
		return 0;  // 不是移动存储
	}
}

//获取新插入盘的盘符
CString CDvrToolUI::GetDiskName(LPARAM lParam)
{
	TCHAR buf[100]; 
	//"C:\<NULL>D:\<NULL>E:\<NULL><NULL>" 
	DWORD len = GetLogicalDriveStrings(sizeof(buf)/sizeof(TCHAR),buf); 

	static vector<TCHAR> vecOldDisk;
	vector<TCHAR> vecDisk;

	TCHAR* s=buf;
	for ( ; *s; s += _tcslen(s)+1 ) 
	{ 
		LPCTSTR sDrivePath = s; //单个盘符 
		if(IsFlashMemory(sDrivePath[0]))
		{
			vecDisk.push_back(sDrivePath[0]);
		}
	} 

	int i = vecOldDisk.size();
	int j = vecDisk.size();
	if(i == j)
		return _T("");

	char Disk;
	if(j > i)
	{
		while (--j >= 0 && --i >=0)
		{
			if(vecDisk[j] != vecOldDisk[i])
			{
				Disk = vecDisk[j];
				break;
			}
		}
	}
	else
	{
		Disk = 'C';
	}

	vecOldDisk.swap(vecDisk);
	CString strDisk;
	strDisk.Format(_T("%C:\\"), Disk);
	return strDisk;
}

bool CDvrToolUI::OpenDisk(const CString& diskName)
{
	//TCHAR szCmd[MAX_PATH] = _T("\"C:\\Windows\\Explorer.exe\" \"C:\\Windows\"");
	CString szCmd(_T("\"C:\\Windows\\Explorer.exe\" "));
	szCmd += _T("\"")+ diskName +_T("\"");
	STARTUPINFO si = {sizeof(si)};
	PROCESS_INFORMATION pi = {0};

	if (CreateProcess(NULL, szCmd.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		//MessageBox(NULL, _T("打开成功"), NULL, MB_OK);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	return true;
}