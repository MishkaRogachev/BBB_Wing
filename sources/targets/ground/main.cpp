// Qt
#include <QtGui/QGuiApplication>

// Internal
#include "branch_node.h"
#include "ground_gateway_node.h"
#include "gui_node.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    using namespace domain;

    BranchNode scheduler;

    // TODO: reduce target dependings(from core)
    scheduler.addNode(new GroundGatewayNode());
    scheduler.addNode(new GuiNode());

    scheduler.init();
    scheduler.start();

    return app.exec();
}
