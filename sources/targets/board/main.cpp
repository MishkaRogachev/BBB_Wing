// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "branch_node.h"

#include "sensor_altimeter_node.h"
#include "sensor_ins_node.h"
#include "sensor_sns_node.h"
#include "servo_drives_node.h"

#include "flight_recorder_node.h"

#include "flight_navigator_node.h"
#include "flight_pilot_node.h"
#include "flight_dynamics_node.h"

#include "board_gateway_node.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    using namespace domain;

    BranchNode scheduler;

    scheduler.addNode(new SensorAltimeterNode());
    scheduler.addNode(new SensorInsNode());
    scheduler.addNode(new SensorSnsNode());
    scheduler.addNode(new ServoDrivesNode());

    scheduler.addNode(new FlightRecorderNode());

    scheduler.addNode(new FlightNavigatorNode());
    scheduler.addNode(new FlightPilotNode());
    scheduler.addNode(new FlightDynamicsNode());

    scheduler.addNode(new BoardGatewayNode());

    scheduler.init();
    scheduler.start();

    return app.exec();
}
