#include "scheduler_node.h"

// Internal
#include "abstract_node_frequency.h"

using namespace domain;


SchedulerNode::SchedulerNode(QObject* parent):
    BranchNode(parent)
{}

void SchedulerNode::addNodeFrequency(AbstractNodeFrequency* node, float frequency)
{
    node->setFrequency(frequency);
    this->addNode(node);
}

