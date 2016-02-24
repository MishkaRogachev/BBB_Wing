#include "debug_node.h"

// Qt
#include <QDebug>

// Internal
#include "subscriber.h"

using namespace domain;

class DebugNode::Impl
{
public:
    QByteArray messages;
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
     d->sub.connectTo("ipc://ins");
     d->sub.connectTo("ipc://sns");

     d->sub.subscribe("");
     connect(&d->sub, &Subscriber::received, this, &DebugNode::onReceived);
}

void DebugNode::exec()
{
    qDebug() << d->messages;
    d->messages.clear();
}

void DebugNode::onReceived(const QString& topic, const QByteArray& data)
{
    d->messages.append(topic.toLatin1() + QByteArray(":") +
                       data + QByteArray("; "));
}
