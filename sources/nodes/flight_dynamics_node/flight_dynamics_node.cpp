#include "flight_dynamics_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "control_packet.h"
#include "drive_impacts_packet.h"

using namespace domain;

class FlightDynamicsNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;
};

FlightDynamicsNode::FlightDynamicsNode(QObject* parent):
    AbstractNode(parent),
    d(new Impl())
{
    d->pub.bind(endpoints::failuresHandler);
}

FlightDynamicsNode::~FlightDynamicsNode()
{
    delete d;
}

void FlightDynamicsNode::init()
{
    d->sub.connectTo({ endpoints::flightController });

    d->sub.subscribe(topics::controlPacket);
    connect(&d->sub, &Subscriber::received, this,
            &FlightDynamicsNode::onSubReceived);
}

void FlightDynamicsNode::start()
{}

void FlightDynamicsNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    if (topic != topics::controlPacket) return;

    ControlPacket control = ControlPacket::fromByteArray(msg);

    DriveImpactsPacket packet;

    d->pub.publish(topics::failuresPacket, packet.toByteArray());
}
