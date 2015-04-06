/*
 * CodeGen.h
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

#ifndef CODE_GEN_H
#define CODE_GEN_H

#include "CommandPairs.h"

class CCodeGen
{
public:
	CCodeGen();
	~CCodeGen();
	
public:
	bool Gen(const CCommandPairs& aCommandPairs);

private:
	bool OnCommandPair(const CCommandPair& aCommandPair);
	bool OnInputCommandParam(const CCommand& aCommand, const CParam& aParam);
	bool OnOutputCommandParam(const CCommand& aCommand, const CParam& aParam);
	bool OnBegin(const CCommandPairs& aCommandPairs);
	bool OnEnd(const CCommandPairs& aCommandPairs);

	bool GenParam(const CCommand& aCommand, bool bOutput, string& strParamList, 
		string& strParamDecl, string& strParamNameList);

	bool GenFileNames(void) ;
	bool GenRequestFuncName(string& strFuncName);
	bool GenResponseFuncName(string& strFuncName);
	bool GenResponseImplFuncName(string& strImplFuncName);
	bool GenRequestFunction(const CCommandPair& aCommandPair);
	bool GenResponseFunction(const CCommandPair& aCommandPair);
	bool GenResponseImplFunction(const CCommandPair& aCommandPair);
	bool GenCreateDestroy(const string& strClassName, string& strDecl, string& strDefine);
	bool GenReadWrite(const string& strClassName, bool bRequest, string& strDecl, string& strDefine);
	string GetCommandParamCount(const CCommand& aCommand) const;	
	bool Save(const string& strFileName, const string& strContent) const;
private:
	string m_strModuleName;
	string m_strLowerModuleName;
	string m_strUpperModuleName;
	
	string m_strCommandName;
	string m_strLowerCommandName;
	string m_strUpperCommandName;
	
	string m_strRequestClass;
	string m_strResponseClass;

	string m_strDispatch;
	string m_strRequestDecl;
	string m_strRequestDefine;
	string m_strResponseDecl;
	string m_strResponseDefine;
	string m_strResponseImplDecl;
	string m_strResponseImplDefine;
	
	string m_strRequestDeclFileName;
	string m_strRequestDefineFileName;
	string m_strResponseDeclFileName;
	string m_strResponseDefineFileName;
	string m_strResponseImplDeclFileName;
	string m_strResponseImplDefineFileName;
};
#endif/*CODE_GEN_H*/
