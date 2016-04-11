#ifndef FLIGHT_RECORD_PLAYER_NODE_H
#define FLIGHT_RECORD_PLAYER_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class FlightRecordPlayerNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        FlightRecordPlayerNode(QObject* parent = nullptr);
        ~FlightRecordPlayerNode() override;

    public slots:
        void init() override;
        void exec() override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FLIGHT_RECORD_PLAYER_NODE_H
