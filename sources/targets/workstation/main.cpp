// Qt
#include <QtGui/QGuiApplication>

// Internal
#include "scheduler_node.h"
#include "debug_node.h"
#include "workstation_transceiver_node.h"
#include "ui_node.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    using namespace domain;

    SchedulerNode scheduler;

//    scheduler.addNodeFrequency(new DebugNode(), 10);
    scheduler.addNodeFrequency(new WorkstationTransceiverNode(), 25);
    scheduler.addNode(new UiNode());

    scheduler.init();
    scheduler.exec();

    return app.exec();
}
