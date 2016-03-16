// Qt
#include <QtGui/QGuiApplication>

// Internal
#include "branch_node.h"
#include "workstation_transceiver_node.h"
#include "ui_node.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    using namespace domain;

    BranchNode scheduler;

    scheduler.addNode(new WorkstationTransceiverNode(1));
    scheduler.addNode(new UiNode());

    scheduler.init();
    scheduler.start();

    return app.exec();
}
