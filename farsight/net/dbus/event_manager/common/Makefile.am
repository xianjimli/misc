EXTRA_DIST=eventmanager_service_gcf.xml  eventmanager_service.xml  eventmanager_type.h \
           eventmanager_service_bindings.h eventmanager_service_glue.h

eventmanagerincludedir     =$(includedir)/eventmanager
eventmanagerinclude_HEADERS= eventmanager_type.h

eventmanager_service_glue.h: eventmanager_service.xml
	dbus-binding-tool --mode=glib-server --prefix=eventmanager_service --output=eventmanager_service_glue.h $(srcdir)/eventmanager_service.xml

eventmanager_service_bindings.h: eventmanager_service.xml
	dbus-binding-tool --mode=glib-client --prefix=eventmanager --output=eventmanager_service_bindings.h $(srcdir)/eventmanager_service.xml

service_xmldir=$(prefix)/service_xml
service_xml_DATA=eventmanager_service.xml
