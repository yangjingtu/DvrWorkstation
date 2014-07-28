//////////////////////////////////////////////////////////////////////////
//Describe:	Avi To Flv
//Date: created by yjt 2014-7-6
//History:	
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <queue>
using namespace std;

typedef queue<wstring> QFlvVideo;

#define AVI2FLV CAvi2Flv::Instance()

UINT ConvertProc(LPVOID param);

class CAvi2Flv
{
	friend UINT ConvertProc(LPVOID param);
private:
	CAvi2Flv(void);
	~CAvi2Flv(void);

public:
	static CAvi2Flv& Instance(); 

	//添加要转换的视频，
	void PutVideo(const wstring& strAviPath);
	
	//运行
	void Run(const wstring& strPath);
	void Stop() { m_bStop = true; }

private:
	void ConvertService();

	void InsertMediaInfo(const wstring &strIn, const wstring& strOut);

	wstring GetStartTime( const wstring& strIn );
	wstring AddTime(const wstring& strStart, const wstring& millSecond);

	wstring GetOutPutPath(const wstring& strInPath);

private:
	//要合成FLV的队列
	QFlvVideo m_qFlv;

	//保存的路径
	wstring m_strPath;

	//是否停止
	bool m_bStop;
};

