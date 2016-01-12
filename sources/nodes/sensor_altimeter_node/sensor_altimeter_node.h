#ifndef SENSOR_ALTIMETER_NODE_H
#define SENSOR_ALTIMETER_NODE_H

#include "i_node.h"

namespace domain
{
    class SensorAltimeterNode: public INode
    {
    public:
        SensorAltimeterNode();

        int exec() override;
    };
}

#endif // SENSOR_ALTIMETER_NODE_H
