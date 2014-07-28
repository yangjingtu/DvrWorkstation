
// DvrToolDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

class CDevBase;

enum EM_DVR_TYPE{
	DVR_WELL = 0,
	DVR_A4,
	DVR_X6,
	DVR_D6
};


// CDvrToolDlg 对话框
class CDvrToolDlg : public CDialogEx
{
// 构造
public:
	CDvrToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DVRTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CDevBase* m_pDvr;

	//获取DVR设备对象--根据类型
	CDevBase* GetDevObj();

	int m_nType;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_edtId;
	CEdit m_edtPID;
	CEdit m_edtUnit;
	CEdit m_edtTime;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	CButton m_btnTypeWell;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnClose();
};
