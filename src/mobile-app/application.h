#ifndef MOBILE_APP_APPLICATION_H
#define MOBILE_APP_APPLICATION_H

#include "base-app/application.h"

namespace mobile {
    class Application : public base::Application {
            Q_OBJECT
        public:
            Application(int& argc, char** argv);
    };
}

#endif

