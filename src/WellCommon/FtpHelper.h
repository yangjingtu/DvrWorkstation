/************************************************************************/
/* 
* Describe: FTP辅助类
*	1. 检测ftp配置信息
*		1.1 单机版必须配置
*		1.2 多机版
*			1.2.1 配置了按单机版的逻辑走
*	2. 先拷贝到本地
*	3. 后台服务上传到ftp服务器上
*		3.1 断点续传
* Date: created by yjt 2014-4-17
* History:
*		add by yjt 2014-6-12 添加定时器处理, 同时把ftp类做成导出类
*		add by yjt 2014-6-13 添加上传回调处理，把要上传的文件回调出来，让客户端处理要不要上传
*/
/************************************************************************/
#pragma once
#include <afxinet.h>
#include <afxmt.h>
#include <map>
using namespace std;

#define TRANS_CONTUNE 0		//继续传
#define TRANS_SKIP 1		//跳过
#define TRANS_DELETE 2		//继续传，传完后删除

enum EM_MSG_TYPE
{
	TRANS_BEGIN = 0,
	TRANS_END
};

//////////////////////////////////////////////////////////////////////////
//功能：上传文件回调函数
//参数：
//		strCurTransFile [IN]	--		指示当前要上传的文件
//返回:
//		0: 上传 
//		1: 不上传,跳过
//////////////////////////////////////////////////////////////////////////
typedef int (__stdcall *TransFileCallBack)(const string& strCurTransFile);

//////////////////////////////////////////////////////////////////////////
//功能: 传输消息回调
//		1. 开始传输和结束传输时都回调一次
//返回：
//		0: 继续
//		1: 跳过		--  可以控制是否删除文件
//////////////////////////////////////////////////////////////////////////
typedef int (__stdcall *TransMsgCB)(EM_MSG_TYPE type);


typedef struct tagRegCB
{
	TransFileCallBack tfCB;
	TransMsgCB	ttNotify;
}RegCB, *PRegCB;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
class __declspec(dllexport) CFtpHelper;

typedef map<UINT_PTR, CFtpHelper*> MapTimer;
typedef MapTimer::iterator MapTimerItor;



UINT PutFileProc(LPVOID pFtp);
DWORD WINAPI FtpThrProc(LPVOID param);

class __declspec(dllexport) CFtpHelper
{
	friend UINT PutFileProc(LPVOID pFtp);
	friend DWORD WINAPI FtpThrProc(LPVOID param);
	
	enum EM_FTP_PUT_STATUS{
		EM_PUT_OK,
		EM_PUT_FAIL,
		EM_PUT_UNKNOW
	};

public:
	CFtpHelper(void);
	~CFtpHelper(void);

	//////////////////////////////////////////////////////////////////////////
	//功能：启动ftp客户端--连接ftp服务器
	//参数：
	//	addr [IN]		--	服务器IP地址
	//	strUser [IN]	--	用户名
	//	strPwd [IN]		--	密码
	//	nPort [IN]		--	端口
	//	strDir	[IN]	--	本地目录（从此目录自动上传到ftp服务器)
	//返回值：
	//	true : 成功连接上服务器
	//////////////////////////////////////////////////////////////////////////
	bool Start(const string& addr, const string& strUser, const string& strPwd, UINT nPort, const string& strDir);
	bool Start(const wstring& addr, const wstring& strUser, const wstring& strPwd, UINT nPort, const wstring& strDir);
	
	//////////////////////////////////////////////////////////////////////////
	//功能：注册回调
	//		1. 当tfFunc设置为空时，不进行回调，直接上传
	//////////////////////////////////////////////////////////////////////////
	void Register(const RegCB& callBacks);

	//////////////////////////////////////////////////////////////////////////
	//功能：后台服务（自动上传服务器)
	//////////////////////////////////////////////////////////////////////////
	void ServiceRun();

	//////////////////////////////////////////////////////////////////////////
	//功能：获取传送百分比
	//////////////////////////////////////////////////////////////////////////
	float GetTransPrecent();

	//////////////////////////////////////////////////////////////////////////
	//功能: 获取传送速度
	//////////////////////////////////////////////////////////////////////////
	void GetTransSpeed(wstring& strSpd);
	void GetTransSpeed(string& strSpd);
	
	//////////////////////////////////////////////////////////////////////////
	//功能：获取正在传送的文件名
	//////////////////////////////////////////////////////////////////////////
	void GetPutFile(wstring& strPF);
	void GetPutFile(string& strPF);

protected:
	//创建目录
	bool CreateDirctory(const wstring& strPath);
	bool CreateDirctory(const string& strPath);

	//上传文件
	UINT PutFile(const wstring& strFile, const wstring& saveFile);
	UINT PutFile(const string& strFile, const string& saveFile);

	//上传文件夹
	bool TransFolder(const wstring& strFoldername, const wstring& strDst);
	bool TransFolder(const string& strFoldername, const string& strDst);

	//停止传输
	void StopTrans() { m_bForceStop = true; }
private:
	//启动ftp客户端
	bool _Start( const wstring& addr, const wstring& strUser, const wstring& strPwd, UINT nPort);
	
	//创建目录
	bool _CreateDirctory(const wstring& strPath);

	//上传文件
	UINT _PutFile(const wstring& strFile, const wstring& saveFile);

	//上传文件夹
	bool _TransFolder(const wstring& strFoldername, const wstring& strDst);

protected:
	UINT PutFile();

	//判断服务器的文件是否存在
	LONGLONG IsFileExit(const wstring& strFile);
	int DelEmptyFolder(const wstring& strFolder);

	bool Init();
	void Unit();

	void Service();

	bool Start();
	void Stop();

	bool ReStart();
	void ReSetTrans();
	//定时器回调， 必须在头文件中定义(全局函数也是，同时要加static)
	static void CALLBACK PutTimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);
	static MapTimer m_mapTimerObjs;
private:

	CInternetSession* m_pInetSession;
	CFtpConnection*   m_pFtpConnection;

	wstring m_strServAddr;		//ftp服务器的地址  LPCTSTR
	wstring m_strUser;			//登陆用户名       LPCTSTR 
	wstring m_strPwd;			//密码            LPCTSTR
	UINT m_nPort;				//端口            UINT

	HANDLE m_hEvent;
	HANDLE m_hThread;

	//FTP本地目录
	wstring m_strLocalDir;

	wstring m_wstrPutFile;
	string m_strPutFile;
	wstring m_strSaveFile;
	bool m_bExit;

	int m_nPutStatus;				//上传结果


	/////////////////////////////////////////////////////////////
	//后台服务
	CCriticalSection m_cs;
	//续传的大小
	char *m_pBuffer;
	int m_nBufSize;
	////////////////////////////////////////////////////////////

	//是否停止传输
	bool m_bForceStop;

	////////////////////////////////////////////////////

	//拷贝速度
	wstring m_wstrSpeed;			//拷贝速度
	string m_strSpeed;

	//拷贝速度定时器
	UINT_PTR m_putTimerId;
	int m_nTotalTanstime;		//总传输时间(秒)
	LONGLONG m_llTransSize;		//传输的大小(每个文件)
	LONGLONG m_llFileSize;		//每个文件的总大小
	////////////////////////////////////////////////////

	//上传回调函数
	RegCB m_regCB;
};

