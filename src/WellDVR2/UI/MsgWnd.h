#pragma once
using namespace DuiLib;

class CMsgWnd : public CWindowWnd, public INotifyUI, public IMessageFilterUI
{
public:
	CMsgWnd();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/); 
	void Init();

	void Notify(TNotifyUI& msg);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	void SetMsg(const CString& msg, const CString& title = _T(""), const CString& img = _T(""));

	bool IsPressOk() const { return m_bOk; }

private:
	CPaintManagerUI m_pm;
	CLabelUI* m_plblTitle;
	CButtonUI* m_pImg;
	CTextUI* m_pTxtMsg;
	
	bool m_bOk;

};