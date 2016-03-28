// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "branch_node.h"
#include "sensor_altimeter_node.h"
#include "sensor_ins_node.h"
#include "sensor_sns_node.h"
#include "flight_recorder_node.h"
#include "flight_navigator_node.h"
#include "flight_controller_node.h"
#include "board_gateway_node.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    using namespace domain;

    BranchNode scheduler;

    scheduler.addNode(new SensorAltimeterNode());
    scheduler.addNode(new SensorInsNode());
    scheduler.addNode(new SensorSnsNode());
    scheduler.addNode(new FlightRecorderNode());
    scheduler.addNode(new FlightNavigatorNode());
    scheduler.addNode(new FlightControllerNode());
    scheduler.addNode(new BoardGatewayNode());

    scheduler.init();
    scheduler.start();

    return app.exec();
}
