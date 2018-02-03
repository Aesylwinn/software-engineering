#ifndef BASE_APP_APPLICATION_H
#define BASE_APP_APPLICATION_H

#include <QApplication>

namespace base {
    class Application : public QApplication {
            Q_OBJECT
        public:
            Application(int& argc, char** argv);
            ~Application();
    };
}

#endif

