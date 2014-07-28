#include "stdafx.h"
#include "cfilelog.h"
#include "DirHelper.h"
#include "CharSetHelper.h"

/**
 * 描	述：　创建日志对象
 * 说	明：
 * 		1. 自动的以当天时间为文件名来创建日志
 * 		2. 使用静态的方法来构造，提高效率
 * 			２．１　如果不关闭（几天），都会写到开启的那一天中－－这个是测试用还是考滤效率好了
 * 			2.2 以后再改为每次获取时间 -- 获取加一个定时器
 * 使用示例: log() << "string" << 100 << 100.00 << true << el/tl;
 * 时间作者：　created by yjt 2012-09-07
 */
CFileLog log() {
    //创建日志对象
    return CFileLog(getLogPath());
}

/**
 * 描	述： 获取日志路径
 *	1. 程序运行目录 + /log/＋日期.txt
 * 时间作者：created by yjt 2012-09-07
 */
string getLogPath()
{
	//应用程序路径
	string strPath = CDirHelper::GetAppPath();
    strPath += "log\\";

	CString strTmp;
	strTmp.Format(_T("%s"), CCharSetHelper::c2w(strPath).c_str());
	static bool bCreate = false;
	if(!bCreate)
	{
		if(CDirHelper::CreateDir(strTmp))
			bCreate = true;
	}
	
	//创建时间.txt
	time_t t;
	time(&t);
	char time_str[20]= {0};
	struct tm timeinfo;
	localtime_s (&timeinfo, &t);
	strftime(time_str, 100, "%Y%m%d.txt", &timeinfo);

	strPath += time_str;
    return strPath;
}


/*
int main()
{
    / *
	//方案1
    CLog log("log\\log.txt");
    log << "sssssa;" << tl;
    log << "打印类信息" << el;
    * /
	
	//方案2
    log() << "打印日韩" << 100 << tl;

    return 0;
}
*/
