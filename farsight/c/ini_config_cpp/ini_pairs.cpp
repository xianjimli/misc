/*
 * File:    ini_pairs.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   ini pairs manager
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
#include "ini_pairs.h"

CIniPair::CIniPair(void)
{
	return;
}

CIniPair::CIniPair(const string& key, const string& value)
{
	this->SetKey(key);
	this->SetValue(value);

	return;
}

CIniPair::~CIniPair(void)
{
	return;
}

const string& CIniPair::GetKey(void) const
{
	return m_key;
}

const string& CIniPair::GetValue(void) const
{
	return m_value;
}

void CIniPair::SetKey(const string& key)
{
	string str = key;
	strtrim((char*)str.data());
	m_key = str.c_str();

	return;
}

void CIniPair::SetValue(const string& value)
{
	string str = value;
	strtrim((char*)str.data());
	m_value = str.c_str();

	return;
}

CIniPairs::CIniPairs(void)
{
	return;
}

CIniPairs::~CIniPairs(void)
{
	return;
}

size_t   CIniPairs::Size(void) const
{
	return m_pairs.size();
}

IniRet   CIniPairs::Del(const string& key)
{
	for(vector<CIniPair>::iterator iter = m_pairs.begin(); iter != m_pairs.end(); iter++)
	{
		if(key == iter->GetKey())
		{
			m_pairs.erase(iter);

			return INI_RET_OK;
		}
	}

	return INI_RET_NOT_EXIST;
}

CIniPair* CIniPairs::Find(const string& key)
{
	for(vector<CIniPair>::iterator iter = m_pairs.begin(); iter != m_pairs.end(); iter++)
	{
		if(key == iter->GetKey())
		{
			return &(*iter);
		}
	}

	return NULL;
}


IniRet CIniPairs::Append(const string& key, const string& value)
{
	m_pairs.push_back(CIniPair(key, value));

	return INI_RET_OK;
}

IniRet   CIniPairs::Save(FILE* fp, char delim_char) const
{
	return_val_if_fail(fp != NULL, INI_RET_FAIL);

	for(vector<CIniPair>::const_iterator iter = m_pairs.begin(); iter != m_pairs.end(); iter++)
	{
		fprintf(fp, "  %s %c %s\n", iter->GetKey().c_str(), delim_char, iter->GetValue().c_str());
	}

	return INI_RET_OK;
}

#ifdef INI_PAIRS_TEST
#include <cassert>

int main(int argc, char* argv[])
{
	CIniPair*  pair = NULL;
	CIniPairs* pairs = new CIniPairs();
	assert(pairs->Append("name  ", "lixianjing") == INI_RET_OK);
	assert((pair = pairs->Find("name")) != NULL);
	assert(pair != NULL && pair->GetKey() == "name" && pair->GetValue() == "lixianjing");
	assert(pairs->Size() == 1);
	assert(pairs->Append("gender", "male") == INI_RET_OK);
	assert((pair = pairs->Find("gender")) != NULL);
	assert(pair != NULL && pair->GetKey() == "gender" && pair->GetValue() == "male");
	assert(pairs->Size() == 2);
	pair = pairs->Find("name");
	assert(pair != NULL && pair->GetKey() == "name" && pair->GetValue() == "lixianjing");
	pair = pairs->Find("gender");
	assert(pair != NULL && pair->GetKey() == "gender" && pair->GetValue() == "male");
	assert(pairs->Save(stdout, '=') == INI_RET_OK);
	assert(pairs->Del("name") == INI_RET_OK);
	assert(pairs->Size() == 1);
	assert(pairs->Find("name") == NULL);

	delete pairs;

	return 0;
}
#endif/*INI_PAIRS_TEST*/


