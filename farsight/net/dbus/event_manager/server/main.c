/*
 * File:    main.c
 * Author:  Li XianJing <lixianjing@broncho.cn>
 * Brief:   the entry point of event manager daemon.
 *
 * Copyright (c) 2006-2007  topwise, Inc.
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
 * 2007-5-14 Li XianJing <lixianjing@broncho.cn> created
 *
 */
#include <stdio.h>
#include <dbus_helper.h>
#include "eventmanager_service.h"

#ifdef EVENTMANAGER_TEST
static gboolean exit_main_loop(gpointer data)
{
	g_main_loop_quit(data);

	return FALSE;
}

int main(int argc, char* argv[])
{
	GMainLoop* main_loop = NULL;

	g_type_init();
	g_thread_init(NULL);

	EventManagerService* obj = eventmanager_service_new();
	
	main_loop = g_main_loop_new(NULL, FALSE);

	if(argv[1] != NULL && strcmp(argv[1], "--debug") == 0)
	{
		g_timeout_add(10000, (GSourceFunc)exit_main_loop, main_loop);
	}

	g_main_loop_run(main_loop);

	g_object_unref(G_OBJECT(obj));

	return 0;
}

#else

static EventManagerService* g_eventmanager = NULL;

void init(void)
{
	g_type_init();

	g_eventmanager = eventmanager_service_new();

	return;
}

void deinit(void)
{
	if(g_eventmanager != NULL)
	{
		g_object_unref(G_OBJECT(g_eventmanager));
		g_eventmanager = NULL;
	}
	
	return;
}
#endif

