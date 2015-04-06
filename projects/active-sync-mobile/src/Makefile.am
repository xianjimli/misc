INCLUDES=-DSYNCD_DEVICE_SO="\"${libdir}/libsyncd-device-%s.so\""
DEVICE_CFLAGS=\
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/rapi/common \
	-I$(top_srcdir)/rapi/device \
	-I$(top_srcdir)/rrac/common \
	-I$(top_srcdir)/rrac/device

DEVICE_LDFLAGS=\
	-L$(top_builddir)/common -lasm-common \
	-L$(top_builddir)/rrac/common -lasm-rrac-common \
	-L$(top_builddir)/rrac/device -lasm-rrac-device \
	-L$(top_builddir)/rapi/common -lasm-rapi-common \
	-L$(top_builddir)/rapi/device -lasm-rapi-device

HOST_CFLAGS=\
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/rapi/common \
	-I$(top_srcdir)/rapi/host \
	-I$(top_srcdir)/rrac/common \
	-I$(top_srcdir)/rrac/host
HOST_LDFLAGS=\
	-L$(top_builddir)/common -lasm-common \
	-L$(top_builddir)/rrac/common -lasm-rrac-common \
	-L$(top_builddir)/rrac/host -lasm-rrac-host \
	-L$(top_builddir)/rapi/common -lasm-rapi-common \
	-L$(top_builddir)/rapi/host -lasm-rapi-host

noinst_PROGRAMS=asm_device_test asm_host_test
asm_device_test_SOURCES=asm-device.c 
asm_device_test_CFLAGS=$(DEVICE_CFLAGS)
asm_device_test_LDFLAGS=$(DEVICE_LDFLAGS) -ldl

asm_host_test_SOURCES=asm-host.c 
asm_host_test_CFLAGS=$(HOST_CFLAGS)
asm_host_test_LDFLAGS=$(HOST_LDFLAGS)

lib_LTLIBRARIES=libsyncd-device-demo.la
libsyncd_device_demo_la_SOURCES=syncd_device_demo.c
libsyncd_device_demo_la_CFLAGS=$(DEVICE_CFLAGS)
libsyncd_device_demo_la_LDFLAGS=$(DEVICE_LDFLAGS)

