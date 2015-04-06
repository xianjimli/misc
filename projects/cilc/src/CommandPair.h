/*
 * CommandPair.h
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

#ifndef COMMAND_PAIR_H
#define COMMAND_PAIR_H
#include "Command.h"
class CCommandPair
{
public:
	CCommandPair();
	~CCommandPair();

	bool Create(const string& strName, const string& strInputPrefix, const string& strInputFormat,
	        const string& strOutputPrefix, const string& strOutputFormat);
public:
	const string&   GetName(void) const;
	const CCommand& GetInputCommand(void) const;
	const CCommand& GetOutputCommand(void) const;
	
	void Dump(void) const;
private:
	string m_strName;
	CCommand m_aInputCommand;
	CCommand m_aOutputCommand;
};
#endif/*COMMAND_PAIR_H*/
