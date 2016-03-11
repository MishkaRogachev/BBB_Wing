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
    BranchNode(parent),
    d(new Impl())
{}

SchedulerNode::~SchedulerNode()
{
    delete d;
}

void SchedulerNode::init()
{
    BranchNode::init();

    for (AbstractNode* node: d->nodesFrequency)
        node->init();
}

void SchedulerNode::exec()
{
    BranchNode::exec();

    for (auto it = d->nodesFrequency.begin();
         it != d->nodesFrequency.end(); ++it)
        it.value()->start(it.key());
}

void SchedulerNode::addNodeFrequency(AbstractNodeFrequency* node, float frequency)
{
    d->nodesFrequency.insert(frequency, node);
    node->setParent(this);
}

void SchedulerNode::removeNodeFrequency(AbstractNodeFrequency* node)
{
    auto it = d->nodesFrequency.find(d->nodesFrequency.key(node), node);

    if (it == d->nodesFrequency.end()) return;

    d->nodesFrequency.erase(it);
    node->setParent(nullptr);
}
