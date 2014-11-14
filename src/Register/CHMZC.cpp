#include "stdafx.h"
#include "chmzc.h"
#include "zcjm.h"

string GetMachineCode()
{
    return zcjm::GetMachineCode();
}

int _GetMachineCode(char* mc)
{
	string str = GetMachineCode();
	strcpy(mc, str.c_str());
	return str.length();
}

string GetRegisterCode(const string& strMichineCode)
{
    return zcjm::GetRegisterCode(strMichineCode);
}

int _GetRegisterCode(const char* chMichineCode, char* rlt)
{
	string str = GetRegisterCode(string(chMichineCode));
	strcpy(rlt, str.c_str());
	return str.length();
}

bool Register(const string& strRegisterCode)
{
    return zcjm::Register(strRegisterCode);
}

bool _Register(const char* strRegisterCode)
{
	return zcjm::Register(string(strRegisterCode));
}

bool IsRegister()
{
    return zcjm::IsRegister();
}


#include <string>
std::string ws2s(const std::wstring& ws)
{
	std::string result;
	std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

std::wstring s2ws(const std::string& s)
{
	std::wstring result;
	setlocale(LC_ALL, "chs"); 
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, "C");
	return result;
}


int _ws2s(const wchar_t* ws, char* rlt)
{
	if(ws && wcslen(ws) > 1)
	{
		string str = ws2s(wstring(ws));
		strcpy(rlt, str.c_str());
		return str.length();
	}
	return 0;
}

int  _s2ws(const char* s, wchar_t* rlt)
{
	if(s && strlen(s) > 1)
	{
		wstring str = s2ws(string(s));
		wcscpy(rlt, str.c_str());
		return str.length();
	}
	return 0;
}