lib_LTLIBRARIES=libasm-rapi-host.la

libasm_rapi_host_la_SOURCES=\
rapi_host_fileman_write.c  rapi_host_procman_read.c   rapi_host_registry_read.h   rapi_host_system_write.c\
rapi_host.c               rapi_host_fileman_write.h  rapi_host_procman_read.h   rapi_host_registry_write.c  rapi_host_system_write.h\
rapi_host.h                rapi_host_procman_write.c  rapi_host_registry_write.h  \
rapi_host_fileman.c       rapi_host_lib.c            rapi_host_procman_write.h  rapi_host_system.c          \
rapi_host_fileman.h       rapi_host_lib.h            rapi_host_registry.c       rapi_host_system.h          \
rapi_host_fileman_read.c  rapi_host_procman.c        rapi_host_registry.h       rapi_host_system_read.c     \
rapi_host_fileman_read.h  rapi_host_procman.h        rapi_host_registry_read.c  rapi_host_system_read.h \
rapi_host_connection_device.c  rapi_host_connection_device.h  \
rapi_host_connection_session.c  rapi_host_connection_session.h \
rapi_host_connection_listen.c rapi_host_connection_listen.h


libasm_rapi_host_la_CFLAGS=-I$(top_srcdir)/common -I$(top_srcdir)/rapi/common
libasm_rapi_host_la_LDFLAGS=-L$(top_builddir)/common -lasm-common -L$(top_builddir)/rapi/common -lasm-rapi-common

noinst_PROGRAMS=rapi_host_test
rapi_host_test_SOURCES=rapi_host_test.c
rapi_host_test_CFLAGS=-I$(top_srcdir)/common -I$(top_srcdir)/rapi/common -I./
rapi_host_test_LDFLAGS=-L./ -lasm-rapi-host -L$(top_builddir)/common -lasm-common -L$(top_builddir)/rapi/common -lasm-rapi-common

asmrapiincludedir=${includedir}/asm
asmrapiinclude_HEADERS= \
	rapi_host_connection_device.h   rapi_host_fileman_read.h   rapi_host_procman.h        rapi_host_registry_read.h \ 
	rapi_host_system_write.h rapi_host_wrapper.h\
	rapi_host_connection_listen.h   rapi_host_fileman_write.h  rapi_host_procman_read.h   rapi_host_registry_write.h  \
	rapi_host_connection_session.h  rapi_host.h                rapi_host_procman_write.h  rapi_host_system.h\
	rapi_host_fileman.h             rapi_host_lib.h            rapi_host_registry.h       rapi_host_system_read.h

EXTRA_DIST=rapi_host_wrapper.c  rapi_host_wrapper.h

