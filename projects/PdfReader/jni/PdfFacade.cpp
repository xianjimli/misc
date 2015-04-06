/*
 * File:    PdfFacade.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   Pdf Facade
 *
 * Copyright (c) 2009 Li XianJing<xianjimli@hotmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2009-09-01 Li XianJing <xianjimli@hotmail.com> created
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "GooString.h"
#include "gmem.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Stream.h"
#include "Array.h"
#include "Dict.h"
#include "XRef.h"
#include "Catalog.h"
#include "Page.h"
#include "PDFDoc.h"
#include "TextOutputDev.h"
#include "CharTypes.h"
#include "UnicodeMap.h"
#include "Error.h"
#include "PdfFacade.h"
#include "SplashOutputDev.h"
#include "SplashBitmap.h"

extern "C"
{
#include "jpeglib.h"
}

static char g_cache_dir[256] = {0};

int   PdfOpen(const char* filename, const char* cache_dir, const char* upwd, const char* opwd)
{
	PDFDoc  *doc = NULL;
	GooString *ownerPW = NULL, *userPW = NULL;
	GooString *fileName = new GooString(filename);
	
	if(cache_dir != NULL)
	{
		strncpy(g_cache_dir, cache_dir, sizeof(g_cache_dir));
	}

	globalParams = new GlobalParams("");
	globalParams->setTextEncoding("UTF-8");	
	globalParams->setTextPageBreaks(gFalse);

	if(opwd != NULL) ownerPW = new GooString(opwd);
	if(upwd != NULL) userPW = new GooString(upwd);

	doc = new PDFDoc(fileName, ownerPW, userPW);
  
	if (userPW)  delete userPW;
	if (ownerPW) delete ownerPW;

	if(doc != NULL && (!doc->isOk()))
	{
		delete doc;
		doc = NULL;
	}

    return (int)doc;

err:
	if(doc != NULL)
	{
		delete doc;
	}

	return (int)0;
}

int   PdfGetPageCount(int docPtr)
{
	int ret = 0;

	PDFDoc* doc = (PDFDoc*)docPtr;
	if(doc != NULL)
	{
		ret = doc->getNumPages();
	}

	return ret;
}

typedef struct _TextBuffer
{
	char* buffer;
	size_t length;
	size_t total_length;
}TextBuffer;

static void OnText(void *stream, char *text, int len)
{
	TextBuffer* tb = (TextBuffer*)stream;
	if(tb->total_length < (tb->length + len))
	{
		size_t new_length = ((tb->total_length + len) >> 1) + tb->total_length + len;
		char* buffer = (char*)realloc(tb->buffer, new_length);
		if(buffer != NULL)
		{
			tb->buffer = buffer;
			tb->total_length = new_length;
		}
	}
	
	if(tb->total_length > (tb->length + len))
	{
		int i = 0;
		for(i = 0; i < len; i++)
		{
			if(tb->length > 0 && (text[i] == ' ' || text[i] == '\t'))
			{
				if(tb->buffer[tb->length-1] != text[i])
				{
					tb->buffer[tb->length++] = text[i];
				}
			}
			else
			{
				tb->buffer[tb->length++] = text[i];
			}
		}
	}

	tb->buffer[tb->length] = '\0';

	return;
}

char* PdfDecodeText(int docPtr, int pageIndex, int flags)
{
	TextBuffer tb = {0};
	PDFDoc* doc = (PDFDoc*)docPtr;
	if(doc != NULL && pageIndex <= PdfGetPageCount(docPtr))
	{
		TextOutputDev *textOut = new TextOutputDev(OnText, &tb, gTrue, gFalse); 
		if (textOut->isOk()) 
		{
			doc->displayPage(textOut, pageIndex, 150, 150, 0,
				  gFalse, gTrue, gFalse);
		} 
		delete textOut;
	}

    return tb.buffer;
}

SplashBitmap* PdfDecodeImageToBitmap(int docPtr, int pageIndex, int flags)
{
	SplashBitmap* bitmap = NULL;
	PDFDoc* doc = (PDFDoc*)docPtr;
	SplashColor paperColor = {0};
	SplashOutputDev *splashOut = NULL;

	if(doc != NULL && pageIndex <= PdfGetPageCount(docPtr))
	{
		paperColor[0] = paperColor[1] = paperColor[2] = 0xff;
		splashOut = new SplashOutputDev(splashModeRGB8, 1, gFalse, paperColor);

		splashOut->startDoc(doc->getXRef());
    	doc->displayPage(splashOut, pageIndex, 72, 72, 0, gFalse, gTrue, gFalse);
		bitmap = splashOut->takeBitmap();

 		delete splashOut;
	}

	return bitmap;
}

static int splash_to_jpeg(SplashBitmap* splash, const char * filename, int quality)
{
	int row_stride = 0;	
	FILE * outfile = NULL;
	JSAMPROW row_pointer[1] = {0};
	struct jpeg_error_mgr jerr = {0};
	struct jpeg_compress_struct cinfo = {0};

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	if ((outfile = fopen(filename, "wb+")) == NULL) 
	{
		fprintf(stderr, "can't open %s\n", filename);

		return -1;
	}

	jpeg_stdio_dest(&cinfo, outfile);
	cinfo.image_width = splash->getWidth();
	cinfo.image_height = splash->getHeight();
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE);
	jpeg_start_compress(&cinfo, TRUE);

	row_stride = splash->getRowSize();
	JSAMPLE* image_buffer = (JSAMPLE*)splash->getDataPtr();
	while (cinfo.next_scanline < cinfo.image_height) 
	{
		row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	fclose(outfile);

	jpeg_destroy_compress(&cinfo);

	return 0;
}

char* PdfDecodeImage(int docPtr, int pageIndex, int flags)
{
	char* filename = NULL;
	SplashBitmap* bitmap = PdfDecodeImageToBitmap(docPtr, pageIndex, flags);
	printf("%s:%d\n", __func__, __LINE__);
	if(bitmap != NULL)
	{
#ifdef PDF_FACADE_TEST
		filename = strdup("./pdf_image.jpg");
#else
		filename = (char*)calloc(260, 1);
		if(filename != NULL)
		{
			snprintf(filename, 260, "%s/pdf_image_%d.jpg", g_cache_dir, pageIndex);
		}
#endif
		splash_to_jpeg(bitmap, filename, 70);
		delete bitmap;
	}

	return filename;
}


void  PdfClose(int docPtr)
{
	PDFDoc  *doc = (PDFDoc*)docPtr;
	if(doc != NULL)
	{
		delete globalParams;
		globalParams = NULL;
		delete doc;
	}

	return;
}

#ifdef PDF_FACADE_TEST
int main(int argc, char* argv[])
{
	int i = 0;
	int n = 0;
	int doc  = PdfOpen(argv[1], NULL, NULL, NULL);
	SplashBitmap* bitmap = NULL;
	
	n = PdfGetPageCount(doc);
#if 1
	for(i = 0; i < n; i++)
	{
		char filename[260] = {0};
		char* buffer = PdfDecodeText(doc, i+1, 0);
//		printf("==================================================\n");
//		printf("%s", buffer);
//		printf("==================================================\n");
		free(buffer);
		bitmap = PdfDecodeImageToBitmap(doc, i+1, 0);
		sprintf(filename, "aaaa-%02d.jpg", i);
		splash_to_jpeg(bitmap, filename, 70);
		PdfDecodeImage(doc, i+1, 0);
		delete bitmap;
	}
#endif
	PdfClose(doc);

	return 0;
}
#endif/*PDF_FACADE_TEST*/
