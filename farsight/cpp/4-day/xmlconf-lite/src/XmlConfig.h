/*
 * XmlConfig.h
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
#ifndef XML_XML_CONFIG_H
#define XML_XML_CONFIG_H

#include "Xml.h"
#include <string>
using std::string;
//
//README: 
// XPATH: /tag1{[indextag1]}/tag2{[indextag2]}/.../{@attribute|#text{[index]}|#comment{[index]}|#pi{[index]}}
// For example: Access text node: /html/body/p[2]/#text   
//              Access attribute: /html/body/p[2]/@align 
//              Access comment  : /html/body/#comment[2]
//
// Usage: refer CXmlConfig.cpp:main
//

XML_BEGIN()
		
class CXmlConfigImpl;

class XML_API CXmlConfig
{
public:
	CXmlConfig();
	~CXmlConfig();
public:
	bool Open(const string& strFileName, bool bIfFailThenCreate = false) throw();
	bool Save(const string& strFileName, bool bAutoIndent) const throw();
	
	bool Get(const string& strXPath, string& strVal) const throw();
	bool Set(const string& strXPath, const string& strVal, bool bIfFailThenAdd = false) throw();
	bool Del(const string& strXPath, const string& strVal) throw();  
private://non-copy
	CXmlConfig(const CXmlConfig&);
	CXmlConfig& operator=(const CXmlConfig&);
private:
	CXmlConfigImpl* m_pImpl;
};

XML_END()

#endif//XML_XML_CONFIG_H
