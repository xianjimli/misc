/*
 * File:    ini_tr2xml_builder.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   translate ini to xml.
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
 * 2009-05-08 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "ini_util.h"
#include "ini_tr2xml_builder.h"

CIniTr2xmlBuilder::CIniTr2xmlBuilder(FILE* fp)
{
	m_fp = (fp != NULL) ? fp : stdout;
	m_is_first_group = true;

	return;
}

CIniTr2xmlBuilder::~CIniTr2xmlBuilder(void)
{
	return;
}

IniRet CIniTr2xmlBuilder::OnGroup(const string& group_name)
{
	string str = group_name;
	strtrim((char*)str.data());
	if(m_is_first_group)
	{
		m_is_first_group = false;
	}
	else
	{
		fprintf(m_fp, "</group>\n");
	}
	fprintf(m_fp, "<group name=\"%s\">\n", str.c_str());

	return INI_RET_OK;
}

IniRet CIniTr2xmlBuilder::OnPair(const string& key, const string& value)
{
	string skey = key;
	strtrim((char*)skey.data());
	
	string svalue = value;
	strtrim((char*)svalue.data());

	fprintf(m_fp, "<key name=\"%s\">%s</key>\n", skey.c_str(), svalue.c_str());

	return INI_RET_OK;
}

IniRet CIniTr2xmlBuilder::OnEnd(void)
{
	if(!m_is_first_group)
	{
		fprintf(m_fp, "</group>\n");
	}

	return INI_RET_OK;
}

#ifdef INI_TR2XML_BUILDER_TEST

#include <assert.h>
#include "ini_parser.h"

int main(int argc, char* argv[])
{
	CIniTr2xmlBuilder* builder = new CIniTr2xmlBuilder(NULL);
	assert(ini_parse("./test1.ini", '#', '=', builder) == INI_RET_OK);
	delete builder;

	return 0;
}
#endif/*INI_TR2XML_BUILDER_TEST*/

