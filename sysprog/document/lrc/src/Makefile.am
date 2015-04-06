## Process this file with automake to produce Makefile.in

noinst_PROGRAMS      =  id_tag_test  list_test  parser_test  time_tag_test demo

id_tag_test_SOURCES = lrc_id_tag.c lrc_pool.c
id_tag_test_CFLAGS  = -DLRC_ID_TAG_TEST -DDEBUG -D_DEBUG

time_tag_test_SOURCES = lrc_time_tag.c lrc_pool.c
time_tag_test_CFLAGS  = -DLRC_TIME_TAG_TEST -DDEBUG -D_DEBUG

parser_test_SOURCES = lrc_parser.c lrc_dumpbuilder.c lrc_internal.c lrc_defaultbuilder.c \
                      lrc_id_tag.c lrc_time_tag.c lrc_list.c lrc_pool.c
parser_test_CFLAGS  = -DLRC_PARSER_TEST -DDEBUG -D_DEBUG

demo_SOURCES = demo.c
demo_LDFLAGS = -llrc

list_test_SOURCES = lrc_list.c lrc_pool.c
list_test_CFLAGS  = -DLRC_LIST_TEST  -DDEBUG -D_DEBUG

lib_LTLIBRARIES       = liblrc.la 

liblrc_la_SOURCES= lrc.c                 lrc_dumpbuilder.c  lrc_list.c    lrc_pool.c      lrc_internal.c \
                   lrc_defaultbuilder.c  lrc_id_tag.c       lrc_parser.c  lrc_time_tag.c
liblrc_la_LDFLAGS =

lrcincludedir=$(includedir)/lrc
lrcinclude_HEADERS =   \
    lrc.h   \
    lrc_type.h \
    lrc_list.h \
    lrc_builder.h
        
EXTRA_DIST= lrc_defaultbuilder.h  lrc.h         lrc_list.h    lrc_pool.h      lrc_internal.h \
            lrc_dumpbuilder.h     lrc_id_tag.h  lrc_parser.h  lrc_time_tag.h  lrc_type.h test.lrc

