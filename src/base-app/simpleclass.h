#ifndef BASE_SIMPLECLASS_H
#define BASE_SIMPLECLASS_H

#include "base-app_global.h"

#include <QObject>

namespace base {
	// An example of a class for unit testing purposes
    class BASEAPPSHARED_EXPORT SimpleClass : public QObject {
		Q_OBJECT
	public:
		bool alwaysTrue();
		bool alwaysFalse();
	};
}

#endif
