#include "application.h"
#include "main-page.h"

int main(int argc, char** argv) {
    // Set up global state
    web::Application app(argc, argv);

    // Create and display the main window
    web::MainPage mainPage;
    mainPage.show();

    // Run
    return app.exec();
}

