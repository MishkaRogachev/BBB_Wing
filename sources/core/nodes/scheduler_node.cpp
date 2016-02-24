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
    for (AbstractNode* node: d->nodesFrequency)
        node->init();
}

void SchedulerNode::exec()
{
    for (auto it = d->nodesFrequency.begin();
         it != d->nodesFrequency.end(); ++it)
        it.value()->start(it.key());
}

void SchedulerNode::addNodeFrequency(AbstractNodeFrequency* node, float frequency)
{
    d->nodesFrequency.insert(frequency, node);
    node->setParent(this);
}
