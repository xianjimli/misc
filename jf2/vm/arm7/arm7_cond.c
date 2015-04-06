/*
 * File:    arm7i_cond.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   instruction decoration to handle cond code.
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

JRet arm7_cond_execute(JInstruction* thiz, jinst_t instr)
{
	J_DECL_MACHINE(thiz);
	JRet    ret     = JRET_OK;
	jbool_t execute = J_TRUE;
	jword_t cond    = J_ARM_COND(instr);
	jword_t opcode  = J_ARM_INSTR(instr);

	j_ret_val_if_fail(m != NULL, JRET_INVALID_PARAM);
	
	switch(cond)
	{
		case J_EQ:
			execute = J_ZFLAG;
			break;
		case J_NE:
			execute = !J_ZFLAG;
			break;
		case J_VS:
			execute = J_VFLAG;
			break;
		case J_VC:
			execute = !J_VFLAG;
			break;
		case J_MI:
			execute = J_NFLAG;
			break;
		case J_PL:
			execute = !J_NFLAG;
			break;
		case J_CS:
			execute = J_CFLAG;
			break;
		case J_CC:
			execute = !J_CFLAG;
			break;
		case J_HI:
			execute = (J_CFLAG && !J_ZFLAG);
			break;
		case J_LS:
			execute = (!J_CFLAG || J_ZFLAG);
			break;
		case J_GE:
			execute = ((!J_NFLAG && !J_VFLAG) || (J_NFLAG && J_VFLAG));
			break;
		case J_LT:
			execute = ((J_NFLAG && !J_VFLAG) || (!J_NFLAG && J_VFLAG));
			break;
		case J_GT:
			execute = ((!J_NFLAG && !J_VFLAG && !J_ZFLAG) || (J_NFLAG && J_VFLAG && !J_ZFLAG));
			break;
		case J_LE:
			execute = ((J_NFLAG && !J_VFLAG) || (!J_NFLAG && J_VFLAG)) || J_ZFLAG;
			break;
		default:break;
	}

	if(execute)
	{
		if(m->instructions[opcode] != NULL)
		{
			ret = jinstruction_execute(m->instructions[opcode], instr);
		}
		else
		{
			printf("unknown instruction 0x%08x at %p\n", instr, m->pc);
		}

		if(m->r[J_RPC] != (m->pc + 2 * I_SIZE)
			|| opcode == 0xa0 || opcode == 0xaf || opcode == 0xb0
			|| opcode == 0xbe || opcode == 0xbf) 
		{
			m->pc = m->r[J_RPC];
		}
		else
		{
			m->pc      += I_SIZE;
			m->r[J_RPC] = m->pc;
		}
	}
	else
	{
		m->pc      += I_SIZE;
		m->r[J_RPC] = m->pc;
	}

	return ret;
}

JRet arm7_cond_das(JInstruction* thiz, jinst_t instr, char* t)
{
	J_DECL_MACHINE(thiz);
	JRet    ret    = JRET_OK;
	jword_t opcode = J_ARM_INSTR(instr);

	j_ret_val_if_fail(t != NULL, JRET_INVALID_PARAM);

	if(m->instructions[opcode] != NULL)
	{
		ret = jinstruction_das(m->instructions[opcode], instr, t);
	}

	return ret;
}

JRet arm7_cond_as(JInstruction* thiz, const char* t, jinst_t* instr)
{
	J_DECL_MACHINE(thiz);
	JRet ret = JRET_OK;

	j_ret_val_if_fail(t != NULL, JRET_INVALID_PARAM);

	/*FIXME*/

	return ret;
}

