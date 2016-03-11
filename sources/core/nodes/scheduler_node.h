#ifndef SCHEDULER_NODE_H
#define SCHEDULER_NODE_H

#include "branch_node.h"

namespace domain
{
    class AbstractNodeFrequency;
    class SchedulerNode: public BranchNode
    {
        Q_OBJECT

    public:
        SchedulerNode(QObject* parent = nullptr);
        ~SchedulerNode() override;

    public slots:
        void init() override;
        void exec() override;

        void addNodeFrequency(AbstractNodeFrequency* node, float frequency);
        void removeNodeFrequency(AbstractNodeFrequency* node);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // SCHEDULER_NODE_H
