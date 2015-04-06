/*
 * File:    arm7_memory.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   memory primitives. 
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
 * 2009-1-25 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef MEMORY_OPS_H
#define MEMORY_OPS_H

#include <arm7_macro.h>

void arm7_store_mult(JMachine* m, jword_t instr, jword_t address, jword_t wbbase);
void arm7_load_mult(JMachine* m, jword_t instr, jword_t address, jword_t wbbase);

#endif/*MEMORY_OPS_H*/

