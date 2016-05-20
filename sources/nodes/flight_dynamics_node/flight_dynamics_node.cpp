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

#include "aircraft_control_factory.h"

using namespace domain;

class FlightDynamicsNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    QList<AbstractAircraftControl*> controls;
};

FlightDynamicsNode::FlightDynamicsNode(QObject* parent):
    AbstractNode(parent),
    d(new Impl())
{
    d->pub.bind(endpoints::flightDynamics);

    AircraftControlFactory factory;

    for (const QVariant& settings:
         Config::value("FlightDynamics/controls").toList())
    {
        d->controls.append(factory.create(settings.toMap()));
    }
}

FlightDynamicsNode::~FlightDynamicsNode()
{
    while (!d->controls.empty())
        delete d->controls.takeFirst();
    delete d;
}

void FlightDynamicsNode::init()
{
    d->sub.connectTo({ endpoints::flightPilot });

    d->sub.subscribe(topics::controlPacket);
    connect(&d->sub, &Subscriber::received, this,
            &FlightDynamicsNode::onSubReceived);
}

void FlightDynamicsNode::start()
{}

void FlightDynamicsNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    if (topic != topics::controlPacket) return;

    ControlPacket controlPacket = ControlPacket::fromByteArray(msg);
    DriveImpactsPacket packet;

    for (AbstractAircraftControl* control: d->controls)
    {
        packet.impacts.insert(control->channel(),
                              control->processControl(controlPacket));
    }

    d->pub.publish(topics::driveImpactsPacket, packet.toByteArray());
}
