#ifndef THREAD_NODE_H
#define THREAD_NODE_H

#include "abstract_node.h"

class QThread;

namespace domain
{
    class ThreadNode: public AbstractNode
    {
        Q_OBJECT

    public:
        ThreadNode(AbstractNode* worker, QObject* parent = nullptr);
        ~ThreadNode() override;

    signals:
        void init() override;
        void start() override;
        void stop() override;

    private:
        AbstractNode* m_worker;
        QThread* m_thread;
    };
}

#endif // THREAD_NODE_H
