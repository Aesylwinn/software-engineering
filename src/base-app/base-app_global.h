#ifndef BASEAPP_GLOBAL_H
#define BASEAPP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BASEAPP_LIBRARY)
#  define BASEAPPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BASEAPPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BASEAPP_GLOBAL_H
