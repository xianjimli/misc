/*
 * StrUtil.h
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
#ifndef COMM_STRUTIL_H
#define COMM_STRUTIL_H

#include "Common.h"

#include <string>
using namespace std;

COMM_BEGIN()
	
class COMM_API CStrUtil 
{
public: 
	static bool LongToStr(long nValue, string& str);
	
	static bool StrToLong(const string& strVal, long& nVal);

	static bool Trim(const string& strFrom, string& strTo, char cTrim);
	
	static bool TrimLeft(const string& strFrom, string& strTo, char cTrim);
	
	static bool TrimRight(const string& strFrom, string& strTo, char cTrim);

	static int  StrCaseCmp(const string& strA, const string& strB);

	static bool ToUpper(const string& strFrom, string& strTo);

	static bool ToLower(const string& strFrom, string& strTo);
	
protected://need not to create a instance for this class.
	CStrUtil();
	~CStrUtil();
};

COMM_END()

#endif//COMM_STRUTIL_H
