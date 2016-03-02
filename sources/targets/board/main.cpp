// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "scheduler_node.h"
#include "debug_node.h"
#include "sensor_altimeter_node.h"
#include "sensor_ins_node.h"
#include "sensor_sns_node.h"
#include "flight_recorder_node.h"
#include "board_transceiver_node.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    using namespace domain;

    SchedulerNode scheduler;

//    scheduler.addNodeFrequency(new DebugNode(), 10);
    scheduler.addNodeFrequency(new SensorAltimeterNode(), 5);
    scheduler.addNodeFrequency(new SensorInsNode(), 10);
    scheduler.addNodeFrequency(new SensorSnsNode(), 5);
    scheduler.addNodeFrequency(new FlightRecorderNode(), 5);
    scheduler.addNodeFrequency(new BoardTransceiverNode(), 5);

    scheduler.init();
    scheduler.exec();

    return app.exec();
}
