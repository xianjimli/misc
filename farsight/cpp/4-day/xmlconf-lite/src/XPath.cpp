#include <stdlib.h>
#include "XPath.h"

COMM_BEGIN()
	
CXPath::CXPath()
{
	m_nPos = 0;
	m_nXPathLen = 0;
	m_cDelimChar = '/';
	m_cIndexStartChar = '[';
	m_cIndexEndChar = ']';

	return;
}

CXPath::~CXPath()
{
	return;
}

bool CXPath::SetXPath(const string& strXPath)
{
	m_strXPath = strXPath;
	m_nPos = 0;
	m_nXPathLen = strXPath.length();

	return (m_nXPathLen != 0);
}

bool CXPath::GetFirst(string& strName, size_t& nIndex)
{
	m_nPos = 0;

	return this->GetNext(strName, nIndex);
}

bool CXPath::GetNext(string& strName, size_t& nIndex)
{

	enum {ST_BEFORE_NAME, ST_IN_NAME, ST_IN_INDEX, ST_ACCEPT};
	int nStat = ST_BEFORE_NAME;
	bool bRet = false;

	string strIndex;
	strName = "";
	while(m_nPos < m_nXPathLen)
	{
		char c = m_strXPath[m_nPos];
		m_nPos++;
		switch(nStat)
		{
			case ST_BEFORE_NAME:
				{
					if(c == m_cDelimChar)
					{
						nStat = ST_IN_NAME;
					}
					else if(c == m_cIndexStartChar)
					{
						nStat = ST_IN_INDEX;
					}	
					else
					{
						strName += c;
						nStat = ST_IN_NAME;
					}
					break;
				}
			case ST_IN_NAME:
				{
					if(c == m_cDelimChar)
					{
						bRet = true;	
					}
					else if(c == m_cIndexStartChar)
					{
						nStat = ST_IN_INDEX;
					}
					else
					{
						strName += c;
					}
					break;
				}
			case ST_IN_INDEX:
				{
					if(c == m_cDelimChar || c == m_cIndexEndChar)
					{
						bRet = true;
					}
					else
					{
						strIndex += c;
					}
					break;
				}
			case ST_ACCEPT:
				{
					bRet = true;
					break;
				}
			default: break;
		}

		if(bRet) break;
	}

	if(strIndex.length() != 0) nIndex = atoi(strIndex.c_str());
	else nIndex = 0;
	
	return (m_nPos < m_nXPathLen || strName.length() != 0);
}

bool CXPath::SetDelimChar(char cDelimChar)
{
	m_cDelimChar = cDelimChar;
	return true;
}

bool CXPath::SetIndexStartChar(char cIndexStartChar)
{
	m_cIndexStartChar = cIndexStartChar;
	return true;
}

bool CXPath::SetIndexEndChar(char cIndexEndChar)
{
	m_cIndexEndChar = cIndexEndChar;
	return true;
}

#ifdef XPATH_TEST
#include <stdio.h>
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s [XPATH]\n");
		return -1;
	}
	
	CXPath XPath;
	XPath.SetXPath(string(argv[1]));
	string str;
	size_t n;
	
	bool bRet =  XPath.GetFirst(str, n);
	while(bRet)
	{
		printf("%s[%u]\n", str.c_str(), n);
		bRet = XPath.GetNext(str, n);
	}

	return 0;
}
#endif//XPATH_TEST

COMM_END()
