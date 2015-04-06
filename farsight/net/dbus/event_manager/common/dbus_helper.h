/*
 * File:    dbus_helper.h
 * Author:  Li XianJing <lixianjing@broncho.cn>
 * Brief:   some helper functions to simplify dbus usage.
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
 * 2007-4-18 Li XianJing <lixianjing@broncho.cn> created
 *
 */

#include <stdio.h>
#include <glib.h>
#include <glib.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus.h>
#include <unistd.h>
#include <sys/syscall.h>

#ifndef DBUS_HELPER_H
#define DBUS_HELPER_H

#define MAX_PATH 260
#define STR_SERVICE_NAME_FORMAT "org.broncho.%sService"
#define STR_OBJECT_NAME_FORMAT "/org/broncho/%sService/%s"
#define STR_INTERFACE_NAME_FORMAT "org.broncho.%sInterface"

#define dbus_system_register_object(type, info, service, object) \
	dbus_register_object(type, info, service, object, DBUS_BUS_SYSTEM);
	
#define dbus_session_register_object(type, info, service, object) \
	dbus_register_object(type, info, service, object, DBUS_BUS_SESSION);

#define dbus_system_create_object(service, object) \
	dbus_create_object(service, object, DBUS_BUS_SYSTEM)

#define dbus_session_create_object(service, object) \
	dbus_create_object(service, object, DBUS_BUS_SESSION)
	
/**
 * dbus_register_object:
 *
 * Register a dbus service object, used by service provider.
 */
static inline GObject* dbus_register_object(GType type, const DBusGObjectInfo* info, 
	const char* service, const char* object, DBusBusType dbus_type)
{
	DBusGConnection* bus       = NULL;
	DBusGProxy*      bus_proxy = NULL;
	GError*          error     = NULL;
	GObject*         obj       = NULL;
	guint request_name_result  = DBUS_NAME_FLAG_DO_NOT_QUEUE;
	char             service_name[MAX_PATH + 1] = {0};
	char             object_name[MAX_PATH + 1] = {0};
	char             interface_name[MAX_PATH + 1] = {0};

	snprintf(service_name, MAX_PATH, STR_SERVICE_NAME_FORMAT, service);
	snprintf(object_name, MAX_PATH, STR_OBJECT_NAME_FORMAT, service, object);
	snprintf(interface_name, MAX_PATH, STR_INTERFACE_NAME_FORMAT, service);

	dbus_g_object_type_install_info(type, info);

	if((bus = dbus_g_bus_get(dbus_type, &error)) != NULL)
	{
		if((bus_proxy = dbus_g_proxy_new_for_name (bus, "org.freedesktop.DBus",
		  "/org/freedesktop/DBus", "org.freedesktop.DBus")) != NULL)
		{
			if(dbus_g_proxy_call(bus_proxy, "RequestName", &error, 
				G_TYPE_STRING, service_name,
				G_TYPE_UINT, 0,
				G_TYPE_INVALID,
				G_TYPE_UINT, &request_name_result,
				G_TYPE_INVALID) && request_name_result == DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
			{
					
				obj = g_object_new(type, NULL);
				dbus_g_connection_register_g_object(bus, object_name, G_OBJECT (obj));

				g_debug("%s %s running...%d", service_name, object_name, request_name_result);
			}
			else
			{
				g_debug("RequestName failed.\n");
			}
		}
		else
		{
			g_debug("dbus_g_proxy_new_for_name failed\n");
		}
	}
	else
	{
		g_debug("dbus_g_bus_get failed\n");
	}

	return obj;
}

#define _DBUS_POINTER_SHIFT(p)   ((void*) (((char*)p) + sizeof (void*)))
#define DBUS_G_CONNECTION_FROM_CONNECTION(x)     ((DBusGConnection*) _DBUS_POINTER_SHIFT(x))

static inline
DBusGConnection* dbus_g_bus_get_private (DBusBusType     type,
				GMainContext* main_context,
                GError    **error)
{
	DBusConnection *connection = NULL;
	DBusError derror = {0};

	g_return_val_if_fail (error == NULL || *error == NULL, NULL);

	//XXX:make sure this function is called in main thread by calling dbus_g_bus_get
	//_dbus_g_value_types_init ();

	dbus_error_init (&derror);

	connection = dbus_bus_get_private (type, &derror);
	if (connection == NULL)
	{
		dbus_set_g_error (error, &derror);
		dbus_error_free (&derror);
		return NULL;
	}

	/* does nothing if it's already been done */
	dbus_connection_setup_with_g_main (connection, main_context);

	return DBUS_G_CONNECTION_FROM_CONNECTION (connection);
}

/**
 * dbus_create_object:
 *
 * Create a dbus object, used by service user.
 */
static inline DBusGProxy* dbus_create_object(const char* service, const char* object, DBusBusType dbus_type)
{
	DBusGConnection* bus       = NULL;
	DBusGProxy*      obj       = NULL;
	GError*          error     = NULL;
	char             service_name[MAX_PATH + 1] = {0};
	char             object_name[MAX_PATH + 1] = {0};
	char             interface_name[MAX_PATH + 1] = {0};
	int              tid = syscall(SYS_gettid);

	snprintf(service_name, MAX_PATH, STR_SERVICE_NAME_FORMAT, service);
	snprintf(object_name, MAX_PATH, STR_OBJECT_NAME_FORMAT, service, object);
	snprintf(interface_name, MAX_PATH, STR_INTERFACE_NAME_FORMAT, service);

	if(tid == getpid())
	{
		bus = dbus_g_bus_get(dbus_type, &error);
	}
	else
	{
		static __thread DBusGConnection* bus_tls = NULL;
		if(bus_tls == NULL)
		{
			GMainContext* main_context = NULL;
			bus_tls = dbus_g_bus_get_private(dbus_type, main_context, &error);
			if(main_context == NULL)
			{
				g_debug("%s:%d non-main thread without main_context, notify/async call will be failed.",
					__func__, __LINE__);
			}
		}
		bus = bus_tls;
	}

	if(bus != NULL)
	{
		if((obj = dbus_g_proxy_new_for_name(bus, service_name, object_name, interface_name)) != NULL)
		{
			g_debug("dbus_g_proxy_new_for_name(%s %s %s) ok.", service_name, object_name, interface_name);
		}
		else
		{
			g_debug("dbus_g_proxy_new_for_name(%s %s %s) failed.", service_name, object_name, interface_name);
		}
	}
	else
	{
		g_debug("dbus_g_bus_get failed\n");
	}

    return obj;
}

/*
 * wrappers for dbus built in service.
 **/

static inline
DBusGProxy* dbus_service_create(int bus_type)
{
	GError*  error = NULL;
	DBusGProxy*      bus_proxy = NULL;
	DBusGConnection* bus = dbus_g_bus_get(bus_type, &error);
	
	if(bus == NULL && error != NULL)
	{
		g_debug("%s %s\n", __func__, error->message);
	}

	bus_proxy = dbus_g_proxy_new_for_name (bus, "org.freedesktop.DBus",
		"/org/freedesktop/DBus", "org.freedesktop.DBus");

	return bus_proxy;
}

#define dbus_service_system_create() dbus_service_create(DBUS_BUS_SYSTEM)
#define dbus_service_session_create() dbus_service_create(DBUS_BUS_SESSION)

static inline 
gboolean dbus_service_list_names(DBusGProxy* proxy, gchar*** names, GError** error)
{
  return dbus_g_proxy_call (proxy, "ListNames", error, G_TYPE_INVALID, G_TYPE_STRV, names, G_TYPE_INVALID);
}

static inline
gboolean dbus_service_get_service_pid(DBusGProxy *proxy, const char* name, guint* pid, GError** error)
{
  return dbus_g_proxy_call (proxy, "GetConnectionUnixProcessID", error, 
  	G_TYPE_STRING, name, G_TYPE_INVALID, G_TYPE_UINT, pid, G_TYPE_INVALID);
}

static inline
gboolean dbus_service_get_service_uid(DBusGProxy *proxy, const char* name, guint* uid, GError** error)
{
  return dbus_g_proxy_call (proxy, "GetConnectionUnixUser", error, 
  	G_TYPE_STRING, name, G_TYPE_INVALID, G_TYPE_UINT, uid, G_TYPE_INVALID);
}

static inline
gboolean dbus_service_reload_config(DBusGProxy *proxy, GError **error)
{
	return dbus_g_proxy_call (proxy, "ReloadConfig", error, G_TYPE_INVALID, G_TYPE_INVALID);
}

static inline
gboolean dbus_service_get_service_owner (DBusGProxy *proxy, const char* name, gchar** owner, GError **error)
{
	return dbus_g_proxy_call (proxy, "GetNameOwner", error, 
		G_TYPE_STRING, name, G_TYPE_INVALID, G_TYPE_STRING, owner, G_TYPE_INVALID);
}

static inline gboolean dbus_service_destroy(DBusGProxy *proxy)
{
	if(proxy != NULL)
	{
		g_object_unref(G_OBJECT(proxy));
	}

	return TRUE;
}

static inline
gboolean dbus_service_request_name(DBusGProxy *proxy, const char* name, gint* result, GError **error)
{
	return dbus_g_proxy_call (proxy, "RequestName", error, 
		G_TYPE_STRING, name, G_TYPE_UINT, 0, G_TYPE_INVALID, G_TYPE_UINT, result, G_TYPE_INVALID);
}

static inline
gboolean dbus_service_release_name(DBusGProxy *proxy, const char* name, gint* result, GError **error)
{
	return dbus_g_proxy_call (proxy, "ReleaseName", error, 
		G_TYPE_STRING, name, G_TYPE_INVALID, G_TYPE_UINT, result, G_TYPE_INVALID);
}

static inline
gboolean dbus_service_dump(int bus_type)
{
	int i   = 0;
	int pid = 0;
	int uid = 0;
	char**  names = NULL;
	char*   owner = NULL;
	GError* error = NULL;
	DBusGProxy* proxy = NULL;

	proxy = dbus_service_create(bus_type);

	if(proxy != NULL)
	{
		dbus_service_list_names(proxy, &names, &error);
		
		for(i = 0; names[i] != NULL; i++)
		{
			dbus_service_get_service_pid(proxy, names[i], &pid, NULL);
			dbus_service_get_service_uid(proxy, names[i], &uid, NULL);
			dbus_service_get_service_owner(proxy, names[i], &owner, NULL);

			g_debug("[%d] %32s pid=%08d uid=%08d\n", i, names[i], pid, uid);
			g_free(owner);
		}

		g_strfreev(names);

		dbus_service_destroy(proxy);
	}

	return proxy != NULL;
}

#endif/*DBUS_HELPER_H*/
