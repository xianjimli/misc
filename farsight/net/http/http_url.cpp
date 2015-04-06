/*
 * File:    http_url.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   http url 
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

#include <cstring>
#include <cstdlib>

#include "http_url.h"

CHttpUrl::CHttpUrl(void)
{
}

CHttpUrl::CHttpUrl(const string& url)
{
	this->Parse(url);

	return;
}

CHttpUrl::~CHttpUrl(void)
{
}

bool CHttpUrl::Parse(const string& url)
{
	enum UrlState
	{
		STAT_PROTOCOL,
		STAT_BEFORE_HOST,
		STAT_HOST,
		STAT_PORT,
		STAT_PATH
	}state = STAT_PROTOCOL;

	string port;
	const char* p = url.c_str();
	state = strstr(p, "://") != NULL ? STAT_PROTOCOL : STAT_HOST;

	m_url  = url;
	m_host = "";
	m_path = "/";
	m_port = 80;
	m_protocol = state == STAT_PROTOCOL ? "" : "http";

	for(; *p != '\0'; p++)
	{
		switch(state)
		{
			case STAT_PROTOCOL:
			{
				if(*p == ':')
				{
					state = STAT_BEFORE_HOST;
				}
				else
				{
					m_protocol += *p;
				}
				break;
			}
			case STAT_BEFORE_HOST:
			{
				if(*p != '/')
				{
					m_host += *p;
					state = STAT_HOST;
				}
				break;
			}
			case STAT_HOST:
			{
				if(*p == ':')
				{
					state = STAT_PORT;
				}
				else if(*p == '/')
				{
					state = STAT_PATH;
				}
				else
				{
					m_host += *p;
				}
				break;
			}
			case STAT_PORT:
			{
				if(*p == '/')
				{
					state = STAT_PATH;
				}
				else
				{
					port += *p;
				}
				break;
			}
			case STAT_PATH:
			{
				m_path += *p;
				break;
			}
			default:break;
		}
	}

	if(!port.empty())
	{
		m_port = atoi(port.c_str());
	}

	return true;
}

bool CHttpUrl::GetProtocol(string& protocol) const
{
	protocol = m_protocol;

	return true;
}

bool CHttpUrl::GetHost(string& host) const
{
	host = m_host;

	return true;
}

bool CHttpUrl::GetPath(string& path) const
{
	path = m_path;

	return true;
}

bool CHttpUrl::GetPort(int& port) const
{
	port = m_port;

	return true;
}

#ifdef HTTP_URL_TEST
#include <assert.h>
int main(int argc, char* argv[])
{
	string str;
	int port = 0;
	CHttpUrl url("http://www.limodev.cn/blog/index.html");
	assert(url.GetProtocol(str) && str == "http");
	assert(url.GetHost(str) && str == "www.limodev.cn");
	assert(url.GetPort(port)  && port == 80);
	assert(url.GetPath(str) && str == "/blog/index.html");
	
	url.Parse("www.limodev.cn/blog/index.html");
	assert(url.GetProtocol(str) && str == "http");
	assert(url.GetHost(str) && str == "www.limodev.cn");
	assert(url.GetPort(port)  && port == 80);
	assert(url.GetPath(str) && str == "/blog/index.html");
	
	url.Parse("http://www.limodev.cn:80/blog/index.html");
	assert(url.GetProtocol(str) && str == "http");
	assert(url.GetHost(str) && str == "www.limodev.cn");
	assert(url.GetPort(port)  && port == 80);
	assert(url.GetPath(str) && str == "/blog/index.html");
	
	url.Parse("www.limodev.cn:8080/blog/index.html");
	assert(url.GetProtocol(str) && str == "http");
	assert(url.GetHost(str) && str == "www.limodev.cn");
	assert(url.GetPort(port)  && port == 8080);
	assert(url.GetPath(str) && str == "/blog/index.html");

	return 0;
}
#endif/*HTTP_URL_TEST*/
