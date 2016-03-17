#ifndef WORKSTATION_RECEIVER_NODE_H
#define WORKSTATION_RECEIVER_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class Publisher;

    class WorkstationReceiverNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        WorkstationReceiverNode(float frequency, Publisher* pub,
                                QObject* parent = nullptr);

    public slots:
        void exec() override;

        void onPacketReceived(const QByteArray& packetData);

    signals:
        void timeout();

    private:
        Publisher* m_pub;
        int m_badCount;
        int m_goodCount;
    };
}

#endif // WORKSTATION_RECEIVER_NODE_H
