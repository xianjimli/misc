/*
 * File:    arm7i_strb_7c.c
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

JRet arm7_7c_execute(JInstruction* thiz, jinst_t instr)
{
	J_DECL_MACHINE(thiz);
	j_ret_val_if_fail(m != NULL, JRET_INVALID_PARAM);
	
	if(J_BIT (instr, 4))
	{
		arm7_undef_instr(m, instr);
	}
	else
	{
		jmachine_put_byte(m, J_LHS + J_LSREGRHS, J_DEST);
	}

	return JRET_OK;
}

JRet arm7_7c_das(JInstruction* thiz, jinst_t instr, char* t)
{
	j_ret_val_if_fail(t != NULL, JRET_INVALID_PARAM);
	if(J_BIT (instr, 4))
	{
		sprintf(t, "undef\n");
	}
	else
	{
		sprintf(t, "strb%s    %s, [%s, %s]\n",
			arm7_cond_name(J_ARM_COND(instr)),
			arm7_r_name(J_RDEST(instr)),
			arm7_r_name(J_RLHS(instr)),
			arm7_r_name(J_RRHS(instr)));
	}

	return JRET_OK;
}

JRet arm7_7c_as(JInstruction* thiz, const char* t, jinst_t* i)
{
	j_ret_val_if_fail(thiz != NULL, JRET_INVALID_PARAM);

	return JRET_OK;
}

void arm7_7c_test(void)
{
	char str[256] = {0};
	jword_t result = 0;
	jword_t text[12] = {0xe7ce1002};
	jword_t data[4] = {0};

	JInstruction* thiz = ARM7_INSTR_CREATE(7c);
	JMachine* m = jmachine_create(text, sizeof(text), 0);
	
	m->r[J_RLR] = (size_t)data;
	m->r[2] = 1;
	m->r[1] = 0x11111111;

	jinstruction_init(thiz, m);
	assert(jinstruction_execute(thiz, text[0]) == JRET_OK);
	assert(jinstruction_das(thiz, text[0], str) == JRET_OK);
	assert(*((char*)(data)+1) == 0x11);

	printf("%s", str);
	
	jinstruction_destroy(thiz);

	return ;
}
