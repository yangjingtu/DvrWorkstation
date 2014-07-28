#include "StdAfx.h"
#include "StringHelper.h"

CStringHelper::CStringHelper(void)
{
}

CStringHelper::~CStringHelper(void)
{
}

/***************************************************************************************
*描    述: 分割字符串
*
*参数列表:	strSrc [IN]		--		要分割的原始串
*				splitString [IN]	--		分割符
*返 回 值:字符串链表--存储分割的集合
*
*时间作者: created by yjt [2012/10/25 17:05]
*
*修改记录:
*
***************************************************************************************/
vector<CString> CStringHelper::split(const CString& strSrc, const CString& splitString)
{
	vector<CString> vecRlt;

	int nStart = 0;
	int nIndex = 0;
	CString strTmp;
	nIndex = strSrc.Find(splitString, nStart);
	while(nIndex > 0)
	{
		strTmp = strSrc.Mid(nStart, nIndex - nStart);
		vecRlt.push_back(strTmp);
		nStart = nIndex + splitString.GetLength();
		nIndex = strSrc.Find(splitString, nStart);
	}
	if(strSrc.GetLength() > nStart)
	{
		strTmp = strSrc.Mid(nStart, strSrc.GetLength() - nStart);
		vecRlt.push_back(strTmp);
	}
	return vecRlt;
}


vector<string> CStringHelper::split(const string& strSrc, const string& splitStr)
{
	vector<string> vecRlt;
	string strSrcT(strSrc);
	string::size_type nPosb = 0;
	string::size_type nPosF = strSrcT.find(splitStr, nPosb);
	string strTmp;
	while( nPosF != string::npos)
	{
		strTmp = strSrcT.substr(nPosb, nPosF - nPosb);
		vecRlt.push_back(strTmp);
		nPosb = nPosF + splitStr.length();
		nPosF = strSrcT.find(splitStr, nPosb);
	}
	if(nPosb < strSrcT.length())
	{
		strTmp = strSrcT.substr(nPosb, strSrcT.length() - nPosb);
		vecRlt.push_back(strTmp);
	}

	return vecRlt;
}


vector<wstring> CStringHelper::split(const wstring& strSrc, const wstring& splitStr)
{
	vector<wstring> vecRlt;
	wstring strSrcT(strSrc);
	wstring::size_type nPosb = 0;
	wstring::size_type nPosF = strSrcT.find(splitStr, nPosb);
	wstring strTmp;
	while( nPosF != wstring::npos)
	{
		strTmp = strSrcT.substr(nPosb, nPosF - nPosb);
		vecRlt.push_back(strTmp);
		nPosb = nPosF + splitStr.length();
		nPosF = strSrcT.find(splitStr, nPosb);
	}
	if(strSrcT.length() > nPosb)
	{
		strTmp = strSrcT.substr(nPosb, strSrcT.length() - nPosb);
		vecRlt.push_back(strTmp);
	}

	return vecRlt;
}

/***************************************************************************************
*描    述:	替换字符串
*
*参数列表:	strSrc [IN]	[OUT]		--		源字符串，同时也是输出字符串
*				strFind [IN]				--		要被替换的串
*				strReplace [IN]			--		规换字符串
*返 回 值:
*
*时间作者: created by yjt [2012/12/4 14:15]
*
*修改记录:
*
***************************************************************************************/
void CStringHelper::Replace( wstring &strSrc, const wstring &strFind, const wstring &strReplace )
{
	if(strSrc.empty() || strFind.empty() || strReplace.empty())
		return;

	wstring::size_type nFindPos = 0;
	nFindPos = strSrc.find(strFind, nFindPos);
	while (nFindPos != wstring::npos) 
	{
		strSrc.replace(nFindPos, strFind.length(), strReplace);
		nFindPos += strReplace.length();
		nFindPos = strSrc.find(strFind, nFindPos);
	}
}
