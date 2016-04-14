#ifndef GATEWAY_NODE_H
#define GATEWAY_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class AbstractLink;
    class GatewayNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        GatewayNode(const QString& endpoint, float frequency,
                    QObject* parent = nullptr);
        ~GatewayNode() override;

        void addLink(AbstractLink* link);
        void removeLink(AbstractLink* link);

        void subscribe(const QStringList& enpoints, const QStringList& topics);

    public slots:
        void exec() override;

    protected:
        virtual void transmit(const QByteArray& data);

    protected slots:
        void onSubReceived(const QString& topic, const QByteArray& data);
        void onLinkReceived(const QByteArray& data);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // GATEWAY_NODE_H
