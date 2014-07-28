//////////////////////////////////////////////////////////////////////////
//Describe:
//		XML²Ù×÷Àà
//Date: created by yjt 2014-06-30
//Example:
/*
	#include "../WellCommon/XmlHelper.h"
	#pragma comment(lib, "WellCommon.lib")

	void TestXml()
	{
		CXmlHelper xml;
		xml.Load("D:\\test.xml", true);

		xml.SetNodeValue("root\\ftp\\serv", "192.168.1.1.");
		xml.SetNodeAttr("root\\ftp\\serv", "port", "21");

		string str = xml.GetNodeValue("root\\ftp\\serv");
		str = xml.GetNodeAttr("root\\ftp\\serv", "port");

		xml.Save("D:\\test1.xml");
	}
*/
//History:
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "../tinyxml/tinyxml.h"
//#pragma comment(lib, "tinyxml.lib")

#include <string>
#include <vector>
using namespace std;


#define IVS_COMM_EXPORTS

#ifdef IVS_COMM_EXPORTS
#define IVS_COMM_API __declspec(dllexport)
#else 
#define IVS_COMM_API __declspec(dllimport)
#endif

class IVS_COMM_API CXmlHelper
{
public:
	CXmlHelper(void);
	~CXmlHelper(void);

	bool Load(const wstring& file, bool bCreate = false);
	bool Load(const string& file, bool bCreate = false);

	bool Load_Xml(const wstring& strXml);
	bool Load_Xml(const string& strXml);

	bool Save(const wstring& file = L"");
	bool Save(const string& file = "");

	wstring GetNodeValue(const wstring& strPath);
	string GetNodeValue(const string& strPath);

	bool SetNodeValue(const wstring& strPath, const wstring& strValue);
	bool SetNodeValue(const string& strPath, const string& strValue);

	wstring GetNodeAttr(const wstring& strPath, const wstring& strAttr);
	string GetNodeAttr(const string& strPath, const string& strAttr);

	bool SetNodeAttr(const wstring strPath, const wstring& strAttr, const wstring& strValue);
	bool SetNodeAttr(const string strPath, const string& strAttr, const string& strValue);

	void Print();

private:
	TiXmlElement* GetNode(const string& strPath);
	TiXmlElement* CreateNode(const string& strPath);

private:
	bool m_bLoad;

	TiXmlDocument m_doc;
};

