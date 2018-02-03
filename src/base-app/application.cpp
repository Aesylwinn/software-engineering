#include "application.h"

namespace base {
    Application::Application(int& argc, char** argv)
        : QApplication(argc, argv)
    {
    }

    Application::~Application() {
    }
}

