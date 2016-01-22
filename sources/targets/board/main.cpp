// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "debug_node.h"
#include "sensor_altimeter_node.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::DebugNode debugNode;
    domain::SensorAltimeterNode altimeterNode;

    debugNode.init();
    altimeterNode.init();

    debugNode.start(1);
    altimeterNode.start(2);

    return app.exec();
}
