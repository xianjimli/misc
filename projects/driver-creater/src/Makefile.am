## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = driver-creater

driver_creater_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	driver_info.c

driver_creater_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

noinst_PROGRAMS=driver_info_test
driver_info_test_SOURCES=driver_info.c
driver_info_test_CFLAGS=@GLIB_CFLAGS@ -DDRIVER_INFO_TEST
driver_info_test_LDFLAGS=-lexpat @GLIB_LIBS@

