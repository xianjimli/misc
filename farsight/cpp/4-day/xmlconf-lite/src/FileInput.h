/*
 * FileInput.h
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
#ifndef COMM_FILE_INPUT_H
#define COMM_FILE_INPUT_H

#include <stdio.h>
#include <string>
using std::string;

#include "Input.h"

COMM_BEGIN()
	
class COMM_API CFileInput:public CInput
{
public:
	CFileInput();
	~CFileInput();
public:
	bool SetFile(FILE* fp);
	bool SetFile(const string& strFileName);

	bool Get(int &c);
	bool Unget(int c);
private:
	bool Reset(void);
private:
	FILE* m_fp;
};

COMM_END()

#endif//COMM_FILE_INPUT_H
