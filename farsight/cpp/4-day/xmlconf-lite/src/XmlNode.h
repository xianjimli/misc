/*
 * XmlNode.h
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
#ifndef XML_XML_CONF_NODE_H
#define XML_XML_CONF_NODE_H

#include "Xml.h"

#include <string>
#include <map>
using namespace std;

XML_BEGIN()

class CAttr;
class CNode
{
public:
	typedef enum {NT_NONE, NT_START, NT_END, NT_STARTEND, NT_TEXT, NT_COMMENT, NT_PI, NT_ROOT} NODE_TYPE;

	CNode();
	CNode(const string& strName, const string& strVal, NODE_TYPE nType);
	~CNode();
public:
	bool GetName(string& strName) const;
	bool GetVal(string& strVal) const;
	bool GetAttVal(const string& strName, string& strVal) const;
	bool GetType(NODE_TYPE& nType) const;

	bool SetName(const string& strName);
	bool SetVal(const string& strVal);
	bool SetAttVal(const string& strName, const string& strVal);
	bool SetType(NODE_TYPE nType);
	bool DelAttr(const string& strName, const string& strVal);

	bool SetParent(CNode* pParent);
	bool SetNext(CNode* pNext);
	bool SetPrev(CNode* pPrev);
	bool SetChild(CNode* pChild);

	CNode* GetParent(void);
	const CNode* GetParent(void) const;
	
	CNode* GetNext(void );
	const CNode* GetNext(void ) const;
	
	CNode* GetPrev(void);
	const CNode* GetPrev(void) const;
	
	CNode* GetChild(void);
	const CNode* GetChild(void) const;

	bool InsertAtEnd(CNode* pLast);

	size_t GetIndentLevel(void) const;

	bool Output(COutput* pOutput, bool bAutoIndent) const;
#ifdef _DEBUG
	static size_t s_nTotalCount;
#endif//_DEBUG
private:
	bool Release(void);
private:
	string m_strName;
	string m_strVal;
	NODE_TYPE m_nType;
	CAttr* m_pAttr;
	CNode* m_pParent;
	CNode* m_pNext;
	CNode* m_pPrev;
	CNode* m_pChild;

private:
	bool IsEmptyTextNode(void);
	bool IndentEnd(COutput* pOutput, bool bAutoIndent) const;
	bool IndentStart(COutput* pOutput, bool bAutoIndent) const;
	CNode(const CNode&);
	CNode& operator=(const CNode&);
};

class CAttr
{
public:
	CAttr();
	~CAttr();
	typedef map<string, string>::iterator ITER;
	typedef map<string, string>::const_iterator CITER;
public:
	bool Del(const string& strName);
	bool GetVal(const string& strName, string& strVal) const;
	bool SetVal(const string& strName, const string& strVal);

	bool Output(COutput* pOutput);
private:
	map<string, string> m_AttrData;
private:
	CAttr(const CAttr&);
	CAttr& operator=(const CAttr&);
};

XML_END()

#endif//XML_XML_CONF_NODE_H
