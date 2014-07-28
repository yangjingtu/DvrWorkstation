/*
   描述：
	    日志操作类
   实现：
	1. 以流的方式实现
	    １.1 流对象－－集中写入--提高效率
	    1.2 当缓冲区满的时候，自动写入
	    1.3 重载<<操作符,方便写入
   时间作者：　
	    created by yjt 2012-09-06
*/

#ifndef CLOGHELPER_H
#define CLOGHELPER_H
#include <time.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "CharSetHelper.h"

class CFileLog;

//全局日志函数
CFileLog IVS_COMM_API log();
//获取日志路径
string getLogPath();

//日志结束类型
enum LogEndType {
    el = 0,			//行结束-end line　\r\n
    tl,				//行结束 - end line, 第二行以时间开头
    lst				//行开始，　加上时间
};

class CFileLog
{
public:
    enum LogType {
        Debug_Log = 0,		//调试日志  --　不是调试状态不打印
        System_Log,		//系统日志	 --　带时间
        Run_Log			//运行日志	 --   打印用户指定信息
    };


    struct Stream {
        Stream(const string& strFileName) : ref(1), space(true), message_output(false), open(false) {
			ts.open(strFileName.c_str(), ios::app);
            if(ts.is_open())
                open = true;
        }
        ofstream ts;					//文件流对象
        int ref;							//引用计数器
        bool space;						//空格
        bool message_output;		//已经输出
        bool open;						//已经打开
    } *stream;

public:
    inline CFileLog(const string& strFileName) : stream(new Stream(strFileName)) {
        (*this)<< lst;
    }

    inline CFileLog(const CFileLog &o):stream(o.stream) {
        ++stream->ref;
    }
    inline CFileLog& operator=(const CFileLog &other);
    inline ~CFileLog() {
        if(stream->ref == 1)
            stream->message_output = true;
        if (!--stream->ref) {
            if(stream->message_output) {
                try {
                    (*this) << el;			//加一个换行符
                    stream->ts.flush();
                    stream->ts.close();
                } catch(std::bad_alloc&) {
                    /* We're out of memory - give up. */
                }
            }
            delete stream;
        }
    }
    inline CFileLog& space() {
        stream->space = true;
        stream->ts << ' ';
        return *this;
    }
    inline CFileLog &nospace() {
        stream->space = false;
        return *this;
    }
    inline CFileLog &maybeSpace() {
        if (stream->space) stream->ts << ' ';
        return *this;
    }

    inline CFileLog &operator<<(bool t) {
        stream->ts << (t ? "true" : "false");
        return maybeSpace();
    }
    inline CFileLog &operator<<(char t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog &operator<<(signed short t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog &operator<<(unsigned short t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog &operator<<(signed int t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog &operator<<(unsigned int t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog &operator<<(signed long t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog &operator<<(unsigned long t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog &operator<<(float t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog &operator<<(double t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog &operator<<(const char* t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog &operator<<(const string& t) {
        stream->ts << '\"' << t  << '\"';
        return maybeSpace();
    }
	inline CFileLog &operator<<(const wstring& t){
		stream->ts <<'\"' << W2C(t) << '\"';
		return maybeSpace();
	}
	inline CFileLog &operator<<(const void * t) {
        stream->ts << t;
        return maybeSpace();
    }
    inline CFileLog&operator<<(LogEndType emET) {
        time_t t;
        time(&t);
        char time_str[23]= {0};
        struct tm timeinfo;
		localtime_s ( &timeinfo,&t);
        strftime(time_str, 100, "[%Y-%m-%d %H:%M:%S] ", &timeinfo);

        if(emET == el)
            stream->ts << "\r\n";
        else if(emET == tl)
            stream->ts << "\r\n" << time_str;
        else if(emET == lst)
            stream->ts << time_str;
	return *this;
    }
};

#endif // CLOGHELPER_H
