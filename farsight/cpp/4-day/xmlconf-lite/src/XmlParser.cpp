/*
 * XmlParser.cpp
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
#include "Input.h"
#include "Output.h"

USE_COMM;

#include "XmlNode.h"
#include "XmlLexer.h"
#include "DebugUtil.h"
#include "XmlParser.h"

XML_BEGIN()

CParser::CParser()
{
	m_pInput = NULL;
	m_pRoot = NULL;
	
	m_pLexer = new CLexer();
	return;
}

CParser::~CParser()
{
	delete m_pLexer;
	m_pLexer = NULL;

	return;
}

CNode* CParser::GetXMLDocument(CInput* pInput)
{
	m_pInput = pInput;
	bool bRet = false;
	ASSERT(pInput != NULL);

	if(pInput != NULL)
	{
		m_pLexer->SetInput(m_pInput); 
			
		m_pRoot = new CNode();
		m_pRoot->SetType(CNode::NT_ROOT);

		bRet = this->Parse(m_pRoot);

	}

	if(!bRet)
	{
		m_pRoot->SetChild(new CNode("<none>", "<none>", CNode::NT_NONE));
	}

	return m_pRoot;
}

bool CParser::Parse(CNode* pParent)
{
	CNode* pNode = NULL;
	CNode* pLastNode = NULL;
	bool bRet = false;
	
	while(m_pLexer->GetNode(pNode))
	{
		bRet = true;

		CNode::NODE_TYPE nType = CNode::NT_TEXT;
		pNode->GetType(nType);
		
		if(pLastNode == NULL)
		{
			pParent->SetChild(pNode);
		}

		if(nType == CNode::NT_END)
		{
			if(this->IsEndNodeOf(pNode, pParent))
			{
				delete pNode;
				pNode = NULL;
				break;
			}
			else if(this->IsEndNodeOfParent(pNode, pParent))
			{
				m_pLexer->UngetNode(pNode);
				PRINTF1("Missing end tag.\n");
				break;
			}
			else
			{
				delete pNode;
				pNode = NULL;
				PRINTF1("Unexpected: end tag\n");
				continue;
			}
		}
		
		if(pLastNode != NULL)
		{
			pLastNode->SetNext(pNode);
		}
		
		if(nType == CNode::NT_TEXT 
				|| nType == CNode::NT_COMMENT 
				|| nType == CNode::NT_PI 
				|| nType == CNode::NT_STARTEND)
		{
		}
		else
		{
			this->Parse(pNode);
		}

		pLastNode = pNode;
	}

	return bRet;
}

bool CParser::IsEndNodeOfParent(CNode* pEndNode, CNode* pStartNode) 
{
	ASSERT(pEndNode != NULL);
	ASSERT(pStartNode != NULL);

	CNode* pParent = NULL;
	CNode* pTempNode = pStartNode;
	
	bool bRet = false;

	if(pEndNode != NULL && pStartNode != NULL)
	{
		while((pParent = pTempNode->GetParent()) != NULL)
		{
			if(IsEndNodeOf(pEndNode, pParent))
			{
				bRet = true;
				break;
			}
			pTempNode = pParent;
		}
	}

	return bRet;
}

bool CParser::IsEndNodeOf(CNode* pEndNode, CNode* pStartNode)
{
	string strEndName;
	string strStartName;
	
	bool bRet = false;
	ASSERT(pEndNode != NULL);
	ASSERT(pStartNode != NULL);
	
	if(pEndNode != NULL && pStartNode != NULL)
	{
		pEndNode->GetName(strEndName);
		pStartNode->GetName(strStartName);
		bRet = (strEndName == strStartName);
	}

	return bRet;
}

XML_END()

#ifdef XML_PARSER_TEST
using namespace AV;
#include <stdio.h>
#include <stdlib.h>
#include "XmlLexer.h"
#include "FileInput.h"
#include "XmlNode.h"
#include "FileOutput.h"
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s [xml file]\n", argv[0]);
		return 0;
	}
	
	CFileInput aFileInput;
	aFileInput.SetFile(argv[1]);
	
	CParser aParser;
	
	CNode* pNode = aParser.GetXMLDocument(&aFileInput);
	if(pNode != NULL)
	{
		CFileOutput aOutput;
		aOutput.SetFile(stdout);
		pNode->Output(&aOutput);
	}
	delete pNode;
	return 0;
}
#endif//XML_PARSER_TEST
