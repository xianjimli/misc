/*
 * File:    rrac_device_test.c
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

#include <rrac_device_default.h>
#include <rrac_device_connection_cmd.h>
#include <rrac_device_connection_data.h>
#define RRAC_DEVICE_MAX_CONNECTION_NR 2

static AsmRet on_connection_broken(void* ctx, AsmConnection* connection)
{
	AsmConnection** connections = (AsmConnection**)ctx;
	asm_return_val_if_fail(ctx != NULL, ASM_RET_FAIL);
	
	size_t i = 0;
	
	for(i = 0; i < RRAC_DEVICE_MAX_CONNECTION_NR; i++)
	{
		if(connections[i] == connection)
		{
			connections[i] = NULL;
			printf("%s: remove %p\n", __func__, connection);
			break;
		}
	}

	return ASM_RET_OK;
}
void process_connections_events(AsmConnection** connections, fd_set* readset)
{
	size_t i = 0;
	for(i = 0; i <= RRAC_DEVICE_MAX_CONNECTION_NR; i++)
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
AsmRet select_connections(AsmConnection** connections)
{
	size_t i = 0;
	int max_fd = -2;

	fd_set readset = {0};
	FD_ZERO(&readset);
	for(i = 0; i <= RRAC_DEVICE_MAX_CONNECTION_NR; i++)
	{
		if(connections[i] != NULL)
		{
			int sock_no = asm_connection_get_fd(connections[i]);
			if(sock_no >= 0)
			{
				FD_SET(sock_no, &readset);
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

	int result = select(max_fd + 1, &readset, NULL, NULL, &tv);

	if(result >= 0)
	{
		process_connections_events(connections, &readset);
	}

	return max_fd > 0 ? ASM_RET_OK : ASM_RET_FAIL;
}

int main(int argc, char* argv[])
{
	
	AsmConnection* connections[RRAC_DEVICE_MAX_CONNECTION_NR + 1] = {0};

	RracDevice* device = rrac_device_default_create();
	AsmConnection* cmd_connection  = rrac_device_connection_cmd_create("localhost", RRAC_PORT, device);
	AsmConnection* data_connection = rrac_device_connection_data_create("localhost", RRAC_PORT, device);

	rrac_device_connection_cmd_set_data_connection(cmd_connection, data_connection);
	rrac_device_connection_data_set_cmd_connection(data_connection, cmd_connection);

	if(cmd_connection != NULL && data_connection != NULL)
	{
		connections[0] = cmd_connection;
		connections[1] = data_connection;

		asm_connection_hook_destroy(cmd_connection, (AsmHookFunc)on_connection_broken, connections);
		asm_connection_hook_destroy(data_connection, (AsmHookFunc)on_connection_broken, connections);
		while(select_connections(connections) == ASM_RET_OK)
		{
				printf("%s:%d: select_connections return\n", __func__, __LINE__);
		}
	}

	asm_connection_destroy(connections[0]);
	asm_connection_destroy(connections[1]);
	rrac_device_destroy(device, NULL);

	return 0;
}
