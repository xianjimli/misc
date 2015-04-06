/*
 * File:    ini_groups.h
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

#ifndef INI_GROUPS_H
#define INI_GROUPS_H

#include "ini_pairs.h"

class CIniGroup
{
public:
	CIniGroup(void);
	~CIniGroup(void);
	CIniGroup(const string& name);

	void  SetName(const string& name);
	const string& GetName(void) const;
	CIniPairs& GetPairs(void);

private:
	CIniPairs m_pairs;
	string    m_name;
};

class CIniGroups
{
public:
	CIniGroups(void);
	~CIniGroups(void);

	size_t     Size(void) const;
	IniRet     Del(const string& name);
	CIniGroup* Find(const string& name);
	IniRet     Append(const string& name);
	IniRet     Save(FILE* fp, char delim_char) const;

private:
	vector<CIniGroup> m_groups;
};

#endif/*INI_GROUPS_H*/

