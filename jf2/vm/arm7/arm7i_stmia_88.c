/*
 * File:    arm7i_stmia_88.c
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

JRet arm7_88_execute(JInstruction* thiz, jinst_t instr)
{
	J_DECL_MACHINE(thiz);
	j_ret_val_if_fail(m != NULL, JRET_INVALID_PARAM);

	jword_t addr = J_LHS;
	arm7_store_mult(m, instr, addr, 0L);

	return JRET_OK;
}

JRet arm7_88_das(JInstruction* thiz, jinst_t instr, char* t)
{
	char* p = NULL;
	jword_t r = 0;
	j_ret_val_if_fail(t != NULL, JRET_INVALID_PARAM);
	sprintf(t, "stmia %s%s, {", arm7_r_name(J_RLHS(instr)),
		J_BIT(instr, 21) ? "!" : "");

	for(r = 0; r < 16; r++)
	{
		if(J_BIT(instr, r))
		{
			strcat(t, arm7_r_name(r));
			strcat(t, ", ");
		}
	}

	if((p = strrchr(t, ',')) != NULL)
	{
		*p = '\0';
	}

	strcat(t, "}\n");

	return JRET_OK;
}

JRet arm7_88_as(JInstruction* thiz, const char* t, jinst_t* i)
{
	j_ret_val_if_fail(thiz != NULL, JRET_INVALID_PARAM);

	return JRET_OK;
}

void arm7_88_test(void)
{
	char str[256] = {0};
	jword_t result = 0;
	jword_t text[12] = {0xe88dd800};
	jword_t data[4] = {0};

	JInstruction* thiz = ARM7_INSTR_CREATE(88);
	JMachine* m = jmachine_create(text, sizeof(text), 0);
	
	m->r[J_RSP] = (size_t)data;
	m->r[J_RFP] = 0x11111111;
	m->r[J_RIP] = 0x22222222;
	m->r[J_RLR] = 0x33333333;
	m->r[J_RPC] = 0x44444444;

	jinstruction_init(thiz, m);
	assert(jinstruction_execute(thiz, text[0]) == JRET_OK);
	assert(jinstruction_das(thiz, text[0], str) == JRET_OK);
	assert(data[0] == m->r[J_RFP]);
	assert(data[1] == m->r[J_RIP]);
	assert(data[2] == m->r[J_RLR]);
	assert(data[3] == m->r[J_RPC]);
	assert((size_t)data == m->r[J_RSP]);

	printf("%s", str);

	jinstruction_destroy(thiz);

	return ;
}
