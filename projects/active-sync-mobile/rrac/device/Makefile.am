lib_LTLIBRARIES=libasm-rrac-device.la
libasm_rrac_device_la_SOURCES= rrac_device_connection_cmd.h   rrac_device_connection_data.h \
			rrac_device_connection_cmd.c  rrac_device_connection_data.c  rrac_device.h \
			rrac_device_default.c rrac_device_default.h

libasm_rrac_device_la_CFLAGS=-I$(top_srcdir)/common -I$(top_srcdir)/rrac/common
libasm_rrac_device_la_LDFLAGS=-L$(top_builddir)/common -lasm-common -L$(top_builddir)/rrac/common -lasm-rrac-common

noinst_PROGRAMS=rrac_device_test
rrac_device_test_SOURCES=rrac_device_test.c
rrac_device_test_CFLAGS=-I$(top_srcdir)/common -I$(top_srcdir)/rrac/common -I./
rrac_device_test_LDFLAGS=-L./ -lasm-rrac-device -L$(top_builddir)/common -lasm-common -L$(top_builddir)/rrac/common -lasm-rrac-common

asmrapiincludedir=${includedir}/asm
asmrapiinclude_HEADERS= \
	rrac_device_connection_cmd.h  rrac_device_connection_data.h  rrac_device_default.h  rrac_device.h  rrac_device_lib.h
