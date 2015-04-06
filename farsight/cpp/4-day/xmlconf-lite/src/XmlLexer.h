/*
 * XmlLexer.h
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
#ifndef XML_XML_CONF_LEXER_H
#define XML_XML_CONF_LEXER_H

XML_BEGIN()
		
class CNode;
class CLexer
{
public: 
	CLexer();
	~CLexer();
public:
	bool SetInput(CInput* pInput);
	
	bool GetNode(CNode* &pNode);
	bool UngetNode(CNode* pNode);
private:
	CNode* ParseNode(void);
private:
	CInput* m_pInput;
	CNode* m_pUngetNode;
private:
	CLexer(const CLexer&);
	CLexer& operator=(const CLexer&);
};

XML_END()

#endif//XML_XML_CONF_LEXER_H

