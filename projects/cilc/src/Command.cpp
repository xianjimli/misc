/*
 * Command.cpp
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

#include "Command.h"

CCommand::CCommand(void)
{
}

CCommand::~CCommand(void)
{
}

bool CCommand::Create(const string& strPrefix, const string& strOrgFormat)
{
	size_t i = 0;
	CParam aParam;

	m_params.clear();
	m_strPrefix = strPrefix;
	m_strFormat = "";

	for(i = 0; i < strOrgFormat.length(); i++)
	{
		if(strOrgFormat[i] == '%')
		{
			break;
		}

		m_strFormat += strOrgFormat[i];
	}
	
	for(; i < strOrgFormat.length(); i++)
	{
		if(strOrgFormat[i] == '%')
		{
			if(strOrgFormat[i + 1] == '%')
			{
				i++;
			}
			else
			{
				if(aParam.Create(strOrgFormat.c_str() + i))
				{
					m_params.push_back(aParam);
					m_strFormat += aParam.GetFormat();
				}
			}
		}
	}

	return !strPrefix.empty(); 
}
	
const string& CCommand::GetPrefix(void) const
{
	return m_strPrefix;
}

const string& CCommand::GetFormat(void) const
{
	return m_strFormat;
}

const vector<CParam>& CCommand::GetParams(void) const
{
	return m_params;
}

#include <iostream>

void CCommand::Dump(void) const
{
	cout<< "prefix: " << GetPrefix() <<endl;
	cout<< "format: " << GetFormat() <<endl;

	for(vector<CParam>::const_iterator iter = m_params.begin(); iter != m_params.end(); iter++)
	{
		iter->Dump();
	}

	return;
}

#ifdef COMMAND_TEST
int main(int argc, char* argv[])
{
	CCommand aComand;

	if(aComand.Create("play", "filename=%{filename}s priority=%{priority}d "))
	{
		aComand.Dump();
	}
	
	return 0;
}
#endif/*COMMAND_TEST*/
