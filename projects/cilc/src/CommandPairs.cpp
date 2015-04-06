/*
 * CommandPairs.cpp
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

#include <iostream>
#include <XmlConfig.h>
#include "CommandPairs.h"

USE_XML;

CCommandPairs::CCommandPairs(void)
{
}

CCommandPairs::~CCommandPairs(void)
{
}

bool CCommandPairs::Load(const string& strFileName)
{
	char szXPath[260] = {0};
	CXmlConfig aXmlConfig;

	if(aXmlConfig.Open(strFileName, false))
	{
		size_t i = 0;
		sprintf(szXPath, "/cil/@name");
		
		if(!aXmlConfig.Get(szXPath, m_strName))
		{
			cout <<"get /cil/@name failed"<<endl;
			return false;
		}

		CCommandPair aCommandPair;

		for(i = 0; ; i++)
		{
			bool ret = true;
			string strName = "";
			string strInputPrefix = "";
			string strInputFormat = "";
			string strOutputPrefix = "";
			string strOutputFormat = "";
			
			sprintf(szXPath, "/cil/command[%d]/@name", i);
			if(aXmlConfig.Get(szXPath, strName))
			{
				sprintf(szXPath, "/cil/command[%d]/input/@prefix", i);
				ret = aXmlConfig.Get(szXPath, strInputPrefix);
				
				sprintf(szXPath, "/cil/command[%d]/input/@format", i);
				ret = aXmlConfig.Get(szXPath, strInputFormat);
				
				sprintf(szXPath, "/cil/command[%d]/output/@prefix", i);
				ret = aXmlConfig.Get(szXPath, strOutputPrefix);
				
				sprintf(szXPath, "/cil/command[%d]/output/@format", i);
				ret = aXmlConfig.Get(szXPath, strOutputFormat);

				if(aCommandPair.Create(strName, strInputPrefix, strInputFormat, strOutputPrefix, strOutputFormat))
				{
					m_CommandPairs.push_back(aCommandPair);
				}
			}
			else
			{
				break;
			}
		}
	}
	
	return !m_CommandPairs.empty() && !m_strName.empty();
}

const vector<CCommandPair>& CCommandPairs::GetCommandPairs(void) const
{
	
	return m_CommandPairs;
}

const string& CCommandPairs::GetName(void) const
{
	return m_strName;
}

void CCommandPairs::Dump(void) const
{
	vector<CCommandPair>::const_iterator iter = m_CommandPairs.begin();

	cout<<GetName()<<endl;
	for(; iter != m_CommandPairs.end(); iter++)
	{
		iter->Dump();
	}
	
	return;
}

