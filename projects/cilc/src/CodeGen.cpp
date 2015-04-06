/*
 * CodeGen.cpp
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

#include <algorithm>
#include <ctype.h>
#include "CodeGen.h"

CCodeGen::CCodeGen()
{
}

CCodeGen::~CCodeGen()
{
}
	
bool CCodeGen::Gen(const CCommandPairs& aCommandPairs)
{
	this->OnBegin(aCommandPairs);

	vector<CCommandPair>::const_iterator iter = aCommandPairs.GetCommandPairs().begin();
	vector<CCommandPair>::const_iterator end  = aCommandPairs.GetCommandPairs().end();

	for(; iter != end; iter++)
	{
		this->OnCommandPair(*iter);
	}

	this->OnEnd(aCommandPairs);

	return true;
}

bool CCodeGen::OnCommandPair(const CCommandPair& aCommandPair)
{
	vector<CParam>::const_iterator iter;
	vector<CParam>::const_iterator end;

	const CCommand& aInputCommand  = aCommandPair.GetInputCommand();
	const CCommand& aOutputCommand = aCommandPair.GetOutputCommand();
	
	m_strCommandName = aCommandPair.GetName();
	
	m_strLowerCommandName = m_strCommandName;
	transform(m_strLowerCommandName.begin(), m_strLowerCommandName.end(), m_strLowerCommandName.begin(), tolower);
	
	m_strUpperModuleName = m_strCommandName;
	transform(m_strUpperModuleName.begin(), m_strUpperModuleName.end(), m_strUpperModuleName.begin(), toupper);

	this->GenRequestFunction(aCommandPair);
	this->GenResponseFunction(aCommandPair);
	this->GenResponseImplFunction(aCommandPair);

	return true;
}

bool CCodeGen::OnInputCommandParam(const CCommand& aCommand, const CParam& aParam)
{
	return true;
}

bool CCodeGen::OnOutputCommandParam(const CCommand& aCommand, const CParam& aParam)
{

	return true;
}

bool CCodeGen::GenCreateDestroy(const string& strClassName, string& strDecl, string& strDefine)
{
	strDecl += "struct _" + strClassName + ";\n";
	strDecl += "typedef struct _" + strClassName + " " + strClassName + ";\n";
	strDecl += strClassName + "* " + m_strLowerModuleName + "_create(int in, int out);\n\n";
	strDecl += "void " + m_strLowerModuleName + "_destroy(" + strClassName + " *thiz);\n\n";
	
	strDefine += "struct _" + strClassName + "\n";
	strDefine += "{\n";
	strDefine += "	int in;\n";
	strDefine += "	int out;\n";
	strDefine += "};\n\n";
	
	strDefine += strClassName + "* " + m_strLowerModuleName + "_create(int in, int out)\n";
	strDefine += "{\n";
	strDefine += "	" + strClassName + "* thiz = (" + strClassName + "*)";
	strDefine += "malloc(sizeof(" + strClassName + "));\n\n";
	strDefine += "	thiz->in = in;\n";
	strDefine += "	thiz->out = out;\n\n";
	strDefine += "	return thiz;\n";
	strDefine += "}\n\n";

	strDefine += "void " + m_strLowerModuleName + "_destroy(" + strClassName + " *thiz)\n";
	strDefine += "{\n";
	strDefine += "	if(thiz != NULL)\n";
	strDefine += "	{\n";
	strDefine += "		close(thiz->in);\n";
	strDefine += "		close(thiz->out);\n";
	strDefine += "		free(thiz);\n\n";
	strDefine += "		return;\n";
	strDefine += "	}\n\n";
	strDefine += "	return;\n";
	strDefine += "}\n\n";

	return true;
}

bool CCodeGen::GenReadWrite(const string& strClassName, bool bRequest, string& strDecl, string& strDefine)
{
	string strReadLength;
	string strWriteLength;

	if(bRequest)
	{
		strReadLength = "MAX_RESPONSE_LENGTH";
		strWriteLength = "MAX_REQUEST_LENGTH";
	}
	else
	{
		strWriteLength = "MAX_RESPONSE_LENGTH";
		strReadLength = "MAX_REQUEST_LENGTH";
	}
	
	strDecl += "BOOL " + m_strLowerModuleName + "_read(" + strClassName + "* thiz, ";
	strDecl += "char str[" + strReadLength + " + 1]);\n";
	
	strDecl += "BOOL " + m_strLowerModuleName + "_write(" + strClassName + "* thiz, ";
	strDecl += "const char str[" + strWriteLength + "+1]);\n\n";
	
	strDefine += "BOOL " + m_strLowerModuleName + "_read(" + strClassName + "* thiz, ";
	strDefine += "char str[" + strReadLength + " + 1])\n";
	strDefine += "{\n";
	strDefine += "	return read(thiz->in, str, " + strReadLength + ") == " + strReadLength + ";\n";
	strDefine += "}\n\n";
	
	strDefine += "BOOL " + m_strLowerModuleName + "_write(" + strClassName + "* thiz,";
	strDefine += "const char str[" + strWriteLength + "+1])\n";
	strDefine += "{\n";
	strDefine += "	return write(thiz->out, str, " + strWriteLength + ") == " + strWriteLength + ";\n";
	strDefine += "}\n\n";

	return true;
}

bool CCodeGen::GenFileNames(void)
{
	m_strRequestDeclFileName = "command_request.h";
	m_strRequestDefineFileName = "command_request.c";
	
	m_strResponseDeclFileName = "command_response.h";
	m_strResponseDefineFileName = "command_response.c";
	
	m_strResponseImplDefineFileName = "command_response_impl.c";
	m_strResponseImplDeclFileName = "command_response_impl.h";

	return true;
}

bool CCodeGen::OnBegin(const CCommandPairs& aCommandPairs)
{
	m_strRequestDecl = "";
	m_strResponseDefine = "";
	m_strRequestDefine = "";
	m_strResponseDecl = "";
	m_strResponseImplDefine = "";
	m_strResponseImplDecl = "";

	this->GenFileNames();
	
	m_strModuleName = aCommandPairs.GetName();
	m_strLowerModuleName = m_strModuleName;
	m_strUpperModuleName = m_strModuleName;

	m_strRequestClass = m_strModuleName + "Request";
	m_strResponseClass = m_strModuleName + "Response";

	transform(m_strLowerModuleName.begin(), m_strLowerModuleName.end(), m_strLowerModuleName.begin(), tolower);
	transform(m_strUpperModuleName.begin(), m_strUpperModuleName.end(), m_strUpperModuleName.begin(), toupper);

	m_strRequestDecl  = "#ifndef " + m_strUpperModuleName + "_REQUEST_H\n";
	m_strRequestDecl += "#define " + m_strUpperModuleName + "_REQUEST_H\n";
	m_strRequestDecl += "#include \"command_type.h\"\n\n";
	
	m_strRequestDefine += "#include \"" + m_strRequestDeclFileName + "\"\n";

	this->GenCreateDestroy(m_strRequestClass, m_strRequestDecl, m_strRequestDefine);
	this->GenReadWrite(m_strRequestClass, true, m_strRequestDecl, m_strRequestDefine);

	m_strResponseDecl  = "#ifndef " + m_strUpperModuleName + "_RESPONSE_H\n";
	m_strResponseDecl += "#define " + m_strUpperModuleName + "_RESPONSE_H\n";
	m_strResponseDecl += "#include \"command_type.h\"\n\n";
	
	m_strResponseDefine += "#include \"" + m_strResponseDeclFileName + "\"\n\n";
	
	this->GenCreateDestroy(m_strResponseClass, m_strResponseDecl, m_strResponseDefine);
	this->GenReadWrite(m_strResponseClass, false, m_strResponseDecl, m_strResponseDefine);
	
	m_strResponseImplDecl  = "#ifndef " + m_strUpperModuleName + "_IMPL_RESPONSE_H\n";
	m_strResponseImplDecl += "#define " + m_strUpperModuleName + "_IMPL_RESPONSE_H\n";
	m_strResponseImplDecl += "#include \"command_type.h\"\n";
	m_strResponseImplDecl += "#include \"" + m_strResponseDeclFileName + "\"\n\n";

	m_strResponseImplDefine += "#include \"" + m_strResponseImplDeclFileName + "\"\n\n";


	m_strDispatch = "typedef BOOL (*command_handler)(" + m_strResponseClass 
					+ "* thiz, char str[MAX_RESPONSE_LENGTH + 1]);\n";
	m_strDispatch += "struct _CommandEntry\n";
	m_strDispatch += "{\n";
	m_strDispatch += "	char* prefix;\n";
	m_strDispatch += "	command_handler cmd;\n";
	m_strDispatch += "};\n";
	m_strDispatch += "typedef struct _CommandEntry CommandEntry;\n\n";
	m_strDispatch += "static CommandEntry g_Commands[] = \n";
	m_strDispatch += "{\n";
	
	return true;
}

bool CCodeGen::Save(const string& strFileName, const string& strContent) const
{
	FILE* fp = fopen(strFileName.c_str(), "w+");

	if(fp != NULL)
	{
		fprintf(fp, "%s", strContent.c_str());
		fclose(fp);
	}

	return true;
}

bool CCodeGen::OnEnd(const CCommandPairs& aCommandPairs)
{

	m_strDispatch += "	{NULL, NULL}\n";
	m_strDispatch += "};\n";

	m_strResponseDefine += m_strDispatch;

	m_strRequestDecl += "\n#endif/*" + m_strUpperModuleName + "_REQUEST_H*/\n";
	m_strResponseDecl += "\n#endif/*" + m_strUpperModuleName + "_RESPONSE_H*/\n";
	m_strResponseImplDecl += "\n#endif/*" + m_strUpperModuleName + "_IMPL_RESPONSE_H*/\n";
	

	this->Save(m_strRequestDeclFileName.c_str(), m_strRequestDecl);
	this->Save(m_strRequestDefineFileName.c_str(), m_strRequestDefine);
	this->Save(m_strResponseDeclFileName.c_str(), m_strResponseDecl);
	this->Save(m_strResponseDefineFileName.c_str(), m_strResponseDefine);
	this->Save(m_strResponseImplDeclFileName.c_str(), m_strResponseImplDecl);
	this->Save(m_strResponseImplDefineFileName.c_str(), m_strResponseImplDefine);
	
	return true;
}

bool CCodeGen::GenParam(const CCommand& aCommand, bool bOutput, string& strParamList, 
		string& strParamDecl, string& strParamNameList)
{
	vector<CParam>::const_iterator begin = aCommand.GetParams().begin();
	vector<CParam>::const_iterator iter = aCommand.GetParams().begin();
	vector<CParam>::const_iterator end = aCommand.GetParams().end();

	strParamList = "";
	strParamDecl = "";
	strParamNameList = "";
	for(; iter != end; iter++)
	{
		strParamList += ", ";

		if(iter->GetType() == "char" && !bOutput)
		{
			strParamList += "const ";
		}
		
		strParamList += iter->GetType();
		
		if(bOutput)
		{
			if(iter->GetType() != "char")
			{
				strParamList += "*";
			}
		}
		strParamList += " " + iter->GetName();
		if(iter->GetType() == "char")
		{
			strParamList += "[" + iter->GetStringLength() + "]" ;
		}

		////////////////////////////////////////
		strParamDecl += "	" + iter->GetType();
		strParamDecl += " " + iter->GetName();
		if(iter->GetType() == "char")
		{
			strParamDecl += "[" + iter->GetStringLength() + "]" ;
		}
		strParamDecl += " = {0};\n";
		////////////////////////////////////////
	
		if(bOutput)
		{
			strParamNameList += ", &" + iter->GetName();
		}
		else
		{
			strParamNameList += ", " + iter->GetName();
		}
	}

	return true;
}
	
bool CCodeGen::GenRequestFuncName(string& strFuncName)
{
	strFuncName = m_strLowerModuleName + "_" + m_strLowerCommandName;

	return true;
}

bool CCodeGen::GenResponseFuncName(string& strFuncName)
{
	strFuncName = m_strLowerModuleName + "_" + m_strLowerCommandName;

	return true;
}

bool CCodeGen::GenRequestFunction(const CCommandPair& aCommandPair)
{
	string strFuncName;
	string strInputParamList;
	string strOutputParamList;
	string strInputParamNameList;
	string strOutputParamNameList;
	string strParamDecl;
	string strFuncPrototype;
	
	const CCommand& aInputCommand = aCommandPair.GetInputCommand();
	const CCommand& aOutputCommand = aCommandPair.GetOutputCommand();
	
	this->GenRequestFuncName(strFuncName);
	this->GenParam(aInputCommand, false, strInputParamList, strParamDecl, strInputParamNameList);
	this->GenParam(aOutputCommand, true, strOutputParamList, strParamDecl, strOutputParamNameList);

	strFuncPrototype  = "BOOL " + strFuncName + "(" + m_strRequestClass + "* thiz";
	strFuncPrototype += strInputParamList + strOutputParamList;
	strFuncPrototype += ")";

	m_strRequestDecl += strFuncPrototype + ";\n";

	m_strRequestDefine += strFuncPrototype + "\n"; 
	m_strRequestDefine += "{\n";
	m_strRequestDefine += "	char request[MAX_REQUEST_LENGTH + 1] = {0};\n";
	m_strRequestDefine += "	char response[MAX_RESPONSE_LENGTH + 1] = {0};\n";
	m_strRequestDefine += "\n";

	m_strRequestDefine += "	snprintf(request, MAX_REQUEST_LENGTH, \"" + aInputCommand.GetFormat() + "\"";
	m_strRequestDefine += strInputParamNameList + ");\n";
	m_strRequestDefine += "\n";
	m_strRequestDefine += "	if(!" + m_strLowerModuleName + "_write(thiz, " + string("request") + "))\n";
	m_strRequestDefine += "	{\n";
	m_strRequestDefine += "		return FALSE;\n";
	m_strRequestDefine += "	}\n";
	m_strRequestDefine += "\n";
	m_strRequestDefine += "	if(!" + m_strLowerModuleName + "_read(thiz, " + string("response") + "))\n";
	m_strRequestDefine += "	{\n";
	m_strRequestDefine += "		return FALSE;\n";
	m_strRequestDefine += "	}\n";
	m_strRequestDefine += "\n";
	this->GenParam(aOutputCommand, false, strOutputParamList, strParamDecl, strOutputParamNameList);
	m_strRequestDefine += "	if(sscanf(response, \"" + aOutputCommand.GetFormat() + "\"" + strOutputParamNameList + ")";
	m_strRequestDefine += " != " + this->GetCommandParamCount(aOutputCommand) + ")\n";
	m_strRequestDefine += "	{\n";
	m_strRequestDefine += "		return FALSE;\n";
	m_strRequestDefine += "	}\n";
	m_strRequestDefine += "\n";
	m_strRequestDefine += "	return TRUE;\n";

	m_strRequestDefine += "}\n";
	m_strRequestDefine += "\n";
	
	return true;
}

bool CCodeGen::GenResponseImplFuncName(string& strImplFuncName)
{
	strImplFuncName = m_strLowerModuleName + "_" + m_strLowerCommandName + "_impl";

	return true;
}

bool CCodeGen::GenResponseFunction(const CCommandPair& aCommandPair)
{
	string strFuncName;
	string strInputParamList;
	string strOutputParamList;
	string strInputParamNameList;
	string strOutputParamNameList;
	string strInputParamDecl;
	string strOutputParamDecl;
	string strFuncPrototype;
	
	const CCommand& aInputCommand = aCommandPair.GetInputCommand();
	const CCommand& aOutputCommand = aCommandPair.GetOutputCommand();
	
	this->GenRequestFuncName(strFuncName);
	this->GenParam(aInputCommand, false, strInputParamList, strInputParamDecl, strInputParamNameList);
	this->GenParam(aOutputCommand, true, strOutputParamList, strOutputParamDecl, strOutputParamNameList);

	strFuncPrototype  = "BOOL " + strFuncName + "(" + m_strResponseClass;
	strFuncPrototype  += "* thiz, const char request[MAX_REQUEST_LENGTH+1])";

	m_strResponseDecl += strFuncPrototype + ";\n";

	m_strResponseDefine += strFuncPrototype + "\n";
	m_strResponseDefine += "{\n";
	m_strResponseDefine += "	char response[MAX_RESPONSE_LENGTH + 1] = {0};\n";
	m_strResponseDefine += strInputParamDecl;
	m_strResponseDefine += strOutputParamDecl;
	m_strResponseDefine += "\n";
	this->GenParam(aInputCommand, true, strInputParamList, strInputParamDecl, strInputParamNameList);
	m_strResponseDefine += "	if(sscanf(request, \"" + aInputCommand.GetFormat() + "\"" + strInputParamNameList + ")";
	m_strResponseDefine += " != " + this->GetCommandParamCount(aInputCommand) + ")\n";
	m_strResponseDefine += "	{\n";
	m_strResponseDefine += "		return FALSE;\n";
	m_strResponseDefine += "	}\n";
	this->GenParam(aInputCommand, false, strInputParamList, strInputParamDecl, strInputParamNameList);
	m_strResponseDefine += "\n";
	m_strResponseDefine += "	" + strFuncName + "_impl(thiz" + strInputParamNameList + strOutputParamNameList + ");\n";
	m_strResponseDefine += "\n";

	this->GenParam(aOutputCommand, false, strOutputParamList, strOutputParamDecl, strOutputParamNameList);

	m_strResponseDefine += "	snprintf(response, MAX_RESPONSE_LENGTH, \"" + aOutputCommand.GetFormat() + "\"";
	m_strResponseDefine += strOutputParamNameList + ");\n"; 
	m_strResponseDefine += "\n";
	m_strResponseDefine += "	if(!" + m_strLowerModuleName + "_write(thiz, " + string("response") + "))\n";
	m_strResponseDefine += "	{\n";
	m_strResponseDefine += "		return FALSE;\n";
	m_strResponseDefine += "	}\n";
	m_strResponseDefine += "\n";
	m_strResponseDefine += "	return TRUE;\n";
	m_strResponseDefine += "}\n";
	m_strResponseDefine += "\n";

	m_strDispatch += "	{\"" + aOutputCommand.GetPrefix() + "\", " +  strFuncName + "},\n";
	
	return true;
}

bool CCodeGen::GenResponseImplFunction(const CCommandPair& aCommandPair)
{
	string strFuncName;
	string strInputParamList;
	string strOutputParamList;
	string strInputParamNameList;
	string strOutputParamNameList;
	string strInputParamDecl;
	string strOutputParamDecl;
	string strFuncPrototype;
	
	const CCommand& aInputCommand = aCommandPair.GetInputCommand();
	const CCommand& aOutputCommand = aCommandPair.GetOutputCommand();
	
	this->GenRequestFuncName(strFuncName);
	this->GenParam(aInputCommand, false, strInputParamList, strInputParamDecl, strInputParamNameList);
	this->GenParam(aOutputCommand, true, strOutputParamList, strOutputParamDecl, strOutputParamNameList);

	strFuncPrototype  = "BOOL " + strFuncName + "_impl(" + m_strResponseClass + "* thiz";
	strFuncPrototype += strInputParamList + strOutputParamList;
	strFuncPrototype += ")";

	m_strResponseImplDecl += strFuncPrototype + ";\n";

	m_strResponseImplDefine += strFuncPrototype + "\n";
	m_strResponseImplDefine += "{\n";
	m_strResponseImplDefine += "	/*TODO: write the implementation code at here*/\n";
	m_strResponseImplDefine += "	return TRUE;\n";
	m_strResponseImplDefine += "}\n";

	return true;
}

string CCodeGen::GetCommandParamCount(const CCommand& aCommand) const
{
	char buff[32] = {0};

	sprintf(buff, "%d", aCommand.GetParams().size());

	return buff;
}
