/*
 * File:    http_heaers.cpp
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
#include "http_util.h"
#include "http_headers.h"

CHttpHeaders::CHttpHeaders(void)
{
}

CHttpHeaders::~CHttpHeaders(void)
{
}

bool CHttpHeaders::Set(const string& key, const string& value)
{
	vector<HttpHeader>::iterator iter = m_headers.begin();

	for(; iter != m_headers.end(); iter++)
	{
		if(iter->key == key)
		{
			iter->value = value;

			return true;
		}
	}

	return this->Append(key, value);
}

bool CHttpHeaders::Append(const string& key, const string& value)
{
	m_headers.push_back(HttpHeader(key, value));

	return true;
}

bool CHttpHeaders::Get(const string& key, string& value) const
{
	vector<HttpHeader>::const_iterator iter = m_headers.begin();

	for(; iter != m_headers.end(); iter++)
	{
		if(iter->key == key)
		{
			value = iter->value;

			return true;
		}
	}

	return false;
}

bool CHttpHeaders::Parse(const string& str)
{
	enum 
	{
		STAT_KEY,
		STAT_VALUE
	}state = STAT_KEY;

	string key;
	string value;
	const char* p = str.c_str();

	m_headers.clear();
	for(; *p != '\0'; p++)
	{
		switch(state)
		{
			case STAT_KEY:
			{
				if(*p == ':')
				{
					state = STAT_VALUE;
				}
				else
				{
					key += *p;
				}
				break;
			}
			case STAT_VALUE:
			{
				if(*p == '\r' || *p == '\n')
				{
					state = STAT_KEY;
					string_trim(key);
					string_trim(value);
					this->Set(key, value);
					key = "";
					value = "";
				}
				else
				{
					value += *p;
				}
			}
			default:break;
		}
	}

	if(!key.empty() && !value.empty())
	{
		string_trim(key);
		string_trim(value);
		this->Set(key, value);
	}

	return true;
}

bool CHttpHeaders::Pack(string& str) const
{
	vector<HttpHeader>::const_iterator iter = m_headers.begin();

	for(; iter != m_headers.end(); iter++)
	{
		str += iter->key;
		str += " : ";
		str += iter->value;
		str += "\r\n";
	}

	return true;
}

#ifdef HTTP_HEADERS_TEST
#include <assert.h>

int main(int argc, char* argv[])
{
	string key;
	string value;
	CHttpHeaders headers;
	string str_in = "Host : www.limodev.cn\r\nContent-Type : text/html\r\n";
	headers.Parse(str_in);
	assert(headers.Get("Host", value) && value == "www.limodev.cn");
	assert(headers.Get("Content-Type", value) && value == "text/html");
	string str_out;
	headers.Pack(str_out);
	assert(str_in == str_out);

	str_in = "Host : www.limodev.cn\r\nContent-Type : text/html";
	headers.Parse(str_in);
	assert(headers.Get("Host", value) && value == "www.limodev.cn");
	assert(headers.Get("Content-Type", value) && value == "text/html");
	
	str_in = "Host: www.limodev.cn\r\nContent-Type   : text/html";
	headers.Parse(str_in);
	assert(headers.Get("Host", value) && value == "www.limodev.cn");
	assert(headers.Get("Content-Type", value) && value == "text/html");

	return 0;
}
#endif/*HTTP_HEADERS_TEST*/

