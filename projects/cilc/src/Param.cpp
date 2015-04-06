/*
 * Param.cpp
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

#include "Param.h"

CParam::CParam(void)
{
	return;
}

CParam::~CParam(void)
{
	return;
}
	
bool CParam::Create(const string& str)
{
	enum 
	{
		STAT_IN_NONE,
		STAT_IN_NAME,
		STAT_IN_TYPE,
		STAT_NR
	}eState;
	
	eState = STAT_IN_NONE;

	string::const_iterator iter = str.begin();

	if(*iter != '%')
	{
		return false;
	}
	
	m_strType = "";
	m_strName = "";
	m_strFormat = "";
	m_bIsOptional = false;
	m_strStringLength = "";

	m_strFormat = *iter;
	++iter;
	
	for(; iter != str.end() && *iter != '%'; iter++)
	{
		switch(eState)
		{
			case STAT_IN_NONE:
			{
				if(*iter == '{')
				{
					m_bIsOptional = false;
					eState = STAT_IN_NAME;
				}
				else if(*iter == '(')
				{
					m_bIsOptional = true;
					eState = STAT_IN_NAME;
				}
				break;
			}
			case STAT_IN_NAME:
			{
				if(*iter == '}' || *iter == ')')
				{
					eState = STAT_IN_TYPE;
				}
				else
				{
					m_strName += *iter;
				}
				break;
			}
			case STAT_IN_TYPE:
			{
				if(m_strType.empty())
				{
					if(*iter == 'd')
					{
						m_strType = "int";
					}
					else if(*iter == 'u')
					{
						m_strType = "unsigned int";
					}
					else if(*iter == 'x')
					{
						m_strType = "int";
					}
					else if(*iter == 's')
					{
						m_strType = "char";
					}
					else if(*iter == 'f')
					{
						m_strType = "float";
					}
				}

				m_strFormat += *iter;
				break;
			}
			default:break;
		}
	}

	if(m_strType == "char")
	{
		char* name = strdup(m_strName.c_str());
		char* len = strchr(name, '[');
		char* end = NULL;
		
		if(len != NULL)
		{
			*len = '\0';
			m_strName = name;
			++len;
			
			end = strchr(len, ']');
			if(end != NULL)
			{
				*end = '\0';
			}
			m_strStringLength = len;
		}
		else
		{
			m_strStringLength = "2";
		}
	}

	return !m_strName.empty() && !m_strType.empty() && !m_strFormat.empty();
}
	
const string& CParam::GetStringLength(void) const
{
	return m_strStringLength;
}

const string& CParam::GetType(void) const
{
	return m_strType;
}

const string& CParam::GetName(void) const
{
	return m_strName;
}

const string& CParam::GetFormat(void) const
{
	return m_strFormat;
}

bool CParam::GetIsOptional(void) const
{
	return m_bIsOptional;
}

#include <iostream>
void CParam::Dump(void) const
{
	cout << "name: " << GetName();
	if(m_strType == "char")
	{
		cout << "["<< GetStringLength() << "]";
	}
	cout << " type: " <<GetType() ;
	cout << " format:" << GetFormat() << "optional: "<< GetIsOptional();
	cout << endl;	

	return;
}

#ifdef PARAM_TEST


const char* testcases[] = 
{
	"%{filename[100]}s",
	"%{priority}d",
	"%{priority}x",
	"%{priority}u",
	"%{priority}f",
	"%{priority}02d",
	"%{priority}08x",
	
	"%(filename[100])s",
	"%(priority)d",
	"%(priority)x",
	"%(priority)u",
	"%(priority)f",
	"%(priority)02d",
	"%(priority)08x",
	
	"%(priority)",
	"%<priority",
	NULL
};
int main(int argc, char* argv[])
{
	size_t i = 0;
	CParam aParam;
	
	for(i = 0; testcases[i] != NULL; i++)
	{
		if(aParam.Create(testcases[i]))
		{
			aParam.Dump();
		}
	}

	return 0;
}
#endif/*PARAM_TEST*/
