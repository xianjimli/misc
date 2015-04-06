/*
 * File:    jmachine.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   machine
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

JRet jmachine_reg_ioport(JMachine* thiz, JIoPort* ioport)
{
	size_t i = 0;
	j_ret_val_if_fail(thiz != NULL && ioport != NULL, JRET_INVALID_PARAM);

	for(i = 0; i < IOPORT_NR; i++)
	{
		if(thiz->ioports[i] == NULL)
		{
			thiz->ioports[i] = ioport;

			return JRET_OK;
		}
	}

	return JRET_OOM;
}

JRet jmachine_reg_instruction(JMachine* thiz, unsigned char pos, JInstruction* i)
{
	j_ret_val_if_fail(thiz != NULL && i != NULL, JRET_INVALID_PARAM);

	thiz->instructions[pos] = i;

	return JRET_OK;
}

int jmachine_ioport_find(JMachine* thiz, jsword_t addr)
{
	size_t i = 0;
	j_ret_val_if_fail(thiz != NULL && addr != NULL, JRET_OK);

	for(i = 0; i < IOPORT_NR && thiz->ioports[i] != NULL; i++)
	{
		JIoPort* p  = thiz->ioports[i];
		size_t low  = (size_t)p->get_base(p);
		size_t high = low + p->get_size(p);

		if((size_t)addr >= low && (size_t)addr < high)
		{
			return i;
		}
	}

	return -1;
}

JMachine* jmachine_create(jword_t* mem, size_t tlen, size_t mlen)
{
	JMachine* thiz = (JMachine*)calloc(1, sizeof(JMachine));

	if(thiz != NULL)
	{
		thiz->text = mem;
		thiz->mem  = mlen != 0 ? mem : NULL;
		thiz->tlen = tlen;
		thiz->mlen = mlen;
	}

	return thiz;
}

void jmachine_destroy(JMachine* thiz)
{
	if(thiz != NULL)
	{
		size_t i = 0;
		for(i = 0; i < IOPORT_NR; i++)
		{
			if(thiz->ioports[i] != NULL)
			{
				jioport_destroy(thiz->ioports[i]);
				thiz->ioports[i] = NULL;
			}
		}

		free(thiz);
	}

	return;
}

void jmachine_put_word (JMachine* thiz, jword_t addr, jword_t data)
{
	if(addr < thiz->mlen)
	{
		char* address = (char*)(thiz->mem) + addr;
		*(jword_t*)address = data;
	}
	else
	{
		int i = jmachine_ioport_find(thiz, addr);
		if(i >= 0)
		{
			jioport_write(thiz->ioports[i], addr, data);
		}
		else if(!thiz->check_mem)
		{
			char* address = (char*)(thiz->mem) + addr;
			*(jword_t*)address = data;
		}
	}

	return;
}

jword_t jmachine_get_word (JMachine* thiz, jword_t addr)
{
	jword_t data = 0;

	if(addr < thiz->mlen)
	{
		char* address = (char*)(thiz->mem) + addr;
		data = *(jword_t*)(address);
	}
	else
	{
		int i = jmachine_ioport_find(thiz, addr);
		if(i >= 0)
		{
			jioport_read(thiz->ioports[i], addr, &data);
		}
		else if(!thiz->check_mem)
		{
			char* address = (char*)(thiz->mem) + addr;
			data = *(jword_t*)(address);
		}
	}
	
	return data;
}

jbyte_t jmachine_get_byte (JMachine* thiz, jword_t addr)
{
	jbyte_t data = 0;

	if(!thiz->check_mem || addr < thiz->mlen)
	{
		char* address = (char*)(thiz->mem) + addr;

		data = address[0];
	}

	return data;
}

void jmachine_put_byte (JMachine* thiz, jword_t addr, jbyte_t data)
{
	if(!thiz->check_mem || addr < thiz->mlen)
	{
		char* address = (char*)(thiz->mem) + addr;

		*address = (char)data;
	}

	return;
}

#ifdef JMACHINE_TEST
int main(int argc, char* argv[])
{
	size_t i = 0;
	jinst_t text[1024] = {0};

	JMachine* thiz = jmachine_create(text, sizeof(text), sizeof(text));
	for(i = 0; i < A_SIZE(text); i++)
	{
		jmachine_put_word(thiz, i, i);
		assert(jmachine_get_word(thiz, i) == i);
	}

	jmachine_destroy(thiz);

	return 0;
}
#endif/*JMACHINE_TEST*/

