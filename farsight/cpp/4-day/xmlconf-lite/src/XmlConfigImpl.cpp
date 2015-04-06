/*
 * XmlConfigImpl.cpp
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
#include "Input.h"
#include "FileOutput.h"

USE_COMM;

#include "XmlAccessor.h"
#include "XmlParser.h"
#include "FileInput.h"
#include "XmlConfigImpl.h"
#include "DebugUtil.h"

XML_BEGIN()
		
CXmlConfigImpl::CXmlConfigImpl()
{
	m_pAccessor = new CAccessor();

	return;
}

CXmlConfigImpl::~CXmlConfigImpl()
{
	delete m_pAccessor;
	m_pAccessor = NULL;

	return;
}
	
bool CXmlConfigImpl::Open(const string& strFileName, bool bIfFailThenAdd)
{
	ASSERT(strFileName.length() > 0);
	if(strFileName.length() == 0) return false;

	//Create aFileInput
	CFileInput aFileInput;
	FILE* fp = fopen(strFileName.c_str(), "r");
	if(fp == NULL)
	{
		if(bIfFailThenAdd)
		{
			fp = fopen(strFileName.c_str(), "w+");
		}
		else
		{
			return false;
		}
	}
	if(fp == NULL) return false;
	aFileInput.SetFile(fp);


	CParser aParser;
	bool bRet = false;
	
	CNode* pDoc = aParser.GetXMLDocument(&aFileInput);

	if(pDoc != NULL)
	{
		bRet = m_pAccessor->SetRootNode(pDoc);
	}

	return bRet;
}

bool CXmlConfigImpl::Save(const string& strFileName, bool bAutoIndent) const
{

	ASSERT(m_pAccessor != NULL);
	bool bRet = false;

	if(m_pAccessor != NULL)
	{
		FILE* fp = fopen(strFileName.c_str(), "w+");
		if(fp != NULL)
		{
			CFileOutput aFileOutput;
			aFileOutput.SetFile(fp);
			bRet = m_pAccessor->Save(&aFileOutput, bAutoIndent);
		}
	}
	
	return bRet;
}

bool CXmlConfigImpl::Get(const string& strXPath, string& strVal) const
{
	ASSERT(m_pAccessor != NULL);
	if(m_pAccessor != NULL)
	{
		return m_pAccessor->Get(strXPath, strVal);
	}

	return false;
}

bool CXmlConfigImpl::Set(const string& strXPath, const string& strVal, bool bIfFailThenAdd)
{
	ASSERT(m_pAccessor != NULL);
	if(m_pAccessor != NULL)
	{
		return m_pAccessor->Set(strXPath, strVal, bIfFailThenAdd);
	}

	return false;
}

bool CXmlConfigImpl::Del(const string& strXPath, const string& strVal)
{
	ASSERT(m_pAccessor != NULL);
	if(m_pAccessor != NULL)
	{
		return m_pAccessor->Del(strXPath, strVal);
	}

	return false;
}

XML_END()
