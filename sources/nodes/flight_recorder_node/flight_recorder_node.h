#ifndef FLIGHT_RECORDER_NODE_H
#define FLIGHT_RECORDER_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class FlightRecorderNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        FlightRecorderNode(QObject* parent = nullptr);
        ~FlightRecorderNode() override;

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

#endif // FLIGHT_RECORDER_NODE_H
