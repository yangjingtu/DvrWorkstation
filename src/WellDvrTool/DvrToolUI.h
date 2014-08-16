#pragma once
#include "stdafx.h"

using namespace DuiLib;

class CDevBase;

class CDvrToolUI :
	public CWindowWnd, public INotifyUI
{
public:
	CDvrToolUI(void);
	~CDvrToolUI(void);

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

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnMyDeviceChange(WPARAM wParam, LPARAM lParam);

protected:
	void EnableUI(bool bEnable);

	void OnClickBtnCheck();
	void OnClickBtnPwd();
	void OnClickBtnDevId();
	void OnClickBtnPoliceId();
	void OnClickBtnDir();
	void OnClickBtnSync();

	void RegisgerDvr();
	CString GetVID_PIDString(const CString &str,  wchar_t  chSplit );
	void AddUsbDevice( const CString& strName, LPARAM lParam);
	void RemoveUsbDevice( const CString& strName );

	CString GetDiskName(LPARAM lParam);
	bool OpenDisk(const CString& diskName);
private:
	CDevBase* m_pDvr;

private:
	CPaintManagerUI m_pm;

	CButtonUI* m_btnClose;
	CButtonUI* m_btnCheck;
	CButtonUI* m_btnPwd;
	CButtonUI* m_btnDevId;
	CButtonUI* m_btnPoliceId;
	CButtonUI* m_btnDir;
	CButtonUI* m_btnSync;

	CEditUI* m_edtPwd;
	CEditUI* m_edtPwdNew;
	CEditUI* m_edtDevId;
	CEditUI* m_edtPoliceId;

	CLabelUI* m_lblMsg;
};

