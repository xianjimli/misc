/*
 * XmlConfig.cpp
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
#include "XmlConfig.h"
#include "DebugUtil.h"
#include "XmlConfigImpl.h"

#ifdef WIN32
#include <windows.h>
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
#endif//WIN32

XML_BEGIN()
		
CXmlConfig::CXmlConfig()
{
	m_pImpl = new CXmlConfigImpl();
	return;
}

CXmlConfig::~CXmlConfig()
{
	delete m_pImpl;
	return;
}

bool CXmlConfig::Open(const string& strFileName, bool bIfFailThenAdd) throw()
{
	ASSERT(m_pImpl != NULL);
	bool bRet = false;
	
	if(m_pImpl != NULL)
	{
		try
		{
			bRet = m_pImpl->Open(strFileName, bIfFailThenAdd);
		}
		catch(...)
		{
			return false;
		}
	}
	
	return bRet;
}

bool CXmlConfig::Save(const string& strFileName, bool bAutoIndent) const throw()
{
	ASSERT(m_pImpl != NULL);
	ASSERT(strFileName.length() > 0);
	bool bRet = false;

	if(m_pImpl != NULL && strFileName.length() > 0)
	{
		try
		{
			bRet = m_pImpl->Save(strFileName, bAutoIndent);
		}
		catch(...)
		{
			return false;
		}
	}

	return bRet;
}

bool CXmlConfig::Get(const string& strXPath, string& strVal) const throw()
{
	ASSERT(m_pImpl != NULL);
	bool bRet = false;
	
	if(m_pImpl != NULL)
	{
		try
		{
			bRet = m_pImpl->Get(strXPath, strVal);
		}
		catch(...)
		{
			return false;
		}
	}
	
	return bRet;
}

bool CXmlConfig::Set(const string& strXPath, const string& strVal, bool bIfFailThenAdd) throw()
{
	ASSERT(m_pImpl != NULL);
	bool bRet = false;
	
	if(m_pImpl != NULL)
	{
		try
		{
			bRet = m_pImpl->Set(strXPath, strVal, bIfFailThenAdd);
		}
		catch(...)
		{
			return false;
		}
	}
	return bRet;
}

bool CXmlConfig::Del(const string& strXPath, const string& strVal) throw()
{
	ASSERT(m_pImpl != NULL);
	bool bRet = false;
	
	if(m_pImpl != NULL)
	{
		try
		{
			bRet = m_pImpl->Del(strXPath, strVal);
		}
		catch(...)
		{
			return false;
		}
	}

	return bRet;
}

XML_END()

#ifdef XML_CONFIG_TEST

using namespace AV;
using namespace XML_CONF;
int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("Usage: %s [xml] [xpath] {[value]}\n", argv[0]);
		return 0;
	}

	CXmlConfig aXmlConfig;
	if(aXmlConfig.Open(string(argv[1])))
	{
		if(argc == 3)
		{
			string strVal;
			aXmlConfig.Get(string(argv[2]), strVal);
			printf("Old:%s = %s\n", argv[2], strVal.c_str());
			aXmlConfig.Set(string(argv[2]), string(argv[3] != NULL?argv[3]:"LiXianJing"));
			
			aXmlConfig.Get(string(argv[2]), strVal);
			printf("New: %s = %s\n", argv[2], strVal.c_str());
			aXmlConfig.Save(string("lxj.xml"), false);
		}
	}
	else
	{
		printf("Parse Failed!\n");
	}
	return 0;
}
#endif//XML_CONFIG_TEST
