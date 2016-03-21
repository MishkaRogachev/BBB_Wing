#ifndef FLIGHT_NAVIGATOR_NODE_H
#define FLIGHT_NAVIGATOR_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class FlightNavigatorNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        FlightNavigatorNode(float frequency, QObject* parent = nullptr);
        ~FlightNavigatorNode() override;

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

#endif // FLIGHT_NAVIGATOR_NODE_H
