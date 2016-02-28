#include "scheduler_node.h"

// Qt
#include <QMultiMap>

// Internal
#include "abstract_node_frequency.h"

using namespace domain;

class SchedulerNode::Impl
{
public:
    QMultiMap<float, AbstractNodeFrequency*> nodesFrequency;
    QList<AbstractNode*> nodes;
};

SchedulerNode::SchedulerNode(QObject* parent):
    AbstractNode(parent),
    d(new Impl())
{}

SchedulerNode::~SchedulerNode()
{
    delete d;
}

void SchedulerNode::init()
{
    for (AbstractNode* node: d->nodes)
        node->init();

    for (AbstractNode* node: d->nodesFrequency)
        node->init();
}

void SchedulerNode::exec()
{
    for (AbstractNode* node: d->nodes)
        node->exec();

    for (auto it = d->nodesFrequency.begin();
         it != d->nodesFrequency.end(); ++it)
        it.value()->start(it.key());
}

void SchedulerNode::addNode(AbstractNode* node)
{
    d->nodes.append(node);
    node->setParent(this);
}

void SchedulerNode::addNodeFrequency(AbstractNodeFrequency* node, float frequency)
{
    d->nodesFrequency.insert(frequency, node);
    node->setParent(this);
}
