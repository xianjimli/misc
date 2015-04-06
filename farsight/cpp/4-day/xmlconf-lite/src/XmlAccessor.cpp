/*
 * XmlAccessor.cpp
 * Copyright (C) 2006-2007 Li XianJing <xianjimli@hotmail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, 
 * Boston, MA 02111-1307, USA.
 */
#include "XPath.h"
#include "Output.h"

USE_COMM;

#include "XmlNode.h"
#include "XmlConst.h"
#include "XmlAccessor.h"

#include "DebugUtil.h"

XML_BEGIN()
		
CAccessor::CAccessor()
{
	m_pRoot = NULL;
}

CAccessor::~CAccessor()
{
	if(m_pRoot != NULL)
	{
		delete m_pRoot;
		m_pRoot = NULL;
	}
}

bool CAccessor::SetRootNode(CNode* pRoot)
{
	m_pRoot = pRoot;

	return true;
}

bool CAccessor::Save(COutput* pOutput, bool bAutoIndent) const
{
	ASSERT(m_pRoot != NULL);
	if(m_pRoot != NULL)
	{
		return m_pRoot->Output(pOutput, bAutoIndent);
	}
	return false;
}

bool CAccessor::Get(const string& strXPath, string& strVal) const
{
	string strPath;
	string strAttr;

	this->SplitXPath2PathAttr(strXPath, strPath, strAttr);

	const CNode* pNode = this->Find(strPath);
	bool bRet = false;
	
	if(pNode != NULL)
	{
		CNode::NODE_TYPE nType = CNode::NT_TEXT;
		pNode->GetType(nType);

		if(strAttr.length() == 0)
		{
			ASSERT(nType != CNode::NT_START);

			if(nType != CNode::NT_START)
			{
				bRet = pNode->GetVal(strVal);
			}
		}
		else
		{
			ASSERT(nType == CNode::NT_START || nType == CNode::NT_STARTEND);
			
			if(nType == CNode::NT_START || CNode::NT_STARTEND)
			{
				bRet = pNode->GetAttVal(strAttr, strVal);
			}
		}
	}
	
	return bRet;
}

bool CAccessor::Set(const string& strXPath, const string& strVal, bool bIfFailThenAdd)
{
	string strPath;
	string strAttr;
	bool bRet = false;

	this->SplitXPath2PathAttr(strXPath, strPath, strAttr);

	CNode* pNode = const_cast<CNode*>(this->Find(strPath));
	if(pNode == NULL && bIfFailThenAdd)
	{
		pNode = this->AddNode(strPath, strVal);
	}	
	
	if(pNode != NULL)
	{
		CNode::NODE_TYPE nType = CNode::NT_TEXT;
		pNode->GetType(nType);

		if(strAttr.length() == 0)
		{
			ASSERT(nType != CNode::NT_START);

			if(nType != CNode::NT_START)
			{
				bRet = pNode->SetVal(strVal);
			}
		}
		else
		{
			ASSERT(nType == CNode::NT_START || CNode::NT_STARTEND);
			
			if(nType == CNode::NT_START || CNode::NT_STARTEND)
			{
				bRet = pNode->SetAttVal(strAttr, strVal);
			}
		}
	}

	return bRet;
}

bool CAccessor::Del(const string& strXPath, const string& strVal)
{
	string strPath;
	string strAttr;

	this->SplitXPath2PathAttr(strXPath, strPath, strAttr);
	CNode* pNode = const_cast<CNode*>(this->Find(strPath));
	bool bRet = false;
	
	if(pNode != NULL)
	{
		if(strAttr.length() == 0)
		{
			CNode* pNext = pNode->GetNext();
			CNode* pPrev = pNode->GetPrev();
			CNode* pParent = pNode->GetParent();
			
			if(pNext != NULL)
			{
				pNext->SetPrev(pPrev);
				pNode->SetNext(NULL);
			}
			
			if(pPrev != NULL)
			{
				pPrev->SetNext(pNext);
				pNode->SetPrev(NULL);
			}
		
			if((pParent != NULL) && (pParent->GetChild() == pNode))
			{
				pParent->SetChild(pPrev != NULL?pPrev:pNext);
			}
				
			pNode->SetParent(NULL);
			
			if(pNode == m_pRoot)
			{
				m_pRoot = NULL;
			}
		
			delete pNode;
			pNode = NULL;

			bRet = true;
		}
		else
		{
			bRet = pNode->DelAttr(strAttr, strVal);
		}	
	}	
	return bRet;
}

bool CAccessor::SplitXPath2PathAttr(const string& strXPath, string& strPath, string& strAttr) const
{
	size_t nLen = strXPath.length();
	enum {ST_IN_PATH, ST_IN_ATTR};
	int nStat = ST_IN_PATH;

	strPath = "";
	strAttr = "";
	
	for(size_t i = 0; i < nLen; i++)
	{
		char c = strXPath[i];
		
		switch(nStat)
		{
			case ST_IN_PATH:
				{
					if(c == '@')
					{
						nStat = ST_IN_ATTR;
					}
					else
					{
						strPath += c;
					}
					break;
				}
			case ST_IN_ATTR:
				{
					strAttr += c;
					break;
				}
			default:break;
		}
	}

	return true;
}

const CNode* CAccessor::Find(const string& strXPath) const
{
	ASSERT(m_pRoot != NULL);
	if(m_pRoot == NULL) return NULL;

	CXPath XPath;
	XPath.SetXPath(strXPath);
	string strPathName;
	string strNodeName;
	size_t nIndex = 0;
	CNode* pNode =  NULL;
	
	pNode = m_pRoot->GetChild();

	bool bRet = XPath.GetNext(strPathName, nIndex);
	while(pNode != NULL)
	{
		while(pNode != NULL)
		{
			pNode->GetName(strNodeName);
#ifdef XML_ACCESS_TEST
			printf("%s:%s[%d]\n", strNodeName.c_str(), strPathName.c_str(), nIndex);
#endif//XML_ACCESS_TEST
			if(strNodeName == strPathName || strPathName.length() == 0)
			{
				if(nIndex == 0)
				{
					break;
				}
				else
				{
					nIndex--;
				}
			}
			
			if(pNode->GetNext())
			{
				pNode = pNode->GetNext();
			}
			else
			{
				return NULL;
			}
			
		}

		bRet = XPath.GetNext(strPathName, nIndex);
			
		if(pNode != NULL && bRet) 
		{
			if(pNode->GetChild())
			{
				pNode = pNode->GetChild();
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			break;
		}
	}

	return pNode;
}

CNode* CAccessor::AddNode(const string& strXPath, const string& strVal)
{
	ASSERT(m_pRoot != NULL);
	if(m_pRoot == NULL) return NULL;

	CXPath XPath;
	XPath.SetXPath(strXPath);
	string strPathName;
	string strNodeName;
	size_t nIndex = 0;
	CNode* pNode =  NULL;
	
	pNode = m_pRoot->GetChild();
	bool bRet = XPath.GetNext(strPathName, nIndex);

	CNode* pLastNode = pNode;
	while(pNode != NULL)
	{
		pLastNode = pNode;
		while(pNode != NULL)
		{
			pLastNode = pNode;
		
			pNode->GetName(strNodeName);
			if(strNodeName == strPathName || strPathName.length() == 0)
			{
				if(nIndex == 0)
				{
					break;
				}
				else
				{
					nIndex--;
				}
			}
			
			pNode = pNode->GetNext();
		}
		
		if(pNode == NULL)
		{
			do
			{
				pNode = this->AddNode(pLastNode, strPathName, strVal, CNode::NT_START);
			}while((nIndex--) != 0);
		}
		
		bRet = XPath.GetNext(strPathName, nIndex);
		PRINTF3("XPath.GetNext: %s[%d]\n", strPathName.c_str(), nIndex);
		if(!bRet) break;		

		if(pNode->GetChild())
		{
			pNode = pNode->GetChild();
		}
		else
		{
			pNode->SetChild(new CNode(strPathName, strVal, CNode::NT_START));
			pNode = pNode->GetChild();
		}
	}
	
	return pNode;
}

CNode* CAccessor::AddNode(CNode* pFirst, const string& strName, const string& strVal, int nType)
{
	PRINTF4("CAccessor::AddNode: %s = %s %d\n", strName.c_str(), strVal.c_str(), nType);	
	CNode* pNode = new CNode(strName, strVal, static_cast<CNode::NODE_TYPE>(nType));
	pFirst->InsertAtEnd(pNode);

	return pNode;
}

XML_END()

#ifdef XML_ACCESS_TEST
#include "XmlParser.h"
#include "XmlNode.h"
#include "FileInput.h"
using  namespace AV;

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s [xml] [xpath]\n", argv[0]);
		return 0;
	}
 
        CFileInput aFileInput;
        aFileInput.SetFile(argv[1]);
 
        CParser aParser;
 
        CNode* pNode = aParser.GetXMLDocument(&aFileInput);  

	CAccessor aAccessor;
	string strVal;

	aAccessor.SetRootNode(pNode);
	aAccessor.Get(string(argv[2]), strVal);

	printf("%s = %s\n", argv[2], strVal.c_str());
	return 0;
}
#endif//XML_ACCESS_TEST

