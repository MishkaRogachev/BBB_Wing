#ifndef BOARD_GATEWAY_NODE_H
#define BOARD_GATEWAY_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class BoardGatewayNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        BoardGatewayNode(QObject* parent = nullptr);
        ~BoardGatewayNode() override;

    public slots:
        void init() override;
        void exec() override;

    private slots:
        void onSubReceived(const QString& topic, const QByteArray& data);
        void onLinkReceived(const QByteArray& data);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // BOARD_GATEWAY_NODE_H
