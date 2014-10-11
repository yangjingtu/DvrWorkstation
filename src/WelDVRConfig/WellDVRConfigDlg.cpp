
// WelDVRConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WellDVRConfig.h"
#include "WellDVRConfigDlg.h"
#include "afxdialogex.h"
#include "FileBackUp.h"

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


// CWelDVRConfigDlg 对话框




CWelDVRConfigDlg::CWelDVRConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWelDVRConfigDlg::IDD, pParent)
{
	m_bOne = false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWelDVRConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edtPath);
	DDX_Control(pDX, IDC_EDIT2, m_edtDBIp);
	DDX_Control(pDX, IDC_EDIT3, m_edtDBPort);
	DDX_Control(pDX, IDC_EDIT4, m_edtDBName);
	DDX_Control(pDX, IDC_EDIT5, m_edtDBUser);
	DDX_Control(pDX, IDC_EDIT6, m_edtDBPwd);
	DDX_Control(pDX, IDC_EDIT7, m_edtDBTime);
	DDX_Control(pDX, IDC_EDIT8, m_edtFTPIp);
	DDX_Control(pDX, IDC_EDIT9, m_edtFTPPort);
	DDX_Control(pDX, IDC_EDIT10, m_edtFTPUser);
	DDX_Control(pDX, IDC_EDIT11, m_edtFTPPwd);
	DDX_Control(pDX, IDC_EDIT13, m_edtFtpIp1);
	DDX_Control(pDX, IDC_EDIT14, m_edtFtpPort1);
	DDX_Control(pDX, IDC_EDIT15, m_edtFtpUser1);
	DDX_Control(pDX, IDC_EDIT16, m_edtFtpPwd1);
	DDX_Control(pDX, IDC_EDIT17, m_edtFtpIp2);
	DDX_Control(pDX, IDC_EDIT18, m_edtFtpPort2);
	DDX_Control(pDX, IDC_EDIT19, m_edtFtpUser2);
	DDX_Control(pDX, IDC_EDIT20, m_edtFtpPwd2);
	DDX_Control(pDX, IDC_COMBO1, m_cbxHDDef);
	DDX_Control(pDX, IDC_EDIT12, m_edtVideoIMP);
	DDX_Control(pDX, IDC_CHECK5, m_ckTransIMP1);
	DDX_Control(pDX, IDC_CHECK6, m_ckTransHD1);
	DDX_Control(pDX, IDC_CHECK7, m_ckTransSD1);
	DDX_Control(pDX, IDC_CHECK8, m_ckTransIMP2);
	DDX_Control(pDX, IDC_CHECK9, m_ckTransHD2);
	DDX_Control(pDX, IDC_CHECK10, m_ckTransSD2);
	DDX_Control(pDX, IDC_CHECK1, m_ckEnableFtp1);
	DDX_Control(pDX, IDC_CHECK2, m_ckEnableFtp2);
	DDX_Control(pDX, IDC_CHECK3, m_ckEnableFtp);
	DDX_Control(pDX, IDC_CHECK11, m_ckTransIMP);
	DDX_Control(pDX, IDC_CHECK12, m_ckTransHD);
	DDX_Control(pDX, IDC_CHECK13, m_ckTransSD);
	DDX_Control(pDX, IDC_CHECK14, m_ckDB);
	DDX_Control(pDX, IDC_LIST1, m_listTransLevel);
	DDX_Control(pDX, IDC_BUTTON2, m_btnUp);
	DDX_Control(pDX, IDC_BUTTON3, m_btnDown);
	DDX_Control(pDX, IDC_EDIT21, m_edtDeviceId);
	DDX_Control(pDX, IDC_EDIT22, m_edtWebIp);
	DDX_Control(pDX, IDC_EDIT23, m_edtWebPort);
	DDX_Control(pDX, IDC_CBX_DVR_TYPE, m_cbxDvrType);
}

BEGIN_MESSAGE_MAP(CWelDVRConfigDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWelDVRConfigDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CWelDVRConfigDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CWelDVRConfigDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CWelDVRConfigDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CWelDVRConfigDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK14, &CWelDVRConfigDlg::OnBnClickedCheck14)
	ON_BN_CLICKED(IDC_BUTTON2, &CWelDVRConfigDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CWelDVRConfigDlg::OnBnClickedButton3)
	ON_LBN_SELCHANGE(IDC_LIST1, &CWelDVRConfigDlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CWelDVRConfigDlg::OnBnClickedButton4)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CWelDVRConfigDlg 消息处理程序

BOOL CWelDVRConfigDlg::OnInitDialog()
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
	ConfigBackUp::Restore();


	m_IniFile.SetIniPathName(GetAppPath() + gc_Config);
	m_mapLevel[1] = _T("FTP");
	m_mapLevel[2] = _T("FTP1");
	m_mapLevel[3] = _T("FTP2");
	m_btnUp.EnableWindow(FALSE);
	m_btnDown.EnableWindow(FALSE);

	m_cbxDvrType.InsertString(0, _T("威尔电器3/4代DVR"));
	m_cbxDvrType.InsertString(1, _T("华安DVR"));
	m_cbxDvrType.InsertString(2, _T("上海凌锐A3/A4"));
	m_cbxDvrType.InsertString(3, _T("上海凌锐D6"));
	m_cbxDvrType.InsertString(4, _T("上海凌锐X6"));

	m_cbxDvrType.SetCurSel(0);

	Init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWelDVRConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWelDVRConfigDlg::OnPaint()
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
HCURSOR CWelDVRConfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWelDVRConfigDlg::Init()
{
	CString strSec, strKey, strDst, strDef;
	int nDef = 0;
	long lConnectTime = 0;
	int num = 0;

	//////////////////////////////////////////////////////////////////////////
	strSec = _T("FILE");
	strKey = _T("Target");
	strKey = _T("Path");
	CString strPath = m_IniFile.ReadString(strSec, strKey, strDef);
	m_edtPath.SetWindowText(strPath);

	//////////////////////////////////////////////////////////////////////////
	strSec = _T("DeviceInfo");
	strKey = _T("DeviceId");
	CString strId = m_IniFile.ReadString(strSec, strKey, strDef);
	m_edtDeviceId.SetWindowText(strId);

	//////////////////////////////////////////////////////////////////////////
	//Web服务器的配置
	strSec = _T("WEB");
	strKey = _T("ip");
	strDst = m_IniFile.ReadString(strSec, strKey, _T("127.0.0.1"));
	m_edtWebIp.SetWindowText(strDst);

	strKey = _T("port");
	strDst = m_IniFile.ReadString(strSec, strKey, _T("8080"));
	m_edtWebPort.SetWindowText(strDst);

	//////////////////////////////////////////////////////////////////////////
	strSec = _T("DB");
	strKey = _T("host");
	CString str = m_IniFile.ReadString(strSec, strKey, strDef);
	m_edtDBIp.SetWindowText(str);

	strKey = _T("port");
	str = m_IniFile.ReadString(strSec, strKey, strDef);
	m_edtDBPort.SetWindowText(str);

	strKey = _T("sid");
	str = m_IniFile.ReadString(strSec, strKey, strDef);
	m_edtDBName.SetWindowText(str);

	strKey = _T("uid");
	str = m_IniFile.ReadString(strSec, strKey, strDef);
	m_edtDBUser.SetWindowText(str);

	strKey = _T("pwd");
	str = m_IniFile.ReadString(strSec, strKey, strDef);
	m_edtDBPwd.SetWindowText(str);

	strKey = _T("ConnectTime");
	str = m_IniFile.ReadString(strSec, strKey, strDef);
	m_edtDBTime.SetWindowText(str);

	strKey = _T("enable");
	int nEnable = m_IniFile.ReadInt(strSec, strKey, 0);
	m_ckDB.SetCheck(nEnable);
	EnableDB(nEnable);

	//////////////////////////////////////////////////////////////////////////
	//上传设置
	strSec = _T("TransSetting");
	strKey = _T("resolution");
	int index = m_IniFile.ReadInt(strSec, strKey, 3);
	m_cbxHDDef.SetCurSel(index);

	strKey = _T("flag");
	str = m_IniFile.ReadString(strSec, strKey, _T("IMP"));
	m_edtVideoIMP.SetWindowText(str);

	//加载级别
	strKey = _T("level1");
	str = m_IniFile.ReadString(strSec, strKey, _T("FTP"));
	m_mapLevel[1] = str;
	strKey = _T("level2");
	str = m_IniFile.ReadString(strSec, strKey, _T("FTP1"));
	m_mapLevel[2] = str;
	strKey = _T("level3");
	str = m_IniFile.ReadString(strSec, strKey, _T("FTP2"));
	m_mapLevel[3] = str;RefreshList();


	//////////////////////////////////////////////////////////////////////////
	//单机版的FTP
	m_ftpOneDvr = LoadFtpObj(_T("FTP"));
	m_edtFTPIp.SetWindowText(m_ftpOneDvr.m_strIp);
	m_edtFTPPort.SetWindowText(m_ftpOneDvr.m_strPort);
	m_edtFTPUser.SetWindowText(m_ftpOneDvr.m_strUser);
	m_edtFTPPwd.SetWindowText(m_ftpOneDvr.m_strPwd);
	m_ckTransIMP.SetCheck(m_ftpOneDvr.m_bTransImp);
	m_ckTransHD.SetCheck(m_ftpOneDvr.m_bTransHd);
	m_ckTransSD.SetCheck(m_ftpOneDvr.m_bTransSd);
	m_ckEnableFtp.SetCheck(m_ftpOneDvr.m_bEnable);
	EnableFtp(m_ftpOneDvr.m_bEnable);
	
	m_ftpFirst = LoadFtpObj(_T("FTP1"));
	m_edtFtpIp1.SetWindowText(m_ftpFirst.m_strIp);
	m_edtFtpPort1.SetWindowText(m_ftpFirst.m_strPort);
	m_edtFtpUser1.SetWindowText(m_ftpFirst.m_strUser);
	m_edtFtpPwd1.SetWindowText(m_ftpFirst.m_strPwd);
	m_ckTransIMP1.SetCheck(m_ftpFirst.m_bTransImp);
	m_ckTransHD1.SetCheck(m_ftpFirst.m_bTransHd);
	m_ckTransSD1.SetCheck(m_ftpFirst.m_bTransSd);
	m_ckEnableFtp1.SetCheck(m_ftpFirst.m_bEnable);
	EnableFtp1(m_ftpFirst.m_bEnable);


	m_ftpSecond = LoadFtpObj(_T("FTP2"));
	//二级FTP
	m_edtFtpIp2.SetWindowText(m_ftpSecond.m_strIp);
	m_edtFtpPort2.SetWindowText(m_ftpSecond.m_strPort);
	m_edtFtpUser2.SetWindowText(m_ftpSecond.m_strUser);
	m_edtFtpPwd2.SetWindowText(m_ftpSecond.m_strPwd);	
	m_ckTransIMP2.SetCheck(m_ftpSecond.m_bTransImp);
	m_ckTransHD2.SetCheck(m_ftpSecond.m_bTransHd);
	m_ckTransSD2.SetCheck(m_ftpSecond.m_bTransSd);
	m_ckEnableFtp2.SetCheck(m_ftpSecond.m_bEnable);
	EnableFtp2(m_ftpSecond.m_bEnable);

	if(m_bOne)
	{
		//单机版
		m_ckEnableFtp1.EnableWindow(FALSE);
		EnableFtp1(FALSE);
		m_ckEnableFtp2.EnableWindow(FALSE);
		EnableFtp2(FALSE);

		m_edtVideoIMP.EnableWindow(FALSE);
		m_listTransLevel.EnableWindow(FALSE);
	}
	else
	{
		//多机版
		m_ckEnableFtp.EnableWindow(FALSE);
		EnableFtp(FALSE);
	}

	//DVR	类型
	strSec = _T("DVR");
	strKey = _T("type");
	int nType = m_IniFile.ReadInt(strSec, strKey, 0);
	m_cbxDvrType.SetCurSel(nType);

}

void CWelDVRConfigDlg::OnBnClickedButton1()
{
	// 打开文件夹
	WCHAR szDir[MAX_PATH]; 
	BROWSEINFO bi; 
	ITEMIDLIST *pidl; 

	bi.hwndOwner = this->m_hWnd; 
	bi.pidlRoot = NULL; 
	bi.pszDisplayName = szDir; 
	bi.lpszTitle = L"请选择目录"; 
	bi.ulFlags = BIF_RETURNONLYFSDIRS; 
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	pidl = SHBrowseForFolder(&bi); 
	if(pidl == NULL) 
		return; 

	if(SHGetPathFromIDList(pidl, szDir))
	{
		CString strPath;
		strPath.Format(L"%s", szDir);
		m_edtPath.SetWindowText(strPath);
	}
}

//确定
void CWelDVRConfigDlg::OnBnClickedOk()
{
	CString strSec, strKey, strDst, strDef;
	int nDef = 0;
	long lConnectTime = 0;
	int num = 0;
	//////////////////////////////////////////////////////////////////////////
	strSec = _T("FILE");
	strKey = _T("Target");
	strKey = _T("Path");
	m_edtPath.GetWindowText(strDst);
	if(strDst.IsEmpty())
	{
		MessageBox(_T("保存路径不能为空，请设置！"), _T("消息提示"));
		m_edtPath.SetFocus();
		return;
	}
	m_IniFile.WriteString(strSec, strKey, strDst);

	m_edtDeviceId.GetWindowText(strDst);
	if(strDst.IsEmpty())
	{
		MessageBox(_T("设备编号不能为空！"), _T("消息提示"));
		m_edtDeviceId.SetFocus();
		return;
	}
	strSec = _T("DeviceInfo");
	strKey = _T("DeviceId");
	m_IniFile.WriteString(strSec, strKey, strDst);

	//DVR	类型
	strSec = _T("DVR");
	strKey = _T("type");
	int nType = m_cbxDvrType.GetCurSel();
	if(nType < 0 && nType > m_cbxDvrType.GetCount())
		nType = 0;
	strDst.Format(_T("%d"), nType);
	m_IniFile.WriteString(strSec, strKey, strDst);


	m_edtWebIp.GetWindowText(strDst);
	strSec = _T("WEB");
	strKey = _T("ip");
	m_IniFile.WriteString(strSec, strKey, strDst);
	
	strKey = _T("port");
	m_edtWebPort.GetWindowText(strDst);
	m_IniFile.WriteString(strSec, strKey, strDst);

	//////////////////////////////////////////////////////////////////////////
	strSec = _T("DB");
	strKey = _T("host");
	m_edtDBIp.GetWindowText(strDst);
	m_IniFile.WriteString(strSec, strKey, strDst);

	strKey = _T("port");
	m_edtDBPort.GetWindowText(strDst);
	m_IniFile.WriteString(strSec, strKey, strDst);

	strKey = _T("sid");
	m_edtDBName.GetWindowText(strDst);
	m_IniFile.WriteString(strSec, strKey, strDst);

	strKey = _T("uid");
	m_edtDBUser.GetWindowText(strDst);
	m_IniFile.WriteString(strSec, strKey, strDst);

	strKey = _T("pwd");
	m_edtDBPwd.GetWindowText(strDst);
	m_IniFile.WriteString(strSec, strKey, strDst);

	strKey = _T("ConnectTime");
	m_edtDBTime.GetWindowText(strDst);
	m_IniFile.WriteString(strSec, strKey, strDst);

	strKey = _T("enable");
	strDst.Format(_T("%s"), m_ckDB.GetCheck() ? _T("1") : _T("0"));
	m_IniFile.WriteString(strSec, strKey, strDst);

	//////////////////////////////////////////////////////////////////////////
	//单机版FTP
	m_edtFTPIp.GetWindowText(m_ftpOneDvr.m_strIp);
	m_edtFTPPort.GetWindowText(m_ftpOneDvr.m_strPort);
	m_edtFTPUser.GetWindowText(m_ftpOneDvr.m_strUser);
	m_edtFTPPwd.GetWindowText(m_ftpOneDvr.m_strPwd);
	m_ftpOneDvr.m_bTransImp = m_ckTransIMP.GetCheck();
	m_ftpOneDvr.m_bTransHd = m_ckTransHD.GetCheck();
	m_ftpOneDvr.m_bTransSd = m_ckTransSD.GetCheck();
	m_ftpOneDvr.m_bDelAfterTrans = true;
	m_ftpOneDvr.m_bEnable = m_ckEnableFtp.GetCheck();
	SaveFtpObj(_T("FTP"), m_ftpOneDvr);
	
	//一级FTP
	m_edtFtpIp1.GetWindowText(m_ftpFirst.m_strIp);
	m_edtFtpPort1.GetWindowText(m_ftpFirst.m_strPort);
	m_edtFtpUser1.GetWindowText(m_ftpFirst.m_strUser);
	m_edtFtpPwd1.GetWindowText(m_ftpFirst.m_strPwd);
	m_ftpFirst.m_bTransImp = m_ckTransIMP1.GetCheck();
	m_ftpFirst.m_bTransHd = m_ckTransHD1.GetCheck();
	m_ftpFirst.m_bTransSd = m_ckTransSD1.GetCheck();
	m_ftpFirst.m_bDelAfterTrans = false;
	m_ftpFirst.m_bEnable = m_ckEnableFtp1.GetCheck();
	SaveFtpObj(_T("FTP1"), m_ftpFirst);

	//二级FTP
	m_edtFtpIp2.GetWindowText(m_ftpSecond.m_strIp);
	m_edtFtpPort2.GetWindowText(m_ftpSecond.m_strPort);
	m_edtFtpUser2.GetWindowText(m_ftpSecond.m_strUser);
	m_edtFtpPwd2.GetWindowText(m_ftpSecond.m_strPwd);	
	m_ftpSecond.m_bTransImp = m_ckTransIMP2.GetCheck();
	m_ftpSecond.m_bTransHd = m_ckTransHD2.GetCheck();
	m_ftpSecond.m_bTransSd = m_ckTransSD2.GetCheck();
	m_ftpSecond.m_bDelAfterTrans = false;
	m_ftpSecond.m_bEnable = m_ckEnableFtp2.GetCheck();
	SaveFtpObj(_T("FTP2"), m_ftpSecond);

	//////////////////////////////////////////////////////////////////////////
	//上传设置
	strSec = _T("TransSetting");
	strKey = _T("resolution");
	int index = m_cbxHDDef.GetCurSel();
	strDst.Format(_T("%d"), index);
	m_IniFile.WriteString(strSec, strKey, strDst);
	
	strKey = _T("flag");
	m_edtVideoIMP.GetWindowText(strDst);
	m_IniFile.WriteString(strSec, strKey, strDst);

	m_IniFile.WriteString(strSec, _T("level1"), m_mapLevel[1]);
	m_IniFile.WriteString(strSec, _T("level2"), m_mapLevel[2]);
	m_IniFile.WriteString(strSec, _T("level3"), m_mapLevel[3]);

	//////////////////////////////////////////////////////////////////////////
	MessageBox(_T("设置成功"), _T("消息提示"));

	//备份文件
	ConfigBackUp::BackUp();

	CDialogEx::OnOK();
}

CString CWelDVRConfigDlg::GetAppPath()
{
	CString path;   
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH),MAX_PATH);   
	int pos = path.ReverseFind('\\');
	path = path.Mid(0, pos);
	return path;
}

CFtpObj CWelDVRConfigDlg::LoadFtpObj(const CString& strSec)
{
	CString strKey, strDst, strDef;
	CFtpObj obj;

	strKey = _T("enable");
	obj.m_bEnable = m_IniFile.ReadInt(strSec, strKey, 0);

	strKey = _T("serv");
	obj.m_strIp = m_IniFile.ReadString(strSec, strKey, strDef);

	strKey = _T("port");
	obj.m_strPort = m_IniFile.ReadString(strSec, strKey, _T("21"));

	strKey = _T("user");
	obj.m_strUser = m_IniFile.ReadString(strSec, strKey, strDef);

	strKey = _T("pwd");
	obj.m_strPwd = m_IniFile.ReadString(strSec, strKey, strDef);

	strKey = _T("transimp");
	obj.m_bTransImp = m_IniFile.ReadInt(strSec, strKey, 0);

	strKey = _T("transhd");
	obj.m_bTransHd = m_IniFile.ReadInt(strSec, strKey, 0);

	strKey = _T("transsd");
	obj.m_bTransSd = m_IniFile.ReadInt(strSec, strKey, 0);

	return obj;
}

void CWelDVRConfigDlg::SaveFtpObj(const CString& strSec, const CFtpObj& obj)
{
	CString strKey = _T("serv");
	m_IniFile.WriteString(strSec, strKey, obj.m_strIp);

	strKey = _T("port");
	m_IniFile.WriteString(strSec, strKey, obj.m_strPort);

	strKey = _T("user");
	m_IniFile.WriteString(strSec, strKey, obj.m_strUser);

	strKey = _T("pwd");
	m_IniFile.WriteString(strSec, strKey, obj.m_strPwd);

	strKey = _T("transimp");
	CString str;
	str.Format(_T("%d"), obj.m_bTransImp ? 1 : 0);
	m_IniFile.WriteString(strSec, strKey, str);

	strKey = _T("transhd");
	str.Format(_T("%d"), obj.m_bTransHd ? 1 : 0);
	m_IniFile.WriteString(strSec, strKey, str);
	
	strKey = _T("transsd");
	str.Format(_T("%d"), obj.m_bTransSd ? 1 : 0);
	m_IniFile.WriteString(strSec, strKey, str);

	strKey = _T("enable");
	str.Format(_T("%d"), obj.m_bEnable ? 1 : 0);
	m_IniFile.WriteString(strSec, strKey, str);
}

//启用一级FTP
void CWelDVRConfigDlg::OnBnClickedCheck1()
{
	bool bEnable = m_ckEnableFtp1.GetCheck();
	EnableFtp1(bEnable);

}

//启用二组FTP
void CWelDVRConfigDlg::OnBnClickedCheck2()
{
	bool bEnable = m_ckEnableFtp2.GetCheck();
	EnableFtp2(bEnable);

}

//启用单机FTP
void CWelDVRConfigDlg::OnBnClickedCheck3()
{
	bool bEnable = m_ckEnableFtp.GetCheck();
	EnableFtp(bEnable);

}

void CWelDVRConfigDlg::EnableFtp1( bool bEnable )
{
	m_edtFtpIp1.EnableWindow(bEnable);
	m_edtFtpPort1.EnableWindow(bEnable);
	m_edtFtpUser1.EnableWindow(bEnable);
	m_edtFtpPwd1.EnableWindow(bEnable);
	m_ckTransIMP1.EnableWindow(bEnable);
	m_ckTransHD1.EnableWindow(bEnable);
	m_ckTransSD1.EnableWindow(bEnable);
}

void CWelDVRConfigDlg::EnableFtp2( bool bEnable )
{
	m_edtFtpIp2.EnableWindow(bEnable);
	m_edtFtpPort2.EnableWindow(bEnable);
	m_edtFtpUser2.EnableWindow(bEnable);
	m_edtFtpPwd2.EnableWindow(bEnable);
	m_ckTransIMP2.EnableWindow(bEnable);
	m_ckTransHD2.EnableWindow(bEnable);
	m_ckTransSD2.EnableWindow(bEnable);
}

void CWelDVRConfigDlg::EnableFtp( bool bEnable )
{
	m_edtFTPIp.EnableWindow(bEnable);
	m_edtFTPPort.EnableWindow(bEnable);
	m_edtFTPUser.EnableWindow(bEnable);
	m_edtFTPPwd.EnableWindow(bEnable);
	m_ckTransIMP.EnableWindow(bEnable);
	m_ckTransHD.EnableWindow(bEnable);
	m_ckTransSD.EnableWindow(bEnable);
}

//是否启用数据库
void CWelDVRConfigDlg::OnBnClickedCheck14()
{
	bool bEnable = m_ckDB.GetCheck();
	EnableDB(bEnable);

}

void CWelDVRConfigDlg::EnableDB( bool bEnable )
{
	m_edtDBIp.EnableWindow(bEnable);
	m_edtDBPort.EnableWindow(bEnable);
	m_edtDBName.EnableWindow(bEnable);
	m_edtDBUser.EnableWindow(bEnable);
	m_edtDBPwd.EnableWindow(bEnable);
	m_edtDBTime.EnableWindow(bEnable);
}

//向上
void CWelDVRConfigDlg::OnBnClickedButton2()
{
	int index = m_listTransLevel.GetCurSel();
	CString str;
	m_listTransLevel.GetText(index, str);
	CString strPrv;
	m_listTransLevel.GetText(index - 1, strPrv);

	m_mapLevel[index + 1] = strPrv;
	m_mapLevel[index] = str;
	
	RefreshList();
}

//向下
void CWelDVRConfigDlg::OnBnClickedButton3()
{
	int index = m_listTransLevel.GetCurSel();
	CString str;
	m_listTransLevel.GetText(index, str);
	CString strNext;
	m_listTransLevel.GetText(index + 1, strNext);

	m_mapLevel[index + 1] = strNext;
	m_mapLevel[index + 2] = str;

	RefreshList();
}

//级别改变
void CWelDVRConfigDlg::OnLbnSelchangeList1()
{
	int index = m_listTransLevel.GetCurSel();
	if(index == 0)
	{
		m_btnUp.EnableWindow(FALSE);
		m_btnDown.EnableWindow(TRUE);
	}
	else if(index == 1)
	{
		m_btnUp.EnableWindow(TRUE);
		m_btnDown.EnableWindow(TRUE);
	}
	else if(index == 2)
	{
		m_btnUp.EnableWindow(TRUE);
		m_btnDown.EnableWindow(FALSE);
	}
	else
	{
		m_btnUp.EnableWindow(FALSE);
		m_btnDown.EnableWindow(FALSE);
	}
}

void CWelDVRConfigDlg::RefreshList()
{
	int n = m_listTransLevel.GetCount();
	for( int i = n - 1; i >= 0; --i )
		m_listTransLevel.DeleteString(i);

	m_listTransLevel.InsertString(0, m_mapLevel[1]);
	m_listTransLevel.InsertString(1, m_mapLevel[2]);
	m_listTransLevel.InsertString(2, m_mapLevel[3]);
}


void CWelDVRConfigDlg::OnBnClickedButton4()
{
	CDialog::OnCancel();
}


void CWelDVRConfigDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	ConfigBackUp::BackUp();

	CDialogEx::OnClose();
}
