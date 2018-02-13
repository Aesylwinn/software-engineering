#ifndef BASE_SIMPLECLASS_H
#define BASE_SIMPLECLASS_H

#include <QObject>

namespace base {
	// An example of a class for unit testing purposes
	class SimpleClass : public QObject {
		Q_OBJECT
	public:
		bool alwaysTrue();
		bool alwaysFalse();
	};
}

#endif
