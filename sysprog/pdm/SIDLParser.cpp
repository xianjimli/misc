//
//File		: parser.cpp
//Author	: Li XianJim<xianjinglee@yahoo.com.cn>
//Create	: 2003-5-1
//Update	:
//===========================================================================
//
//

#include <list>
#include <string>
using namespace std;

#include "templategen.h"
#include "token.h"
#include "node.h"
#include "lexer.h"
#include "parser.h"
#include "DebugUtil.h"
#include "uihandler.h"

XJ_BEGIN()
TG_BEGIN()

CParser::CParser(void)
{
	m_pRootNode = NULL;
	m_pLexer = NULL;

	return;
}

CParser::~CParser(void)
{
	return;
}

CNode* CParser::Parse(CLexer* pLexer, CUIHandler* pUIHandler)
{
	ASSERT(pLexer != NULL && pUIHandler != NULL);
	if(pLexer == NULL || pUIHandler == NULL)
	{
		return NULL;
	}
	else
	{
		m_pLexer = pLexer;
		m_pUIHandler = pUIHandler;
		m_pRootNode = new CNode(NULL, STR_TYPE_ROOT, STR_TYPE_ROOT, NT_AST_ROOT);

		return this->Parse();
	}
}

CNode* CParser::Parse(void)
{
	if(this->MatchToken(TK_CLASS))
	{
		this->ParseClass(m_pRootNode);
	}
	else
	{
		m_pUIHandler->OnExpectToken(STR_TYPE_CLASS, m_aToken.Row(), m_aToken.Col());
	}

	return m_pRootNode;
}

//
// <Class> ::= "class" <ClassName> '{' <FunctionList> '}'
//
void CParser::ParseClass(CNode* pNode)
{
	if(this->MatchToken(TK_NAME))
	{
		CNode* pClassNode = new CNode(pNode, m_aToken.Name(), STR_TYPE_CLASS, NT_AST_CLASS);

		if(this->MatchToken(TK_LBRACE))
		{
			this->ParseFunctionList(pClassNode);
		}
		else
		{
			m_pUIHandler->OnExpectToken("{", m_aToken.Row(), m_aToken.Col());
		}
	}
	else
	{
		m_pUIHandler->OnUnexpectedToken(m_aToken.Name(), m_aToken.Row(), m_aToken.Col());
	}
	
	this->MatchToken(TK_RBRACE);
	this->MatchToken(TK_SEMICOLON);

	return;
}

//
// <FunctionList>  ::= <Function> ; | <Function> ; <FunctionList>
//
void CParser::ParseFunctionList(CNode* pNode)
{
	while(this->MatchToken(TK_UNKNOWN))
	{
		if(m_aToken.Type() == TK_NAME)
		{
			this->ParseFunction(pNode);
		}
		else if(m_aToken.Type() == TK_SEMICOLON)
		{
			continue;
		}
		else if(m_aToken.Type() == TK_RBRACE)
		{
			this->UngetToken();
			break;
		}
		else
		{
			m_pUIHandler->OnUnexpectedToken(m_aToken.Name(), m_aToken.Row(), m_aToken.Col());
		}
	}

	return;
}

//
// <Function> ::= FunctionName '(' <ArgumentList> ')'
//
void CParser::ParseFunction(CNode* pNode)
{
	CNode* pFunctionNode = new CNode(pNode, m_aToken.Name(), STR_TYPE_FUNCTION, NT_AST_FUNCTION);
	
	if(this->MatchToken(TK_LPAREN))
	{
		this->ParseArgumentList(pFunctionNode);
	}
	else
	{
		m_pUIHandler->OnExpectToken("(", m_aToken.Row(), m_aToken.Col());
	}
	
	if(!this->MatchToken(TK_RPAREN))
	{
		m_pUIHandler->OnExpectToken(")", m_aToken.Row(), m_aToken.Col());
	}
	
	this->MatchToken(TK_SEMICOLON);

	return;
}

//
// <ArgumentList> =<Argument> | <Argument> <ArgumentList>
// <Argument> ::= <SimpleArgument> | <StructArugment>
//
void CParser::ParseArgumentList(CNode* pNode)
{
	while(this->MatchToken(TK_UNKNOWN))
	{
		if(m_aToken.Type() == TK_STRUCT)
		{
			this->ParseStructArgument(pNode);
		}
		else if(m_aToken.Type() == TK_NAME)
		{
			this->ParseSimpleArgument(pNode);
		}	
		else if(m_aToken.Type() == TK_COMMA)
		{
			continue;
		}
		else
		{
			this->UngetToken();
			break;
		}
		continue;
	}

	return;
}

//
// <SimpleArgument> ::= BuiltinType Name 
//
void CParser::ParseSimpleArgument(CNode* pNode)
{
	string strTypeName = m_aToken.Name();

	if(this->MatchToken(TK_NAME))
	{
		CNode* pArgumentNode = new CNode(pNode, m_aToken.Name(), strTypeName, NT_AST_ARGUMENT); 
		pArgumentNode = pArgumentNode;//disable warning.
	}
	else
	{
		m_pUIHandler->OnExpectToken("Argument Name", m_aToken.Row(), m_aToken.Col());
	}
	
	return ;
}

//
//<StructArugment> ::= "struct" StructName '{' <ArgumentList> '}'
//
void CParser::ParseStructArgument(CNode* pNode)
{
	if(this->MatchToken(TK_NAME))
	{
		CNode* pStructNode = new CNode(pNode, m_aToken.Name(), STR_TYPE_STRUCT, NT_AST_STRUCT);
		
		if(this->MatchToken(TK_LBRACE))
		{
			this->ParseArgumentList(pStructNode);
		}
		else
		{
			m_pUIHandler->OnExpectToken("{", m_aToken.Row(), m_aToken.Col());
		}

		if(!this->MatchToken(TK_RBRACE))
		{
			m_pUIHandler->OnExpectToken("}", m_aToken.Row(), m_aToken.Col());
		}
	}

	return;
}

bool CParser::MatchToken(token_t nType)
{
	m_aToken = m_pLexer->GetToken();
	if(nType != TK_UNKNOWN && m_aToken.Type() != nType)
	{
		m_pLexer->UngetToken(m_aToken);
		return false;
	}
	else if(m_aToken.Type() == TK_EOF)
	{
		return false;
	}
	else
	{
		m_pUIHandler->OnToken(m_aToken.Name(), m_aToken.Row(), m_aToken.Col());
		return true;
	}
}

void CParser::UngetToken(void)
{
	m_pLexer->UngetToken(m_aToken);
}

TG_END()
XJ_END()

#ifdef TG_PARSER_TEST_H
#include <iostream>
#include "testcase.h"
#include "nodedumper.h"

int main(int argc, char* argv[])
{
	size_t i = 0;
	while(pszTestCase[i] != NULL)
	{
		CUIHandler aUIHandler;
		CLexer aLexer(pszTestCase[i], &aUIHandler);	
		CParser aParser;
		CNodeDumper aNodeDumper;

		CNode* pRootNode = aParser.Parse(&aLexer, &aUIHandler);
		pRootNode->Accept(aNodeDumper);

		CNode::ReleaseNode(pRootNode);
		i++;
	}

	return 0;
}
#endif//TG_PARSER_TEST_H
