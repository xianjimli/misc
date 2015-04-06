/*
 * File:    http_client.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   http client api.
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

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "http_client.h"
#include "http_stream_factory.h"

CHttpResponse* CHttpClient::Request(CHttpRequest& request, const string& method, void* data, size_t data_length)
{
	int ret  = 0;
	int port = 0;
	string host;
	string protocol;
	char* p = NULL;
	char buffer[2048] = {0};
	CHttpResponse* response = NULL;

	if(!request.GetProtocol(protocol) || !request.GetHost(host) || !request.GetPort(port))
	{
		return NULL;
	}

	CHttpStream* stream = CHttpStreamFactory::CreateStream(protocol, host, port);
	if(stream == NULL)
	{
		return NULL;
	}

	string str = method + " ";
	request.SetHeader("Connection", "Close");
	request.Pack(str);

	do
	{
		ret = stream->Write(str.c_str(), str.size());
		if(ret != (int)str.size()) break;

		if(data != NULL)
		{
			ret = stream->Write((char*)data, data_length);
			if(ret != (int)data_length) break;
		}
		
		if((ret = stream->Read(buffer, sizeof(buffer))) <= 0) break;
				
		if((p = strstr(buffer, "\r\n\r\n")) != NULL)
		{
			*p = '\0';
			p += 4;
		}
		else
		{
			break;
		}

		string str;
		response = new CHttpResponse();
		response->Parse(buffer, strlen(buffer));

		if(response->GetHeader("Content-Length", str))
		{
			int length = atoi(str.c_str());
			int got_length = ret - (p - buffer);
			int rlength = length - got_length;
			char* body = new char[length + 1];

			memcpy(body, p, got_length);
			if(rlength > 0)
			{
				ret = stream->Read(body, rlength); 
			}
			body[length] = '\0';
			response->SetBody(body, length);
		}
		else if(response->GetHeader("Transfer-Encoding", str) && str == "chunked")
		{
			/*FIXME: handle chuncked data.*/	
			cout << "chunked data: not handle yet." <<endl;
		}
	}while(0);

	delete stream;

	return response;
}

CHttpResponse* CHttpClient::Get(CHttpRequest& request)
{
	return CHttpClient::Request(request, "GET", NULL, 0);
}

CHttpResponse* CHttpClient::Post(CHttpRequest& request, void* data, size_t length)
{
	return CHttpClient::Request(request, "POST", data, length);
}

#ifdef HTTP_CLIENT_TEST
#include <assert.h>
#include <iostream>

void auto_test()
{
	string str;
	CHttpRequest request;
	request.SetUrl("http://www.limodev.cn/blog");

	CHttpResponse* response = CHttpClient::Get(request);
	assert(response != NULL);
	assert(response->GetCode() == 301);
	assert(response->GetHeader("Server", str) && str == "Apache/2.2.11 (Unix) mod_ssl/2.2.11 OpenSSL/0.9.8i DAV/2 mod_auth_passthrough/2.1 mod_bwlimited/1.4 FrontPage/5.0.2.2635");
	assert(response->GetHeader("Location", str) && str == "http://www.limodev.cn/blog/");
	assert(response->GetHeader("Content-Type", str) && str == "text/html; charset=iso-8859-1");


	delete response;

	return;
}

void test_get(const char* url, const char* file_name)
{
	string str;
	CHttpRequest request;
	request.SetUrl(url);

	CHttpResponse* response = CHttpClient::Get(request);
	assert(response != NULL);

	cout << "resp code: " << response->GetCode() << endl;
	FILE* fp = fopen(file_name, "wb+");
	if(fp != NULL)
	{
		fwrite(response->GetBodyData(), response->GetBodyLength(), 1, fp);
		fclose(fp);
	}

	delete response;

	return;
}

int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		auto_test();
		cout << "usage: " << argv[0] << " get|post url file" << endl;
		return 0;
	}

	if(strcmp(argv[1], "get") == 0)
	{
		test_get(argv[2], argv[3]);	
	}

	return 0;
}
#endif/*HTTP_CLIENT_TEST*/

