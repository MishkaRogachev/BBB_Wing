#ifndef FAILURES_HANDLER_NODE_H
#define FAILURES_HANDLER_NODE_H

#include "abstract_node_frequency.h"

namespace domain
{
    class FailuresHandlerNode: public AbstractNodeFrequency
    {
        Q_OBJECT

    public:
        FailuresHandlerNode(QObject* parent = nullptr);
        ~FailuresHandlerNode() override;

    public slots:
        void init() override;
        void exec() override;

    private slots:
        void onSubReceived(const QString& topic, const QByteArray& msg);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FAILURES_HANDLER_NODE_H
