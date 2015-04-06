/*
 * File:    jpeg2rle.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   convert jpeg to rle.
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
 * 2009-08-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include <stdio.h>
#include "jpeglib.h"
#include <setjmp.h>

struct my_error_mgr
{
	struct jpeg_error_mgr pub;	/* "public" fields */
	jmp_buf setjmp_buffer;	/* for return to caller */
};
typedef struct my_error_mgr *my_error_ptr;

METHODDEF (void)
my_error_exit (j_common_ptr cinfo)
{
	my_error_ptr myerr = (my_error_ptr) cinfo->err;

	(*cinfo->err->output_message) (cinfo);

	longjmp (myerr->setjmp_buffer, 1);
}

void
put_scanline_to_file (FILE * outfile, char *scanline, int width,
					int row_stride)
{
	int i = 0;
	char *pixels = scanline;
	char *start = scanline;

	while (i < width)
	{
		unsigned short n = 0;
		for (; i < width; i++, n++)
		{
			if (memcmp (pixels, pixels + 3 * n, 3) != 0)
			{
				break;
			}
		}
		unsigned char r = pixels[0];
		unsigned char g = pixels[1];
		unsigned char b = pixels[2];
		unsigned short rle565 = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);

		fwrite (&n, 2, 1, outfile);
		fwrite (&rle565, 2, 1, outfile);
		pixels += 3 * n;
	}

	return;
}

int jpeg2rle (char *filename, char *outfilename)
{
	struct jpeg_decompress_struct cinfo;
	int i = 0;
	struct my_error_mgr jerr;
	FILE *infile;	
	FILE *outfile;
	JSAMPARRAY buffer;	
	int row_stride;	
	
	if ((infile = fopen (filename, "rb")) == NULL)
	{
		fprintf (stderr, "can't open %s\n", filename);
		return 0;
	}

	if ((outfile = fopen (outfilename, "wb")) == NULL)
	{
		fprintf (stderr, "can't open %s\n", outfilename);
		fclose (infile);
		return 0;
	}

	cinfo.err = jpeg_std_error (&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	
	if (setjmp (jerr.setjmp_buffer))
	{
		jpeg_destroy_decompress (&cinfo);
		fclose (infile);
		fclose (outfile);
		return 0;
	}
	jpeg_create_decompress (&cinfo);
	jpeg_stdio_src (&cinfo, infile);

	(void) jpeg_read_header (&cinfo, TRUE);

	(void) jpeg_start_decompress (&cinfo);
	row_stride = cinfo.output_width * cinfo.output_components;
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) & cinfo, JPOOL_IMAGE, row_stride, 1);
	printf("size: %dx%d\n", cinfo.output_width, cinfo.output_height);
	while (cinfo.output_scanline < cinfo.output_height)
	{
		(void) jpeg_read_scanlines (&cinfo, buffer, 1);
		put_scanline_to_file (outfile, buffer[0], cinfo.output_width,
				row_stride);
	}

	(void) jpeg_finish_decompress (&cinfo);
	jpeg_destroy_decompress (&cinfo);

	fclose (infile);
	fclose (outfile);

	return 1;
}

int main (int argc, char *argv[])
{
	if (argc != 3)
	{
		printf ("\nusage: %s jpeg rle\n", argv[0]);
		printf("-----------------------------------------\n");
		printf("Powered by broncho(www.broncho.cn)\n");
	}
	else
	{
		jpeg2rle(argv[1], argv[2]);
	}

	return 0;
}
