/*
 * File:   soft_irq.c   
 * Author: Li XianJing <xianjimli@hotmail.com>
 * Brief:  swi handler. 
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
#include <trace.h>
#include <jtype.h>
#include <jos_type.h>

typedef struct _SwiRegs
{
	jword_t r[13];
	jword_t cpsr;
	jword_t pc; 
} SwiRegs;

int swi_dispatch(jword_t swi_no, SwiRegs* regs)
{
	os_trace(__func__, __LINE__, "enter");

	switch(regs->r[0])
	{
		case SYS_TRACE:
		{
			os_trace((const char*)regs->r[1], regs->r[2], (const char*)regs->r[3]);
			break;
		}
		default:
		{
			os_trace(__func__, __LINE__, "unhandle.");
			break;
		}
	}
	os_trace(__func__, __LINE__, "leave");

	return 0;
}
