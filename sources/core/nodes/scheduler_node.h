#ifndef SCHEDULER_NODE_H
#define SCHEDULER_NODE_H

#include "abstract_node.h"

namespace domain
{
    class AbstractNodeFrequency;
    class SchedulerNode: public AbstractNode
    {
        Q_OBJECT

    public:
        SchedulerNode(QObject* parent = nullptr);
        ~SchedulerNode() override;

    public slots:
        void init() override;
        void exec() override;

        void addNode(AbstractNode* node);
        void addNodeFrequency(AbstractNodeFrequency* node, float frequency);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // SCHEDULER_NODE_H
