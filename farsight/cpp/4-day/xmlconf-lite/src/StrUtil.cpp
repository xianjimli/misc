/*
 * StrUtil.cpp
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
#include <cstdio>
#include <ctype.h>
#include "StrUtil.h"
#include <strings.h>

COMM_BEGIN()

#ifdef WIN32
#define strcasecmp stricmp
#endif//WIN32

bool CStrUtil::StrToLong(const string& strVal, long& nVal)
{
	bool bRet = false;
	if(strVal.length() != 0)
	{
		bRet = (1 == sscanf(strVal.c_str(), "%ld", &nVal));
	}
	return bRet;
}

bool CStrUtil::LongToStr(long nValue, string& str)
{
	char szBuff[20] = {0};
	sprintf(szBuff, "%ld", nValue);
	str = szBuff;

	return true;
}

bool CStrUtil::TrimLeft(const string& strFrom, string& strTo, char cTrim)
{
	size_t nLen = strFrom.length();
	size_t nStart = 0;
	strTo = "";
	if(0 == nLen) return false;

	if(' ' == cTrim)
	{
		while((nStart < nLen) && isspace(strFrom[nStart])) nStart++;
	}
	else
	{
		while((nStart < nLen) && (strFrom[nStart] == cTrim)) nStart++;
	}

	strTo = strFrom.substr(nStart, (nLen - nStart + 1));

	return true;
}

bool CStrUtil::TrimRight(const string& strFrom, string& strTo, char cTrim)
{
	size_t nLen = strFrom.length();
	long nEnd = nLen - 1;
	strTo = "";
	if(0 == nLen) return false;

	if(' ' == cTrim)
	{
		while((nEnd > -1) && (isspace(strFrom[nEnd]))) nEnd--;
	}
	else
	{
		while((nEnd > -1) && (strFrom[nEnd] == cTrim)) nEnd--;
	}

	if(nEnd > -1)
	{
		strTo = strFrom.substr(0, (nEnd + 1));
	}	
	else
	{
		strTo = "";
	}

	return true;
}

bool CStrUtil::Trim(const string& strFrom, string& strTo, char cTrim)
{
	string str;
	if(strFrom.length() == 0) return false;

	TrimLeft(strFrom, str, cTrim);
	TrimRight(str, strTo, cTrim);

	return true;
}

int CStrUtil::StrCaseCmp(const string& strA, const string& strB)
{
	int nRet = 0;
	const char* pszA = strA.c_str();
	const char* pszB = strB.c_str();
	
	if((pszA == NULL) && (pszB == NULL))
	{
		nRet = 0;
	}
	else if(pszA == NULL)
	{
		nRet = -1;
	}
	else if(pszB == NULL)
	{
		nRet = 1;
	}
	else
	{
		nRet = strcasecmp(pszA, pszB);
	}

	return nRet;
}

bool CStrUtil::ToUpper(const string& strFrom, string& strTo)
{
	size_t nLen = strFrom.length();
	
	strTo.resize(nLen+1);
	strTo = "";
	for(size_t i = 0; i < nLen; i++)
	{
		strTo += toupper(strFrom[i]);
	}

	return true;
}

bool CStrUtil::ToLower(const string& strFrom, string& strTo)
{
	size_t nLen = strFrom.length();

	strTo.resize(nLen+1);
	strTo = "";
	for(size_t i = 0; i < nLen; i++)
	{
		strTo += tolower(strFrom[i]);
	}

	return true;	
}

COMM_END()

#ifdef STRUTIL_TEST
#define _DEBUG
#include <iostream>
using namespace std;
using namespace AV;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout<<"Usage: "<<argv[0]<<" [string]"<<endl;
		return -1;
	}

	string strFrom = argv[1];
	string strTo;
	long nValue = 0;

	bool bRet = CStrUtil::StrToLong(strFrom, nValue);
	cout<<"CStrUtil::StrToLong: "<<(bRet?"TRUE ":"FALSE ")<<strFrom <<"-->("<<nValue<<')'<<endl;

	bRet = CStrUtil::LongToStr(nValue, strTo);
	cout<<"CStrUtil::LongToStr: "<<(bRet?"TRUE ":"FALSE ")<<nValue <<"-->("<<strTo<<')'<<endl;

	bRet = CStrUtil::TrimLeft(strFrom, strTo, ' ');
	cout<<"CStrUtil::TrimLeft: "<<(bRet?"TRUE ":"FALSE ")<<strFrom <<"-->("<<strTo<<')'<<endl;

	bRet = CStrUtil::TrimRight(strFrom, strTo, ' ');
	cout<<"CStrUtil::TrimRight: "<<(bRet?"TRUE ":"FALSE ")<<strFrom <<"-->("<<strTo<<')'<<endl;

	bRet = CStrUtil::Trim(strFrom, strTo, ' ');
	cout<<"CStrUtil::Trim: "<<(bRet?"TRUE ":"FALSE ")<<strFrom<<"-->("<<strTo<<')'<<endl;
	
	bRet = CStrUtil::ToUpper(strFrom, strTo);
	cout<<"CStrUtil::ToUpper: "<<(bRet?"TRUE ":"FALSE ")<<strFrom<<"-->("<<strTo<<')'<<endl;

	bRet = CStrUtil::ToLower(strFrom, strTo);
	cout<<"CStrUtil::ToLower: "<<(bRet?"TRUE ":"FALSE ")<<strFrom<<"-->("<<strTo<<')'<<endl;
	
	if(argc > 2) strTo = argv[2];
	
	int nRet = CStrUtil::StrCaseCmp(strFrom, strTo);
	cout<<"CStrUtil::StrCaseCmp: "<<nRet<<" "<<strFrom<<"<-->"<<strTo<<endl;

	return 0;
}
#endif//STRUTIL_TEST
