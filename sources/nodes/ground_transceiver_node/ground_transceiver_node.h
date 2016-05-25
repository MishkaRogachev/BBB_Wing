#ifndef GROUND_TRANSCEIVER_NODE_H
#define GROUND_TRANSCEIVER_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class GroundTransceiverNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        GroundTransceiverNode(QObject* parent = nullptr);
        ~GroundTransceiverNode() override;

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

#endif // GROUND_TRANSCEIVER_NODE_H
