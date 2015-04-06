/*
 * FileInput.cpp
 * Copyright (C) 2006-2007 Li XianJing <xianjimli@hotmail.com
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
#include <stdio.h>
#include "DebugUtil.h"
#include "FileInput.h"

COMM_BEGIN()
	
CFileInput::CFileInput()
{
	m_fp = NULL;

	return;
}

CFileInput::~CFileInput()
{
	this->Reset();

	return;
}
	
bool CFileInput::SetFile(FILE* fp)
{
	this->Reset();
	m_fp = fp;
	
	return true;
}

bool CFileInput::SetFile(const string& strFileName)
{
	ASSERT(strFileName.length() != 0);
	bool bRet = false;

	if(strFileName.length() != 0)
	{
		FILE* fp = fopen(strFileName.c_str(), "r");
		if(fp != NULL)
		{
			this->Reset();
			m_fp = fp;
			bRet = true;
		}
	}

	return bRet;
}

bool CFileInput::Get(int &c)
{
	ASSERT(m_fp != NULL);
	bool bRet = false;
	if(m_fp != NULL)
	{
		if(!feof(m_fp))
		{
			c = fgetc(m_fp);
			if(c != EOF) bRet = true;
		}
	}

	return bRet;
}

bool CFileInput::Unget(int c)
{
	 ASSERT(m_fp != NULL);
	 bool bRet = false;
	 if(m_fp != NULL)
	 {
		 bRet = (ungetc(c, m_fp) == 0);
	 }

	 return bRet;
}

bool CFileInput::Reset(void)
{
	if(m_fp != NULL)
	{
		fclose(m_fp);
		m_fp = NULL;
	}

	return true;
}

COMM_END()

