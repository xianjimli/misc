/*
 * File:    ini_pairs.h
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
#ifndef INI_PAIRS_H
#define INI_PAIRS_H
using namespace std;

#include "ini_type.h"

class CIniPair
{
public:
	CIniPair(void);
	CIniPair(const string& key, const string& value);
	~CIniPair(void);

	const string& GetKey(void) const;
	const string& GetValue(void) const;
	void  SetKey(const string& key);
	void  SetValue(const string& value);

private:
	string m_key;
	string m_value;
};

class CIniPairs
{
public:
	CIniPairs(void);
	~CIniPairs(void);

	size_t    Size(void) const;
	IniRet    Del(const string& key);
	CIniPair* Find(const string& key);
	IniRet     Append(const string& key, const string& value);
	IniRet    Save(FILE* fp, char delim_char) const;

private:
	vector<CIniPair> m_pairs;
};

#endif/*INI_PAIRS_H*/

