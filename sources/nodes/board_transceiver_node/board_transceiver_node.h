#ifndef BOARD_TRANSCEIVER_NODE_H
#define BOARD_TRANSCEIVER_NODE_H

#include "branch_node.h"

namespace domain
{
    class BoardTransceiverNode: public BranchNode
    {
        Q_OBJECT

    public:
        BoardTransceiverNode(QObject* parent = nullptr);
        ~BoardTransceiverNode() override;

    public slots:
        void init() override;

    private slots:
        void onPacketReceived(const QByteArray& packet);
        void onTimeout();
        void transmitPacket(const QByteArray& packet);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // BOARD_TRANSCEIVER_NODE_H
