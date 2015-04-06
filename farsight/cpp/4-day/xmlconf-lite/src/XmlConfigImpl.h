/*
 * XmlConfigImpl.h
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
#ifndef XML_XML_CONF_CONFIG_IMPL_H
#define XML_XML_CONF_CONFIG_IMPL_H

XML_BEGIN()
		
class CAccessor;

class CXmlConfigImpl
{
public:
	CXmlConfigImpl();
	~CXmlConfigImpl();
public:
	bool Open(const string& strFileName, bool bIfFailThenAdd);
	bool Save(const string& strFileName, bool bAutoIndent) const;
	
	bool Get(const string& strXPath, string& strVal) const;
	bool Set(const string& strXPath, const string& strVal, bool bIfFailThenAdd);
	bool Del(const string& strXPath, const string& strVal);  
private:
	CAccessor* m_pAccessor;
};

XML_END()

#endif//XML_XML_CONF_CONFIG_IMPL_H
