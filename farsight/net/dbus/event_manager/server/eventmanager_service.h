/*
 * eventmanager_service.h
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
#ifndef EVENTMANAGER_SERVICE_H
#define EVENTMANAGER_SERVICE_H

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define EVENTMANAGER_TYPE_SERVICE                 (eventmanager_service_get_type ())
#define EVENTMANAGER_SERVICE(obj)                 (G_TYPE_CHECK_INSTANCE_CAST ((obj), EVENTMANAGER_TYPE_SERVICE, EventManagerService))
#define EVENTMANAGER_SERVICE_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST ((klass), EVENTMANAGER_TYPE_SERVICE, EventManagerServiceClass))
#define EVENTMANAGER_IS_SERVICE(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EVENTMANAGER_TYPE_SERVICE))
#define EVENTMANAGER_IS_SERVICE_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), EVENTMANAGER_TYPE_SERVICE))
#define EVENTMANAGER_SERVICE_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), EVENTMANAGER_TYPE_SERVICE, EventManagerServiceClass))

typedef struct _EventManagerService        EventManagerService;
typedef struct _EventManagerServiceClass   EventManagerServiceClass;

struct _EventManagerService
{
	GObject object;


};

struct _EventManagerServiceClass
{
	GObjectClass parent_class;

	gboolean (*trigger_event)(EventManagerService* thiz, char* type, int status, char* detail);
	gboolean (*query_event)(EventManagerService* thiz, char* type, int* status, char** detail);

	void (*event)(EventManagerService* thiz, char* type, int status, char* detail);

};

GType eventmanager_service_get_type(void) G_GNUC_CONST;
EventManagerService* eventmanager_service_new(void);

gboolean eventmanager_service_trigger_event(EventManagerService* thiz, char* type, int status, char* detail);
gboolean eventmanager_service_query_event(EventManagerService* thiz, char* type, int* status, char** detail);

void eventmanager_service_event(EventManagerService* thiz, char* type, int status, char* detail);

G_END_DECLS

#endif /*EVENTMANAGER_SERVICE_H*/
