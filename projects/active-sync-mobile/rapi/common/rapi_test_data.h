/*
 * File:    rapi_test_data.h
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

#include <rapi_lib.h>

#ifndef RAPI_TEST_DATA_H
#define RAPI_TEST_DATA_H

static inline AsmRet rapi_dump_system_info(RapiSystemInfo* system_info)
{
	asm_return_val_if_fail(system_info != NULL, ASM_RET_FAIL);

	printf("processor_arch=%d\n", system_info->processor_arch);
	printf("reserved=%d\n", system_info->reserved);
	printf("page_size=%d\n", system_info->page_size);
	printf("min_app_addr=%d\n", system_info->min_app_addr);
	printf("max_app_addr=%d\n", system_info->max_app_addr);
	printf("active_processor_mask=%d\n", system_info->active_processor_mask);
	printf("processor_nr=%d\n", system_info->processor_nr);
	printf("processor_type=%d\n", system_info->processor_type);
	printf("allocation_granularity=%d\n", system_info->allocation_granularity);
	printf("processor_level=%d\n", system_info->processor_level);
	printf("processor_revision=%d\n", system_info->processor_revision);

	return ASM_RET_OK;
}

static inline AsmRet rapi_dump_power_status(RapiSystemPowerStatus* power_status)
{
	asm_return_val_if_fail(power_status != NULL, ASM_RET_FAIL);

	printf("ac_line_status=%d\n", power_status->ac_line_status);
	printf("battery_flag=%d\n", power_status->battery_flag);
	printf("battery_life_percent=%d\n", power_status->battery_life_percent);
	printf("reserved1=%d\n", power_status->reserved1);
	printf("battery_life_time=%d\n", power_status->battery_life_time);
	printf("battery_full_life_time=%d\n", power_status->battery_full_life_time);
	printf("reserved2=%d\n", power_status->reserved2);
	printf("backup_battery_flag=%d\n", power_status->backup_battery_flag);
	printf("backup_battery_life_percent=%d\n", power_status->backup_battery_life_percent);
	printf("reserved3=%d\n", power_status->reserved3);
	printf("backup_battery_life_time=%d\n", power_status->backup_battery_life_time);
	printf("backup_battery_full_life_time=%d\n", power_status->backup_battery_full_life_time);

	return ASM_RET_OK;
}

static inline rapi_dump_version_info(RapiVersionInfo* version_info)
{
	printf("size_of_rest=%d\n", version_info->size_of_rest);
	printf("size=%d\n", version_info->size);
	printf("major=%d\n", version_info->major);
	printf("minor=%d\n", version_info->minor);
	printf("build_number=%d\n", version_info->build_number);
	printf("platform_id=%d\n", version_info->platform_id);

	return;
}



static const WStr default_name[12] = {'l','i','n','u','x','m','o','b','i','l','e', 0};

static inline int rapi_test_data_device_info_cmp(RapiDeviceInfo* info1, RapiDeviceInfo* info2)
{
	if(info1 == NULL || info2 == NULL)
	{
		return -1;
	}

	if(memcmp(&info1->guid, &info2->guid, sizeof(info1->guid)) != 0) return -1;
	if(info1->os_version_major != info2->os_version_major) return -1;
	if(info1->os_version_minor != info2->os_version_minor) return -1;
	
	if(wstr_compare(info1->name, info2->name) != 0) return -1;

	if(info1->dev_version != info2->dev_version) return -1;
	if(info1->cpu_type != info2->cpu_type) return -1;
	if(info1->dev_magic != info2->dev_magic) return -1;
	if(info1->current_partner != info2->current_partner) return -1;
	if(info1->dev_id != info2->dev_id) return -1;
	if(strcmp(info1->platform, info2->platform) != 0) return -1;
	if(strcmp(info1->model, info2->model) != 0) return -1;
	if(info1->components_nr != info2->components_nr) return -1;
	if(memcmp(info1->components, info2->components, sizeof(RapiComponent) * info1->components_nr) != 0) return -1;
	if(info1->pw_key != info2->pw_key) return -1;

	return 0;
}
static RapiComponent components[4] = {{1,2},{3,4}, {5,6}, {7,8}};
static inline AsmRet rapi_test_data_get_device_info(RapiDeviceInfo* info)
{
	asm_return_val_if_fail(info != NULL, ASM_RET_FAIL);

	info->os_version_major = 1;
	info->os_version_minor = 2;
	info->guid.data1 = 0x11223344;
	info->guid.data2 = 0x5566;
	info->guid.data3 = 0x7788;
	info->name = (WStr*)default_name;
	info->dev_version = 3;
	info->cpu_type = 4;
	info->dev_magic = 5;
	info->current_partner = 6;
	info->dev_id = 7;
	info->platform = "linuxmobile";
	info->model = "linuxmobile";
	info->components_nr = sizeof(components)/sizeof(components[0]);
	info->components = components;
	info->pw_key = 0;

	return ASM_RET_OK;
}

static inline AsmRet rapi_test_data_get_version_info(RapiVersionInfo* version)
{
	asm_return_val_if_fail(version != NULL, ASM_RET_FAIL);
	
	version->size_of_rest = sizeof(RapiVersionInfo) - sizeof(int);
	version->size = version->size_of_rest;
	version->major = 1;
	version->minor = 2;
	version->build_number = 3;
	version->platform_id = 4;

	return ASM_RET_OK;
}
#define  TEST_DATA_SPECIAL_FOLDER_PROGRAMS           "programs"
#define  TEST_DATA_SPECIAL_FOLDER_PERSONAL           "personal"
#define  TEST_DATA_SPECIAL_FOLDER_FAVORITES_GRYPHON  "favorites_gryphon"
#define  TEST_DATA_SPECIAL_FOLDER_STARTUP            "startup"
#define  TEST_DATA_SPECIAL_FOLDER_RECENT             "recent"
#define  TEST_DATA_SPECIAL_FOLDER_STARTMENU          "startmenu"
#define  TEST_DATA_SPECIAL_FOLDER_DESKTOPDIRECTORY   "desktopdirectory"
#define  TEST_DATA_SPECIAL_FOLDER_FONTS              "fonts"
#define  TEST_DATA_SPECIAL_FOLDER_FAVORITES          "favorites"

#define TEST_DATA_STORAGE_USED_SIZE 0x112233
#define TEST_DATA_STORAGE_FREE_SIZE 0x223344

static inline AsmRet rapi_test_data_get_system_info(RapiSystemInfo** system_info_ret)
{
	*system_info_ret = ASM_ALLOC(RapiSystemInfo, 0);
	(*system_info_ret)->processor_arch = 1;
	(*system_info_ret)->reserved = 2;
	(*system_info_ret)->page_size = 3;
	(*system_info_ret)->min_app_addr = 4;
	(*system_info_ret)->max_app_addr = 5;
	(*system_info_ret)->active_processor_mask = 6;
	(*system_info_ret)->processor_nr = 7;
	(*system_info_ret)->processor_type = 8;
	(*system_info_ret)->allocation_granularity = 9;
	(*system_info_ret)->processor_level = 10;
	(*system_info_ret)->processor_revision = 11;

	return ASM_RET_OK;
}

static inline AsmRet rapi_test_data_get_power_status(RapiSystemPowerStatus** power_status)
{
	*power_status = ASM_ALLOC(RapiSystemPowerStatus, 0);

	(*power_status)->ac_line_status = 1;
	(*power_status)->battery_flag = 2;
	(*power_status)->battery_life_percent = 3;
	(*power_status)->reserved1 = 4;
	(*power_status)->battery_life_time = 5;
	(*power_status)->battery_full_life_time = 6;
	(*power_status)->reserved2 = 7;
	(*power_status)->backup_battery_flag = 8;
	(*power_status)->backup_battery_life_percent = 9;
	(*power_status)->reserved3 = 10;
	(*power_status)->backup_battery_life_time = 11;
	(*power_status)->backup_battery_full_life_time = 12;

	return ASM_RET_OK;
}
#endif/*RAPI_TEST_DATA_H*/

