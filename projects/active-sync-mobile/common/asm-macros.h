/*
 * File:    asm-macros.h
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

#ifndef _ASM_MACORS_H
#define _ASM_MACORS_H

#define ASM_TO_LE32(n)   uint32_to_endian(n, ASM_ENDIAN_LITTLE)
#define ASM_TO_LE16(n)   uint16_to_endian(n, ASM_ENDIAN_LITTLE)
#define ASM_FROM_LE32(n) uint32_from_endian(n, ASM_ENDIAN_LITTLE)
#define ASM_FROM_LE16(n) uint16_from_endian(n, ASM_ENDIAN_LITTLE)

#define ASM_ALLOC(type, extra) (type*)calloc(1, (sizeof(type) + extra))
#define ASM_FREE(p) if(p != NULL){free(p); p = NULL;}

#define ASM_IS_SOCKET_VALID(sock_no) ((sock_no) > 0)

#define PRINTF printf

#endif/*_ASM_MACORS_H*/

