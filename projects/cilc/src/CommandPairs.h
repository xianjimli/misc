/*
 * CommandPairs.h
 * Copyright (C) 2006 absurd <xianjimli@hotmail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, 
 * Boston, MA 02111-1307, USA.
 */

#ifndef COMMAND_PAIRS_H
#define COMMAND_PAIRS_H

#include "CommandPair.h"

class CCommandPairs
{
public:
	CCommandPairs(void);
	~CCommandPairs(void);

	bool Load(const string& strFileName);

public:
	const vector<CCommandPair>& GetCommandPairs(void) const;
	const string& GetName(void) const;

	void Dump(void) const;
	
private:
	string m_strName;
	vector<CCommandPair> m_CommandPairs;
};

#endif/*COMMAND_PAIRS_H*/
