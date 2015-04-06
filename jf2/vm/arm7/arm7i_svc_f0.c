/*
 * File:    arm7i_svc_f0.c
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

JRet arm7_f0_execute(JInstruction* thiz, jinst_t instr)
{
	J_DECL_MACHINE(thiz);
	j_ret_val_if_fail(m != NULL, JRET_INVALID_PARAM);

	arm7_abort(m, ARM7_V_SWI);

	return JRET_OK;
}

JRet arm7_f0_das(JInstruction* thiz, jinst_t instr, char* t)
{
	J_DECL_MACHINE(thiz);
	j_ret_val_if_fail(t != NULL, JRET_INVALID_PARAM);

	sprintf(t, "svc %x\n", J_BITS (instr, 0, 23));
	return JRET_OK;
}

JRet arm7_f0_as(JInstruction* thiz, const char* t, jinst_t* i)
{
	j_ret_val_if_fail(thiz != NULL, JRET_INVALID_PARAM);

	return JRET_OK;
}

void arm7_f0_test(void)
{
	char str[256] = {0};
	jword_t result = 0;
	jword_t text[12] = {0x1f000002};

	JInstruction* thiz = ARM7_INSTR_CREATE(f0);
	JMachine* m = jmachine_create(text, sizeof(text), 0);
	
	m->r[J_RPC] = 0x44;

	jinstruction_init(thiz, m);
	assert(jinstruction_das(thiz, text[0], str) == JRET_OK);
	assert(jinstruction_execute(thiz, text[0]) == JRET_OK);
	printf("%s", str);
	
	jinstruction_destroy(thiz);

	return ;
}
