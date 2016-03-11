#ifndef SENSOR_INS_NODE_H
#define SENSOR_INS_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class SensorInsNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        SensorInsNode(float frequency, QObject* parent = nullptr);
        ~SensorInsNode() override;

        void init() override;
        void exec() override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // SENSOR_INS_NODE_H
