#ifndef WEB_APP_APPLICATION_H
#define WEB_APP_APPLICATION_H

#include "base-app/application.h"

namespace web {
    class Application : public base::Application {
            Q_OBJECT
        public:
            Application(int& argc, char** argv);
    };
}

#endif

