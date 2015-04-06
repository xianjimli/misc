/*
 * File:    ini_groups.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   ini groups manager.
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

#include "ini_util.h"
#include "ini_groups.h"

CIniGroup::CIniGroup(void)
{
	return;
}

CIniGroup::~CIniGroup(void)
{
	return;
}

CIniGroup::CIniGroup(const string& name)
{
	this->SetName(name);

	return;
}

void  CIniGroup::SetName(const string& name)
{
	string str = name;
	strtrim((char*)str.data());
	m_name = str.c_str();

	return;
}

const string& CIniGroup::GetName(void) const
{
	return m_name;
}

CIniPairs& CIniGroup::GetPairs(void)
{
	return m_pairs;
}

CIniGroups::CIniGroups(void)
{
	return;
}

CIniGroups::~CIniGroups(void)
{
	return;
}

size_t     CIniGroups::Size(void) const
{
	return m_groups.size();
}

IniRet     CIniGroups::Del(const string& name)
{
	for(vector<CIniGroup>::iterator iter = m_groups.begin(); iter != m_groups.end(); iter++)
	{
		if(iter->GetName() == name)
		{
			m_groups.erase(iter);

			return INI_RET_OK;
		}
	}

	return INI_RET_NOT_EXIST;
}

CIniGroup* CIniGroups::Find(const string& name)
{
	for(vector<CIniGroup>::iterator iter = m_groups.begin(); iter != m_groups.end(); iter++)
	{
		if(iter->GetName() == name)
		{
			return &(*iter);
		}
	}

	return NULL;
}

IniRet CIniGroups::Append(const string& name)
{
	m_groups.push_back(CIniGroup(name));

	return INI_RET_OK;
}

IniRet     CIniGroups::Save(FILE* fp, char delim_char) const
{
	for(vector<CIniGroup>::const_iterator iter = m_groups.begin(); iter != m_groups.end(); iter++)
	{
		if(DEFAULT_GROUP != iter->GetName())
		{
			fprintf(fp, "[%s]\n", iter->GetName().c_str());
		}
		const_cast<CIniGroup&>(*iter).GetPairs().Save(fp, delim_char);
	}

	return INI_RET_OK;
}

#ifdef INI_GROUPS_TEST
#include <assert.h>
int main(int argc, char* argv[])
{
	CIniGroup* group = NULL;
	CIniGroups* groups = new CIniGroups();

	assert(groups->Append("   lixianjing   ") == INI_RET_OK);
	assert((group = groups->Find("lixianjing")) != NULL);
	assert(group != NULL && group->GetName() == "lixianjing");
	assert(groups->Size() == 1);
	
	assert(groups->Append("zhangshan") == INI_RET_OK);
	assert((group = groups->Find("zhangshan")) != NULL);
	assert(group != NULL && group->GetName() == "zhangshan");
	assert(groups->Size() == 2);

	group = groups->Find("lixianjing");
	assert(group != NULL && group->GetName() == "lixianjing");
	
	group = groups->Find("zhangshan");
	assert(group != NULL && group->GetName() == "zhangshan");

	groups->Save(stdout, '=');

	groups->Del("lixianjing");
	assert(groups->Size() == 1);

	delete groups;

	return 0;
}
#endif/*INI_GROUPS_TEST*/

