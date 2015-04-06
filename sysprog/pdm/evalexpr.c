//Build: gcc -Wall -DDEBUG -g evalexpr.c -o ee.exe

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

typedef enum tagTOK_E
{
	TOK_NONE,   
	TOK_ADD,      //'+'
	TOK_SUB,      //'-'
	TOK_MULTI,    //'*'
	TOK_DIV,      //'/'
	TOK_LPAREN,   //'('
	TOK_RPAREN,   //')'
	TOK_NUM,      //number
	TOK_NR
}TOK_E;

typedef struct tagLEX_T
{
	char*  pszBuff;
	size_t nReadPos;
	
	int    bUngetToken;
	TOK_E  eTokType;
	int    nTokVal;
}LEX_T, *PLEX_T;

TOK_E LEX_GetToken(PLEX_T thiz)
{
	assert(thiz != NULL && thiz->pszBuff != NULL);

	if(thiz == NULL || thiz->pszBuff == NULL || thiz->pszBuff[thiz->nReadPos] == '\0')
	{
		thiz->eTokType = TOK_NONE;
		
		return thiz->eTokType;
	}

	if(thiz->bUngetToken)
	{
		thiz->bUngetToken = !thiz->bUngetToken;
		
		return thiz->eTokType;
	}

	thiz->eTokType = TOK_NONE;

	while(thiz->pszBuff[thiz->nReadPos] != '\0')
	{
		switch(thiz->pszBuff[thiz->nReadPos])
		{
			case '+':
			{
				thiz->eTokType = TOK_ADD;
				break;
			}
			case '-':
			{
				thiz->eTokType = TOK_SUB;
				break;
			}
			case '*':
			{
				thiz->eTokType = TOK_MULTI;
				break;
			}
			case '/':
			{
				thiz->eTokType = TOK_DIV;
				break;
			}
			case '(':
			{
				thiz->eTokType = TOK_LPAREN;
				break;
			}
			case ')':
			{
				thiz->eTokType = TOK_LPAREN;
				break;
			}
			default:
			{
				if(isdigit(thiz->pszBuff[thiz->nReadPos]))
				{
					int nTokVal = 0;
					sscanf(thiz->pszBuff+thiz->nReadPos, "%d", &nTokVal);
					
					thiz->nTokVal = nTokVal;

					while(thiz->pszBuff[thiz->nReadPos] != '\0' && isdigit(thiz->pszBuff[thiz->nReadPos]))
					{
						++thiz->nReadPos;
					}

					thiz->eTokType = TOK_NUM;
				}
				else
				{
					//skip invalid cahr.
				}
				break;
			}
		}

		if(thiz->eTokType != TOK_NUM)
		{
			++thiz->nReadPos;
		}

		if(thiz->eTokType != TOK_NONE)
		{
			break;
		}
	}
	
	return thiz->eTokType;
}

void LEX_UngetToken(PLEX_T thiz)
{
	assert(thiz != NULL && thiz->pszBuff != NULL);

	thiz->bUngetToken = !thiz->bUngetToken;

	return;
}

//<FACTOR> ::= ( <EXPR> ) | number
int EvalFactor(PLEX_T pLex)
{
	int nVal = 0;
	TOK_E eTokType = LEX_GetToken(pLex);
	
	switch(eTokType)
	{
		case TOK_LPAREN:
		{
			nVal = EvalExpr(pLex);
			break;
		}
		case TOK_NUM:
		{
			nVal = pLex->nTokVal;
			break;
		}
		default:
		{
			//unexpected token.
			break;
		}
	}

	return nVal;
}

//<TERM>  ::= <FACTOR>  { <MULOP> <FACTOR> }
//<MULOP> ::= * | /
int EvalTerm(PLEX_T pLex)
{
	int nVal = EvalFactor(pLex);
	TOK_E eTokType = LEX_GetToken(pLex);
	
	while(eTokType == TOK_MULTI || eTokType == TOK_DIV)
	{
		if(eTokType == TOK_MULTI)
		{
			nVal *= EvalFactor(pLex);
		}
		else
		{
			nVal /= EvalFactor(pLex);
		}
		eTokType = LEX_GetToken(pLex);
	}

	LEX_UngetToken(pLex);
	
	return nVal;
}

//EXPR  ::= TERM { ADDOP TERM }
//ADDOP ::= + | -
int EvalExpr(PLEX_T pLex)
{
	int nVal = EvalTerm(pLex);
	TOK_E eTokType = LEX_GetToken(pLex);
	
	while(eTokType == TOK_ADD || eTokType == TOK_SUB)
	{
		if(eTokType == TOK_ADD)
		{
			nVal += EvalTerm(pLex);
		}
		else
		{
			nVal -= EvalTerm(pLex);
		}

		eTokType = LEX_GetToken(pLex);
	}

	//LEX_UngetToken(pLex);

	return nVal;
}

typedef struct tagTESTCASE_T
{
	int nVal;
	char* pszExpr;
}TESTCASE_T, *PTESTCASE_T;

TESTCASE_T g_aTestcase[] =
{
	{1, "1"},
	{2, "1+1"},
	{3, "1+1+1"},
	{4, "(1+1)*2"},
	{5, "2*2+1"},
	{6, "2+(2*2)"},
	{7, "(1+2)+(2*2)"},
	{8, "64/8)"},
	{9, "(82-1)/9)"},
	{0, "(64/8-8)"},
	{1, "  1  "},
	{2, "  1  +  1  "},
	{3, "  1  +  1  +  1"},
	{4, "  (  1  +  1  )  *  2  "},
	{5, "  2  *  2  +  1  "},
	{6, "  2  +  (  2  *  2  )"},
	{7, "  (  1  +  2  )  +  (  2  *  2  )  "},
	{8, "  64 /  8  ) "},
	{9, "  (  82 -  1  )  /  9  )  "},
	{0, "  (  64 /  8  -  8  )  "},
	{0, NULL}
};

int main(int argc, char* argv[])
{
	int i = 0;
	int nVal = 0;

	while(g_aTestcase[i].pszExpr != NULL)
	{
		LEX_T aLex = {0};
		aLex.pszBuff = g_aTestcase[i].pszExpr;
		aLex.nReadPos = 0;
		nVal = EvalExpr(&aLex);
		printf("%s=%d\n", g_aTestcase[i].pszExpr, nVal);
		assert(g_aTestcase[i].nVal == nVal);

		i++;
	}
	
	return 0;
}
