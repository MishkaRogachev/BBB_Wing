#ifndef SERVO_CONTROL_NODE_H
#define SERVO_CONTROL_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class SerovoControlNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        SerovoControlNode(QObject* parent = nullptr);
        ~SerovoControlNode() override;

    public slots:
        void init() override;
        void exec() override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // SERVO_CONTROL_NODE_H
