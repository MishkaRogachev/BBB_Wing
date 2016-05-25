#ifndef BOARD_GATEWAY_NODE_H
#define BOARD_GATEWAY_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class BoardTransceiverNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        BoardTransceiverNode(QObject* parent = nullptr);
        ~BoardTransceiverNode() override;

    public slots:
        void init() override;
        void exec() override;

    protected:
        void timerEvent(QTimerEvent* event);

    private slots:
        void onSubReceived(const QString& topic, const QByteArray& data);
        void onWireLinkReceived(const QByteArray& data);
        void onAirLinkReceived(const QByteArray& data);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // BOARD_GATEWAY_NODE_H
