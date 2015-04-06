lib_LTLIBRARIES=libasm-rapi-common.la
libasm_rapi_common_la_SOURCES=\
	rapi_enums.h    rapi_lib.c  rapi_macros.h   rapi_registry.h  rapi_system.h\
	rapi_fileman.h  rapi_lib.h  rapi_procman.h  rapi_structs.h   rapi_test_data.h

libasm_rapi_common_la_CFLAGS=-I$(top_srcdir)/common
libasm_rapi_common_la_LDFLAGS=-L$(top_builddir)/common -lasm-common

asmrapiincludedir=${includedir}/asm
asmrapiinclude_HEADERS= \
	rapi_enums.h  rapi_fileman.h  rapi_lib.h  rapi_macros.h  rapi_procman.h \
	rapi_registry.h  rapi_structs.h  rapi_system.h
