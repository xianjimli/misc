/*
 * File:   arm7.s 
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  arm7 dependent functions. 
 *
 * Copyright (c) 2009  Li XianJing
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
 * 2009-1-28 Li XianJing <xianjimli@hotmail.com> created
 *
 */
	.text
	.code 32
	.align 0
	.global _syscall, syscall

_syscall:
     stmfd   r13!,  {r0-r4,r12,lr}
     mov     r4,    r0
     ldmia   r4,    {r0-r3}
     swi     0x0000
     stmia   r4,    {r0-r3}
     ldmfd   r13!,  {r0-r4,r12,pc}

.end
