#include "stdafx.h"
#include "ConvertVideo.h"
#include <sstream>


CConvertVideo::CConvertVideo(void)
{
}


CConvertVideo::~CConvertVideo(void)
{

}

bool CConvertVideo::Convert(const wstring& strCmd)
{
	SECURITY_ATTRIBUTES sa;//创建一个安全属性的变量
	HANDLE hRead,hWrite; //管道的读写句柄声明
	sa.nLength = sizeof(SECURITY_ATTRIBUTES); //获取安全属性的长度
	sa.lpSecurityDescriptor = NULL;  //使用系统默认的安全描述符 
	sa.bInheritHandle = TRUE;  //创建的进程允许继承句柄

	if (!CreatePipe(&hRead,&hWrite,&sa,0))  //创建匿名管道
	{  
		//MessageBox(_T("CreatePipe Failed!"), _T("提示"), MB_OK | MB_ICONWARNING);  
		return false;
	}
	STARTUPINFO si;				//启动信息结构体变量
	PROCESS_INFORMATION pi;		//需要传入的进程信息的变量

	ZeroMemory(&si,sizeof(STARTUPINFO)); //因为要传入参数，所以先清空该变量
	si.cb = sizeof(STARTUPINFO); //结构体的长度
	GetStartupInfo(&si); 
	si.hStdError = hWrite; 
	si.hStdOutput = hWrite;  //新创建进程的标准输出连在写管道一端
	si.wShowWindow = SW_HIDE;  //隐藏窗口 
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	TCHAR cmdline[512] = {0};
	CString tmp,stredit2;
	//GetDlgItemText(IDC_EDIT2,stredit2);  //获取编辑框中输入的命令行
	//tmp.Format(_T("cmd /C %s"),stredit2);
	tmp.Format(_T("cmd /C %s"), strCmd.c_str());
	swprintf(cmdline,_T("%s"),tmp);

	if (!CreateProcess(_T("C://Windows//System32//cmd.exe"),cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))  //创建子进程
	{		
		DWORD dwErr = GetLastError();
		//MessageBox(_T("CreateProcess Failed!"), _T("提示"),MB_OK | MB_ICONWARNING);
		return false;
	}
	CloseHandle(hWrite);  //关闭管道句柄

	char buffer[4096] = {0};
	CString strOutput;
	DWORD bytesRead;

	while (true)
	{
		if (ReadFile(hRead,buffer,4095,&bytesRead,NULL) == NULL)  //读取管道内容到buffer中  
			break;

		strOutput += buffer;
		//m_edtMsg.SetWindowText(strOutput);
		//SetDlgItemText(IDC_EDIT2,strOutput);  //显示输出信息到编辑框,并刷新窗口
		//UpdateWindow();
		//Sleep(100);
	}
	CloseHandle(hRead); //关闭读取句柄

	return true;
}

//高质量: ffmpeg -i 20140625_111916.avi -ab 128 -acodec libmp3lame -ac 1 -ar 22050 -r 29.97 -qscale 6 -y 2.flv
//低质量: ffmpeg -i 20140625_111916.avi -ab 128 -acodec libmp3lame -ac 1 -ar 22050 -r 29.97 -b 360 -y 3.flv
bool CConvertVideo::Avi2Flv(const wstring& sAviFile, const wstring& sFlvFile, int width, int Height)
{
	wstringstream os;
	os << GetAppPath().GetString() << _T("\\ffmpeg.exe -i ")
		<< sAviFile
		<< _T(" -ab 128 -acodec libmp3lame -ac 1 -ar 22050 -r 29.97 -b 360 -s ")
		<< width  << _T("x") << Height
		<< _T(" ")
		<< sFlvFile 
		<< _T("");

	return Convert(os.str());
}