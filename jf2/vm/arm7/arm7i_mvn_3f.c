/*
 * File:    arm7i_mvn_3f.c
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

JRet arm7_3f_execute(JInstruction* thiz, jinst_t instr)
{
	J_DECL_MACHINE(thiz);
	j_ret_val_if_fail(m != NULL, JRET_INVALID_PARAM);
	
	jword_t imm  = J_BITS(instr, 0, 11);
	jword_t rhs  = arm7_decode_immed(J_BITS(instr, 0, 11));
	if(imm > 255)
	{
		J_ASSIGNC (rhs >> 31);
	}

	J_R_WR(m, J_RDEST(instr), ~rhs);

	return JRET_OK;
}

JRet arm7_3f_das(JInstruction* thiz, jinst_t instr, char* t)
{
	J_DECL_MACHINE(thiz);
	j_ret_val_if_fail(t != NULL, JRET_INVALID_PARAM);
	jword_t imm  = J_BITS(instr, 0, 11);
	jword_t rhs  = arm7_decode_immed(J_BITS(instr, 0, 11));

	sprintf(t, "mvn%s %s, #%d ; 0x%x\n",
		arm7_cond_name(J_ARM_COND(instr)),
		arm7_r_name(J_RDEST(instr)),
		rhs, rhs);

	return JRET_OK;
}

JRet arm7_3f_as(JInstruction* thiz, const char* t, jinst_t* i)
{
	j_ret_val_if_fail(thiz != NULL, JRET_INVALID_PARAM);

	return JRET_OK;
}

void arm7_3f_test(void)
{
	char str[256] = {0};
	jword_t text[12] = {0xe3f0233f};

	JInstruction* thiz = ARM7_INSTR_CREATE(3f);
	JMachine* m = jmachine_create(text, sizeof(text), 0);
	
	jinstruction_init(thiz, m);
	assert(jinstruction_execute(thiz, text[0]) == JRET_OK);
	assert(jinstruction_das(thiz, text[0], str) == JRET_OK);
	assert(m->r[2] ==~0xfc000000);
	printf("%s", str);
	
	jinstruction_destroy(thiz);

	return ;
}
