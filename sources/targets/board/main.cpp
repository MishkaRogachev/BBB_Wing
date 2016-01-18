

// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "sensor_altimeter_node.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    domain::SensorAltimeterNode altNode;
    altNode.start(25);

    return app.exec();
}
