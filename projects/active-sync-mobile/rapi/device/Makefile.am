lib_LTLIBRARIES=libasm-rapi-device.la

libasm_rapi_device_la_SOURCES=rapi_device_connection_session.c rapi_device_connection_session.h \
	rapi_device_connection_device.c rapi_device_connection_device.h \
	rapi_device_default.c rapi_device_default.h \
	rapi_device_lib.c rapi_device_lib.h \
	rapi_device_connection.h rapi_device.h\
	rapi_device_registry_default.c  rapi_device_registry_read.c\
	rapi_device_registry_write.h\
	rapi_device_registry_default.h  rapi_device_registry_read.h\
	rapi_device_registry.h          rapi_device_registry_write.c \
	rapi_device_procman_default.c   rapi_device_procman_read.h\
	rapi_device_procman_default.h   rapi_device_procman.h           rapi_device_procman_write.c\
	rapi_device_procman_read.c      rapi_device_procman_write.h\
	rapi_device_system_default.c   rapi_device_system_read.h\
	rapi_device_system_default.h   rapi_device_system.h           rapi_device_system_write.c\
	rapi_device_system_read.c      rapi_device_system_write.h\
	rapi_device_fileman_default.c   rapi_device_fileman_read.h\
	rapi_device_fileman_default.h   rapi_device_fileman.h           rapi_device_fileman_write.c\
	rapi_device_fileman_read.c      rapi_device_fileman_write.h

libasm_rapi_device_la_CFLAGS=-I$(top_srcdir)/common -I$(top_srcdir)/rapi/common
libasm_rapi_device_la_LDFLAGS=-L$(top_builddir)/common -lasm-common -L$(top_builddir)/rapi/common -lasm-rapi-common

noinst_PROGRAMS=rapi_device_test
rapi_device_test_SOURCES=rapi_device_test.c
rapi_device_test_CFLAGS=-I$(top_srcdir)/common -I$(top_srcdir)/rapi/common -I./ 
rapi_device_test_LDFLAGS=-L./ -lasm-rapi-device -L$(top_builddir)/common -lasm-common -L$(top_builddir)/rapi/common -lasm-rapi-common 

asmrapiincludedir=${includedir}/asm
asmrapiinclude_HEADERS= \
	rapi_device_connection_device.h   rapi_device_fileman_read.h      rapi_device_procman_read.h       rapi_device_system_default.h\
	rapi_device_connection.h          rapi_device_fileman_write.h     rapi_device_procman_write.h      rapi_device_system_dispatch.h\
	rapi_device_connection_session.h  rapi_device.h                   rapi_device_registry_default.h   rapi_device_system.h\
	rapi_device_default.h             rapi_device_lib.h               rapi_device_registry_dispatch.h  rapi_device_system_read.h\
	rapi_device_fileman_default.h     rapi_device_procman_default.h   rapi_device_registry.h           rapi_device_system_write.h\
	rapi_device_fileman_dispatch.h    rapi_device_procman_dispatch.h  rapi_device_registry_read.h\
	rapi_device_fileman.h             rapi_device_procman.h           rapi_device_registry_write.h

EXTRA_DIST=\
	rapi_device_fileman_dispatch.c  rapi_device_procman_dispatch.c\
	rapi_device_registry_dispatch.c  rapi_device_system_dispatch.c\
	rapi_device_fileman_dispatch.h  rapi_device_procman_dispatch.h\
	rapi_device_registry_dispatch.h  rapi_device_system_dispatch.h

