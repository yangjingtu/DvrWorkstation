#pragma once

#include <string>
using namespace std;

class AFX_EXT_CLASS CFileBackUp
{
public:
	CFileBackUp(void);
	~CFileBackUp(void);

	static bool BackUp(const wstring& src, const wstring& dst);
	static bool BackUp(const string& src, const string& dst);
	static bool FileCopyTo(CString source, CString destination, CString searchStr, BOOL cover = TRUE);
};

