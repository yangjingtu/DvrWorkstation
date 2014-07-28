#include "StdAfx.h"
#include "XmlHelper.h"
#include "StringHelper.h"

CXmlHelper::CXmlHelper(void)
{
	m_bLoad = false;
}


CXmlHelper::~CXmlHelper(void)
{
}

bool CXmlHelper::Load(const wstring& file, bool bCreate)
{
	return Load(WS2S(file), bCreate);
}

bool CXmlHelper::Load(const string& file, bool bCreate)
{
	try
	{
		FILE* pFile = fopen(file.c_str(), "r");
		if(pFile == NULL)
		{
			if(bCreate)
			{
				m_doc.LoadFile(file.c_str(), TIXML_ENCODING_UTF8);

				TiXmlNode *pDelar = new TiXmlDeclaration("1.0", "UTF-8", "no");
				TiXmlNode* pNode = m_doc.LinkEndChild(pDelar);

				delete pDelar;

				TiXmlNode *pRoot  = new TiXmlElement("root");
				m_doc.LinkEndChild(pRoot);	

				m_doc.SaveFile(file.c_str());

				m_bLoad = true;
			}
		}
		else
		{
			fclose(pFile);
			m_bLoad = m_doc.LoadFile(file.c_str(), TIXML_ENCODING_UTF8);
		}
	}
	catch(...)
	{
		m_bLoad = false;
	}

	return m_bLoad;
}

bool CXmlHelper::Load_Xml(const wstring& strXml)
{
	return Load_Xml(WS2S(strXml));
}

bool CXmlHelper::Load_Xml(const string& strXml)
{
	try
	{
		const char* p = m_doc.Parse(strXml.c_str());
		if(p == NULL)
			m_bLoad = false;
		else
			m_bLoad = true;
	}
	catch(...)
	{
		m_bLoad = false;
	}
	return m_bLoad;
}

bool CXmlHelper::Save(const wstring& file)
{
	return Save(WS2S(file));
}

bool CXmlHelper::Save(const string& file)
{
	if(!m_bLoad)
		return false;
	bool bRlt = false;
	try
	{
		if(file.empty())
		{
			bRlt = m_doc.SaveFile();
		}
		else
		{
			bRlt = m_doc.SaveFile(file.c_str());
		}
	}
	catch(...)
	{
		bRlt = false;
	}
	return bRlt;
}

TiXmlElement* CXmlHelper::GetNode(const string& strPath)
{
	TiXmlElement* pNode = NULL;
	if(!m_bLoad)
		return pNode;

	try
	{
		vector<string> ret;
		CStringHelper::split(strPath, "\\", &ret);

		if(ret.empty())
			return pNode;

		//获得根元素，即Persons。
		TiXmlElement *RootElement = m_doc.RootElement();
		if( RootElement == NULL)
			return pNode;

		if(RootElement->Value() != ret[0])
			return pNode;

		TiXmlElement* pElem = RootElement;
		vector<string>::iterator it = ret.begin();
		++it;
		for( ; it != ret.end(); ++it)
		{
			//循环获取子节点
			pElem = pElem->FirstChildElement( (*it).c_str() );
			if(pElem == NULL)
				break;
		}
		pNode = pElem;
	}
	catch(...)
	{
		return NULL;
	}
	return pNode;
}

TiXmlElement* CXmlHelper::CreateNode(const string& strPath)
{
	TiXmlElement* pNode = NULL;
	if(!m_bLoad)
		return pNode;

	try
	{
		vector<string> ret;
		CStringHelper::split(strPath, "\\", &ret);

		if(ret.empty())
			return pNode;

		//获得根元素，即Persons。
		TiXmlElement *RootElement = m_doc.RootElement();
		if( RootElement == NULL)
		{
			RootElement = new TiXmlElement(ret[0].c_str());
			m_doc.LinkEndChild(RootElement);	
		}

		if(RootElement->Value() != ret[0])
			return pNode;

		TiXmlElement* pElemCld = NULL;
		TiXmlElement* pElem = RootElement;
		vector<string>::iterator it = ret.begin();
		++it;
		for( ; it != ret.end(); ++it)
		{
			//循环创建子节点
			pElemCld = pElem->FirstChildElement( (*it).c_str() );
			if(pElemCld == NULL)
			{
				pElemCld = new TiXmlElement((*it).c_str());
				pElem->LinkEndChild(pElemCld);
			}
			pElem = pElemCld;
		}
		pNode = pElem;
	}
	catch(...)
	{
		return NULL;
	}
	return pNode;
}

wstring CXmlHelper::GetNodeValue(const wstring& strPath)
{	
	return S2WS(GetNodeValue(WS2S(strPath)));
}

string CXmlHelper::GetNodeValue(const string& strPath)
{
	TiXmlElement* pNode = GetNode(strPath);
	if(pNode == NULL)
		return "";

	return pNode->GetText();
}

bool CXmlHelper::SetNodeValue(const wstring& strPath, const wstring& strValue)
{
	return SetNodeValue(WS2S(strPath), WS2S(strValue));
}

bool CXmlHelper::SetNodeValue(const string& strPath, const string& strValue)
{
	TiXmlElement* pNode = CreateNode(strPath);//GetNode(strPath);
	if(pNode == NULL)
		return false;

	//添加节点下文本
	TiXmlText *pNameValue=new TiXmlText(strValue.c_str());
	pNode->LinkEndChild(pNameValue);

	return true;
}

wstring CXmlHelper::GetNodeAttr(const wstring& strPath, const wstring& strAttr)
{
	return S2WS(GetNodeAttr(WS2S(strPath), WS2S(strAttr)));
}

string CXmlHelper::GetNodeAttr(const string& strPath, const string& strAttr)
{
	TiXmlElement* pNode = GetNode(strPath);
	if(pNode == NULL)
		return "";

	return pNode->Attribute(strAttr.c_str());
}

bool CXmlHelper::SetNodeAttr(const wstring strPath, const wstring& strAttr, const wstring& strValue)
{	
	return SetNodeAttr(WS2S(strPath), WS2S(strAttr), WS2S(strValue));
}

bool CXmlHelper::SetNodeAttr(const string strPath, const string& strAttr, const string& strValue)
{	
	TiXmlElement* pNode = CreateNode(strPath); //GetNode(strPath);
	if(pNode == NULL)
		return false;

	pNode->SetAttribute(strAttr.c_str(), strValue.c_str());
	return true;
}

void CXmlHelper::Print()
{
	if(m_bLoad)
	{
		m_doc.Print();
	}
}