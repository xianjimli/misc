lib_LTLIBRARIES=libeventmanager.la

libeventmanager_la_SOURCES=eventmanager.h eventmanager.c
libeventmanager_la_CFLAGS=@PACKAGE_CFLAGS@ -I$(top_srcdir)/common
libeventmanager_la_LDFLAGS=@PACKAGE_LIBS@

autotestdir=$(prefix)/test/service/eventmanager
autotest_PROGRAMS=eventmanager_test
autotest_SCRIPTS =autotest.sh

autotest.sh:
	echo "autotest.sh ok"

eventmanager_test_SOURCES=eventmanager.h eventmanager.c
eventmanager_test_CFLAGS=@PACKAGE_CFLAGS@ -I$(top_srcdir)/common -DEVENT_MANAGER_TEST
eventmanager_test_LDFLAGS=@PACKAGE_LIBS@

eventmanagerincludedir=$(includedir)/eventmanager
eventmanagerinclude_HEADERS=eventmanager.h

pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA=eventmanager.pc

EXTRA_DIST=eventmanager.pc.in
