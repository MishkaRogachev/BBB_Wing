#ifndef BOARD_TRANSMITTER_NODE_H
#define BOARD_TRANSMITTER_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class BoardTransmitterNode : public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        BoardTransmitterNode(float frequency, QObject* parent = nullptr);
        ~BoardTransmitterNode() override;

    public slots:
        void exec() override;

        void onSubReceived(const QString& topic, const QByteArray& msg);

    signals:
        void transmit(const QByteArray& packet);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // BOARD_TRANSMITTER_NODE_H
