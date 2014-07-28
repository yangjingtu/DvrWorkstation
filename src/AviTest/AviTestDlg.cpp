
// AviTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AviTest.h"
#include "AviTestDlg.h"
#include "afxdialogex.h"
#include "AviHelper.h"

#pragma comment(lib, "WellCommon.lib")

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


// CAviTestDlg 对话框




CAviTestDlg::CAviTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAviTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAviTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtAviFile);
	DDX_Control(pDX, IDC_EDIT2, m_edtBmpDir);
}

BEGIN_MESSAGE_MAP(CAviTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAviTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAviTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CAviTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CAviTestDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CAviTestDlg 消息处理程序

BOOL CAviTestDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAviTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAviTestDlg::OnPaint()
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
HCURSOR CAviTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//选择Avi文件
void CAviTestDlg::OnBnClickedButton1()
{
	TCHAR szFilters[]= _T("AVI Files (*.avi)|*.avi|All Files (*.*)|*.*||");
	CFileDialog fileDlg(TRUE, _T("avi"), _T("*.avi"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	if(fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();
		m_edtAviFile.SetWindowText(pathName);
	}
}

//bmp目录
void CAviTestDlg::OnBnClickedButton2()
{
	// 获取特定文件夹的LPITEMIDLIST，可以将之理解为HANDLE
	// 所谓的特定文件夹,你可以用CSIDL_XXX来检索之。
	LPITEMIDLIST rootLoation;
	SHGetSpecialFolderLocation( NULL, CSIDL_DESKTOP, &rootLoation );
	if ( rootLoation == NULL ) {
		// unkown error
		return;
	}

	// 配置对话框
	BROWSEINFO bi;
	ZeroMemory( &bi, sizeof( bi ) );
	bi.pidlRoot = rootLoation;			// 文件夹对话框之根目录，不指定的话则为我的电脑
	bi.lpszTitle = _T( "BMP存储目录" ); // 可以不指定
	// bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS;

	// 打开对话框, 有点像DoModal
	LPITEMIDLIST targetLocation = SHBrowseForFolder( &bi );
	if ( targetLocation != NULL ) {
		TCHAR targetPath[ MAX_PATH ];
		SHGetPathFromIDList( targetLocation, targetPath );
		// MessageBox( targetPath );
		m_edtBmpDir.SetWindowText(targetPath);
	}

}


//读取
void CAviTestDlg::OnBnClickedButton4()
{

}

//转换
void CAviTestDlg::OnBnClickedButton3()
{
	CString aviFile;
	m_edtAviFile.GetWindowText(aviFile);
	CString bmpDir;
	m_edtBmpDir.GetWindowText(bmpDir);

	CAviHelper::AVItoBmp(aviFile, bmpDir);
}