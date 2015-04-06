lib_LTLIBRARIES=libasm-rrac-common.la
libasm_rrac_common_la_SOURCES=rrac_lib.h rrac_lib.c
libasm_rrac_common_la_CFLAGS=-I$(top_srcdir)/common
libasm_rrac_common_la_LDFLAGS=-L$(top_builddir)/common -lasm-common

asmrapiincludedir=${includedir}/asm
asmrapiinclude_HEADERS= \
	rrac_enums.h  rrac_lib.h  rrac_macros.h  rrac_structs.h  rrac_test_data.h
