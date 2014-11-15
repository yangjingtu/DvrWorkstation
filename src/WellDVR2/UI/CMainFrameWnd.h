#pragma once

#include "../DataDef.h"
using namespace DuiLib;

class CNetClient;
class DvrListUI;

class CMainFrameWnd : public CWindowWnd, public INotifyUI
{
public:
	enum { 
		SHOWTIME_TIMERID = 10,					//显示状态栏时间
		CHECKDEV_STATUS_TIMERID,				//检查设备状态
		CHECKDEV_DATA_TIMERID,					//检查设备数据
		CHECKFTP_TIMERID,							//检查FTP
		CHECKUSB_TIMERID							//检查USB状态
	};

	CMainFrameWnd();
	~CMainFrameWnd();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/);

	void Init();

	void OnPrepare();

	void Notify(TNotifyUI& msg);  

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void SetInstance(HINSTANCE hInstance);

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnMyDeviceChange(WPARAM wParam, LPARAM lParam);

	LRESULT OnNotifyData(WPARAM wParam, LPARAM lParam);

	LRESULT OnSysKeyHandle(WPARAM wParam, LPARAM lParam);

	void ShowMsgInfo(const CDuiString& msg);

	//获取选择的位置（行列）
	void GetSelectPos(int& row, int& col);

	bool Alert(const CString& strMsg, const CString& title = _T(""), const CString& img = _T(""));

	wstring GetIpAddr();
private:
	BOOL InitSystem();

	void RegisgerDvr();

	void ShowDateTime();
	void ShowIPAddr();

	void ShowCompanyAndVersion();
	void ShowFreeSpace();

	//画空间使用率饼图
	void DrawSpacePie(float nUsed);

	//void ShowFtpInfo();

	void CreateNotifyIcon();
	void DeleteNotifyIcon();

	void CheckDeviceDataTimer();
	void CheckDeviceStatusTimer();

	void CheckUsbHub();

	//设置顶层窗口
	void SetTopWnd();

	static void ShowFtpInfo(const wstring& file, const wstring& info, int nPrecent);

	void RemoveUsbDevice(const CString& strName);
	void AddUsbDevice( const CString& strName);
	CString GetVID_PIDString(const CString &strName, wchar_t chSplit);

	bool CloseWnd();
	bool KeyFrameCheck();

private:
	HINSTANCE m_hInstance;

	NOTIFYICONDATA m_NotifyData;

	BOOL m_bMass;
	int m_cntMass;

	//是否为最上层窗口
	BOOL m_bTopWnd;

	CNetClient* m_pHttpClient;

public:
	CPaintManagerUI m_pm;

private:
	CButtonUI* m_pLogoBtn;
	CTextUI* m_pCaptionTxt;
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;
	
	CLabelUI* m_pMsgLbl;
	CProgressUI* m_pFtpPro;
	CLabelUI* m_pIpLbl;
	CLabelUI* m_pCompanyLbl;
	CLabelUI* m_pVersionLbl;
	CLabelUI* m_pDateTimeLbl;
	
	CLabelUI* m_pFreeSpace;
	CLabelUI* m_pUsedSpace;
	CLabelUI* m_pTotalSpace;
	CLabelUI* m_pUsedPecent;
	CLabelUI* m_pDrawLbl;

	CLabelUI* m_pPhoneLbl;

	DvrListUI* m_pDvrListUI;
};