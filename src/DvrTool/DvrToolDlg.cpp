
// DvrToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DvrTool.h"
#include "DvrToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "../../lib/Dvr.lib")

#include "../Dvr/WellDvr34.h"
#include "../Dvr/HADvr.h"


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


// CDvrToolDlg 对话框




CDvrToolDlg::CDvrToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDvrToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nType = DVR_WELL;
	m_pDvr = NULL;
}

void CDvrToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtId);
	DDX_Control(pDX, IDC_EDIT2, m_edtPID);
	DDX_Control(pDX, IDC_EDIT3, m_edtUnit);
	DDX_Control(pDX, IDC_EDIT4, m_edtTime);
	DDX_Control(pDX, IDC_BUTTON1, m_btnTypeWell);
}

BEGIN_MESSAGE_MAP(CDvrToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDvrToolDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDvrToolDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDvrToolDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDvrToolDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDvrToolDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDvrToolDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDvrToolDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CDvrToolDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CDvrToolDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_RADIO1, &CDvrToolDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDvrToolDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDvrToolDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CDvrToolDlg::OnBnClickedRadio4)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDvrToolDlg 消息处理程序

BOOL CDvrToolDlg::OnInitDialog()
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
	m_btnTypeWell.SetCheck(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDvrToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDvrToolDlg::OnPaint()
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
HCURSOR CDvrToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//获取设备iD
void CDvrToolDlg::OnBnClickedButton1()
{
	CDevBase* pDvr = GetDevObj();
	if(pDvr == NULL)
		return;
	CString strId;
	if( pDvr->GetIDEx(strId) )
	{
		m_edtId.SetWindowText(strId);
	}
}

//设ID
void CDvrToolDlg::OnBnClickedButton2()
{
	CString strId;
	m_edtId.GetWindowText(strId);
	if(strId.IsEmpty())
	{
		m_edtId.SetFocus();
		return;
	}

	CDevBase* pDvr = GetDevObj();
	if(pDvr == NULL)
		return;
	pDvr->SetIDEx(strId);
}

//获取警员ID
void CDvrToolDlg::OnBnClickedButton3()
{
	CDevBase* pDvr = GetDevObj();
	if(pDvr == NULL)
		return;

	CString strT;
	pDvr->GetMachinID(strT);
	m_edtPID.SetWindowText(strT);
}


void CDvrToolDlg::OnBnClickedButton4()
{
	CDevBase* pDvr = GetDevObj();
	if(pDvr == NULL)
		return;
	CString strT;
	m_edtPID.GetWindowText(strT);
	pDvr->SetMachinID(strT);
}

//获取单位
void CDvrToolDlg::OnBnClickedButton5()
{
	
}


void CDvrToolDlg::OnBnClickedButton6()
{
	
}

//获取时间
void CDvrToolDlg::OnBnClickedButton7()
{
	CDevBase* pDvr = GetDevObj();
	if(pDvr == NULL)
		return;
	SYSTEMTIME t;
	pDvr->GetTimeEx(&t);
	CString strT;
	strT.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);

	m_edtTime.SetWindowText(strT);
}


void CDvrToolDlg::OnBnClickedButton8()
{
	
}
#include "../WellCommon/XmlHelper.h"
#pragma comment(lib, "WellCommon.lib")

void TestXml()
{
	CXmlHelper xml;
	xml.Load("D:\\test.xml", true);

	xml.SetNodeValue("root\\ftp\\serv", "192.168.1.1.");
	xml.SetNodeAttr("root\\ftp\\serv", "port", "21");

	string str = xml.GetNodeValue("root\\ftp\\serv");
	str = xml.GetNodeAttr("root\\ftp\\serv", "port");

	xml.Save("D:\\test.xml");
}

//U盘
void CDvrToolDlg::OnBnClickedButton9()
{
	CDevBase* pDvr = GetDevObj();
	if(pDvr == NULL)
		return;

	pDvr->SetMassEx();
	//TestXml();
}


void CDvrToolDlg::OnBnClickedRadio1()
{
	m_nType = DVR_WELL;
}


void CDvrToolDlg::OnBnClickedRadio2()
{
	m_nType = DVR_A4;
}


void CDvrToolDlg::OnBnClickedRadio3()
{
	m_nType = DVR_X6;
}


void CDvrToolDlg::OnBnClickedRadio4()
{
	m_nType = DVR_D6;
}


CDevBase* CDvrToolDlg::GetDevObj()
{
	if(m_pDvr)
	{
		delete m_pDvr;
		m_pDvr == NULL;
	}

	if(m_nType == DVR_WELL)
	{
		m_pDvr = new CWellDvr34;
	}
	else if(m_nType == DVR_A4)
	{
		m_pDvr = new CA4Dvr;
	}
	else if(m_nType == DVR_X6)
	{
		m_pDvr = new CHADvr;
	}
	else if(m_nType == DVR_D6)
	{
		m_pDvr = new CHADvr;
	}
	return m_pDvr;
}

void CDvrToolDlg::OnClose()
{
	
	if(m_pDvr)
	{
		delete m_pDvr;
		m_pDvr = NULL;
	}

	CDialogEx::OnClose();
}
