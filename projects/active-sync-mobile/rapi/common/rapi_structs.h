/*
 * File:    rapi_structs.h
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

#ifndef _RAPI_STRUCTS_H
#define _RAPI_STRUCTS_H

typedef struct _RapiComponent
{
	unsigned int l;
	unsigned int h;
}RapiComponent;

typedef struct _RapiVersionInfo{
	unsigned int size_of_rest;
	unsigned int size;
	unsigned int major;
	unsigned int minor;
	unsigned int build_number;
	unsigned int platform_id;
	WStr memo[128];
}RapiVersionInfo;

typedef struct _RapiDeviceGuid
{
	unsigned int   data1;
	unsigned short data2;
	unsigned short data3;
	unsigned char  data4[8];
}RapiDeviceGuid;

typedef struct _RapiDeviceInfo
{
	RapiDeviceGuid   guid;
	unsigned int os_version_major;
	unsigned int os_version_minor;
	WStr*  name;
	unsigned int dev_version;
	unsigned int cpu_type;
	unsigned int dev_magic; 
	unsigned int current_partner;
	unsigned int dev_id;
	char*  platform;
	char*  model;
	unsigned int components_nr;
	RapiComponent* components;
	unsigned int pw_key;
}RapiDeviceInfo;

typedef struct _RapiProcessInfo
{
	unsigned int process_handle;
	unsigned int thread_handle;
	unsigned int pid;
	unsigned int tid;
}RapiProcessInfo;

typedef struct _RapiStoreInfo
{
	unsigned int used_size;
	unsigned int free_size;
}RapiStoreInfo;

typedef struct _RapiSystemInfo
{
	unsigned short processor_arch;
	unsigned short reserved;
	unsigned int   page_size;
	unsigned int   min_app_addr;
	unsigned int   max_app_addr;
	unsigned int   active_processor_mask;
	unsigned int   processor_nr;
	unsigned int   processor_type;
	unsigned int   allocation_granularity;
	unsigned short processor_level;
	unsigned short processor_revision;
}RapiSystemInfo;

typedef struct _RapiSystemPowerStatus
{
	unsigned char ac_line_status;
	unsigned char battery_flag;
	unsigned char battery_life_percent;
	unsigned char reserved1;
	unsigned int  battery_life_time;
	unsigned int  battery_full_life_time;
	unsigned char reserved2;
	unsigned char backup_battery_flag;
	unsigned char backup_battery_life_percent;
	unsigned char reserved3;
	unsigned int backup_battery_life_time;
	unsigned int backup_battery_full_life_time;
}RapiSystemPowerStatus;

typedef struct _RapiFileTime
{
	unsigned int low;
	unsigned int high;
}RapiFileTime;

typedef struct _RapiFindData
{
	unsigned int file_attributes;
	RapiFileTime create_time;
	RapiFileTime last_access_time;
	RapiFileTime last_write_time;
	unsigned int size_high;
	unsigned int size_low;
	unsigned int oid;
	WStr     file_name[RAPI_MAX_PATH];
}RapiFindData;

#endif/*_RAPI_STRUCTS_H*/

