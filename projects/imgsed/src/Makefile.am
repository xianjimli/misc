INCLUDES=@GDKPIXBUF_CFLAGS@ -I./

noinst_PROGRAMS=resize_test clip_test text_test rotate_test save_test factory_test imgsed params_test expr_test

clip_test_SOURCES=img_filter_clip.c img_filter_params.c expr.c 
clip_test_CFLAGS=-DIMG_FILTER_CLIP_TEST
clip_test_LDFLAGS=@GDKPIXBUF_LIBS@

rotate_test_SOURCES=img_filter_rotate.c img_filter_params.c expr.c 
rotate_test_CFLAGS=-DIMG_FILTER_ROTATE_TEST 
rotate_test_LDFLAGS=@GDKPIXBUF_LIBS@

save_test_SOURCES=img_filter_save.c img_filter_params.c expr.c
save_test_CFLAGS=-DIMG_FILTER_SAVE_TEST
save_test_LDFLAGS=@GDKPIXBUF_LIBS@

text_test_SOURCES=img_filter_text.c img_filter_params.c expr.c
text_test_CFLAGS=-DIMG_FILTER_TEXT_TEST
text_test_LDFLAGS=@GDKPIXBUF_LIBS@

resize_test_SOURCES=img_filter_resize.c img_filter_params.c expr.c
resize_test_CFLAGS=-DIMG_FILTER_RESIZE_TEST
resize_test_LDFLAGS=@GDKPIXBUF_LIBS@

factory_test_SOURCES=img_filter_factory.c img_filter_clip.c img_filter_rotate.c img_filter_save.c img_filter_text.c img_filter_resize.c img_filter_params.c expr.c 
factory_test_CFLAGS=-DIMG_FILTER_FACTORY_TEST
factory_test_LDFLAGS=@GDKPIXBUF_LIBS@

imgsed_SOURCES=main.c $(factory_test_SOURCES)
imgsed_LDFLAGS=@GDKPIXBUF_LIBS@

params_test_SOURCES = img_filter_params.c expr.c 
params_test_CFLAGS= -DIMG_FILTER_PARAMS_TEST
params_test_LDFLAGS=@GDKPIXBUF_LIBS@

expr_test_SOURCES=expr.c 
expr_test_CFLAGS=-DEXPR_TEST

EXTRA_DIST=expr.h img_filter_factory.h img_filter_params.h img_filter_rotate.h  img_param_spec.h\
	img_filter_clip.h   img_filter_gray.h     img_filter_param_spec.h  img_filter_save.h    typedef.h\
	img_filter_dummy.h  img_filter.h          img_filter_resize.h      img_filter_text.h

