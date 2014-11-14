/************************************************************************/
/* 
* 描述： DVR管理类
*		1. 以单例的方式向外提供接口
* 时间： created by yjt 2014-4-12
* 历史：
*/
/************************************************************************/
#pragma once

#include "DvrWnd.h"
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <afxmt.h>
#include "WellCommon/CriLock.h"
#include "DataDef.h"

using namespace std;

class CDevBase;

//<窗口对象>
typedef vector<CDvrWnd*> VecDvrWnd;
typedef VecDvrWnd::iterator VecDvrWndItor;

//<窗口索引，窗口对象>
typedef map<int, DvrWndInfo*> MapDvrWnd;
typedef MapDvrWnd::iterator MapDvrWndItor;

class CDvrMgrBase{
public:
	CDvrMgrBase();
	~CDvrMgrBase();
	
public:
	CDvrWnd* GetDvr(int wndIndex);
	CDvrWnd* GetDvr(int row, int col);
	CDvrWnd* GetDvr(const wstring& strPort);
		
	virtual int GetWndIndex(const wstring& strPort);

protected:
	void Init();
	void UnInit();

	virtual bool GetRowCol(const wstring& strPort, int& row, int& col);
	virtual void GetRowCol( int nWndIndex, int& row, int& col );

	//根据行列获取窗口的索引
	int GetWndIndexByRowCol(int row, int col);

protected:
	//<Dvr窗口对象>
	VecDvrWnd m_vecDvrWnd;
	DECLARE_LOCK
};


UINT ClearProc(LPVOID param);

class CDvrMgr : public CDvrMgrBase
{
	friend UINT ClearProc(LPVOID param);
public:
	CDvrMgr(void);
	virtual ~CDvrMgr();

public:
	static CDvrMgr& Instance();

	virtual CDvrWnd* PutDvr(const wstring& strPort);
	virtual void RemoveDvr(const wstring& strPort);

	void CopyDvrFile(const wstring& strPort, const wstring& diskName);

protected:
	//获取DVRId
	bool GetDvrId(CString& strId, CDevBase** pDvr);

	void InsertDvrDevice(const CString& strID, const CString& strLog);

	//清除不可用的dvr
	void ClearInValidDvr();

protected:
	CCriticalSection m_cs;

	//清除无用窗口用
	vector<int> m_vecClear;

	//////////////////////////////////////////////////////////////////////////
	//用于记录每个窗口的对象状态
	//有些机器反应很慢，很久才能枚举出U盘
	//当枚举出U盘时，窗口早已清空，可以用
	//这些缓存的对象恢复窗口的状态
	//  1. 插入并读取ID时，缓存
	//	2. 变成U盘时，如果没有ID，则恢复
	//	3. 一分种后清除
	//////////////////////////////////////////////////////////////////////////
	MapDvrWnd m_mapDvrWnd;

	//沒有定位接口--Alert狀態存儲
	//已接示的就不要重復提示
	map<wstring, int> m_mapAlertPort;
};

