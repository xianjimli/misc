/*
 * File:    ini_config.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   ini config interface.
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
 * 2009-05-07 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "ini_parser.h"
#include "ini_config.h"

CIniConfig::CIniConfig(void)
{
	m_groups = NULL;
}

CIniConfig::~CIniConfig(void)
{
	delete m_groups;
	m_groups = NULL;

	return;
}

IniRet CIniConfig::Load(const string& file_name)
{
	if(m_groups != NULL)
	{
		delete m_groups;
		m_groups = NULL;
	}

	if((m_groups = ini_parse(file_name.c_str(), '#', '=')) == NULL)
	{
		m_groups = new CIniGroups();
	}
	m_file_name = file_name;

	return m_groups != NULL ? INI_RET_OK : INI_RET_FAIL;
}

IniRet CIniConfig::Get(const string& group_name, const string& key, string& value) const
{
	CIniGroup* group = NULL;
	IniRet ret = INI_RET_FAIL;

	return_val_if_fail(m_groups != NULL, INI_RET_FAIL);
	
	if((group = m_groups->Find(group_name)) != NULL)
	{
		CIniPair* pair = group->GetPairs().Find(key);
		if(pair != NULL)
		{
			value = pair->GetValue();
			ret = INI_RET_OK;
		}
	}

	return ret;
}

IniRet CIniConfig::Set(const string& group_name, const string& key, const string& value)
{
	CIniGroup* group = NULL;
	IniRet ret = INI_RET_FAIL;

	return_val_if_fail(m_groups != NULL, INI_RET_FAIL);
	
	if((group = m_groups->Find(group_name)) == NULL)
	{
		m_groups->Append(group_name);
		group = m_groups->Find(group_name);
	}

	if(group != NULL)
	{
		CIniPair* pair = group->GetPairs().Find(key);
		if(pair != NULL)
		{
			pair->SetValue(value);
		}
		else
		{
			group->GetPairs().Append(key, value);
		}

		ret = INI_RET_OK;
	}

	return ret;
}

IniRet CIniConfig::Del(const string& group_name, const string& key)
{
	CIniGroup* group = NULL;
	IniRet ret = INI_RET_FAIL;

	return_val_if_fail(m_groups != NULL, INI_RET_FAIL);
	
	if((group = m_groups->Find(group_name)) != NULL)
	{
		ret = group->GetPairs().Del(key);
	}

	return ret;
}

IniRet CIniConfig::Save(void)
{
	FILE* fp = NULL;
	IniRet ret = INI_RET_FAIL;
	return_val_if_fail(m_groups != NULL, INI_RET_FAIL);
	fp = fopen(m_file_name.c_str(), "wb+");
	return_val_if_fail(fp != NULL, INI_RET_FAIL);

	ret = m_groups->Save(fp, '=');
	fclose(fp);

	return ret;
}

#ifdef INI_CONFIG_TEST
#include <assert.h>

void ini_config_test1(void)
{
	string value;
	CIniConfig* ini = new CIniConfig();
	assert(ini->Load("test1.ini") == INI_RET_OK);

	assert(ini->Set("lixianjing", "name", "lixianjing") == INI_RET_OK);
	assert(ini->Set("lixianjing", "gender", "male") == INI_RET_OK);
	assert(ini->Set("lixianjing", "email", "xianjimli@hotmail.com") == INI_RET_OK);
	
	assert(ini->Set("zhangshan", "name", "zhangshan") == INI_RET_OK);
	assert(ini->Set("zhangshan", "gender", "male") == INI_RET_OK);
	assert(ini->Set("zhangshan", "email", "zhangshan@hotmail.com") == INI_RET_OK);
	assert(ini->Get("zhangshan", "name", value) == INI_RET_OK && value == "zhangshan");
	assert(ini->Get("zhangshan", "gender", value) == INI_RET_OK && value == "male");
	assert(ini->Get("zhangshan", "email", value) == INI_RET_OK && value == "zhangshan@hotmail.com");

	assert(ini->Save() == INI_RET_OK);
	assert(ini->Del("zhangshan", "name") == INI_RET_OK);
	assert(ini->Get("zhangshan", "name", value) != INI_RET_OK);

	delete ini;

	return;
}

int main(int argc, char* argv[])
{
	ini_config_test1();
	return 0;
}
#endif/*INI_CONFIG_TEST*/

