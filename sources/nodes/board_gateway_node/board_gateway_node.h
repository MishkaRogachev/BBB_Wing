#ifndef BOARD_GATEWAY_NODE_H
#define BOARD_GATEWAY_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class BoardGatewayNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        BoardGatewayNode(int frequency, QObject* parent = nullptr);
        ~BoardGatewayNode() override;

    public slots:
        void init() override;
        void start() override;
        void exec() override;

    private slots:
        void onTimeout();
        void onSubReceived(const QString& topic, const QByteArray& data);
        void onLineReceived(const QByteArray& data);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // BOARD_GATEWAY_NODE_H
