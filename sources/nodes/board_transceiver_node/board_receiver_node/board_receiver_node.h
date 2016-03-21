#ifndef BOARD_RECEIVER_NODE_H
#define BOARD_RECEIVER_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class Publisher;

    class BoardReceiverNode : public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        BoardReceiverNode(float frequency, Publisher* pub,
                          QObject* parent = nullptr);

    public slots:
        void exec() override;

        void processPacket(const QByteArray& packetData);

    private:
        Publisher* m_pub;
        bool m_status;
    };
}

#endif // BOARD_RECEIVER_NODE_H
