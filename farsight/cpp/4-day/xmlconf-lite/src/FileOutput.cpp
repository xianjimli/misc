/*
 * FileOutput.cpp
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
#include "FileOutput.h"
#include "DebugUtil.h"

COMM_BEGIN()
	
CFileOutput::CFileOutput()
{
	m_fp = NULL;

	return;
}

CFileOutput::~CFileOutput()
{
	this->Reset();
	return;
}

bool CFileOutput::SetFile(FILE* fp)
{
	m_fp = fp;

	return true;	
}

bool CFileOutput::Put(char c)
{
	bool bRet = false;
	if(m_fp != NULL)
	{
		bRet = (fputc(c, m_fp) != 0);
	}

	return bRet;
}

bool CFileOutput::Put(const char* cBuff, long nLen)
{
	bool bRet = false;
	
	for(long i = 0; i < nLen; i++)
	{
		bRet = this->Put(cBuff[i]);
		if(!bRet) break;
	}
	
	return bRet;
}

bool CFileOutput::Reset()
{
	if(m_fp != NULL)
	{
		int nRet = fflush(m_fp);
		ASSERT(nRet == 0);
		nRet = 0;

		fclose(m_fp);
		m_fp = NULL;
	}
	return true;
}

COMM_END()


