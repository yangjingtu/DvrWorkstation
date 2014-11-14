
// GetRegisterCodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GetRegisterCode.h"
#include "GetRegisterCodeDlg.h"
#include "afxdialogex.h"

#include "../Register/chmzc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGetRegisterCodeDlg 对话框




CGetRegisterCodeDlg::CGetRegisterCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetRegisterCodeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_IsLong = true;
}

void CGetRegisterCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtMC);
	DDX_Control(pDX, IDC_EDIT2, m_edtRC);
	DDX_Control(pDX, IDC_CHK_LONG, m_chkLong);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dtEnd);
}

BEGIN_MESSAGE_MAP(CGetRegisterCodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGetRegisterCodeDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CGetRegisterCodeDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_CHK_LONG, &CGetRegisterCodeDlg::OnBnClickedChkLong)
END_MESSAGE_MAP()


// CGetRegisterCodeDlg 消息处理程序

BOOL CGetRegisterCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_dtStart.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	m_dtEnd.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));
	CTime tm = CTime::GetCurrentTime() - CTimeSpan(1, 0, 0, 0);
	m_dtStart.SetTime(&tm);

	CTime tmE = CTime::GetCurrentTime() + CTimeSpan(31, 0, 0, 0);
	m_dtEnd.SetTime(&tmE);

	m_dtStart.EnableWindow(FALSE);
	m_dtEnd.EnableWindow(FALSE);


	m_chkLong.SetCheck(1);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGetRegisterCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGetRegisterCodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGetRegisterCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGetRegisterCodeDlg::OnBnClickedOk()
{
	CString strMC;
	m_edtMC.GetWindowText(strMC);
	if(strMC.IsEmpty())
	{
		MessageBox(_T("机器码不能为空"));
		return;
	}

	if(!m_IsLong)
	{
		CTime tmS;
		CTime tmE; 
		CTimeSpan tmOffset;
		DWORD dwResult = m_dtStart.GetTime(tmS);
		dwResult = m_dtEnd.GetTime(tmE);
		if(dwResult == GDT_VALID)
		{
			tmOffset = tmE - tmS;
		}
		if(tmOffset.GetDays() < 1)
		{
			MessageBox(_T("有效期不合法，请检查！"));
			return;
		}
 		CString strDV;
		strDV.Format(_T("@%s-%s"), tmS.Format(_T("%Y%m%d")), tmE.Format(_T("%Y%m%d")));
 		strMC += strDV;
	}

	//string mc = ws2s(strMC.GetBuffer(0));
	//string rc = GetRegisterCode(mc);
	//string rc = GetRegisterCode(mc);
	char mc[1024] = {0};
	int len = _ws2s((wchar_t*)strMC.GetBuffer(0), mc);
	char rc[1024] = {0};
	len = _GetRegisterCode(mc, rc);

	CString strRc;
	strRc.Format(_T("%s"), s2ws(rc).c_str());

	m_edtRC.SetWindowText(strRc);
}


void CGetRegisterCodeDlg::OnEnChangeEdit1()
{
	CString strMC;
	m_edtMC.GetWindowText(strMC);
	static int len = 0;
	if(strMC.GetLength() != len)
	{
		len = strMC.GetLength();
		strMC = strMC.MakeUpper();
		m_edtMC.SetWindowText(strMC);
		m_edtMC.SetSel(-1);
	}
}

void CGetRegisterCodeDlg::OnBnClickedChkLong()
{
	m_IsLong = m_chkLong.GetCheck();
 	m_dtStart.EnableWindow(!m_IsLong);
 	m_dtEnd.EnableWindow(!m_IsLong);

}
