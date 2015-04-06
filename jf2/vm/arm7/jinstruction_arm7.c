/*
 * File:    jinstruction_arm7.c
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
#include <jinstruction.h>
#include <jinstruction_arm7.h>

typedef struct _PrivInfo
{
	int opcode;
	JMachine* machine;
}PrivInfo;

static JRet arm7_instruction_init(JInstruction* thiz, JMachine* machine)
{
	DECL_PRIV();
	j_ret_val_if_fail(thiz != NULL && machine != NULL, JRET_INVALID_PARAM);

	priv->machine = machine;
#ifndef ARM7_TEST
	jmachine_reg_instruction(machine, priv->opcode, thiz);
#endif/*ARM7_TEST*/

	return JRET_OK;
}

static void arm7_instruction_destroy(JInstruction* thiz)
{
	if(thiz != NULL)
	{
		free(thiz);
	}

	return;
}

JMachine* jinstruction_arm7_get_machine(JInstruction* thiz)
{
	DECL_PRIV();
	j_ret_val_if_fail(priv != NULL, NULL);

	return priv->machine;
}

JInstruction* jinstruction_arm7_create(int opcode,
	JInstructionExecuteFunc execute,
	JInstructionDasFunc das, JInstructionAsFunc as)
{
	JInstruction* thiz = calloc(1, sizeof(JInstruction) + sizeof(PrivInfo));
	
	if(thiz != NULL)
	{
		DECL_PRIV();

		thiz->as      = as;
		thiz->das     = das;
		thiz->execute = execute;
		thiz->init    = arm7_instruction_init;
		thiz->destroy = arm7_instruction_destroy;

		priv->opcode = opcode;
	}

	return thiz;
}

jword_t arm7_get_dprhs(JMachine* m, jword_t instr)
{
	jword_t base = 0;
	jword_t shamt = 0;

	if(J_BIT(instr, 4))
	{
		base = J_RHS;
		shamt = m->r[J_BITS(instr, 8, 11)] & 0xff;
		m->r[J_RPC] += I_SIZE;

		switch ((int) J_BITS (instr, 5, 6))
		{
			case J_LSL:
			{
				if (shamt == 0)
				{
					return (base);
				}
				else if (shamt >= 32)
				{
					return (0);
				}
				else
				{
					return (base << shamt);
				}

				break;
			}
			case J_LSR:
			{
				if(shamt == 0)
				{
					return (base);
				}
				else if (shamt >= 32)
				{
					return (0);
				}
				else
				{
					return (base >> shamt);
				}
	
				break;
			}
			case J_ASR:
			{
				if (shamt == 0)
				{
					return (base);
				}
				else if (shamt >= 32)
				{
					return ((jword_t) ((jsword_t) base >> 31L));
				}
				else
				{
					return ((jword_t)((jsword_t) base >> (int) shamt));
				}
				break;
			}
			case J_ROR:
			{
				shamt &= 0x1f;
				if (shamt == 0)
				{
					return (base);
				}
				else
				{
					return ((base << (32 - shamt)) | (base >> shamt));
				}

				break;
			}
		}
	}
	else
	{
		shamt = J_BITS (instr, 7, 11);
		switch ((int) J_BITS (instr, 5, 6))
		{
			case J_LSL:
			{
		 		return (base << shamt);
		 	}
		 	case J_LSR:
		 	{
		 		if (shamt == 0)
		 		{
		 			return (0);
		 		}
		 		else
		 		{
		 			return (base >> shamt);
		 		}
		 	}
		 	case J_ASR:
		 	{
		 		if (shamt == 0)
		 		{
		 			return ((jword_t) ((jsword_t) base >> 31L));
		 		}
		 		else
		 		{
		 			return ((jword_t)((jsword_t) base >>(int) shamt));
		 		}
		 	}
		 	case J_ROR:
		 	{
		 		if (shamt == 0)
		 		{
		 			return ((base >> 1) | (shamt << 31));		 	
		 		}
		 		else
		 		{
		 			return ((base << (32 - shamt)) | (base >> shamt));
		 		}
		 	}
		 }
	}

	return 0;
}

jword_t arm7_get_dpsrhs(JMachine* m, jword_t instr)
{
	jword_t base = 0;
	jword_t shamt = 0;
	if(J_BIT(instr, 4))
	{
		base = J_RHS;
		shamt = m->r[J_BITS(instr, 8, 11)] & 0xff;
		m->r[J_RPC] += I_SIZE;

		switch ((int) J_BITS (instr, 5, 6))
		{
			case J_LSL:
			{
				if (shamt == 0)
				{
					return (base);
				}
				else if (shamt == 32)
				{
					J_ASSIGNC (base & 1);
					return (0);
				}
				else if (shamt > 32)
				{
					J_CLEARC;
					return (0);
				}
				else
				{
					J_ASSIGNC ((base >> (32 - shamt)) & 1);
					return (base << shamt);
				}

				break;
			}
			case J_LSR:
			{
				if(shamt == 0)
				{
					return (base);
				}
				else if (shamt == 32)
				{
					J_ASSIGNC (base >> 31);
					return (0);
				}
				else if (shamt > 32)
				{
					J_CLEARC;
					return (0);
				}
				else
				{
					J_ASSIGNC ((base >> (shamt - 1)) & 1);

					return (base >> shamt);
				}
	
				break;
			}
			case J_ASR:
			{
				if (shamt == 0)
				{
					return (base);
				}
				else if (shamt >= 32)
				{
					J_ASSIGNC (base >> 31L);

					return ((jword_t) ((jsword_t) base >> 31L));
				}
				else
				{
					J_ASSIGNC ((jword_t)((jsword_t) base >> (int) (shamt - 1)) & 1);
					return ((jword_t)((jsword_t) base >> (int) shamt));
				}
				break;
			}
			case J_ROR:
			{
				if (shamt == 0)
				{
					return (base);
				}
				shamt &= 0x1f;
				if (shamt == 0)
				{
					J_ASSIGNC (base >> 31);
					return (base);
				}
				else
				{
					J_ASSIGNC ((base >> (shamt - 1)) & 1);
					return ((base << (32 - shamt)) | (base >> shamt));
				}

				break;
			}
		}
	}
	else
	{
		shamt = J_BITS (instr, 7, 11);
		switch ((int) J_BITS (instr, 5, 6))
		{
			case J_LSL:
			{
		 		J_ASSIGNC ((base >> (32 - shamt)) & 1);
		 		return (base << shamt);
		 	}
		 	case J_LSR:
		 	{
		 		if (shamt == 0)
		 		{
		 			J_ASSIGNC (base >> 31);
		 			return (0);
		 		}
		 		else
		 		{
		 			J_ASSIGNC ((base >> (shamt - 1)) & 1);
		 			return (base >> shamt);
		 		}
		 	}
		 	case J_ASR:
		 	{
		 		if (shamt == 0)
		 		{
		 			J_ASSIGNC (base >> 31L);
		 			return ((jword_t) ((jsword_t) base >> 31L));
		 		}
		 		else
		 		{
		 			J_ASSIGNC((jword_t)((jsword_t)base>>(int)(shamt - 1))&1);
		 			return ((jword_t)((jsword_t) base >>(int) shamt));
		 		}
		 	}
		 	case J_ROR:
		 	{
		 		if (shamt == 0)
		 		{
		 			shamt = J_CFLAG;
		 			J_ASSIGNC (base & 1);
		 			return ((base >> 1) | (shamt << 31));		 	
		 		}
		 		else
		 		{
		 			J_ASSIGNC ((base >> (shamt - 1)) & 1);
		 			return ((base << (32 - shamt)) | (base >> shamt));
		 		}
			}
		}
	}

	return 0;
}

jword_t arm7_get_lsregrhs(JMachine* m, jword_t instr)
{
	jword_t base  = J_RHS;
	jword_t shamt = J_BITS (instr, 7, 11);

	switch ((int) J_BITS (instr, 5, 6))
	{
	case J_LSL: return (base << shamt);
	case J_LSR: return (shamt == 0) ? 0 : (base >> shamt);
    case J_ASR: return (shamt == 0)?(jsword_t)base>>31L:(jsword_t)base>>(int)shamt;
    case J_ROR: return (shamt == 0)?((base >> 1) | (J_CFLAG << 31)) 
		: ((base << (32 - shamt)) | (base >> shamt));
    default:break;
	}

	return 0;
}

int arm7_count_one(jword_t data)
{
	jword_t i    = 0;
	jword_t one  = 1;
	jword_t bits = 0;

	for(i = 0; i < 32; i++)
	{
		if((one << i) & data)
		{
			bits++;
		}
	}

	return bits;
}

jword_t arm7_switch_mode(JMachine* m, jword_t old_mode, jword_t new_mode)
{
	int i = 0;
	jword_t old_bank = arm7_mode_to_bank(old_mode);
	jword_t new_bank = arm7_mode_to_bank(new_mode);
	
	m->bank = new_bank;

	if(old_bank != new_bank)
	{
		switch(old_bank)
		{
			case J_USER_BANK:
			case J_IRQ_BANK:
			case J_SVC_BANK:
			case J_ABORT_BANK:
			{
				m->r_bank[old_bank][13] = m->r[13];
				m->r_bank[old_bank][14] = m->r[14];
				break;
			}
			case J_FIQ_BANK:
			{
				for(i = 8; i < 15; i++)
				{
					m->r_bank[old_bank][i] = m->r[i];
				}
				break;
			}
			case J_DUMMY_BANK:
			{
				for(i = 8; i < 15; i++)
				{
					m->r_bank[old_bank][i] = 0;
				}
				break;
			}
			default:break;
		}
		
		switch(old_bank)
		{
			case J_USER_BANK:
			case J_IRQ_BANK:
			case J_SVC_BANK:
			case J_ABORT_BANK:
			{
				m->r[13] = m->r_bank[old_bank][13];
				m->r[14] = m->r_bank[old_bank][14];
				break;
			}
			case J_FIQ_BANK:
			{
				for(i = 8; i < 15; i++)
				{
					m->r[i] = m->r_bank[old_bank][i];
				}
				break;
			}
			case J_DUMMY_BANK:
			{
				for(i = 8; i < 15; i++)
				{
					m->r[i] = 0;
				}
				break;
			}
			default:break;
		}
	}

	return new_mode;
}

void arm7_cpsr_changed(JMachine* m)
{
	jword_t old_mode = m->mode;
	
	if (m->mode != (m->cpsr & J_MODEBITS))
	{
		m->mode = arm7_switch_mode (m, m->mode, m->cpsr & J_MODEBITS);
	}
	
	m->cpsr &= ~J_MODEBITS;
	
	J_ASSIGNINT (m->cpsr & J_INTBITS);
	m->cpsr &= ~J_INTBITS;
	J_ASSIGNN ((m->cpsr & J_NBIT) != 0);
	m->cpsr &= ~J_NBIT;
	J_ASSIGNZ ((m->cpsr & J_ZBIT) != 0);
	m->cpsr &= ~J_ZBIT;
	J_ASSIGNC ((m->cpsr & J_CBIT) != 0);
	m->cpsr &= ~J_CBIT;
	J_ASSIGNV ((m->cpsr & J_VBIT) != 0);
	m->cpsr &= ~J_VBIT;
	J_ASSIGNS ((m->cpsr & J_SBIT) != 0);
	m->cpsr &= ~J_SBIT;
	
	return;
}

void arm7_neg_zero (JMachine* m, jsword_t result)
{  
	if (J_NEG (result))
	{
		J_SETN;
		J_CLEARZ;
	}
	else if (result == 0)
	{ 
		J_CLEARN;
		J_SETZ;
	}
	else
	{
		J_CLEARN;
		J_CLEARZ;
	}

	return;
}

void  arm7_subcarry (JMachine* m, jword_t a, jword_t b, jword_t result)
{
	J_ASSIGNC ((J_NEG (a) && J_POS (b)) ||
         (J_NEG (a) && J_POS (result)) || (J_POS (b) && J_POS (result)));
}

void arm7_sub_overflow (JMachine* m, jword_t a,	jword_t b, jword_t result)
{
	int overflow = ((J_NEG (a) && J_POS (b) && J_POS (result)) \
        || (J_POS (a) && J_NEG (b) && J_NEG (result)));

	J_ASSIGNV (overflow);

	return;
}

void arm7_undef_instr(JMachine* m, jword_t instr)
{
	/*TODO*/

	return;
}

void arm7_set_abort(JMachine* m, jword_t irq, jword_t mode, jword_t lr)
{
	arm7_set_spsr(m, mode, arm7_get_cpsr(m));
	arm7_set_cpsr(m, (arm7_get_cpsr(m) & ~(J_EMODE | J_TBIT))|(irq)|mode);

	m->r[J_RLR] = lr;

	return;
}

void arm7_abort(JMachine* m, jword_t vector)
{
	jword_t pc = m->pc;

	m->aborted = 0;
	switch(vector)
	{
		default:
		case ARM7_V_RESET:
		{
			arm7_set_abort(m, J_INTBITS, J_SVC32_MODE, 0); 
			break;
		}
		case ARM7_V_UNDEF_INSTR:
		{
			arm7_set_abort(m, J_IBIT, J_UNDEF32_MODE, pc + I_SIZE); 
			break;
		}
		case ARM7_V_SWI:
		{
			arm7_set_abort(m, J_IBIT, J_SVC32_MODE, pc + I_SIZE); 
			break;
		}
		case ARM7_V_PREFETCH_ABORT:
		{
			arm7_set_abort(m, J_IBIT, J_ABORT32_MODE, pc + I_SIZE); 
			break;
		}
		case ARM7_V_DATA_ABORT:
		{
			arm7_set_abort(m, J_IBIT, J_ABORT32_MODE, pc - I_SIZE); 
			break;
		}
		case ARM7_V_IRQ:
		{
			arm7_set_abort(m, J_IBIT, J_IRQ32_MODE, pc + I_SIZE); 
			break;
		}
		case ARM7_V_FIQ:
		{
			arm7_set_abort(m, J_IBIT, J_FIQ32_MODE, pc + I_SIZE); 
			break;
		}
	}

	m->r[J_RPC] = vector;

	return;
}

jword_t arm7_mode_to_bank(jword_t mode)
{
	const static jword_t bank_of_mode[] =
	{
		J_USER_BANK,  J_FIQ_BANK,   J_IRQ_BANK,   J_SVC_BANK,
		J_DUMMY_BANK, J_DUMMY_BANK, J_DUMMY_BANK, J_DUMMY_BANK,
		J_DUMMY_BANK, J_DUMMY_BANK, J_DUMMY_BANK, J_DUMMY_BANK,
		J_DUMMY_BANK, J_DUMMY_BANK, J_DUMMY_BANK, J_DUMMY_BANK,
		J_USER_BANK,  J_FIQ_BANK,   J_IRQ_BANK,   J_SVC_BANK,
		J_DUMMY_BANK, J_DUMMY_BANK, J_DUMMY_BANK, J_ABORT_BANK,
		J_DUMMY_BANK, J_DUMMY_BANK, J_DUMMY_BANK, J_UNDEF_BANK,
		J_DUMMY_BANK, J_DUMMY_BANK, J_DUMMY_BANK, J_SYSTEM_BANK
	};

	if(mode < A_SIZE(bank_of_mode))
	{
		return bank_of_mode[mode];
	}

	return J_DUMMY_BANK;
}

jword_t arm7_get_spsr(JMachine* m, jword_t mode)
{
	jword_t bank = arm7_mode_to_bank(mode);

	if(bank == J_USER_BANK || bank == J_SYSTEM_BANK || bank == J_DUMMY_BANK)
	{
		return m->cpsr;
	}

	return m->spsr[bank];
}

void arm7_set_spsr(JMachine* m, jword_t mode, jword_t spsr)
{
	jword_t bank = arm7_mode_to_bank(mode);

	if(bank == J_USER_BANK || bank == J_SYSTEM_BANK || bank == J_DUMMY_BANK)
	{
		m->spsr[bank] = spsr;
	}

	return;
}

jword_t arm7_get_cpsr(JMachine* m)
{
	return (J_CPSR | m->cpsr);
}

void arm7_set_cpsr(JMachine* m, jword_t cpsr)
{
	m->cpsr = cpsr;
	arm7_cpsr_changed(m);

	return;
}

jword_t arm7_align(JMachine* m, jword_t address, jword_t data)
{
	address = (address & 3) << 3;

	return ((data >> address) | (data << (32 - address)));
}

void arm7_fix_cpsr(JMachine* m, jword_t instr, jword_t cpsr)
{
	m->cpsr = J_CPSR | m->cpsr;
	
	if (m->mode != J_USER26_MODE && m->mode != J_USER32_MODE)
	{
		if (J_BIT (instr, 16))
		{
			J_SETPSR_C (m->cpsr, cpsr);
		}

		if (J_BIT (instr, 17))
		{
			J_SETPSR_X (m->cpsr, cpsr);
		}

		if (J_BIT (instr, 18))
		{
			J_SETPSR_S (m->cpsr, cpsr);
		}
	}

	if (J_BIT (instr, 19))
	{
		J_SETPSR_F (m->cpsr, cpsr);
	}

	arm7_cpsr_changed(m);

	return;
}

void arm7_fix_spsr(JMachine* m, jword_t instr, jword_t spsr)
{
	jword_t bank = m->bank;

	if(bank != J_USER_BANK && bank != J_SYSTEM_BANK && bank != J_DUMMY_BANK)
	{
		if(J_BIT(instr, 16))
		{
 			J_SETPSR_C (m->spsr[bank], spsr);
 		}

		if(J_BIT(instr, 17))   
		{
			J_SETPSR_X (m->spsr[bank], spsr);
		}

		if(J_BIT(instr, 18)) 
		{
			J_SETPSR_S (m->spsr[bank], spsr);
		}

		if(J_BIT(instr, 19))
		{
			J_SETPSR_F (m->spsr[bank], spsr);
		}
    }

    return;
}

static jword_t g_arm7_immed_table[4096] = {0};

jbool_t arm7_init(JMachine* m)
{
	jword_t i = 0;
	for(i = 0; i < A_SIZE(g_arm7_immed_table); i++)
	{
		g_arm7_immed_table[i] = J_ROTATER(i & 0xffL, (i >> 7L) & 0x1eL);
	}

	return J_TRUE;
}

jword_t arm7_decode_immed(jword_t index)
{
	return index < A_SIZE(g_arm7_immed_table) ? g_arm7_immed_table[index] : 0;
}

#ifdef ARM7_TEST
int main(int argc, char* argv[])
{
	assert(arm7_count_one(0) == 0);
	assert(arm7_count_one(1) == 1);
	assert(arm7_count_one(7) == 3);
	assert(arm7_count_one(16) == 1);

	return 0;
}
#endif/*ARM7_TEST*/
