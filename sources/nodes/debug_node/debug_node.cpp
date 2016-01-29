#include "debug_node.h"

// Qt
#include <QDebug>
#include <QDateTime>

// Internal
#include "subscriber.h"

using namespace domain;
using TimedMessage = QPair<QDateTime, QByteArray>;

class DebugNode::Impl
{
public:
    Subscriber sub;
    QList<TimedMessage> messages;
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
     d->sub.connectTo("ipc://imu");
     d->sub.connectTo("ipc://sns");

     d->sub.subscribe("");
     connect(&d->sub, &Subscriber::received, this, &DebugNode::onReceived);
}

void DebugNode::exec()
{
    while (!d->messages.isEmpty())
    {
        TimedMessage message = d->messages.takeFirst();
        qDebug() << message.first.toString(Qt::ISODate) << message.second;
    }
}

void DebugNode::onReceived(const QString& topic, const QByteArray& data)
{
    d->messages.append(TimedMessage(QDateTime::currentDateTime(),
                                     topic.toLatin1() + QByteArray(":") + data));
}
