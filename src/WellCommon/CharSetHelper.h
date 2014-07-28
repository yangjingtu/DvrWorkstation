#pragma once
/********************************************************************
	created:	2012/05/25 12:53  
	filename: 	CharSetHelper.h
	author:		yjt
	purpose:	字符集辅助类

	资料:
		1.string 转 CString
		CString.format(”%s”, string.c_str());

		2.char 转 CString
		CString.format(”%s”, char*);

		3.char to string
		string s(char *);

		4.string 转 char *
		char *p = string.c_str();

		5.CString 转 string
		string s(CString.GetBuffer());

		6.string -> CString
		CString.format(”%s”, string.c_str());
		用c_str()确实比data()要好.
		7.CString -> string
		string s(CString.GetBuffer());
		GetBuffer()后一定要ReleaseBuffer(),否则就没有释放缓冲区所占的空间.
		8.有三个函数可以将字符串的内容转换为字符数组和C—string
		1.data(),返回没有”\0“的字符串数组
		2,c_str()，返回有”\0“的字符串数组
		3，copy()

		9.将字符转换为整数，可以使用atoi、_atoi64或atol。
		10.将数字转换为CString变量，可以使用CString的Format函数

		CString s;
		int i = 64;
		s.Format(”%d”, i)
		Format函数的功能很强，值得你研究一下。

		11.cstring TO char *
		charpoint=strtest.GetBuffer(strtest.GetLength());

		12.CString转换 char[100]

		char a[100];
		CString str(”aaaaaa”);
		strncpy(a,(LPCTSTR)str,sizeof(a));
*********************************************************************/
#include <string>
using namespace std;

#define IVS_COMM_EXPORTS

#ifdef IVS_COMM_EXPORTS
#define IVS_COMM_API __declspec(dllexport)
#else 
#define IVS_COMM_API __declspec(dllimport)
#endif

#define C2W(str) CCharSetHelper::c2w((str))
#define W2C(str) CCharSetHelper::w2c((str))

class IVS_COMM_API CCharSetHelper
{
public:
	CCharSetHelper(void);
	~CCharSetHelper(void);

	//char to wchar_t
	static size_t c2w(wchar_t *pwstr, char *str);
	static void c2w(wchar_t *pwstr,size_t len,char *str);
	static wstring c2w(const string& str);
	static size_t c2w(const string& strIn, wstring& wstrOut);

	//wchar_t change to char
	static char* w2c(char *pcstr,wchar_t *pwstr, size_t len);
	static size_t w2c(char *pcstr,wchar_t *pwstr);
	static string w2c(const wstring& wstr);
	static size_t w2c(const wstring& wstrIn, string& strOut);
};

