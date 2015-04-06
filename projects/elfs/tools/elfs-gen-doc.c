/*
 * File:    elfs-gen.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   a tool to generate makefile for embeded linux from scratch.
 *
 * Copyright (c) 2009  Li XianJing <xianjimli@hotmail.com>
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
 * 2009-05-29 Li XianJing <xianjimli@hotmail.com> created
 *
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ini_config.h>

#define PKGS_DIR "packages"
static void gen_one_pkg(IniGroup* group, FILE* fp);
static void gen_doc(IniConfig* ini);

char* read_file(const char* file_name)
{
	FILE* fp = NULL;
	struct stat st = {0};
	char* buffer = NULL;
	return_val_if_fail(file_name != NULL, NULL);

	if(stat(file_name, &st) != 0) 
		return NULL;
	fp = fopen(file_name, "r");
	return_val_if_fail(fp != NULL, NULL);
	buffer = (char*)malloc(st.st_size + 1);

	if(buffer == NULL)
	{
		fclose(fp);

		return NULL;
	}
	fread(buffer, 1, st.st_size, fp);
	buffer[st.st_size] = '\0';

	return buffer;
}

int main(int argc, char* argv[])
{
	IniConfig* ini = NULL;
	
	if(argc != 2)
	{
		printf("Usage: %s pkg-config\n", argv[0]);

		return 0;
	}

	ini = ini_config_create(argv[1]);
	if(ini != NULL)
	{
		gen_doc(ini);
		ini_config_destroy(ini);
	}

	return 0;
}

static const char* get_pkg_tar(const char* url)
{
	const char* start = strrchr(url, '/');

	return start == NULL ? start : start + 1;
}

static const char* get_pkg_dir(const char* pkg_tar, char* dir)
{
	char* end = NULL;
	return_val_if_fail(pkg_tar != NULL && dir != NULL, NULL);

	strcpy(dir, pkg_tar);
	if((end = strstr(dir, ".tar")) != NULL)
	{
		*end = '\0';
	}

	return dir;
}

static void gen_one_pkg_make(IniGroup* group, FILE* fp)
{
	char buffer[2048] = {0};

	IniPair* url          = ini_pairs_find(group->pairs, "url");
	IniPair* config_env   = ini_pairs_find(group->pairs, "config-env");
	IniPair* config_cmd  = ini_pairs_find(group->pairs, "config-cmd");
	IniPair* config_param = ini_pairs_find(group->pairs, "config-param");
	IniPair* patch_cmd    = ini_pairs_find(group->pairs, "patch-cmd");
	IniPair* config_precmd   = ini_pairs_find(group->pairs, "config-precmd");

	return_if_fail(url != NULL && url->value != NULL);

	const char* tar = get_pkg_tar(url->value);
	const char* dir = get_pkg_dir(tar, buffer);

	fprintf(fp, "%s:\n", group->name);

	if(patch_cmd != NULL && patch_cmd->value != NULL)
	{
		fprintf(fp, "	%s && \\\n", patch_cmd->value);
	}

	if(config_env != NULL && config_env->value != NULL)
	{
		fprintf(fp, "	%s && \\\n", config_env->value);
	}

	if(config_precmd != NULL && config_precmd->value != NULL)
	{
		fprintf(fp, "	cd %s && %s; cd -;\\\n", dir, config_precmd->value);
	}

	if(config_cmd == NULL || config_cmd->value == NULL)
	{
		fprintf(fp, "	cd %s && \\\n", dir);
	}
	else if(strcmp(config_cmd->value, "autoconf") == 0)
	{
		fprintf(fp, "	mkdir %s/$(ARCH); cd %s/$(ARCH) && \\\n", dir, dir);
		fprintf(fp, "	../configure $(HOST_PARAM) --prefix=$(PREFIX) %s &&\\\n", 
			config_param != NULL ? config_param->value:"");
	}
	else
	{
		fprintf(fp, "	cd %s && \\\n", dir);
		fprintf(fp, "	./%s %s &&\\\n", config_cmd->value,
			config_param != NULL ? config_param->value:""); 
	}
	fprintf(fp, "	make clean; make && make install\n");
	

	return;
}


#define STR_HEADER \
"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n\
<html xmlns=\"http://www.w3.org/1999/xhtml\" dir=\"ltr\" lang=\"en-US\">\n\
\n\
<head profile=\"http://gmpg.org/xfn/11\">\n\
    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\n\
    <title>Embedded Linux From Scratch(www.limodev.cn)</title>\n\
</head>\n\
<body>\n\
<pre>\n\
</pre>\n\
<a href=\"http://www.limodev.cn/elfs/elfs.html\">Embedded Linux From Scratch</a>\n\
<hr>\n\
<table width=\"800\">\n\
<tbody>\n\
<tr>\n\
<td align=\"center\">软件包</td>\n\
<td bgcolor=\"#D0D0D0\">%s</td>\n\
</tr>\n\
<tr>\n\
<td align=\"center\">功能</td>\n\
<td bgcolor=\"#D0D0D0\">%s</td>\n\
</tr>\n\
<tr>\n\
<td align=\"center\">主页</td>\n\
<td bgcolor=\"#D0D0D0\"><a href=\"%s\">%s</a></td>\n\
</tr>\n\
<tr>\n\
<td align=\"center\">下载</td>\n\
<td bgcolor=\"#D0D0D0\"><a href=\"%s\">%s</a></td>\n\
</tr>\n\
<tr><td align=\"center\">问题解决方法</td>\n\
<td bgcolor=\"#D0D0D0\">\n\
<pre>\n\
%s\n\
</pre>\n\
</td></tr>\n\
<tr>\n\
<td align=\"center\">编译脚本</td>\n\
<td bgcolor=\"#D0D0D0\">\n\
<pre>\n"

#define STR_TAIL \
"</pre>\n\
</td>\n\
</tr>\n\
</tbody>\n\
</table>\n\
<hr>\n\
<center><a href=\"http://www.limodev.cn/blog\">Copyright (C) 2009 limodev.cn</a></center>\n\
</body>\n\
<html>"

static void gen_one_pkg(IniGroup* group, FILE* fp)
{
	IniPair* desc = ini_pairs_find(group->pairs, "desc");
	IniPair* home = ini_pairs_find(group->pairs, "home");
	IniPair* url          = ini_pairs_find(group->pairs, "url");

	char file_name[260] = {0};
	snprintf(file_name, sizeof(file_name), "%s_fix.txt", group->name);
	char* buffer = read_file(file_name);
	fprintf(fp, STR_HEADER, group->name, 
		desc->value, home->value, home->value, 
		url->value, url->value,
		buffer != NULL? buffer : "none");
	free(buffer);

	gen_one_pkg_make(group, fp);

	fprintf(fp, STR_TAIL);

	return;
}

#define STR_INDEX_HEADER \
"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n\
<html xmlns=\"http://www.w3.org/1999/xhtml\" dir=\"ltr\" lang=\"en-US\">\n\
<head profile=\"http://gmpg.org/xfn/11\">\n\
    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\n\
    <title>Embedded Linux From Scratch(www.limodev.cn)</title>\n\
</head>\n\
<body>\n\
<center><a href=\"http://www.limodev.cn/elfs/elfs.html\">Embedded Linux From Scratch</a></center>\n\
<br><hr>\n\
Cross Compile:<br>\n\
<ol>\n"

static void gen_doc(IniConfig* ini)
{
	IniGroup* group = NULL;
	FILE* fpelfs = fopen("elfs/elfs.html", "wb+");
	if(fpelfs != NULL)
	{
		fprintf(fpelfs, "%s", STR_INDEX_HEADER);
		fprintf(fpelfs, "<li><a href=\"http://www.limodev.cn/elfs/env.html\">Environment variables</a>\n");
		for(group = ini->groups->first_group; group != NULL; group = group->next)
		{
			char file_name[260] = {0};
			snprintf(file_name, sizeof(file_name), "elfs/%s.html", group->name);
			FILE* fp = fopen(file_name, "wb+");
			if(fp != NULL)
			{
				gen_one_pkg(group, fp);
				fclose(fp);
			}
			fprintf(fpelfs, "<li><a href=\"http://www.limodev.cn/elfs/%s.html\">%s</a>\n", 
				group->name, group->name);
		}
		fprintf(fpelfs, "</ol>\n");
		fprintf(fpelfs, "<br>Download:<hr><ul>\n");
		fprintf(fpelfs, "<li><a href=\"http://downloads.openmoko.org/developer/toolchains/openmoko-i686-20090323-armv4t-linux-gnueabi-toolchain-openmoko.tar.bz2\">Openmoko toolchain</a>\n");
		fprintf(fpelfs, "<li><a href=\"http://www.limodev.cn/elfs/elfs.tar.gz\">Elfs Scripts</a><hr>\n");
		fprintf(fpelfs, "</ul></body></html>\n");
		fclose(fpelfs);
	}

	return;
}
