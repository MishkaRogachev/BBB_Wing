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
    domain::SensorAltimeterNode altNode;

    debugNode.init();
    altNode.init();

    debugNode.start(1);
    altNode.start(2);

    return app.exec();
}
