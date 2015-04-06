/*
 * File:    asm-handle-dir.c
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

#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <asm-handle-dir.h>

typedef struct _PrivInfo
{
	DIR *dir;
	char* name;
}PrivInfo;

static AsmRet asm_handle_dir_get_handle(AsmHandle* thiz,  void** handle)
{
	asm_return_val_if_fail(thiz != NULL && handle != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	*handle = priv->dir;

	return ASM_RET_OK;
}

void asm_handle_dir_destroy(AsmHandle* thiz)
{
	if(thiz != NULL)
	{
		PrivInfo* priv = (PrivInfo*)thiz->priv;

		printf("%s:%d %p %s\n", __func__, __LINE__, priv->dir, priv->name);

		closedir(priv->dir);
		ASM_FREE(priv->name);
		ASM_FREE(thiz);
	}

	return;
}

AsmHandle* asm_handle_dir_create(DIR* dir, const char* name)
{
	asm_return_val_if_fail(dir != NULL && name != NULL, NULL);

	AsmHandle* thiz = (AsmHandle*)ASM_ALLOC(AsmHandle, sizeof(PrivInfo));
	
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	priv->dir = dir;
	priv->name = strdup(name);

	thiz->get_handle = asm_handle_dir_get_handle;
	thiz->destroy = asm_handle_dir_destroy;

	return thiz;
}

