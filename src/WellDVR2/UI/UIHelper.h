//////////////////////////////////////////////////////////////////////////
//������
//		����UI����Ĵ�����
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "ControlEx.h"

#define WELLUI CUIHelper::Instance()

class CUIHelper
{
private:
	CUIHelper(void);
	~CUIHelper(void);

public:
	static CUIHelper& Instance();

	//////////////////////////////////////////////////////////////////////////
	//���̶Ի���--У��
	bool Check(const CStdString& strCheck, HWND hPWnd = NULL);

	//////////////////////////////////////////////////////////////////////////
	//ע��Ի���
	bool Register(HWND hPWnd = NULL);

	//////////////////////////////////////////////////////////////////////////
	//��ʾ��
	bool Alert(const CString& strMsg, const CString& title, const CString& img, HWND hPWnd = NULL);

	//////////////////////////////////////////////////////////////////////////
	//��¼�Ի���
	bool Login(HWND hPWnd = NULL);

	//////////////////////////////////////////////////////////////////////////
	//���ڶԻ���
	void AboutWnd(HWND hPWnd = NULL);

	//////////////////////////////////////////////////////////////////////////
	//�����˵�
	void MenuWnd(CControlUI* pOwner, POINT pt);
};
