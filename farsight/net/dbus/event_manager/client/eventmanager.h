/*
 * File:    event_manager.h
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

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <glib.h>
#include <eventmanager_type.h>

G_BEGIN_DECLS

struct _EventManager;
typedef struct _EventManager EventManager;

/**
 * EventManagerOnEventFunc:
 * the event handler prototype.
 * @thiz:   [in] the #EventManager instance
 * @type:   [in] the event type, the builtin event type are declared in eventmanager_type.h
 * @status: [in] the value depend on event type, some are gboolean type, some are enum type.
 * @detail: [in] detail information, they are key/value pairs, buitlt in keys are declared in eventmanager_type.h
 *               for example: SENDER=system_settings;VALUE=zh_CH.UTF-8;TIMESTAMP=1182135791
 */
typedef void (*EventManagerOnEventFunc)(gpointer user_data, const char* type, int status, const char* detail);

/**
 * event_manager_create:
 *
 * create a #EventManager instance.
 * 
 * Return value: a #EventManager object.
 *
 */
EventManager* event_manager_create(void);

/**
 * event_manager_destroy:
 *
 * destroy a #EventManager object.
 *
 * Return value: N/A
 *
 */
void          event_manager_destroy(EventManager* thiz);

/**
 * event_manager_trigger_event:
 * @thiz:   [in] the #EventManager instance
 * @type:   [in] the event type, the builtin event type are declared in eventmanager_type.h
 * @status: [in] the value depend on event type, some are gboolean type, some are enum type.
 * @detail: [in] detail information, they are key/value pairs, buitlt in keys are declared in eventmanager_type.h
 *               for example: SENDER=system_settings;VALUE=zh_CH.UTF-8;TIMESTAMP=1182135791
 * 
 * triger a event.
 *
 * Return value: return TRUE if succeed, return FALSE in else case.
 *  
 */
gboolean event_manager_trigger_event(EventManager* thiz, const char* type, int status, const char* detail);

/**
 * event_manager_query_event:
 * @thiz:   [in] the #EventManager instance
 * @type:   [in] the event type, the builtin event type are declared in eventmanager_type.h
 * @status: [out] the value depend on event type, some are gboolean type, some are enum type.
 * @detail: [out] detail information, they are key/value pairs, buitlt in keys are declared in eventmanager_type.h
 * 
 * qurey the status of specified event, if detail is not NULL, caller should free it.
 *
 * Return value: return TRUE if succeed, return FALSE in else case.
 *  
 */
gboolean event_manager_query_event(EventManager* thiz, const char* type, int* status, char** detail);

/**
 * event_manager_reg_event:
 * @thiz:      [in] the #EventManager instance
 * @on_event:  [in] the event handler.
 * @user_data: [in] the context of the event handler.
 *
 * register a event handler, it will be called when a event is trigered.
 *
 * Return value: return TRUE if succeed, return FALSE in else case.
 *
 */
gboolean event_manager_reg_event(EventManager* thiz, EventManagerOnEventFunc on_event, gpointer user_data);

/**
 * event_manager_get_default:
 *
 * get the singleton object, don't release it.
 *
 * Return value: a #EventManager object.
 *
 */
EventManager* event_manager_get_default(void);

G_END_DECLS

#endif/*EVENT_MANAGER_H*/

