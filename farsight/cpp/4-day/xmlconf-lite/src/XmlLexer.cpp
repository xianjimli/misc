/*
 * XmlLexer.cpp
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
#include "Input.h"
#include "Output.h"
#include "StrUtil.h"

USE_COMM;

#include "XmlNode.h"
#include "XmlLexer.h"
#include "XmlConst.h"
#include "DebugUtil.h"

XML_BEGIN()

CLexer::CLexer()
{
	m_pInput = NULL;
	m_pUngetNode = NULL;
}

CLexer::~CLexer()
{
	if(m_pUngetNode != NULL)
	{
		delete m_pUngetNode;
		m_pUngetNode = NULL;
	}
}

bool CLexer::SetInput(CInput* pInput)
{
	m_pInput = pInput;

	return true;
}
	
bool CLexer::GetNode(CNode* &pNode)
{
	ASSERT(m_pInput != NULL);
	if(m_pUngetNode != NULL)
	{
		pNode = m_pUngetNode;
		m_pUngetNode = NULL;
		return true;
	}

	if(m_pInput != NULL)
	{
		pNode = this->ParseNode();
	}

	return (pNode != NULL);
}

CNode* CLexer::ParseNode(void)
{
	enum {ST_IN_NONE, ST_IN_TEXT, ST_IN_NAME, ST_BEFORE_ATTR_NAME, 
		ST_IN_ATTR_NAME, ST_BEFORE_ATTR_VAL, ST_IN_ATTR_VAL, 
		ST_IN_COMMENT, ST_IN_PI, ST_ACCEPT} nStat;
	nStat = ST_IN_NONE;
	
	int iChar = 0;
	bool bRet = false;
	char cQuato = '\0';
	string strName = "";
	string strVal = "";
	string strAttName = "";
	string strAttVal = "";

	CNode *pNode = new CNode();

	while(m_pInput->Get(iChar))
	{
		char c = (char) iChar;
		switch(nStat)
		{
			case ST_IN_NONE:
				{
					if(c == '<')
					{
						nStat = ST_IN_NAME;
						pNode->SetType(CNode::NT_START);
					}
					else
					{
						pNode->SetType(CNode::NT_TEXT);
						strVal += c;
						strName = STR_XML_TEXT_NAME;
						nStat = ST_IN_TEXT;
					}
					break;
				}
			case ST_IN_TEXT:
				{
					if(c == '<')
					{
						m_pInput->Unget(c);
						bRet = true;
					}
					else
					{
						strVal += c;
					}
					break;
				}
			case ST_IN_NAME:
				{
					if(isspace(c))
					{
						nStat = ST_BEFORE_ATTR_NAME;
					}
					else if(c == '>')
					{
						bRet = true;	
					}
					else if(c == '/')
					{
						if(strName.length() > 0)
						{
							nStat = ST_ACCEPT;
							pNode->SetType(CNode::NT_STARTEND);
						}
						else
						{
							pNode->SetType(CNode::NT_END);
						}
					}
					else if(strName[0] == '!')
					{
						pNode->SetType(CNode::NT_COMMENT);
						strName = STR_XML_COMMENT_NAME;
						strVal = "";

						nStat = ST_IN_COMMENT;
					}
					else if(strName[0] == '?')
					{
						pNode->SetType(CNode::NT_PI);
						strVal = strName;
						strVal += c;
						strName = STR_XML_PI_NAME;

						nStat = ST_IN_PI;
					}
					else
					{
						strName += c;
					}
					break;
				}
			case ST_IN_COMMENT://FIXME: may be cause problem if comment contains '>'.
			case ST_IN_PI:
				{
					if(c == '>')
					{
						string str;
						if(nStat == ST_IN_COMMENT)
						{
							CStrUtil::Trim(strVal, str, '-');
						}
						else
						{
							CStrUtil::Trim(strVal, str, '?');
						}

						strVal = str;
						bRet = true;
					}
					else
					{
						strVal += c;
					}
					break;
				}
			case ST_BEFORE_ATTR_NAME:
				{
					if(strAttName.length() != 0)
					{
						PRINTF3("%s=%s\n", strAttName.c_str(), strAttVal.c_str());
						pNode->SetAttVal(strAttName, strAttVal);
						strAttName = "";
						strAttVal = "";					
					}

					if(c == '/')
					{
						pNode->SetType(CNode::NT_STARTEND);
						nStat = ST_ACCEPT;		
					}
					else if(c == '>')
					{
						bRet = true;
					}
					else if(!isspace(c))
					{
						strAttName += c;	
						nStat = ST_IN_ATTR_NAME;
					}
					break;
				}
			case ST_IN_ATTR_NAME:
				{
					if(c == '/')
					{
						pNode->SetType(CNode::NT_STARTEND);
						nStat = ST_ACCEPT; 
					}
					else if(c == '>')
					{
						bRet = true;
					}
					else if(c == '=')
					{
						nStat = ST_BEFORE_ATTR_VAL;
					}
					else
					{
						strAttName += c;
					}
					break;
				}
			case ST_BEFORE_ATTR_VAL:
				{
					if(c == '/')
					{
						nStat = ST_ACCEPT;
					}
					else if(c == '>')
					{
						bRet = true;
					}
					else if(!isspace(c))
					{
						if(c == '\'' || c == '\"')
						{
							cQuato = c;
						}
						else
						{
							cQuato ='\0';
							strAttVal += c;
						}
						nStat = ST_IN_ATTR_VAL;
					}
					break;
				}
			case ST_IN_ATTR_VAL:
				{
					if(c == '/')
					{
						nStat = ST_ACCEPT;
					}
					else if(c == '>')
					{
						bRet = true;
					}
					else if(cQuato == c && (c == '\'' || c == '\"'))
					{
						nStat = ST_BEFORE_ATTR_NAME;
					}
					else if(isspace(c))
					{
						if(cQuato == '\'' || cQuato == '\"')
						{
							strAttVal += c;
						}
						else
						{
							nStat = ST_BEFORE_ATTR_NAME;
						}
					}
					else
					{
						strAttVal += c;
					}
					break;					
				}
			case ST_ACCEPT:
				{
					bRet = true;
					if(c == '/' && strVal.length() == 0)
					{
						pNode->SetType(CNode::NT_STARTEND);
					}
					else if(strName.length() > 0 && strName[0] == '/')
					{
						pNode->SetType(CNode::NT_END);
					}
				}
			default: break;
		}
		if(strName.length() > 0 && strName[0] == '/')
		{
			pNode->SetType(CNode::NT_END);
		}

		if(bRet) break;
	}

	if(!bRet) 
	{
		delete pNode;
		pNode = NULL;
	}
	else
	{
		pNode->SetName(strName);
		pNode->SetVal(strVal);
		if(strAttName.length() != 0) pNode->SetAttVal(strAttName, strAttVal);
	}
	return pNode;
}

bool CLexer::UngetNode(CNode* pNode)
{
	bool bRet = false;
	
	if(m_pUngetNode == NULL)
	{
		m_pUngetNode = pNode;
		bRet = true;
	}
	
	return bRet;
}

XML_END()

#ifdef XML_LEXER_TEST
#include "FileInput.h"
using namespace AV;
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s [xml file]\n", argv[0]);
		return 0;
	}
	
	CNode* pNode = NULL;
	string str;

	CLexer aLexer;
	CFileInput aFileInput;
	aFileInput.SetFile(string(argv[1]));
	
	aLexer.SetInput(&aFileInput);
	
	CNode::NODE_TYPE nType;
	while(aLexer.GetNode(pNode))
	{
		pNode->GetType(nType);
		pNode->GetName(str);
		switch(nType)
		{
			case CNode::NT_START:
				{
					printf("<%s>", str.c_str());
					break;
				}
			case CNode::NT_END:
				{
					printf("</%s>", str.c_str());
					break;
				}
			case CNode::NT_STARTEND:
				{
					printf("<%s/>", str.c_str());
					break;
				}
			case CNode::NT_TEXT:
				{
					pNode->GetVal(str);
					printf("%s", str.c_str());
					break;
				}
			default:
				{
					pNode->GetVal(str); 
					printf("<%s>", str.c_str());
					break;
				}
		}
	}
	aLexer.SetInput(NULL);
	return 0;
}
#endif//XML_LEXER_TEST

