/*
 * Common.h
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

#ifndef COMMON_H
#define COMMON_H

#ifdef WIN32
#ifdef COMMON_EXPORTS
#define COMM_API __declspec(dllexport)
#else
#define COMM_API __declspec(dllimport)
#endif
#pragma warning(disable: 4251)
#pragma warning(disable: 4786)
#else 
#define COMM_API
#endif

#define COMM_BEGIN() namespace COMM {
#define COMM_END() };
#define USE_COMM using namespace COMM;

#endif//COMMON_H
