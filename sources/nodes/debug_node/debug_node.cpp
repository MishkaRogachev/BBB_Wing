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
    // Using ipc instead inproc becouse https://github.com/zeromq/libzmq/issues/1434
     d->sub.connectTo("ipc://altimeter");
     d->sub.subscribe("");
     connect(&d->sub, &Subscriber::received, this, &DebugNode::onReceived);
}

void DebugNode::exec()
{
    qDebug() << "-----------------------------------";
}

void DebugNode::onReceived(const QString& topic, const QByteArray& data)
{
    qDebug() << topic << data;
}
