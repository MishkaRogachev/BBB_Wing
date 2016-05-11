#ifndef FLIGHT_DYNAMICS_NODE_H
#define FLIGHT_DYNAMICS_NODE_H

#include "abstract_node.h"

namespace domain
{
    class FlightDynamicsNode: public AbstractNode
    {
        Q_OBJECT

    public:
        FlightDynamicsNode(QObject* parent = nullptr);
        ~FlightDynamicsNode() override;

    public slots:
        void init() override;
        void start() override;

    private slots:
        void onSubReceived(const QString& topic, const QByteArray& msg);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FLIGHT_DYNAMICS_NODE_H
