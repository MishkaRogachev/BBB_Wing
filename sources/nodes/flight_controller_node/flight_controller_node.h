#ifndef FLIGHT_CONTROLLER_NODE_H
#define FLIGHT_CONTROLLER_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class FlightControllerNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        FlightControllerNode(float frequency, QObject* parent = nullptr);
        ~FlightControllerNode() override;

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

#endif // FLIGHT_CONTROLLER_NODE_H
