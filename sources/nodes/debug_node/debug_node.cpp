#include "debug_node.h"

// Qt
#include <QDebug>

// Internal
#include "subscriber.h"

using namespace domain;

class DebugNode::Impl
{
public:
    Subscriber sub;
};

DebugNode::DebugNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{}

DebugNode::~DebugNode()
{
    delete d;
}

void DebugNode::init()
{
     d->sub.connectTo("inproc://altimeter");
     d->sub.subscribe("");
}

void DebugNode::exec()
{
    for (;;)
    {
        QByteArray msg = d->sub.recv(1);
        if (msg.isEmpty()) break;
        qDebug() << msg;
    }
    qDebug() << "-----------------------------------";
}
