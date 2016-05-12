#ifndef FLIGHT_PILOT_NODE_H
#define FLIGHT_PILOT_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class FlightPilotNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        FlightPilotNode(QObject* parent = nullptr);
        ~FlightPilotNode() override;

    public slots:
        void init() override;
        void exec() override;

    private slots:
        void onSubReceived(const QString& topic, const QByteArray& msg);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FLIGHT_PILOT_NODE_H
