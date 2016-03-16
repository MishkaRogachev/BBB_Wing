// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "branch_node.h"
#include "sensor_altimeter_node.h"
#include "sensor_ins_node.h"
#include "sensor_sns_node.h"
#include "flight_recorder_node.h"
#include "board_transceiver_node.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    using namespace domain;

    BranchNode scheduler;

    scheduler.addNode(new SensorAltimeterNode(5));
    scheduler.addNode(new SensorInsNode(100));
    scheduler.addNode(new SensorSnsNode(5));
    scheduler.addNode(new FlightRecorderNode(25));
    scheduler.addNode(new BoardTransceiverNode(10));

    scheduler.init();
    scheduler.start();

    return app.exec();
}
