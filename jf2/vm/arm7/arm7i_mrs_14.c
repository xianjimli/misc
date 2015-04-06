/*
 * File:    arm7i_mrs_14.c
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
#include <jinstruction_arm7.h>

JRet arm7_14_execute(JInstruction* thiz, jinst_t instr)
{
	J_DECL_MACHINE(thiz);
	j_ret_val_if_fail(m != NULL, JRET_INVALID_PARAM);

	if(J_BITS(instr, 4, 11) == 9)
	{
		jword_t addr = J_LHS;
		J_R_WR(m, J_RDEST(instr), arm7_swap_word(m, addr, J_RHS));
	}
	else if ((J_BITS (instr, 0, 11) == 0) && (J_RLHS(instr) == 15))
	{
		J_R_WR(m, J_RDEST(instr), arm7_get_spsr(m, J_EMODE));
	}

	return JRET_OK;
}

JRet arm7_14_das(JInstruction* thiz, jinst_t instr, char* t)
{
	j_ret_val_if_fail(t != NULL, JRET_INVALID_PARAM);

	if(J_BITS(instr, 4, 11) == 9)
	{
		sprintf(t, "swp%s %s, %s, [%s]\n",
			arm7_cond_name(J_ARM_COND(instr)),
			arm7_r_name(J_RDEST(instr)),
			arm7_r_name(J_RRHS(instr)),
			arm7_r_name(J_RLHS(instr)));
	}
	else if ((J_BITS (instr, 0, 11) == 0) && (J_RLHS(instr) == 15))
	{
		sprintf(t, "mrs%s %s, SPSR\n", 
			arm7_cond_name(J_ARM_COND(instr)),
			arm7_r_name(J_RDEST(instr)));
	}

	return JRET_OK;
}

JRet arm7_14_as(JInstruction* thiz, const char* t, jinst_t* i)
{
	j_ret_val_if_fail(thiz != NULL, JRET_INVALID_PARAM);

	return JRET_OK;
}

void arm7_14_test(void)
{
	char str[256] = {0};
	jword_t result = 0;
	jword_t text[12] = {0xe14f2000, 0xe1013092};
	jword_t data[6] =  {0x11111111, 0x22222222};
	JInstruction* thiz = ARM7_INSTR_CREATE(14);
	JMachine* m = jmachine_create(text, sizeof(text), 0);
	
	jinstruction_init(thiz, m);
	m->mode = J_FIQ32_MODE;
	m->spsr[J_FIQ_BANK] = 0x11111111;
	assert(jinstruction_execute(thiz, text[0]) == JRET_OK);
	assert(jinstruction_das(thiz, text[0], str) == JRET_OK);
	assert(m->r[2] == 0x11111111);
	printf("%s", str);
	
	m->r[1] = (size_t)data;
	m->r[2] = 0x33333333;
	assert(jinstruction_execute(thiz, text[1]) == JRET_OK);
	assert(jinstruction_das(thiz, text[1], str) == JRET_OK);
	assert(m->r[3] == 0x11111111);
	assert(data[0] == 0x33333333);

	printf("%s", str);

	jinstruction_destroy(thiz);

	return ;
}
