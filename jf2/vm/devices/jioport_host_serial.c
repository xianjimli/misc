/*
 * File:    jioport_host_serial.c
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

#include <stdlib.h>
#include <jioport_host_serial.h>

typedef struct _PrivInfo
{
	void* base;
	size_t size;
}PrivInfo;

void* jioport_host_serial_get_base(JIoPort* thiz)
{
	DECL_PRIV();
	
	return priv->base;
}

size_t     jioport_host_serial_get_size(JIoPort* thiz)
{
	DECL_PRIV();

	return priv->size;
}

JRet  jioport_host_serial_write(JIoPort* thiz, jword_t addr, jword_t data)
{
	DECL_PRIV();
	if(addr == (J_UART0_BASE + J_UTXBUF))
	{
		fprintf(stderr, "%c", (char)data);
	}

	return JRET_OK;
}

JRet      jioport_host_serial_read(JIoPort* thiz,  jword_t addr, jword_t* data)
{
	DECL_PRIV();
	if(addr == (J_UART0_BASE + J_URXBUF))
	{
		*data = (char*)getchar();
	}

	return JRET_OK;
}

static inline void jioport_host_serial_destroy(JIoPort* thiz)
{
	free(thiz);

	return;
}

JIoPort* jioport_host_serial_create(void* base, size_t size)
{
	JIoPort* thiz = calloc(1, sizeof(JIoPort) + sizeof(PrivInfo));
	
	if(thiz != NULL)
	{
		DECL_PRIV();

		thiz->get_base = jioport_host_serial_get_base;
		thiz->get_size = jioport_host_serial_get_size;
		thiz->write    = jioport_host_serial_write;
		thiz->read     = jioport_host_serial_read;
		thiz->destroy  = jioport_host_serial_destroy;

		priv->base = base;
		priv->size = size;
	}

	return thiz;
}

#ifdef DUMMY_IOPORT_TEST
int main(int argc, char* argv[])
{
	jword_t i = 0;
	unsigned int port[32] = {0};
	int n = sizeof(port)/sizeof(port[0]);

	JIoPort* thiz = jioport_host_serial_create(port, sizeof(port));
	assert((size_t)jioport_get_base(thiz) == (size_t)port);
	assert(jioport_get_size(thiz) == sizeof(port));
	for(i = 0; i < n; i++)
	{
		jword_t data = 0;
		assert(jioport_write(thiz, port+i, i) == JRET_OK);
		assert(jioport_read(thiz, port+i, &data)== JRET_OK);
		assert(data == i);
	}

	jioport_destroy(thiz);

	return 0;
}
#endif/*DUMMY_IOPORT_TEST*/

