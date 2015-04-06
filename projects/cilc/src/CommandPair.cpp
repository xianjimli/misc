/*
 * CommandPair.cpp
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

#include "CommandPair.h"

CCommandPair::CCommandPair()
{
}

CCommandPair::~CCommandPair()
{

}

bool CCommandPair::Create(const string& strName, const string& strInputPrefix, const string& strInputFormat, 
		const string& strOutputPrefix, const string& strOutputFormat)
{
	m_strName = strName;

	return m_aInputCommand.Create(strInputPrefix, strInputFormat)
			&& m_aOutputCommand.Create(strOutputPrefix, strOutputFormat);
}

const string&   CCommandPair::GetName(void) const
{
	return m_strName;
}

const CCommand& CCommandPair::GetInputCommand(void) const
{
	return m_aInputCommand;
}

const CCommand& CCommandPair::GetOutputCommand(void) const
{
	return m_aOutputCommand;
}

#include <iostream>

void CCommandPair::Dump(void) const
{
	cout<<"============================="<<endl;
	cout<<"name: "<<GetName()<<endl;
	cout<<"===========input============"<<endl;
	m_aInputCommand.Dump();
	cout<<"===========output============"<<endl;
	m_aOutputCommand.Dump();
	cout<<"============================="<<endl;

	return;
}
