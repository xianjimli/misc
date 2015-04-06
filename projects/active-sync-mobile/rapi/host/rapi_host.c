/*
 * File:    rapi_host.c
 * Author:  Li XianJing <lixianjing@broncho.org>
 * Brief:   
 *
 * Copyright (c) 2008 topwise, Inc.
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
 * 2008-01-28 Li XianJing <lixianjing@topwisesz.com> created
 *
 */

#include <rapi_host.h>
#include <asm-input-buffer.h>
#include <asm-output-buffer.h>
#include <rapi_host_registry.h>
#include <rapi_host_fileman.h>
#include <rapi_host_procman.h>
#include <rapi_host_system.h>
#include <rapi_host_connection_device.h>

struct _RapiHost
{
	RapiHostRegistry* registry;
	RapiHostFileman* fileman;
	RapiHostProcman* procman;
	RapiHostSystem*  system;

	AsmConnection*  session;
};

#include <rapi_host_wrapper.c>

RapiHost* rapi_host_create(AsmConnection* session)
{
	asm_return_val_if_fail(session != NULL, NULL);
	RapiHost* thiz = (RapiHost*)malloc(sizeof(RapiHost));
		
	AsmStream* stream = rapi_host_connection_session_get_stream(session);

	thiz->session = session;
	thiz->registry = rapi_host_registry_create(stream);
	thiz->fileman = rapi_host_fileman_create(stream);
	thiz->procman = rapi_host_procman_create(stream);
	thiz->system = rapi_host_system_create(stream);

	return thiz;
}

void      rapi_host_destroy(RapiHost* thiz)
{
	if(thiz != NULL)
	{
		rapi_host_registry_destroy(thiz->registry);
		thiz->registry = NULL;
		rapi_host_fileman_destroy(thiz->fileman);
		thiz->fileman = NULL;
		rapi_host_procman_destroy(thiz->procman);
		thiz->procman = NULL;
		rapi_host_system_destroy(thiz->system);
		thiz->system = NULL;
		asm_connection_destroy(thiz->session);
		thiz->session = NULL;

		ASM_FREE(thiz);
	}

	printf("%s:%d\n", __func__, __LINE__);

	return;
}


