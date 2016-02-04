// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "scheduler_node.h"
#include "debug_node.h"
#include "sensor_altimeter_node.h"
#include "sensor_imu_node.h"
#include "sensor_sns_node.h"
#include "flight_recorder_node.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    using namespace domain;

    SchedulerNode scheduler;

    scheduler.addNodeFrequency(new DebugNode(), 1);
    scheduler.addNodeFrequency(new SensorAltimeterNode(), 5);
    scheduler.addNodeFrequency(new SensorImuNode(), 10);
    scheduler.addNodeFrequency(new SensorSnsNode(), 5);
    scheduler.addNodeFrequency(new FlightRecorderNode(), 4);

    scheduler.init();
    scheduler.exec();

    return app.exec();
}
