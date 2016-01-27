// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "debug_node.h"
#include "sensor_altimeter_node.h"
#include "sensor_sns_node.h"
#include "flight_recorder_node.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::DebugNode debugNode;
    domain::SensorAltimeterNode altimeterNode;
    domain::SensorSnsNode snsNode;
    domain::FlightRecorderNode flightRecorderNode;

    debugNode.init();
    altimeterNode.init();
    snsNode.init();
    flightRecorderNode.init();

    debugNode.start(1);
    altimeterNode.start(2);
    snsNode.start(10);
    flightRecorderNode.start(2);

    return app.exec();
}
