/*
 * File:    arm7_memory.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   
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

#include <jmachine.h>
#include <arm7_memory.h>

void arm7_store_mult (JMachine* m, jword_t instr, 
	jword_t address, jword_t wbbase)
{
	jword_t r = 0;

	if (J_BIT(instr, 21) && J_RLHS(instr) != 15)
		J_R_WR(m, J_RLHS(instr), wbbase);

	for (; r < 16; r ++)
	{
		if(J_BIT(instr, r))
		{
			jmachine_put_word(m, address, m->r[r]);
			address += 4;
		}
	}

	return;
}

void arm7_load_mult (JMachine* m, jword_t instr, 
	jword_t address, jword_t wbbase)
{
	jword_t r = 0;

	if (J_BIT(instr, 21) && J_RLHS(instr) != 15)
		J_R_WR(m, J_RLHS(instr), wbbase);

	for (; r < 16; r ++)
	{
		if(J_BIT(instr, r))
		{
			m->r[r] = jmachine_get_word(m, address);
			address += 4;
		}
	}

	return;
}

jword_t arm7_swap_word(JMachine* m, jword_t address, jword_t data)
{
	jword_t temp = jmachine_get_word(m, address);
	jmachine_put_word(m, address, data);

	return temp;
}

