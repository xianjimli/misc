
noinst_PROGRAMS=eventmanager

eventmanager_SOURCES=eventmanager_service.c eventmanager_service.h main.c
eventmanager_CFLAGS=@PACKAGE_CFLAGS@ -I$(top_srcdir)/common -DEVENTMANAGER_TEST
eventmanager_LDFLAGS=@PACKAGE_LIBS@

libactiondaemondir=${libdir}/actiondaemon

libactiondaemon_LTLIBRARIES=libeventmanageraction.la
libeventmanageraction_la_SOURCES=eventmanager_service.c eventmanager_service.h main.c
libeventmanageraction_la_CFLAGS=@PACKAGE_CFLAGS@ -I$(top_srcdir)/common
libeventmanageraction_la_LDFLAGS=@PACKAGE_LIBS@

servicedir = $(DBUS_SERVICE_DIR)
service_DATA = org.broncho.EventManagerService.service

