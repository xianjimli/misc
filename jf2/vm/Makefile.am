INCLUDES=-I$(top_srcdir)/common -I$(srcdir)/arm7 -I$(srcdir)/devices

noinst_PROGRAMS=dummy_ioport_test machine_test arm7_test

dummy_ioport_test_SOURCES=jioport_dummy.h jioport_dummy.c
dummy_ioport_test_CFLAGS=-DDUMMY_IOPORT_TEST

machine_test_SOURCES=jmachine.c
machine_test_CFLAGS=-DJMACHINE_TEST

lib_LTLIBRARIES=libvm.la
libvm_la_SOURCES=jioport_dummy.c  jmachine.c arm7.c

arm7_test_SOURCES=arm7_test.c
arm7_test_LDFLAGS=-lvm -L$(builddir)/arm7 -lvm-arm7 \
	-L$(builddir)/devices -ldevice-host-serial

bin_PROGRAMS=vm_arm7
vm_arm7_SOURCES=main_arm7.c
vm_arm7_LDFLAGS=-lvm -L$(builddir)/arm7 -lvm-arm7 \
	-L$(builddir)/devices -ldevice-host-serial
vm_arm7_CFLAGS=-I$(srcdir)/arm7

SUBDIRS=arm7 devices

EXTRA_DIST=jinstruction.h  jioport_dummy.h  jioport.h  jmachine.h
