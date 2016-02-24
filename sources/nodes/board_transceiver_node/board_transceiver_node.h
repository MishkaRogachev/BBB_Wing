#ifndef BOARDTRANSCEIVERNODE_H
#define BOARDTRANSCEIVERNODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class BoardTransceiverNode: public AbstractNodeFrequency
    {
    public:
        BoardTransceiverNode(QObject* parent = nullptr);
        ~BoardTransceiverNode() override;

        void init() override;
        void exec() override;

    private slots:
        void onReceived(const QString& topic, const QByteArray& msg);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // BOARDTRANSCEIVERNODE_H
