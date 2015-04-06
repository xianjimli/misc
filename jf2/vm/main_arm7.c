/*
 * File:    main_arm7.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   arm7 vm entry. 
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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <jinstruction_arm7.h>
#include <jioport_host_serial.h>

extern JRet arm7_init(JMachine* m);

#define MEM_SIZE 64 * 1024 * 1024

JRet arm7_cond_execute(JInstruction* thiz, jinst_t instr);
JRet arm7_cond_das(JInstruction* thiz, jinst_t instr, char* t);
JRet arm7_cond_as(JInstruction* thiz, const char* t, jinst_t* instr);

JRet arm7_device_init(JMachine* m)
{
	JIoPort* ioport = jioport_host_serial_create((void*)J_UART0_BASE, 0x1000);
	jmachine_reg_ioport(m, ioport);
	
	ioport = jioport_host_serial_create((void*)J_UART1_BASE, 0x1000);
	jmachine_reg_ioport(m, ioport);

	return JRET_OK;
}

JRet jmachine_execute(JMachine* m, JInstruction* instr, size_t nr, jbool_t das)
{
	size_t i     = 0;
	JRet ret     = JRET_OK;
	jword_t opcode     = 0;
	jword_t instr_code = 0;

	for(i = 0; i < nr && m->pc < m->tlen; i++)
	{
		char str[256] = {0};

		instr_code = m->text[m->pc>>2];
		opcode = J_ARM_INSTR(instr_code);

		if(das)
		{
			ret = jinstruction_das(instr, instr_code, str);
			printf("%04x 0x%08x %s", m->pc, instr_code, str);
		}

		m->r[J_RPC] = m->pc + 2 * I_SIZE;
		ret = jinstruction_execute(instr, instr_code);
	}

	return JRET_OK;
}

JRet jmachine_run(JMachine* m, jbool_t das)
{
	JInstruction* instr = jinstruction_arm7_create(0xff, 
		arm7_cond_execute, arm7_cond_das, arm7_cond_as);
	jinstruction_init(instr, m);

	m->r[J_RSP]  = 2048;
	m->mode      = J_SVC32_MODE;
	m->bank      = J_SVC_BANK;
	m->check_mem = J_TRUE;

	while(jmachine_execute(m, instr, 1, das) == JRET_OK)
	{
	}

	jinstruction_destroy(instr);

	return JRET_OK;
}

JRet jmachine_das(JMachine* m)
{
	size_t i = 0;
	size_t instr_nr = m->tlen >> 2;

	for(i = 0; i < instr_nr; i++)
	{
		char str[256] = {0};
		int opcode = J_ARM_INSTR(m->text[i]);
		m->r[J_RPC] = i << 2;
		if(m->instructions[opcode] != NULL)
		{
			jinstruction_das(m->instructions[opcode], m->text[i], str);
			printf("%04x %08x %s", i<<2, m->text[i], str);
		}
		else
		{
			printf("%04x %08x %s\n", i<<2, m->text[i], "unknown");
		}
	}

	return JRET_OK;
}

int main(int argc, char* argv[])
{
	FILE* fp = NULL;
	JMachine* m = NULL;
	char* memory = NULL;
	const char* bin = NULL;
	struct stat st = {0};
	jbool_t run = 0;
	jbool_t das = 0;
	jbool_t rdas = 0;

	do
	{
		if(argc < 3)
		{
			printf("usage: %s [run|das|rdas] bin\n", argv[0]);
			break;
		}

		bin = argv[2];
		run = strcmp("run", argv[1]) == 0;
		das = strcmp("das", argv[1]) == 0;
		rdas = strcmp("rdas", argv[1]) == 0;

		if((fp = fopen(bin, "rb")) == NULL)
		{
			break;
		}

		if(fstat(fileno(fp), &st) != 0)
		{
			break;
		}

		if((memory = calloc(1, MEM_SIZE)) == NULL)
		{
			break;
		}
		fread(memory, 1, st.st_size, fp);
		if((m = jmachine_create((jword_t*)memory, st.st_size, MEM_SIZE)) == NULL)
		{
			break;
		}

		arm7_init(m);
		arm7_device_init(m);
		arm7_instruction_init(m);

		if(das)
		{
			jmachine_das(m);
		}

		if(run || rdas)
		{
			jmachine_run(m, rdas);
		}

	}while(0);

	if(fp != NULL)
	{
		fclose(fp);
	}
	
	if(memory != NULL)
	{
		free(memory);
	}
	
	if(m != NULL)
	{
		jmachine_destroy(m);
	}

	return 0;
}
