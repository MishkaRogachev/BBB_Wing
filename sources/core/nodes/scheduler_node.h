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

    public slots:
        void addNodeFrequency(AbstractNodeFrequency* node, float frequency);
    };
}

#endif // SCHEDULER_NODE_H
