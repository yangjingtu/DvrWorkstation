#pragma once
#include "ControlEx.h"

class CKeyFrameWnd: public CWindowWnd, public INotifyUI, public IMessageFilterUI
{
public:
	CKeyFrameWnd(const CDuiString& strCheck);
	~CKeyFrameWnd(void);

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

	bool IsOk() { return m_bOk; }
private:
	void InputNumber(const CDuiString& strNumber);
	void InputBack();
	void InputOk();

private:
	bool m_bOk;
	CDuiString m_strCheck;

public:
	CPaintManagerUI m_pm;
	
	CButtonUI* m_btnClose;

	CLabelUI* m_lblMsg;
	CEditUI* m_edtPwd;
	
	CButtonUI* m_btn1;
	CButtonUI* m_btn2;
	CButtonUI* m_btn3;
	CButtonUI* m_btn4;
	CButtonUI* m_btn5;
	CButtonUI* m_btn6;
	CButtonUI* m_btn7;
	CButtonUI* m_btn8;
	CButtonUI* m_btn9;
	CButtonUI* m_btn0;
	CButtonUI* m_btnBack;
	CButtonUI* m_btnOk;

};

