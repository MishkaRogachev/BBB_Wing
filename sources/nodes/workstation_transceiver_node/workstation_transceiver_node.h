#ifndef WORKSTATION_TRANSCEIVER_NODE_H
#define WORKSTATION_TRANSCEIVER_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class WorkstationTransceiverNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        WorkstationTransceiverNode(float frequency, QObject* parent = nullptr);
        ~WorkstationTransceiverNode() override;

        void init() override;
        void exec() override;

    private slots:
        void onPacketReceived(const QByteArray& packetData);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // WORKSTATION_TRANSCEIVER_NODE_H
