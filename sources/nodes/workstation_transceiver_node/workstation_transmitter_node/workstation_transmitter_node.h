#ifndef WORKSTATION_TRANSMITTER_NODE_H
#define WORKSTATION_TRANSMITTER_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class WorkstationTransmitterNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        WorkstationTransmitterNode(float frequency,
                                   QObject* parent = nullptr);

    public slots:
        void exec() override;

        void onSubReceived(const QString& topic, const QByteArray& msg);

    signals:
        void transmit(const QByteArray& packet);
    };
}

#endif // WORKSTATION_TRANSMITTER_NODE_H
