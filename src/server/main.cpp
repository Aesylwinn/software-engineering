#include <QCoreApplication>
#include <QTimer>

#include "../base-app/servernetworkmgr.h"

int main(int argc, char *argv[])
{
    // Provides the event loop
    QCoreApplication app(argc, argv);

    // Create and initialize server
    auto mgr = new base::ServerNetworkMgr(&app);
    mgr->listen(1942);

    // Run until terminated
    return app.exec();
}
