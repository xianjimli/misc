/*
 * File:    http_heaers.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   http headers
 *
 * Copyright (c) 2009  Li XianJing <xianjimli@hotmail.com>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2009-05-09 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef HTTP_HEADERS_H
#define HTTP_HEADERS_H
#include "http_type.h"

class CHttpHeaders
{
public:
	CHttpHeaders(void);
	~CHttpHeaders(void);

	bool Set(const string& key, const string& value);
	bool Append(const string& key, const string& value);
	bool Get(const string& key, string& value) const;
	
	bool Parse(const string& str);
	bool Pack(string& str) const;

private:
	struct HttpHeader 
	{
		HttpHeader(const string& k, const string& v)
		{
			key = k;
			value = v;
		}

		string key;
		string value;
	};

	vector<HttpHeader> m_headers;
};

#endif/*HTTP_HEADERS_H*/

