// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "debug_node.h"
#include "sensor_altimeter_node.h"
#include "sensor_sns_node.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::DebugNode debugNode;
    domain::SensorAltimeterNode altimeterNode;
    domain::SensorSnsNode snsNode;

    debugNode.init();
    altimeterNode.init();
    snsNode.init();

    debugNode.start(1);
    altimeterNode.start(2);
    snsNode.start(10);

    return app.exec();
}
