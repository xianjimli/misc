## Process this file with automake to produce Makefile.in

noinst_PROGRAMS      =  demo


lib_LTLIBRARIES       = libxmlconfig.la 

libxmlconfig_la_SOURCES= Common.h        Input.cpp     StrUtil.h          XmlConst.h     XmlParser.h \
                         DebugUtil.h     Input.h       XmlAccessor.cpp    Xml.h          XPath.cpp \
                         Demo.cpp        MemInput.cpp  XmlAccessor.h      XmlLexer.cpp   XPath.h\
                         FileInput.cpp   MemInput.h    XmlConfig.cpp      XmlLexer.h \
                         FileInput.h     Output.cpp    XmlConfig.h        XmlNode.cpp \
                         FileOutput.cpp  Output.h      XmlConfigImpl.cpp  XmlNode.h \
                         FileOutput.h    StrUtil.cpp   XmlConfigImpl.h    XmlParser.cpp
libxmlconfig_la_LDFLAGS = -lstdc++

demo_SOURCES  = Demo.cpp
demo_CXXFLAGS = 
demo_LDFLAGS  = -lxmlconfig

xmlconfigincludedir=$(includedir)/xmlconfig
xmlconfiginclude_HEADERS =  XmlConfig.h Xml.h
        

