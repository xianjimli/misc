/*
 * File:    ini_config.h
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
#ifndef INI_CONFIG_H
#define INI_CONFIG_H

#include "ini_groups.h"

class CIniConfig
{
public:
	CIniConfig(void);
	~CIniConfig(void);

	IniRet Load(const string& file_name);
	IniRet Get(const string& group, const string& key, string& value) const;
	IniRet Set(const string& group, const string& key, const string& value);
	IniRet Del(const string& group, const string& key);
	IniRet Save(void);

private:
	CIniGroups* m_groups;
	string      m_file_name;

private:
	CIniConfig(const CIniConfig& other);
	CIniConfig& operator=(const CIniConfig& other);
};

#endif/*INI_CONFIG_H*/
