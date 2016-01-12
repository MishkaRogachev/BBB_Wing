#include "sensor_altimeter_node.h"

#include "mpl3115a2.h"

using namespace domain;

SensorAltimeterNode::SensorAltimeterNode()
{}

int SensorAltimeterNode::exec()
{
    devices::Mpl3115A2 altimeter;

    altimeter.start();

    // TODO: publish values

    return 0;
}
