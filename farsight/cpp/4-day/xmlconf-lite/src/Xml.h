#ifndef XML_H
#define XML_H

#ifdef WIN32
#ifdef XMLCONFIG_EXPORTS
#define XML_API __declspec(dllexport)
#else
#define XML_API __declspec(dllimport)
#endif
#pragma warning(disable: 4251)
#pragma warning(disable: 4786)
#else 
#define XML_API
#endif

#define XML_BEGIN() namespace XML {
#define XML_END() };
#define USE_XML using namespace XML;

#endif//XML_H
