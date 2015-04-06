#ifndef COMM_XPATH_H
#define COMM_XPATH_H

#include "Common.h"

#include <string>
using std::string;

COMM_BEGIN()
	
class COMM_API CXPath
{
public:
	CXPath();
	~CXPath();
public:
	bool SetXPath(const string& strXPath);

	bool GetFirst(string& strName, size_t& nIndex);
	bool GetNext(string& strName, size_t& nIndex);

	bool SetDelimChar(char cDelimChar = '/');
	bool SetIndexStartChar(char cIndexStartChar = '[');
	bool SetIndexEndChar(char cIndexEndChar = ']');

private:
	string m_strXPath;
	size_t m_nPos;
	size_t m_nXPathLen;

	char m_cDelimChar;
	char m_cIndexStartChar;
	char m_cIndexEndChar;	
private:
	CXPath(const CXPath&);
	CXPath& operator=(const CXPath&);
};

COMM_END()

#endif//COMM_XPATH_H
