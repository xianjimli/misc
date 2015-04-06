/*
 * File:    http_url.h
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

#ifndef HTTP_URL_H
#define HTTP_URL_H

#include "http_type.h"

class CHttpUrl
{
public:
	CHttpUrl(void);
	CHttpUrl(const string& url);
	~CHttpUrl(void);

	bool Parse(const string& url);

	bool GetProtocol(string& protocol) const;
	bool GetHost(string& host) const;
	bool GetPath(string& path) const;
	bool GetPort(int& port) const;

private:
	string m_url;
	string m_protocol;
	string m_host;
	string m_path;
	int    m_port;
};

#endif/*HTTP_URL_H*/

