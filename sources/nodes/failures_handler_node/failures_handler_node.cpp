#include "failures_handler_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "topics.h"

#include "subscriber.h"
#include "publisher.h"

using namespace domain;

class FailuresHandlerNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;
};

FailuresHandlerNode::FailuresHandlerNode(QObject* parent):
    AbstractNodeFrequency(Config::value("FailuresHandler/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind("ipc://failures");
}

FailuresHandlerNode::~FailuresHandlerNode()
{
    delete d;
}

void FailuresHandlerNode::init()
{
    d->sub.connectTo("ipc://alt");
    d->sub.connectTo("ipc://ins");
    d->sub.connectTo("ipc://sns");
    d->sub.connectTo("ipc://navigator");
    d->sub.connectTo("ipc://controller");
    d->sub.connectTo("ipc://ground_gateway");

    d->sub.subscribe(topics::status);
    connect(&d->sub, &Subscriber::received, this,
            &FailuresHandlerNode::onSubReceived);
}

void FailuresHandlerNode::exec()
{
}

void FailuresHandlerNode::onSubReceived(const QString& topic, const QByteArray& msg)
{}
