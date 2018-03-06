#ifndef BASEAPP_GLOBAL_H
#define BASEAPP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BASEAPP_LIBRARY)
#  define BASEAPPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BASEAPPSHARED_EXPORT Q_DECL_IMPORT
#endif

#define SERVER_ADDRESS "ec2-35-163-240-76.us-west-2.compute.amazonaws.com"
#define SERVER_PORT 1942

#endif // BASEAPP_GLOBAL_H
