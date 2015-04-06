/*
 * File:    event_manager.c
 * Author:  Li XianJing <lixianjing@broncho.cn>
 * Brief:   event manager client api.
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

#include <pthread.h>
#include "dbus_helper.h"
#include "eventmanager.h"
#include "eventmanager_service_bindings.h"

#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)

struct _EventManager
{
	DBusGProxy* proxy;

	gpointer    user_data;
	EventManagerOnEventFunc on_event;
};

static void event_manager_on_event(DBusGProxy *proxy, 
	const char* type, int status, const char* detail, gpointer user_data);

static void
eventmanager_service_marshal_VOID__GPOINTER_INT_GPOINTER(GClosure  *closure, GValue *return_value, guint n_param_values,
				const GValue *param_values, gpointer invocation_hint, gpointer marshal_data)
{
	typedef void (*GMarshalFunc_VOID__GPOINTER_INT_GPOINTER) 
		(gpointer data1, char* type, int status, char* detail, gpointer data2);
	register GMarshalFunc_VOID__GPOINTER_INT_GPOINTER callback;
	register GCClosure *cc = (GCClosure*) closure;
	register gpointer data1, data2;

	g_return_if_fail (n_param_values == 4);

	if (G_CCLOSURE_SWAP_DATA (closure))
	{
		data1 = closure->data;
		data2 = g_value_peek_pointer (param_values + 0);
	}
	else
	{
		data1 = g_value_peek_pointer (param_values + 0);
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__GPOINTER_INT_GPOINTER) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_marshal_value_peek_string(param_values + 1),
		g_marshal_value_peek_int(param_values + 2),g_marshal_value_peek_string(param_values + 3), data2);

	return;
}

EventManager* event_manager_create(void)
{
	EventManager* thiz = g_new0(EventManager, 1);

	if(thiz != NULL)
	{
		thiz->proxy = dbus_system_create_object("EventManager", "object");

		if(thiz->proxy == NULL)
		{
			g_free(thiz);
			thiz = NULL;
		}
	}
	
	return thiz;
}

void        event_manager_destroy(EventManager* thiz)
{
	if(thiz != NULL)
	{
		if(thiz->proxy != NULL)
		{
			if(thiz->on_event != NULL)
			{
				dbus_g_proxy_disconnect_signal(thiz->proxy, "Event",
					G_CALLBACK (event_manager_on_event), thiz);
			}
			g_object_unref(G_OBJECT(thiz->proxy));
		}

		thiz->on_event = NULL;
		thiz->user_data = NULL;

		thiz->proxy = NULL;
		g_free(thiz);
	}

	return;
}

gboolean event_manager_trigger_event(EventManager* thiz, const char* type, int status, const char* detail)
{
	GError* error = NULL;
	gboolean ret = FALSE;
	char* str = NULL;
	
	g_return_val_if_fail(thiz != NULL && thiz->proxy != NULL && type != NULL, FALSE);

	ret = org_broncho_EventManagerInterface_trigger_event(thiz->proxy, type, status, detail, &error);

	if(error != NULL)
	{
		g_debug("%s:%s", __func__, error->message);
		g_error_free(error);
	}
	
	return ret;	
}

gboolean event_manager_query_event(EventManager* thiz, const char* type, int* status, char** detail)
{
	GError* error = NULL;
	gboolean ret = FALSE;

	g_return_val_if_fail(thiz != NULL && thiz->proxy != NULL && type != NULL, FALSE);

	ret = org_broncho_EventManagerInterface_query_event(thiz->proxy, type, status, detail, &error);

	if(error != NULL)
	{
		g_debug("%s:%s", __func__, error->message);
		g_error_free(error);
	}
	
	return ret;	
}

static void event_manager_on_event(DBusGProxy *proxy, 
	const char* type, int status, const char* detail, gpointer user_data)
{
	EventManager* thiz = (EventManager*)user_data;

	if(thiz->on_event != NULL)
	{
		thiz->on_event(thiz->user_data, type, status, detail);
	}
	
	return;
}

gboolean event_manager_reg_event(EventManager* thiz, EventManagerOnEventFunc on_event, gpointer user_data)
{
	g_return_val_if_fail(thiz != NULL && thiz->proxy != NULL, FALSE);

	thiz->user_data = user_data;
	thiz->on_event = on_event;

	if(on_event != NULL)
	{
		dbus_g_object_register_marshaller(eventmanager_service_marshal_VOID__GPOINTER_INT_GPOINTER,
			G_TYPE_NONE, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INVALID);
			
		dbus_g_proxy_add_signal(thiz->proxy, "Event",
			G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INVALID);
			
		dbus_g_proxy_connect_signal(thiz->proxy, "Event",
			G_CALLBACK (event_manager_on_event), thiz, NULL);
	}
	else
	{
		dbus_g_proxy_disconnect_signal(thiz->proxy, "Event",
			G_CALLBACK (event_manager_on_event), thiz);
	}
	
	return TRUE;
}

EventManager* event_manager_get_default(void)
{
	static __thread EventManager* event_manager = NULL;

	if(event_manager == NULL)
	{
		event_manager = event_manager_create();
	}

	return event_manager;
}

#ifdef EVENT_MANAGER_TEST
static gboolean exit_main_loop(GMainLoop* main_loop)
{
	g_main_loop_quit(main_loop);
	
	return FALSE;
}

static void on_event(gpointer user_data, 
	const char* type, int status, const char* detail)
{

	g_debug("%s: tid=%p %s %d %s", __func__, pthread_self(), type, status, detail);
	
	return;
}

void single_thread_test(void)
{
	int i = 0;
	int status = 0;
	char* detail = NULL;
	
	GMainLoop* main_loop = NULL;
	EventManager* thiz = NULL;
	
	g_type_init();

	main_loop = g_main_loop_new(NULL, FALSE);
	thiz = event_manager_create();
	
	event_manager_reg_event(thiz, on_event, NULL);

	for(i = 0; i < 100; i++)
	{
		g_assert(event_manager_trigger_event(thiz, STR_SYSTEM_EVENT_TYPE_DISK_FULL, TRUE, "full"));
		g_assert(event_manager_query_event(thiz, STR_SYSTEM_EVENT_TYPE_DISK_FULL, &status, &detail));
		g_assert(status);
		g_assert(strcmp(detail, "full") == 0);
		
		g_assert(event_manager_trigger_event(thiz, STR_SYSTEM_EVENT_TYPE_DISK_FULL, TRUE, "full"));
		g_assert(event_manager_query_event(thiz, STR_SYSTEM_EVENT_TYPE_DISK_FULL, &status, NULL));
		g_assert(status);
		
		g_assert(event_manager_trigger_event(thiz, STR_SYSTEM_EVENT_TYPE_DISK_FULL, FALSE, NULL));
		g_assert(event_manager_query_event(thiz, STR_SYSTEM_EVENT_TYPE_DISK_FULL, &status, &detail));
		g_assert(!status);
		g_assert(strcmp(detail, "") == 0);
	}

	g_timeout_add(10000, (GSourceFunc)exit_main_loop, main_loop);
	g_main_loop_run(main_loop);
	g_main_loop_unref(main_loop);

	event_manager_destroy(thiz);

	return ;
}	

void* thread_entry(void* param)
{
	int i = 0;
	int status = 0;
	char* detail = NULL;
	
	GMainLoop* main_loop = NULL;
	GMainContext* context = g_main_context_new();
	EventManager* thiz = NULL;
	main_loop = g_main_loop_new(context, FALSE);
	
	thiz = event_manager_get_default();
	
	event_manager_reg_event(thiz, on_event, NULL);

	for(i = 0; i < 100; i++)
	{
		g_assert(event_manager_trigger_event(thiz, STR_SYSTEM_EVENT_TYPE_DISK_FULL, TRUE, "full"));
		g_assert(event_manager_query_event(thiz, STR_SYSTEM_EVENT_TYPE_DISK_FULL, &status, &detail));
		g_assert(status);
		g_assert(strcmp(detail, "full") == 0);
		
		g_assert(event_manager_trigger_event(thiz, STR_SYSTEM_EVENT_TYPE_DISK_FULL, TRUE, "full"));
		g_assert(event_manager_query_event(thiz, STR_SYSTEM_EVENT_TYPE_DISK_FULL, &status, NULL));
		g_assert(status);
		
		g_assert(event_manager_trigger_event(thiz, STR_SYSTEM_EVENT_TYPE_MEMORY_LOW, FALSE, NULL));
		g_assert(event_manager_query_event(thiz, STR_SYSTEM_EVENT_TYPE_MEMORY_LOW, &status, &detail));
		g_assert(!status);
		g_assert(strcmp(detail, "") == 0);
	}

	g_timeout_add(10000, (GSourceFunc)exit_main_loop, main_loop);
	g_main_loop_run(main_loop);
	g_main_loop_unref(main_loop);

	return NULL;
}

void multi_thread_test(void)
{
	int i = 0;
	pthread_t tid[10] = {0};

	for(i = 0; i < sizeof(tid)/sizeof(tid[0]); i++)
	{
		pthread_create(tid+i, NULL, thread_entry, NULL);
	}

	for(i = 0; i < sizeof(tid)/sizeof(tid[0]); i++)
	{
		pthread_join(tid[i], NULL);
	}

	return;
}

int main(int argc, char* argv[])
{
	g_type_init();
	g_thread_init(NULL);
	dbus_g_thread_init();

	event_manager_get_default();
	if(argc == 1)
	{
		single_thread_test();
	}
	else
	{
		multi_thread_test();	
	}

	return 0;
}
#endif/*EVENT_MANAGER_TEST*/
