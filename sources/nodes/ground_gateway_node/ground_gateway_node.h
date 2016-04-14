#ifndef GROUND_GATEWAY_NODE_H
#define GROUND_GATEWAY_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class GroundGatewayNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        GroundGatewayNode(QObject* parent = nullptr);
        ~GroundGatewayNode() override;

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

#endif // GROUND_GATEWAY_NODE_H
