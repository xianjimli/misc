/*
 * File:    http_request.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   http request
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

#include "http_request.h"

CHttpRequest::CHttpRequest(void)
{
}

CHttpRequest::~CHttpRequest(void)
{
}

bool CHttpRequest::SetUrl(const string& str)
{
	if(m_url.Parse(str))
	{
		string host;
		if(m_url.GetHost(host))
		{
			m_headers.Set("Host", host);

			return true;
		}
	}

	return false;
}

bool CHttpRequest::SetHeader(const string& key, const string& value)
{
	return m_headers.Set(key, value);
}

bool CHttpRequest::GetHeader(const string& key, string& value) const
{
	return m_headers.Get(key, value);
}

bool CHttpRequest::GetProtocol(string& protocol) const
{
	return m_url.GetProtocol(protocol);
}

bool CHttpRequest::GetHost(string& host) const
{
	return m_url.GetHost(host);
}

bool CHttpRequest::GetPort(int& port) const
{
	return m_url.GetPort(port);
}

bool CHttpRequest::Pack(string& str) const
{
	string path;
	m_url.GetPath(path);
	str += path;
	str += " HTTP/1.1\r\n";
	m_headers.Pack(str);
	str += "\r\n";

	return true;
}

#ifdef HTTP_REQUEST_TEST
#include <assert.h>
#include <iostream>

int main(int argc, char* argv[])
{
	int port = 0;
	string str;
	CHttpRequest r;
	r.SetUrl("http://www.limodev.cn/blog");
	r.SetHeader("Connection", "Close");

	assert(r.GetHost(str) && str == "www.limodev.cn");
	assert(r.GetProtocol(str) && str == "http");
	assert(r.GetPort(port) && port == 80);
	assert(r.GetHeader("Connection", str) && str == "Close");	
	str = "GET ";
	r.Pack(str);
	cout << str;

	return 0;
}
#endif/*HTTP_REQUEST_TEST*/
