/*
 * XmlNode.cpp
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
#include <ctype.h>
#include "Output.h"
#include "StrUtil.h"

USE_COMM;

#include "XmlNode.h"
#include "XmlConst.h"
#include "DebugUtil.h"

XML_BEGIN()
	
#ifdef _DEBUG
size_t CNode::s_nTotalCount = 0;	
#endif//_DEBUG	

CNode::CNode()
{
	m_pAttr = new CAttr();
	m_pParent = NULL;
	m_pNext = NULL;
	m_pPrev = NULL;
	m_pChild = NULL;
	m_nType = CNode::NT_START;
#ifdef _DEBUG
	CNode::s_nTotalCount ++;
#endif//_DEBUG
	return;
}

CNode::CNode(const string& strName, const string& strVal, CNode::NODE_TYPE nType)
{
	m_pAttr = new CAttr();
	m_pParent = NULL;
	m_pNext = NULL;
	m_pPrev = NULL;
	m_pChild = NULL;

	if(strName == string(STR_XML_TEXT_NAME))
	{
		nType = CNode::NT_TEXT;
	}
	else if(strName == string(STR_XML_PI_NAME))
	{
		nType = CNode::NT_PI;
	}
	else if(strName == string(STR_XML_COMMENT_NAME))
	{
		nType = CNode::NT_COMMENT;
	}

	m_strName = strName;
	m_strVal = strVal;
	m_nType = nType;
	
#ifdef _DEBUG
	CNode::s_nTotalCount ++;
#endif//_DEBUG
	return;
}
		
CNode::~CNode()
{
	this->Release();
	if(m_pAttr != NULL)
	{
		delete m_pAttr;
		m_pAttr = NULL;
	}
#ifdef _DEBUG
	CNode::s_nTotalCount --;
	if(CNode::s_nTotalCount == 0)
	{
		PRINTF1("Great! no memory leak for CNode!\n");
	}
#endif//_DEBUG
	return;
}

bool CNode::GetName(string& strName) const
{
	strName = m_strName;

	return true;
}

bool CNode::GetVal(string& strVal) const
{
	strVal = m_strVal;
	
	return true;
}

bool CNode::GetAttVal(const string& strName, string& strVal) const
{
	ASSERT(m_pAttr != NULL);
	bool bRet = false;

	if(m_pAttr != NULL)
	{
		bRet = m_pAttr->GetVal(strName, strVal);
	}

	return bRet;
}

bool CNode::GetType(NODE_TYPE& nType) const
{
	nType = m_nType;

	return true;
}

bool CNode::SetName(const string& strName)
{
	CStrUtil::Trim(strName, m_strName, ' ');

	return true;
}

bool CNode::SetVal(const string& strVal)
{
	m_strVal = strVal;

	return true;
}

bool CNode::SetAttVal(const string& strName, const string& strVal)
{
	ASSERT(m_pAttr != NULL);
	bool bRet = false;
	if(m_pAttr != NULL)
	{
		bRet = m_pAttr->SetVal(strName, strVal);
	}

	return bRet;
}

bool CNode::SetType(NODE_TYPE nType)
{
	m_nType = nType;

	return true;
}

bool CNode::DelAttr(const string& strName, const string& strVal)
{
	return m_pAttr->Del(strName);
}

bool CNode::SetParent(CNode* pParent)
{
	m_pParent = pParent;

	return true;
}

bool CNode::SetNext(CNode* pNext)
{
	m_pNext = pNext;
	if(m_pNext != NULL)
	{
		m_pNext->m_pParent = m_pParent;
		m_pNext->m_pPrev = this;
	}
	
	return true;
}

bool CNode::SetPrev(CNode* pPrev)
{
	m_pPrev = pPrev;
	if(m_pPrev != NULL)
	{
		m_pPrev->m_pParent = m_pParent;
		m_pPrev->m_pNext = this;
	}
	
	return true;
}

bool CNode::SetChild(CNode* pChild)
{
	m_pChild = pChild;
	if(m_pChild != NULL)
	{
		m_pChild->m_pParent = this;
	}
	
	return true;
}

CNode* CNode::GetParent(void)
{
	return m_pParent;
}

const CNode* CNode::GetParent(void) const
{
	return m_pParent;
}
	
CNode* CNode::GetNext(void)
{
	return m_pNext;
}

const CNode* CNode::GetNext(void) const
{
	return m_pNext;
}
	
CNode* CNode::GetPrev(void)
{
	return m_pPrev;
}

const CNode* CNode::GetPrev(void) const
{
	return m_pPrev;
}

CNode* CNode::GetChild(void)
{
	return m_pChild;
}

const CNode* CNode::GetChild(void) const
{
	return m_pChild;
}

size_t CNode::GetIndentLevel(void) const
{
	const CNode* pParent = m_pParent;
	size_t nIndentLevel = 0;
	
	while(pParent != NULL && pParent->m_nType != CNode::NT_ROOT)
	{
		pParent = pParent->m_pParent;
	}
	
	return nIndentLevel;
}

bool CNode::InsertAtEnd(CNode* pLast)
{
	CNode* pNode = this;
	while(pNode->m_pNext != NULL)
	{
		pNode = pNode->m_pNext;
	}

	pNode->SetNext(pLast);
	return true;
}

bool CNode::Output(COutput* pOutput, bool bAutoIndent) const
{
	ASSERT(pOutput != NULL);
	if(pOutput != NULL)
	{
		string strName;
		this->GetName(strName);
		string strVal;
		this->GetVal(strVal);
		const CNode* pNode = this;
		if(m_nType != NT_TEXT && m_nType != NT_ROOT)
		{
			this->IndentStart(pOutput, bAutoIndent);
		}
		switch(m_nType)
		{
			case CNode::NT_START:
			case CNode::NT_STARTEND:
				{
					pOutput->Put('<');
					pOutput->Put(strName.c_str(), strName.length());
					if(m_pAttr != NULL) m_pAttr->Output(pOutput);
					pOutput->Put('>');

					if((pNode = this->GetChild()) != NULL)
					{
						pNode->Output(pOutput, bAutoIndent);
					}
					
					this->IndentEnd(pOutput, bAutoIndent);

					pOutput->Put('<');
					pOutput->Put('/');
					pOutput->Put(strName.c_str(), strName.length());
					pOutput->Put('>'); 
					if(bAutoIndent 
						&& (m_pNext == NULL || m_pNext->m_nType != NT_TEXT))
					{
						pOutput->Put('\n'); 
					}
					break;
				}
			case CNode::NT_COMMENT:
				{
					pOutput->Put("<!--", 4);
					pOutput->Put(strVal.c_str(), strVal.length());
					pOutput->Put("-->", 3);
					break;
				}
			case CNode::NT_PI:
				{
					pOutput->Put("<?", 2);
					pOutput->Put(strVal.c_str(), strVal.length());
					pOutput->Put("?>", 2);
					break;
				}
			case CNode::NT_TEXT:
				   {
					   if(bAutoIndent)
					   {
						   string str;
						   CStrUtil::Trim(m_strVal, str, ' ');
						   if(str.length() > 0)
						   {
							   pOutput->Put(str.c_str(), str.length());
						   }
						   else
						   {
							   pOutput->Put(m_strVal.c_str(), m_strVal.length());
						   }
					   }
					   else
					   {
							pOutput->Put(m_strVal.c_str(), m_strVal.length());
					   }
					   break;
				   }
			case CNode::NT_ROOT:
				   {
					   if((pNode = this->GetChild()) != NULL) pNode->Output(pOutput, bAutoIndent);
				   }
			default:break;
		}

		if((pNode = this->GetNext()) != NULL) pNode->Output(pOutput, bAutoIndent);
	}
	return true;
}

bool CNode::Release(void)
{
	CNode* pChild = this->GetChild();
	this->SetChild(NULL);

	if(pChild != NULL)
	{
		CNode* pNode = pChild;
		CNode* pNext = pChild;
		while(pNode != NULL)
		{
			pNext = pNode->GetNext();
			delete pNode;
			pNode = pNext;
		}
	}

	CNode* pParent = this->GetParent();
	if(pParent != NULL && pParent->GetChild() == this)
	{
		if(pParent != NULL) pParent->SetChild(NULL);
	}

	return true;
}

CAttr::CAttr()
{
}

CAttr::~CAttr()
{
}

bool CAttr::GetVal(const string& strName, string& strVal) const
{
	 CITER i = m_AttrData.find(strName);
	 if(i != m_AttrData.end())
	 {
		 strVal = i->second;
		 return true;
	 }

	 return false;
}

bool CAttr::SetVal(const string& strName, const string& strVal)
{
	string _strName = strName;
	CStrUtil::Trim(strName, _strName, ' ');
	PRINTF3("CAttr::SetVal: %s = %s\n", strName.c_str(), strVal.c_str());
	m_AttrData[_strName] = strVal;

	return true;
}

bool CAttr::Output(COutput* pOutput)
{
	bool bRet = false;
	
	if(pOutput != NULL)
	{
		for(map<string, string>::iterator i = m_AttrData.begin();
				i != m_AttrData.end(); i++)
		{
			if(i->first.length() > 0)
			{	
				pOutput->Put(' ');
				pOutput->Put(i->first.c_str(), i->first.length());
			}
			else
			{
				continue;
			}
			
			pOutput->Put('=');
			
			pOutput->Put('\"');
			if(i->second.length() > 0)
			{
				pOutput->Put(i->second.c_str(), i->second.length());
			}
			pOutput->Put('\"');
		}
	}

	return bRet;
}

bool CNode::IndentStart(COutput *pOutput, bool bAutoIndent) const
{
	if(bAutoIndent)
	{
		switch(m_nType)
		{
		case NT_START:
		case NT_STARTEND:
		case NT_PI:
		case NT_COMMENT:
			{
				if(m_pPrev == NULL && m_pParent->m_nType != NT_ROOT)
				{
					pOutput->Put('\n');
				}
				break;
			}
		case NT_TEXT:
			{
				break;
			}
		default:break;
		}
	}
	return true;
}

bool CNode::IndentEnd(COutput *pOutput, bool bAutoIndent) const
{
	if(bAutoIndent)
	{
		switch(m_nType)
		{
		case NT_START:
		case NT_STARTEND:
			{
				break;
			}
		case NT_PI:
		case NT_COMMENT:
		case NT_TEXT:
		default:break;
		}
	}
	return true;
}

bool CNode::IsEmptyTextNode()
{
	size_t nLen = m_strVal.length();
	if(nLen == 0) return true;

	for(size_t i = 0; i < nLen; i++)
	{
		if(!isspace(m_strVal[i])) return false;
	}
	
	return true;
}

bool CAttr::Del(const string &strName)
{
	map<string, string>::iterator iter = m_AttrData.find(strName);
	if(iter != m_AttrData.end())
	{
		m_AttrData.erase(iter);
	}
	return true;
}

XML_END()






