//////////////////////////////////////////////////////////////////////////
//描述：视频转换类
//		1. AVI转成FLV
//Date: created by yjt 2014-7-6
//History:
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
using namespace std;

class CConvertVideo
{
public:
	CConvertVideo(void);
	~CConvertVideo(void);

	static bool Avi2Flv(const wstring& sAviFile, const wstring& sFlvFile, int width, int Height);

private:
	static bool Convert(const wstring& strCmd);
};

