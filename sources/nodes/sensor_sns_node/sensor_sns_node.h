#ifndef SENSOR_SNS_NODE_H
#define SENSOR_SNS_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class SensorSnsNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        SensorSnsNode(float frequency, QObject* parent = nullptr);
        ~SensorSnsNode() override;

    public slots:
        void init() override;
        void exec() override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // SENSOR_SNS_NODE_H
