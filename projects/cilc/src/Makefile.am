## Process this file with automake to produce Makefile.in

noinst_PROGRAMS=param_test
lib_LTLIBRARIES   = libcilc.la 
libcilc_la_SOURCES = Command.cpp  Command.h  CommandPair.cpp  CommandPair.h  CommandPairs.cpp\
					CommandPairs.h  Param.cpp  Param.h CodeGen.h CodeGen.cpp
libcilc_la_CXXFLAGS=@XMLCONFIG_CFLAGS@
libcilc_la_LDFLAGS = -lstdc++ @XMLCONFIG_LIBS@

bin_PROGRAMS=cilc
cilc_SOURCES  = main.cpp
cilc_CXXFLAGS = 
cilc_LDFLAGS  = -lcilc

param_test_SOURCES  = Param.cpp
param_test_CXXFLAGS = -DPARAM_TEST

EXTRA_DIST=cilc.xml command_type.h

