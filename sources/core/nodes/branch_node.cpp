#include "branch_node.h"

using namespace domain;

BranchNode::BranchNode(QObject* parent):
    AbstractNode(parent)
{}

void BranchNode::init()
{
    for (AbstractNode* node: m_nodes)
        node->init();
}

void BranchNode::exec()
{
    for (AbstractNode* node: m_nodes)
        node->exec();
}

void BranchNode::addNode(AbstractNode* node)
{
    m_nodes.append(node);
    node->setParent(this);
}

void BranchNode::removeNode(AbstractNode* node)
{
    if (m_nodes.removeOne(node)) node->setParent(nullptr);
}

const QList<AbstractNode*>& BranchNode::nodes() const
{
    return m_nodes;
}
