/*
 * File:    http_response.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   http response
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
#include "http_response.h"

CHttpResponse::CHttpResponse(void)
{
	m_body_data   = NULL;
	m_body_length = 0;

	return;
}

CHttpResponse::~CHttpResponse(void)
{
	delete[] m_body_data;

	return;
}

bool   CHttpResponse::Parse(char* data, size_t length)
{
	enum 
	{
		STAT_HTTP,
		STAT_RESP_CODE,
		STAT_RESP_TEXT,
		STAT_HEADER,
	}state = STAT_HTTP;
	
	char* p = data;
	for(; *p != '\0'; p++)
	{
		switch(state)
		{
			case STAT_HTTP:
			{
				if(*p == ' ')
				{
					m_resp_code = atoi(p + 1);
					state = STAT_RESP_CODE;
				}
				break;
			}
			case STAT_RESP_CODE:
			{
				if(isspace(*p))
				{
					state = STAT_RESP_TEXT;
				}
				break;
			}
			case STAT_RESP_TEXT:
			{
				if(*p == '\n')
				{
					state = STAT_HEADER;
					break;
				}
				break;
			}
			default:break;
		}

		if(state == STAT_HEADER)
		{
			break;
		}
	}

	m_headers.Parse(p);

	return true;
}

bool   CHttpResponse::SetBody(char* data, size_t length)
{
	m_body_data = data;
	m_body_length = length;

	return true;
}

int    CHttpResponse::GetCode(void)
{
	return m_resp_code;
}

bool   CHttpResponse::GetHeader(const string& key, string& value)
{
	return m_headers.Get(key, value);
}

void*  CHttpResponse::GetBodyData(void) const
{
	return m_body_data;
}

size_t CHttpResponse::GetBodyLength(void) const
{
	return m_body_length;
}

#ifdef HTTP_RESPONSE_TEST
#include <assert.h>

int main(int argc, char* argv[])
{
	CHttpResponse r;

	string str;
	char* buff = strdup("HTTP/1.1 500 ( 无效索引。  )\r\nVia: 1.1 SERVER\r\nConnection: close\r\nProxy-Connection: close\r\nPragma: no-cache\r\nCache-Control: no-cache\r\nContent-Type: text/html\r\nContent-Length: 4\r\n");
	r.Parse(buff, strlen(buff));
	assert(r.GetCode() == 500);
	assert(r.GetHeader("Via", str) && str == "1.1 SERVER");
	assert(r.GetHeader("Content-Length", str) && str == "4");
	assert(r.SetBody((char*)strdup("1234"), 4));
	assert(strncmp((char*)r.GetBodyData(), "1234", r.GetBodyLength()) == 0);
	free(buff);

	return 0;
}
#endif/*HTTP_RESPONSE_TEST*/

