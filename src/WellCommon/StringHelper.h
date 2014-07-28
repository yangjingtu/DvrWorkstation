#pragma once

#include <vector>
using namespace std;


#define IVS_COMM_EXPORTS

#ifdef IVS_COMM_EXPORTS
#define IVS_COMM_API __declspec(dllexport)
#else 
#define IVS_COMM_API __declspec(dllimport)
#endif

class IVS_COMM_API CStringHelper
{
public:
	CStringHelper(void);
	~CStringHelper(void);

public:
	//·Ö¸î
	static vector<CString> split(const CString& strSrc, const CString& splitString);
	static vector<string> split(const string& strSrc, const string& splitString);
	static vector<wstring> split(const wstring& strSrc, const wstring& splitString);

	//Ìæ»»
	static void Replace( wstring &strSrc, const wstring &strFind, const wstring &strReplace );
};
