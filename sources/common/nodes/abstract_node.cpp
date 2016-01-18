#include "abstract_node.h"

using namespace domain;

AbstractNode::AbstractNode(QObject* parent):
    QObject(parent)
{}

AbstractNode::~AbstractNode()
{}

void AbstractNode::init()
{}
