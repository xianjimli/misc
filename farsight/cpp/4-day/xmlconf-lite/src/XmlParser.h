/*
 * XmlParser.h
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
#ifndef XML_PARSER_H
#define XML_PARSER_H

XML_BEGIN()

class CNode;
class CLexer;

class CParser
{
public:
	CParser();
	~CParser();
public:	
	CNode* GetXMLDocument(CInput* pInput);

private:
	bool Parse(CNode* pParent); 
	bool IsEndNodeOfParent(CNode* pEndNode, CNode* pStartNode);
	bool IsEndNodeOf(CNode* pEndNode, CNode* pStartNode);
private:
	CInput* m_pInput;
	CLexer* m_pLexer;
	CNode* m_pRoot;
	CNode* m_pCurrent;
private:
	CParser(const CParser&);
	CParser& operator=(const CParser&);
};//class CParser

XML_END()

#endif//XML_PARSER_H
