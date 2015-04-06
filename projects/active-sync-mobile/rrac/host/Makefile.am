lib_LTLIBRARIES=libasm-rrac-host.la
libasm_rrac_host_la_SOURCES= \
	rrac_host_connection_cmd.c  rrac_host_connection_data.c  rrac_host.h    \
	rrac_host_connection_cmd.h  rrac_host_connection_data.h  rrac_host_lib.c \
	rrac_host_connection_listen.c rrac_host_connection_listen.h \
	rrac_host_lib.h rrac_host.c

libasm_rrac_host_la_CFLAGS=-I$(top_srcdir)/common -I$(top_srcdir)/rrac/common
libasm_rrac_host_la_LDFLAGS=-L$(top_builddir)/common -lasm-common -L$(top_builddir)/rrac/common -lasm-rrac-common

noinst_PROGRAMS=rrac_host_test
rrac_host_test_SOURCES=rrac_host_test.c
rrac_host_test_CFLAGS=-I$(top_srcdir)/common -I$(top_srcdir)/rrac/common -I./
rrac_host_test_LDFLAGS=-L./ -lasm-rrac-host -L$(top_builddir)/common -lasm-common -L$(top_builddir)/rrac/common -lasm-rrac-common

asmrapiincludedir=${includedir}/asm
asmrapiinclude_HEADERS= \
	rrac_host_connection_cmd.h  rrac_host_connection_data.h  rrac_host_connection_listen.h  rrac_host.h  rrac_host_lib.h
