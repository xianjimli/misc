#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "m2d_lib.h"

#define FB_W 320
#define FB_H 480

void test_fill(struct m2d_context* ctx, struct m2d_buff *src, int w, int h, GCU_PIXEL_FORMAT format, GCU_COLOR_VALUE color)
{
	int ret = 0;
	struct m2d_op_region region;
	memset(&region, 0x00, sizeof(region));
	region.width  = w;
	region.height = h;

	ret = m2d_set_dstbuf2(ctx, src);
	ret = m2d_set_fill_color(ctx, format, color);	
	ret = m2d_color_fill(ctx, &region);

	ret = m2d_set_dstbuf2(ctx, src);
	m2d_set_line_width(ctx, 2);
	ret = m2d_set_line_color(ctx, format, 0xff);
	ret = m2d_draw_line(ctx, w/4, 0, w/4, h-1);
	ret = m2d_draw_line(ctx, w/2, 0, w/2, h-1);
	ret = m2d_draw_line(ctx, 3*w/4, 0, 3*w/4, h-1);

	ret = m2d_sync(ctx);

	return;
}

void test_stretch(struct m2d_context* ctx, struct m2d_buff* fb, struct m2d_buff *src)
{
	int ret = 0;
	struct m2d_op_region region;
	printf("%s:%d\n", __func__, __LINE__);
	memset(&region, 0x00, sizeof(region));
    region.width = FB_W/4;
    region.height = FB_H/4;
	ret = m2d_set_srcbuf0(ctx, src);
    ret = m2d_set_dstbuf2(ctx, fb);
	ret = m2d_stretch_blt(ctx, &region, FB_W, FB_H);
	ret = m2d_submit(ctx);

	return;
}

void test_decimate(struct m2d_context* ctx, struct m2d_buff* fb, struct m2d_buff *src)
{
	int ret = 0;
	struct m2d_op_region region;
	printf("%s:%d\n", __func__, __LINE__);
	memset(&region, 0x00, sizeof(region));
    region.width = FB_W/2;
    region.height = FB_H/2;
	ret = m2d_set_srcbuf0(ctx, src);
    ret = m2d_set_dstbuf2(ctx, fb);
	ret = m2d_decimate_blt(ctx, &region, FB_W/2, FB_H/2);
	ret = m2d_submit(ctx);

	return;
}

void test_scale(struct m2d_context* ctx, struct m2d_buff* fb, struct m2d_buff *src)
{
	int ret = 0;
	struct m2d_op_region region;
	printf("%s:%d\n", __func__, __LINE__);
	memset(&region, 0x00, sizeof(region));
    region.width = FB_W-1;
    region.height = FB_H-1;
	ret = m2d_set_srcbuf0(ctx, src);
    ret = m2d_set_dstbuf2(ctx, fb);
	ret = m2d_scale_blt(ctx, &region, 0x100);
	ret = m2d_submit(ctx);

	return;
}

void test_bias(struct m2d_context* ctx, struct m2d_buff* fb, struct m2d_buff *src)
{
	int ret = 0;
	struct m2d_op_region region;
	printf("%s:%d\n", __func__, __LINE__);
	memset(&region, 0x00, sizeof(region));
    region.width = FB_W-1;
    region.height = FB_H-1;
	ret = m2d_set_srcbuf0(ctx, src);
    ret = m2d_set_dstbuf2(ctx, fb);
	ret = m2d_bias_blt(ctx, &region, 0);
	ret = m2d_submit(ctx);

	return;
}

void test_rotate(struct m2d_context* ctx, struct m2d_buff* fb, struct m2d_buff *src, int w, int h, GCU_ROTATION rot)
{
	int ret = 0;
	struct m2d_op_region region;
	printf("%s:%d\n", __func__, __LINE__);
	memset(&region, 0x00, sizeof(region));
    region.width = w;
    region.height = h;
	ret = m2d_set_srcbuf0(ctx, src);
    ret = m2d_set_dstbuf2(ctx, fb);
	ret = m2d_rotate_blt(ctx, &region, rot);
	ret = m2d_submit(ctx);

	return;
}

GCU_COLOR_VALUE bg[] = {0xFFFF, 0x1F, 0x7E0, 0xF40000, 0x00};
int main(int argc, char* argv[])
{
    struct m2d_context* ctx = m2d_create_context();
    struct m2d_buff* fb = m2d_get_primary();
	struct m2d_buff *src = m2d_alloc_buffer(ctx, FB_W, FB_H, GCU_PXLFMT_RGB565);
	struct m2d_buff *rsrc = m2d_alloc_buffer(ctx, FB_H, FB_W, GCU_PXLFMT_RGB565);

	test_fill(ctx, fb, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xFFFF);
	test_fill(ctx, src, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xF800);
	test_scale(ctx, fb, src);
	
	sleep(1);
	test_fill(ctx, fb, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xFFFF);
	sleep(1);
	test_fill(ctx, src, FB_W, FB_H, GCU_PXLFMT_RGB565, 0x7E0);
	test_bias(ctx, fb, src);
	
	sleep(1);
	test_fill(ctx, fb, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xFFFF);
	sleep(1);
	test_fill(ctx, src, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xF800);
	test_stretch(ctx, fb, src);
	
	sleep(1);
	test_fill(ctx, fb, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xFFFF);
	sleep(1);
	test_fill(ctx, src, FB_W, FB_H, GCU_PXLFMT_RGB565, 0x7E0);
	test_decimate(ctx, fb, src);
	
	sleep(1);
	test_fill(ctx, fb, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xFFFF);
	sleep(1);
	test_fill(ctx, rsrc, FB_H, FB_W, GCU_PXLFMT_RGB565, 0xF800);
	test_rotate(ctx, fb, rsrc, FB_H, FB_W, GCU_ROTATE_90);
	sleep(1);
	
	test_fill(ctx, fb, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xFFFF);
	sleep(1);
	test_fill(ctx, rsrc, FB_H, FB_W, GCU_PXLFMT_RGB565, 0xF800);
	test_rotate(ctx, fb, rsrc, FB_H, FB_W, GCU_ROTATE_270);
	sleep(1);
	
	test_fill(ctx, fb, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xFFFF);
	sleep(1);
	test_fill(ctx, src, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xF800);
	test_rotate(ctx, fb, src, FB_W, FB_H, GCU_ROTATE_0);
	sleep(1);
	
	test_fill(ctx, fb, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xFFFF);
	sleep(1);
	test_fill(ctx, src, FB_W, FB_H, GCU_PXLFMT_RGB565, 0xF800);
	test_rotate(ctx, fb, src, FB_W, FB_H, GCU_ROTATE_180);
	sleep(1);
	
	m2d_free_buffer(ctx, src);
	m2d_free_buffer(ctx, rsrc);
    m2d_free_context(ctx);

    return 0;
}
