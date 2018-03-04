#include <QCoreApplication>
#include <QTimer>

#include "../base-app/base-app_global.h"
#include "../base-app/servernetworkmgr.h"

int main(int argc, char *argv[])
{
    // Provides the event loop
    QCoreApplication app(argc, argv);

    // Create and initialize server
    auto mgr = new base::ServerNetworkMgr(&app);
    mgr->listen(SERVER_PORT);

    // Run until terminated
    return app.exec();
}
