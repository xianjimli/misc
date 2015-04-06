/*
 * File:    rapi_device_procman_default.c
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

#include <asm-wstr.h>
#include <asm-handle-process.h>
#include <asm-handle-thread.h>
#include <rapi_device_procman_default.h>

typedef struct _PrivInfo
{
	int dummy;
}PrivInfo;

static AsmRet rapi_device_procman_default_create_process
	(RapiDeviceProcman* thiz, unsigned int* return_value, WStr* app_name, WStr* cmd_line, unsigned int zero1, unsigned int zero2, unsigned int zero3, unsigned int flags,unsigned int zero4, unsigned int zero5, unsigned int zero6, RapiProcessInfo** process_info)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	char* name = wstr_to_ascii(app_name);
	char* args = wstr_to_ascii(cmd_line);
	char commands[260] = {0};
	sprintf(commands, "%s %s", name, args);
	*process_info = ASM_ALLOC(RapiProcessInfo, 0);

	int pid = 1;//fork();
	if(pid == 0)
	{
		printf("%s:%d: pid = %d %s\n", __func__, __LINE__, getpid(), commands);
		exit(0);
	}
	else
	{
		(*process_info)->process_handle = asm_handle_process_create(pid, commands);
		(*process_info)->thread_handle= asm_handle_thread_create(pid, commands);
		(*process_info)->pid = pid;
		(*process_info)->tid = pid;
	}

	*return_value = 1;
	ASM_FREE(name);
	ASM_FREE(args);

	return ASM_RET_OK;
}

static AsmRet rapi_device_procman_default_config_process
	(RapiDeviceProcman* thiz, unsigned int* return_value, WStr* config, unsigned int flags, unsigned int* ret_data_length, void** ret_data)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	char* conf = wstr_to_ascii(config);

	printf("%s:%d: flags=%d config=%s\n", __func__, __LINE__, flags, conf);
	ASM_FREE(conf);

	*ret_data = wstr_dup_from_ascii("<wap-provisioningdoc1> <characteristic type=\"Sync\"> <characteristic-query recursive=\"false\" type=\"Sources\"/> </characteristic> </wap-provisioningdoc1>");
	*ret_data_length = (wstr_length(*ret_data) + 1) * sizeof(WStr); 
	
	*return_value = RAPI_SUCCESS;

	return ASM_RET_OK;
}

void rapi_device_procman_default_destroy(RapiDeviceProcman* thiz)
{
	ASM_FREE(thiz);

	return;
}

RapiDeviceProcman* rapi_device_procman_default_create(void)
{
	RapiDeviceProcman* thiz = (RapiDeviceProcman*)ASM_ALLOC(RapiDeviceProcman, sizeof(PrivInfo));
	thiz->create_process = rapi_device_procman_default_create_process;
	thiz->config_process = rapi_device_procman_default_config_process;
	thiz->destroy = rapi_device_procman_default_destroy;

	return thiz;
}

