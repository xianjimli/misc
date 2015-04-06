/*
 * File: fontextrac.c    
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   extract bitmap font from truetype font. 
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
 * 2009-09-11 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fontdata.h"
#include <ft2build.h>
#include FT_GLYPH_H

void show_usage(int argc, char* argv[])
{
	if(argc != 5)
	{
		printf("%s fontfile size input_file output_file\n", argv[0]);
		printf("-----------------------------------------------\n");
		printf("  fontfile:    the truetype filename.\n");
		printf("  size:        the size of output font.\n");
		printf("  input_file:  contains the chars that you want to generate font for them.\n");
		printf("  output_file: output font file.\n");
		exit(0);
	}

	return;
}

char* read_file(const char* file_name, int* length)
{
	struct stat st = {0};
	if(stat(file_name, &st))
	{
		return NULL;
	}
	else
	{
		char* buffer = malloc(st.st_size + 1);
		FILE* fp = fopen(file_name, "rb");
		fread(buffer, 1, st.st_size, fp);
		fclose(fp);
		buffer[st.st_size] = '\0';
		*length = st.st_size;

		return buffer;
	}
}

void verify_font_data(FT_Face face, FILE* fp, const char* font_data_file)
{
	int length = 0;
	Glyph glyph = {0};
	unsigned short ch = 0;
	char* buffer = read_file(font_data_file, &length);
	FontData* data = font_data_load(buffer, length);

	printf("verifing...\n");
	fseek(fp, SEEK_SET, 0);
	while(fread(&ch, 1, sizeof(ch), fp) > 0 && data != NULL)
	{
		int index = FT_Get_Char_Index(face, ch);
		FT_Error err = FT_Load_Glyph(face, index, FT_LOAD_DEFAULT|FT_LOAD_RENDER);

		if(err == 0)
		{
			printf("code=%04x width=%d height=%d\n", ch, face->glyph->bitmap.width, face->glyph->bitmap.rows);

			memset(&glyph, 0x00, sizeof(Glyph));
			assert(font_data_get_glyph(data, ch, &glyph) == RET_OK);

			assert(glyph.code == ch);
			assert(glyph.x == face->glyph->bitmap_left);
			assert(glyph.y == face->glyph->bitmap_top);
			assert(glyph.w == face->glyph->bitmap.width);
			assert(glyph.h == face->glyph->bitmap.rows);
			assert(memcmp(glyph.data, face->glyph->bitmap.buffer, glyph.w * glyph.h) == 0);
		}
		else
		{
			printf("not found code=%04x\n", ch);
		}
	}

	return;
}

void extract(FT_Face face, int size, const char* input_file, const char* output_file)
{
	Glyph glyph = {0};
	struct stat st = {0};
	FontData* data = NULL;
	unsigned short ch = 0;
	FILE* fp = fopen(input_file, "rb");

	if(fp == NULL)
	{
		printf("open %s failed\n", input_file);
		return;
	}

	printf("extracting...\n");
	stat(input_file, &st);
	data = font_data_create(st.st_size>>1, ENC_UTF16);

	font_data_set_author(data, "FontExtract");
	font_data_set_family(data, face->family_name);
	font_data_set_style(data, face->style_name);

	font_data_set_size(data, size, size);
	while(fread(&ch, 1, sizeof(ch), fp) > 0 && data != NULL)
	{
		int index = FT_Get_Char_Index(face, ch);
		FT_Error err = FT_Load_Glyph(face, index, FT_LOAD_DEFAULT|FT_LOAD_RENDER);

		if(err == 0)
		{
			glyph.code = ch;
			glyph.x = face->glyph->bitmap_left;
			glyph.y = face->glyph->bitmap_top;
			glyph.w = face->glyph->bitmap.width;
			glyph.h = face->glyph->bitmap.rows;
			glyph.data = face->glyph->bitmap.buffer;
			
			font_data_add_glyph(data, &glyph);
			printf("code=%04x x=%d y=%d width=%d height=%d\n", ch, 
				glyph.x, glyph.y, face->glyph->bitmap.width, face->glyph->bitmap.rows);
		}
		else
		{
			printf("not found code=%04x\n", ch);
		}
	}
	font_data_save(data, output_file);
	font_data_destroy(data);
	verify_font_data(face, fp, output_file);
	fclose(fp);

	return;
}

int main(int argc, char* argv[])
{
	int size = 0;
	FT_Face     face = {0};
	FT_Library  library = {0};
	const char* input_file  = NULL;
	const char* output_file = NULL;
	const char* font_file   = NULL;
	FT_Error err = FT_Init_FreeType( &library );

	show_usage(argc, argv);

	font_file = argv[1];
	size = atoi(argv[2]);
	input_file = argv[3];
	output_file = argv[4];

	if((err = FT_New_Face( library, font_file, 0, &face)))
	{
		printf("load %s failed.\n", font_file);
		return 0;
	}

	err = FT_Select_Charmap( face, ft_encoding_unicode);
	
	if(err)
	{
		err = FT_Select_Charmap( face, ft_encoding_latin_1 );
	}
	err = FT_Set_Pixel_Sizes(face, 0, size);

	extract(face, size, input_file, output_file);

	FT_Done_Face( face );
	FT_Done_FreeType( library );

	return 0;
}

