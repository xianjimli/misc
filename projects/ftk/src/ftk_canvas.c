/*
 * File: ftk_canvas.c    
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   
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
 * 2009-10-03 Li XianJing <xianjimli@hotmail.com> created
 *
 */
#include "ftk_log.h"
#include "ftk_util.h"
#include "ftk_canvas.h"

struct _FtkCanvas
{
	FtkGc gc;
	FtkBitmap* bitmap;
};

FtkCanvas* ftk_canvas_create(int w, int h, FtkColor clear_color)
{
	FtkCanvas* thiz = (FtkCanvas*)FTK_ZALLOC(sizeof(FtkCanvas));
	if(thiz != NULL)
	{
		thiz->gc.bg = clear_color;
		thiz->gc.fg.a = 0xff;
		thiz->gc.fg.r = 0xff - clear_color.r;
		thiz->gc.fg.g = 0xff - clear_color.g;
		thiz->gc.fg.b = 0xff - clear_color.b;

		thiz->bitmap = ftk_bitmap_create(w, h, clear_color);
	}

	return thiz;
}

Ret ftk_canvas_set_gc(FtkCanvas* thiz, FtkGc* gc)
{
	return_val_if_fail(thiz != NULL && gc != NULL, RET_FAIL);

	return ftk_gc_copy(&thiz->gc, gc);
}

Ret ftk_canvas_draw_point(FtkCanvas* thiz, int x, int y)
{
	int width = 0;
	int height = 0;
	FtkColor* bits = NULL;
	return_val_if_fail(thiz != NULL, RET_FAIL);

	width  = ftk_bitmap_width(thiz->bitmap);
	height = ftk_bitmap_height(thiz->bitmap);
	bits   = ftk_bitmap_bits(thiz->bitmap);
	return_val_if_fail(bits != NULL && x < width && y < height, RET_FAIL);

	bits[y * width + x] = thiz->gc.fg;

	return RET_OK;
}

Ret ftk_canvas_draw_vline(FtkCanvas* thiz, int x, int y, int h)
{
	int i = 0;
	int width = 0;
	int height = 0;
	FtkColor* bits = NULL;
	return_val_if_fail(thiz != NULL, RET_FAIL);
	
	width  = ftk_bitmap_width(thiz->bitmap);
	height = ftk_bitmap_height(thiz->bitmap);
	bits   = ftk_bitmap_bits(thiz->bitmap);
	return_val_if_fail(bits != NULL && y < height, RET_FAIL);

	x = x < 0 ? 0 : x;
	y = y < 0 ? 0 : y;
	h = (y + h) < height ? h : (height - y);

	for(i = 0; i < h; i++)
	{
		bits[width * (y + i) + x] = thiz->gc.fg;
	}

	return RET_OK;
}

Ret ftk_canvas_draw_hline(FtkCanvas* thiz, int x, int y, int w)
{
	int i = 0;
	int width = 0;
	int height = 0;
	FtkColor* bits = NULL;
	return_val_if_fail(thiz != NULL, RET_FAIL);
	width  = ftk_bitmap_width(thiz->bitmap);
	height = ftk_bitmap_height(thiz->bitmap);
	bits   = ftk_bitmap_bits(thiz->bitmap);
	return_val_if_fail(bits != NULL && x < width, RET_FAIL);
	
	x = x < 0 ? 0 : x;
	y = y < 0 ? 0 : y;
	w = (x + w) < width ? w : width - x;
	bits += y * width;

	for(i = 0; i < w; i++)
	{
		bits[x+i] = thiz->gc.fg;
	}

	return RET_OK;
}

static Ret ftk_canvas_draw_normal_line(FtkCanvas* thiz, 
          int x1, 
          int y1, 
          int x2,
          int y2)
{
    int dx, dy;
    int stepx, stepy;
    int width = ftk_bitmap_width(thiz->bitmap);
	FtkColor* bits = ftk_bitmap_bits(thiz->bitmap);

    /* Bresenham's line drawing algorithm */

    dx = x2 - x1;
    dy = y2 - y1;
    
    if (dy < 0) 
    { 
        dy = -dy;  
        stepy = -1; 
    } 
    else 
    { 
        stepy = 1; 
    }
    if (dx < 0) 
    { 
        dx = -dx;  
        stepx = -1; 
    } 
    else 
    { 
        stepx = 1; 
    }
    dy <<= 1;
    dx <<= 1;

	bits[y1 * width + x1] = thiz->gc.fg;
    if (dx > dy) 
    {
        int fraction = dy - (dx >> 1);
        while (x1 != x2) 
        {
            if (fraction >= 0) 
            {
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;
			bits[y1 * width + x1] = thiz->gc.fg;
        }
    } 
    else 
    {
        int fraction = dx - (dy >> 1);
        while (y1 != y2) 
        {
            if (fraction >= 0) 
            {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;
			bits[y1 * width + x1] = thiz->gc.fg;
        }
    }
	
	return RET_OK;
}

Ret ftk_canvas_draw_line(FtkCanvas* thiz, int x1, int y1, int x2, int y2)
{
	Ret ret = RET_FAIL;
	return_val_if_fail(thiz != NULL, RET_FAIL);

	if(x1 == x2)
	{
		ret = ftk_canvas_draw_vline(thiz, x1, MIN(y1, y2), MAX(y1, y2));
	}
	else if(y1 == y2)
	{
		ret = ftk_canvas_draw_hline(thiz, y1, MIN(x1, x2), MAX(x1, x2));
	}
	else
	{
		ret = ftk_canvas_draw_normal_line(thiz, x1, y1, x2, y2);
	}

	return ret;
}

Ret ftk_canvas_draw_rect(FtkCanvas* thiz, int x, int y, int w, int h, int fill)
{
	int i = 0;
	int width  = 0;
	int height = 0;
	return_val_if_fail(thiz != NULL, RET_FAIL);
	width  = ftk_bitmap_width(thiz->bitmap);
	height = ftk_bitmap_height(thiz->bitmap);
	return_val_if_fail(x < width && y < height, RET_FAIL);

	if(fill)
	{
		for(i = 0; i < h; i++)
		{
			ftk_canvas_draw_hline(thiz, x, (y+i), w);	
		}
	}
	else
	{
		ftk_canvas_draw_hline(thiz, x,   y, w);		
		ftk_canvas_draw_hline(thiz, x,   y+h-1, w);		
		ftk_canvas_draw_vline(thiz, x,   y, h);		
		ftk_canvas_draw_vline(thiz, x+w-1, y, h);		
	}

	return RET_OK;
}

#define SET_PIXEL(x, y) bits[(y)*(width) + (x)] = thiz->gc.fg
Ret ftk_canvas_draw_ellipse(FtkCanvas* thiz, int x, int y, int rx, int ry,int fill)
{

    /* Algorithm from IEEE CG&A Sept 1984 p.24 */

    int t1 = rx * rx, t2 = t1 << 1, t3 = t2 << 1;
    int t4 = ry * ry, t5 = t4 << 1, t6 = t5 << 1;
    int t7 = rx * t5, t8 = t7 << 1, t9 = 0;
    int d1 = t2 - t7 + (t4 >> 1);
    int d2 = (t1 >> 1) - t8 + t5;

    int ex = rx, ey = 0;
    int width = ftk_bitmap_width(thiz->bitmap);
	FtkColor* bits = ftk_bitmap_bits(thiz->bitmap);

    while (d2 < 0)
    {
        if (fill)
        {
        	ftk_canvas_draw_hline(thiz, x - ex, y + ey, 2 * ex);
        	ftk_canvas_draw_hline(thiz, x - ex, y - ey, 2 * ex);
        }
        else
        {
        	SET_PIXEL(x + ex, y + ey);
        	SET_PIXEL(x + ex, y - ey);
        	SET_PIXEL(x - ex, y + ey);
        	SET_PIXEL(x - ex, y - ey);
        }

        ey++;        
        t9 += t3;    
        if (d1 < 0)
        {
            d1 += t9 + t2;
            d2 += t9;
        }
        else
        {
            ex--;
            t8 -= t6;
            d1 += t9 + t2 - t8;
            d2 += t9 + t5 - t8;
        }
    }

    do
    {
        if (fill)
        {
        	ftk_canvas_draw_hline(thiz, x - ex, y + ey, 2*ex);
        	ftk_canvas_draw_hline(thiz, x - ex, y - ey, 2*ex);
        }
        else
        {
        	SET_PIXEL(x + ex, y + ey);
        	SET_PIXEL(x + ex, y - ey);
        	SET_PIXEL(x - ex, y + ey);
        	SET_PIXEL(x - ex, y - ey);
        }

        ex--;    
        t8 -= t6;    
        if (d2 < 0)
        {
            ey++;
            t9 += t3;
            d2 += t9 + t5 - t8;
        }
        else
        {
            d2 += t5 - t8;
        }
    } 
    while (ex >= 0);

	return RET_OK;
}

Ret ftk_canvas_draw_string(FtkCanvas* thiz, int x, int y, const char* str)
{
	int i = 0;
	int j = 0;
	int ox = x;
	int oy = y;
	int width = 0;
	int height = 0;
	FtkGlyph glyph = {0};
	FtkColor color = {0};
	FtkColor fg = {0};
	FtkColor bg = {0};
	FtkColor* bits = NULL;
	unsigned short code = 0;
	return_val_if_fail(thiz != NULL && str != NULL, RET_FAIL);

	width  = ftk_bitmap_width(thiz->bitmap);
	height = ftk_bitmap_height(thiz->bitmap);
	bits   = ftk_bitmap_bits(thiz->bitmap);
	return_val_if_fail(thiz != NULL, RET_FAIL);

	//ftk_logv("%s: x=%d y=%d s=%s\n", __func__, x, y, str);
	color.a = 0xff;
	fg = thiz->gc.fg;

	while(*str)
	{
		code = utf8_get_char(str, &str);

		if(code == 0x20)
		{
			x += FTK_SPACE_WIDTH;
			ox = x;
			continue;
		}
		if(ftk_font_lookup(thiz->gc.font, code, &glyph) != RET_OK) continue;
		if((x + glyph.x + glyph.w) >= width) break;
		if((y + glyph.y + glyph.h) >= height) break;

		int offset = 0;
		x = x + glyph.x;
		y = y - glyph.y;
		for(i = 0; i < glyph.h; i++,y++)
		{
			for(j = 0, x= ox; j < glyph.w; j++,x++)
			{
				unsigned char data = glyph.data[i * glyph.w + j];
				offset = y * width + x;
				bg = bits[offset];
				color.r = ((fg.r * data) + (bg.r * (0xff - data)))/0xff;
				color.g = ((fg.g * data) + (bg.g * (0xff - data)))/0xff;
				color.b = ((fg.b * data) + (bg.b * (0xff - data)))/0xff;
				bits[offset] = color;
			}
		}

		y = oy;
		x = ox + glyph.x + glyph.w;
		ox = x;
	}

	return RET_OK;
}

Ret ftk_canvas_draw_bitmap(FtkCanvas* thiz, FtkBitmap* bitmap, int x, int y, int w, int h, int xoffset, int yoffset)
{
	int i = 0;
	int j = 0;
	return_val_if_fail(thiz != NULL && bitmap != NULL, RET_FAIL);

	int width  = ftk_bitmap_width(thiz->bitmap);
	int height = ftk_bitmap_height(thiz->bitmap);
	int bitmap_width   = ftk_bitmap_width(bitmap);
	int bitmap_height  = ftk_bitmap_height(bitmap);

	return_val_if_fail(x < bitmap_width, RET_FAIL);
	return_val_if_fail(y < bitmap_height, RET_FAIL);
	return_val_if_fail(xoffset < width, RET_FAIL);
	return_val_if_fail(yoffset < height, RET_FAIL);

	FtkColor* src = ftk_bitmap_bits(bitmap);
	FtkColor* dst = ftk_bitmap_bits(thiz->bitmap);

	w = (x + w) < bitmap_width  ? w : bitmap_width - x;
	w = (xoffset + w) < width  ? w : width  - xoffset;
	h = (y + h) < bitmap_height ? h : bitmap_height - y;
	h = (yoffset + h) < height ? h : height - yoffset;
	
	w += x;
	h += y;

	src += y * bitmap_width + x;
	dst += yoffset * width + xoffset;

	for(i = y; i < h; i++)
	{
		for(j = x; j < w; j++)
		{
			if(src[j].a == 0xff)
			{
				dst[j] = src[j];
			}
			else
			{
				dst[j].r = (src[j].r * src[j].a + dst[j].r * (0xff - src[j].a)) >> 8;
				dst[j].g = (src[j].g * src[j].a + dst[j].g * (0xff - src[j].a)) >> 8;
				dst[j].b = (src[j].b * src[j].a + dst[j].b * (0xff - src[j].a)) >> 8;
			}
		}
		src += bitmap_width;
		dst += width;
	}

	return RET_OK;
}

FtkBitmap* ftk_canvas_bitmap(FtkCanvas* thiz)
{
	return_val_if_fail(thiz != NULL, NULL);

	return thiz->bitmap;
}

int ftk_canvas_font_height(FtkCanvas* thiz)
{
	return ftk_font_height(thiz->gc.font);
}

int ftk_canvas_get_extent(FtkCanvas* thiz, const char* str)
{
	int extent = 0;
	FtkGlyph glyph = {0};
	unsigned short code = 0;
	return_val_if_fail(thiz != NULL && str != NULL && thiz->gc.font != NULL, 0);
	
	while(*str)
	{
		code = utf8_get_char(str, &str);
		if(code == ' ')
		{
			glyph.x = 0;
			glyph.w = FTK_SPACE_WIDTH;
		}
		else if(ftk_font_lookup(thiz->gc.font, code, &glyph) != RET_OK) 
		{
			continue;
		}

		extent += glyph.x + glyph.w + 1;
	}

	return extent;
}

const char* ftk_canvas_available(FtkCanvas* thiz, const char* str, int width, int* nr)
{
	FtkGlyph glyph = {0};
	const char* ret = str;
	unsigned short code = 0;

	return_val_if_fail(thiz != NULL && str != NULL && nr != NULL && thiz->gc.font != NULL, NULL);

	while(*str)
	{
		ret = str;
		code = utf8_get_char(str, &str);

		if(code == ' ')
		{
			glyph.x = 0;
			glyph.w = FTK_SPACE_WIDTH;
		}
		else if(ftk_font_lookup(thiz->gc.font, code, &glyph) != RET_OK)
		{
			continue;
		}

		width -= glyph.x + glyph.w + 1;
		if(width >= 0)
		{
			(*nr)++;
		}
		else
		{
			break;
		}
	}

	return ret;
}


void ftk_canvas_destroy(FtkCanvas* thiz)
{
	if(thiz != NULL)
	{
		ftk_bitmap_unref(thiz->bitmap);
		FTK_ZFREE(thiz, sizeof(*thiz));
	}

	return;
}

