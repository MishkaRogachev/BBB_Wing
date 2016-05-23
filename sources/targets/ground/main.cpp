// Qt
#include <QtGui/QGuiApplication>

// Internal
#include "branch_node.h"
#include "thread_node.h"
#include "ground_gateway_node.h"
#include "flight_record_player_node.h"
#include "gui_node.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    using namespace domain;

    BranchNode scheduler;

    // TODO: data source manager node
    scheduler.addNode(new ThreadNode(new GroundGatewayNode()));
//    scheduler.addNode(new FlightRecordPlayerNode());
    scheduler.addNode(new GuiNode());

    scheduler.init();
    scheduler.start();

    return app.exec();
}
