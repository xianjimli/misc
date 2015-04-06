/*
 * File:    ini_default_builder.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   default implementation for builder interface.
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

#include "ini_default_builder.h"

CIniDefaultBuilder::CIniDefaultBuilder(void)
{
	m_groups = new CIniGroups();
	m_current_group = NULL;

	return;
}

CIniDefaultBuilder::~CIniDefaultBuilder(void)
{
	return;
}

IniRet CIniDefaultBuilder::OnGroup(const string& group_name)
{
	m_groups->Append(group_name);
	m_current_group = m_groups->Find(group_name);

	return INI_RET_OK;
}

IniRet CIniDefaultBuilder::OnPair(const string& key, const string& value)
{
	if(m_current_group == NULL)
	{
		m_groups->Append(DEFAULT_GROUP);
		m_current_group = m_groups->Find(DEFAULT_GROUP);
	}
	
	m_current_group->GetPairs().Append(key, value);
	
	return INI_RET_OK;
}

IniRet CIniDefaultBuilder::OnEnd(void)
{
	return INI_RET_OK;
}

CIniGroups* CIniDefaultBuilder::GetGroups(void) const
{
	return m_groups;
}


#ifdef INI_DEFAULT_BUILDER_TEST

#include <assert.h>

int main(int argc, char* argv[])
{
	CIniGroup*  group = NULL;
	CIniGroups* groups = NULL;
	CIniDefaultBuilder* builder = new CIniDefaultBuilder();

	assert(builder->OnGroup("lixianjing") == INI_RET_OK);
	assert(builder->OnPair("name", "lixianjing") == INI_RET_OK);
	assert(builder->OnPair("age", "31") == INI_RET_OK);

	assert(builder->OnGroup("zhangshan") == INI_RET_OK);
	assert(builder->OnPair("name", "zhangshan") == INI_RET_OK);
	assert(builder->OnPair("age", "10") == INI_RET_OK);

	groups = builder->GetGroups();
	assert(groups != NULL);
	assert((group = groups->Find("lixianjing")) != NULL);
	assert(group->GetName() == "lixianjing");

	assert((group = groups->Find("zhangshan")) != NULL);
	assert(group->GetName() == "zhangshan");
	assert(group->GetPairs().Find("name") != NULL);

	delete groups;
	delete builder;

	return 0;
}
#endif/*INI_DEFAULT_BUILDER_TEST*/

