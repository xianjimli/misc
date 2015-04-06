/*
 * File:    rapi_device_test.c
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

#include <stdio.h>
#include <string.h>
#include <asm-common.h>
#include <sys/select.h>
#include <rapi_device_default.h>
#include <rapi_device_connection_device.h>

AsmRet on_connection_changed(void* ctx, void* device_connection)
{
	AsmConnection** connections = (AsmConnection**)ctx;

	memset(connections+1, 0x00, sizeof(AsmConnection*) * (RAPI_MAX_SESSION_NR - 1));
	rapi_device_connection_device_get_connections(device_connection, connections + 1, RAPI_MAX_SESSION_NR);

	return ASM_RET_OK;
}

AsmRet on_device_connection_connection_broken(void* ctx, void* connnection)
{
	AsmConnection** connections = (AsmConnection**)ctx;
	
	memset(connections, 0x00, sizeof(AsmConnection*) * RAPI_MAX_SESSION_NR);

	return ASM_RET_OK;
}

void process_connections_events(AsmConnection** connections, fd_set* readset)
{
	size_t i = 0;
	for(i = 0; i <= RAPI_MAX_SESSION_NR; i++)
	{
		if(connections[i] != NULL)
		{
			if(FD_ISSET(asm_connection_get_fd(connections[i]), readset))
			{
				asm_connection_process_event(connections[i]);
			}
		}
	}

	return;
}

AsmRet select_connections(AsmConnection** connections, fd_set* readset)
{
	size_t i = 0;
	int max_fd = -2;

	FD_ZERO(readset);
	for(i = 0; i <= RAPI_MAX_SESSION_NR; i++)
	{
		if(connections[i] != NULL)
		{
			int sock_no = asm_connection_get_fd(connections[i]);
			if(sock_no >= 0)
			{
				FD_SET(sock_no, readset);
				PRINTF("connection=%p sock_no = %d\n", connections[i], sock_no);
				max_fd = max_fd < sock_no ? sock_no : max_fd;
			}
			else
			{
				connections[i] = NULL;
			}
		}
	}
	
	struct timeval tv = {100, 100};

	if(max_fd > 0)
	{
		int result = select(max_fd + 1, readset, NULL, NULL, &tv);

		if(result >= 0)
		{
			process_connections_events(connections, readset);
		}

		return ASM_RET_OK;
	}
	else
	{
		return ASM_RET_FAIL;
	}
}

int main(int argc, char* argv[])
{
	fd_set readset = {0};

	AsmConnection* connections[RAPI_MAX_SESSION_NR + 1] = {0};
	RapiDevice*  device = rapi_device_default_create();
	AsmConnection* device_connection = rapi_device_connection_device_create(device, "localhost", RAPI_PORT);

	rapi_device_connection_device_hook_connection_change(device_connection, on_connection_changed, connections);
	connections[0] = device_connection;

	asm_connection_hook_destroy(device_connection, on_device_connection_connection_broken, connections);
	while(select_connections(connections, &readset) == ASM_RET_OK)
	{
	};

	rapi_device_destroy(device, NULL);

	return 0;
}

