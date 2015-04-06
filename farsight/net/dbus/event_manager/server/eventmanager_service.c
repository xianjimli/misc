/*
 * eventmanager_service.c
 * Copyright (C) 2006 gclassfactory
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <dbus_helper.h>
#include "eventmanager_service.h"
#include "eventmanager_service_glue.h"

enum {
	PROP_0,
	PROP_LAST
};

enum {
	SIGNAL_EVENT,
	SIGNAL_LAST
};

static GObjectClass* parent_class = NULL;
static guint service_signals[SIGNAL_LAST + 1] = { 0 };

static void
eventmanager_service_marshal_VOID__GPOINTER_INT_GPOINTER(GClosure  *closure, GValue *return_value, guint n_param_values, 
		const GValue *param_values, gpointer invocation_hint, gpointer marshal_data);
static void eventmanager_service_class_init (EventManagerServiceClass *class);
static void eventmanager_service_init (EventManagerService *object);

static gboolean eventmanager_service_real_trigger_event(EventManagerService* thiz, char* type, int status, char* detail);
static gboolean eventmanager_service_real_query_event(EventManagerService* thiz, char* type, int* status, char** detail);

static void eventmanager_service_real_event(EventManagerService* thiz, char* type, int status, char* detail);
static void eventmanager_service_dispose(GObject *object);
static void eventmanager_service_finalize(GObject *object);


GType eventmanager_service_get_type (void)
{
	static GType service_type = 0;

	if (!service_type)
	{
		static const GTypeInfo service_info =
		{
			sizeof (EventManagerServiceClass),
			NULL,       /* base_init */
			NULL,       /* base_finalize */
			(GClassInitFunc) eventmanager_service_class_init,
			NULL,       /* class_finalize */
			NULL,       /* class_data */
			sizeof (EventManagerService),
			0,      /* n_preallocs */
			(GInstanceInitFunc) eventmanager_service_init,
		};
		service_type = g_type_register_static (G_TYPE_OBJECT, "EventManagerService", &service_info, 0);
	}

	return service_type;
}

static void eventmanager_service_class_init (EventManagerServiceClass *class)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (class);

	parent_class = g_type_class_peek_parent(class);
	gobject_class->dispose = eventmanager_service_dispose;
	gobject_class->finalize = eventmanager_service_finalize;

	class->trigger_event = eventmanager_service_real_trigger_event;
	class->query_event = eventmanager_service_real_query_event;

	class->event = eventmanager_service_real_event;

	service_signals[SIGNAL_EVENT] = 
		g_signal_new ("event",
		G_TYPE_FROM_CLASS (class),
		G_SIGNAL_RUN_FIRST,
		G_STRUCT_OFFSET (EventManagerServiceClass, event),
		NULL, NULL,
		eventmanager_service_marshal_VOID__GPOINTER_INT_GPOINTER,
		G_TYPE_NONE, 3,
		G_TYPE_STRING,
		G_TYPE_INT,
		G_TYPE_STRING);



	return;
}

static void eventmanager_service_init (EventManagerService *object)
{
	return;
}

static void
eventmanager_service_marshal_VOID__GPOINTER_INT_GPOINTER(GClosure  *closure, GValue *return_value, guint n_param_values,
				const GValue *param_values, gpointer invocation_hint, gpointer marshal_data)
{
	typedef void (*GMarshalFunc_VOID__GPOINTER_INT_GPOINTER) (gpointer data1, char* type, int status, char* detail, gpointer data2);
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
	callback (data1, g_marshal_value_peek_string(param_values + 1),g_marshal_value_peek_int(param_values + 2),g_marshal_value_peek_string(param_values + 3), data2);

	return;
}

typedef struct _SysEvent
{
	GQuark type;
	int    status;
	char*  detail;
}SysEvent;

static SysEvent* sysevent_create(const char* type, int    status, char*  detail)
{
	SysEvent* event = NULL;
	
	if(type != NULL)
	{
		event = g_new0(SysEvent, 1);
		
		if(event != NULL)
		{
			event->type   = g_quark_from_string(type);
			event->status = status;
			event->detail = g_strdup(detail);
		}
	}

	return event;
}

static void sysevent_destroy(SysEvent* event)
{
	if(event != NULL)
	{
		g_free(event->detail);
		g_free(event);
	}
}

static gboolean eventmanager_service_real_trigger_event(EventManagerService* thiz, char* type, int status, char* detail)
{
	gboolean ret = TRUE;
	SysEvent* event = sysevent_create(type, status, detail);
	
	g_object_set_data_full(G_OBJECT(thiz), type, event, sysevent_destroy);

	eventmanager_service_event(thiz, type, status, detail);
	
	return event != NULL;
}

static gboolean eventmanager_service_real_query_event(EventManagerService* thiz, char* type, int* status, char** detail)
{
	gboolean ret = FALSE;
	SysEvent* event = (SysEvent*)g_object_get_data(G_OBJECT(thiz), type);
	
	if(event != NULL)
	{
		*status = event->status;
		*detail = g_strdup(event->detail);

		ret = TRUE;
	}
	
	return ret;
}


static void eventmanager_service_real_event(EventManagerService* thiz, char* type, int status, char* detail)
{
	g_debug("%s: %s %d %s", __func__, type, status, detail);

	return;
}


gboolean eventmanager_service_trigger_event(EventManagerService* thiz, char* type, int status, char* detail)
{
	gboolean ret = {0};
	EventManagerServiceClass* class;

	g_return_val_if_fail (EVENTMANAGER_IS_SERVICE (thiz), ret);
	g_return_val_if_fail(type != NULL && detail != NULL, ret);

	class = EVENTMANAGER_SERVICE_GET_CLASS (thiz);

	ret   = class->trigger_event(thiz, type, status, detail);

	return ret;
}

gboolean eventmanager_service_query_event(EventManagerService* thiz, char* type, int* status, char** detail)
{
	gboolean ret = {0};
	EventManagerServiceClass* class;

	g_return_val_if_fail (EVENTMANAGER_IS_SERVICE (thiz), ret);
	g_return_val_if_fail(type != NULL && status != NULL && detail != NULL, ret);
	
	class = EVENTMANAGER_SERVICE_GET_CLASS (thiz);

	ret   = class->query_event(thiz, type, status, detail);

	return ret;
}


void eventmanager_service_event(EventManagerService* thiz, char* type, int status, char* detail)
{
	g_signal_emit (thiz, service_signals[SIGNAL_EVENT], 0, type, status, detail);
}


EventManagerService* eventmanager_service_new(void)
{
    static GObject* obj = NULL;

    if(obj == NULL)
    {
        obj = dbus_system_register_object(EVENTMANAGER_TYPE_SERVICE,
            &dbus_glib_eventmanager_service_object_info, "EventManager", "object");
    }
    else
    {
        g_object_ref(obj);
    }

    return (EventManagerService*)obj;
}

static void eventmanager_service_dispose (GObject *object)
{
	G_OBJECT_CLASS (parent_class)->dispose (object);

	return;
}

static void eventmanager_service_finalize (GObject *object)
{
	G_OBJECT_CLASS (parent_class)->finalize (object);

	return;
}

