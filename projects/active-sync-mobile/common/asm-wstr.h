/*
 * File:    asm-wstr.h
 * Author:  Li XianJing <lixianjing@broncho.org>
 * Brief:   
 *
 * Copyright (c) 2008 topwise, Inc.
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2008-01-28 Li XianJing <lixianjing@topwisesz.com> created
 *
 */

#include <asm-types.h>

#ifndef ASM_WSTR_H
#define ASM_WSTR_H

size_t wstr_length(const WStr* str);
int    wstr_compare(const WStr* str1, const WStr* str2);
WStr*  wstr_from_ascii(WStr* str, const char* ascii, size_t chas_nr);
WStr*  wstr_dup(WStr* str);
WStr*  wstr_dup_from_ascii(const char* ascii);
char*  wstr_to_ascii(WStr* str);

#endif/*ASM_WSTR_H*/

