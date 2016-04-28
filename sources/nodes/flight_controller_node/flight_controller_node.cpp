#include "flight_controller_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "direct_packet.h"
#include "drive_impacts_packet.h"

using namespace domain;

class FlightControllerNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    DriveImpacts impacts;
};

FlightControllerNode::FlightControllerNode(QObject* parent):
    AbstractNodeFrequency(Config::value("FlightController/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::flightController);
}

FlightControllerNode::~FlightControllerNode()
{
    delete d;
}

void FlightControllerNode::init()
{
    d->sub.connectTo({ endpoints::altimeter,
                       endpoints::ins,
                       endpoints::sns,
                       endpoints::navigator,
                       endpoints::boardGateway });

    d->sub.subscribe({ topics::data });
    connect(&d->sub, &Subscriber::received, this,
            &FlightControllerNode::onSubReceived);
}

void FlightControllerNode::exec()
{
    DriveImpactsPacket packet;
    packet.impacts = d->impacts;
    d->pub.publish(topics::driveImpactsPacket, packet.toByteArray());
}

void FlightControllerNode::onSubReceived(const QString& topic,
                                         const QByteArray& msg)
{
    if (topic == topics::directPacket)
    {
        DirectPacket packet = DirectPacket::fromByteArray(msg);

        // TODO: deviation to angle recalculation
        d->impacts[0] = packet.manual.deviationX;
        d->impacts[1] = packet.manual.deviationY;
        d->impacts[2] = packet.manual.deviationZ;
    }

}
