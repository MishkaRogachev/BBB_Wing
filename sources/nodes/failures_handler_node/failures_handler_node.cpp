#include "failures_handler_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "failures_packet.h"

using namespace domain;

class FailuresHandlerNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    FailuresPacket packet;
};

FailuresHandlerNode::FailuresHandlerNode(QObject* parent):
    AbstractNodeFrequency(Config::value("FailuresHandler/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::failuresHandler);
}

FailuresHandlerNode::~FailuresHandlerNode()
{
    delete d;
}

void FailuresHandlerNode::init()
{
    d->sub.connectTo({ endpoints::altimeter,
                       endpoints::ins,
                       endpoints::sns,
                       endpoints::navigator,
                       endpoints::flightController,
                       endpoints::boardGateway });

    d->sub.subscribe(topics::status);
    connect(&d->sub, &Subscriber::received, this,
            &FailuresHandlerNode::onSubReceived);
}

void FailuresHandlerNode::exec()
{
    d->pub.publish(topics::failuresPacket, d->packet.toByteArray());
}

void FailuresHandlerNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    if (topic == topics::altStatus)
        d->packet.altStatus = msg.toInt();
    else if (topic == topics::insStatus)
        d->packet.insStatus = msg.toInt();
    else if (topic == topics::snsStatus)
        d->packet.snsStatus = msg.toInt();
}
