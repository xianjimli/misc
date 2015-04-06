/*
 * File:    rapi_lib.h
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

#include <assert.h>
#include <stdlib.h>
#include <asm-common.h>
#include <asm-output-buffer.h>
#include <asm-input-buffer.h>
#include <asm-stream.h>
#include <rapi_enums.h>
#include <rapi_macros.h>
#include <rapi_structs.h>

#ifndef RAPI_LIB_H
#define RAPI_LIB_H

AsmRet rapi_stream_read(AsmStream* stream, AsmInputBuffer* input);
AsmRet rapi_stream_write(AsmStream* stream, AsmOutputBuffer* output);

#endif/*RAPI_LIB_H*/

