#include "flight_controller_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "navigator_packet.h"
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
    if (topic == topics::navigatorPacket)
    {
        // TODO: PID regulation calc impats using navigatorPacket
    }

    if (topic == topics::directPacket)
    {
        DirectPacket packet = DirectPacket::fromByteArray(msg);

//        float targetVelocity = 0.0;
//        float targetPitch = 0.0;
//        float targetRoll = 0.0;

        // TODO: deviation to angle recalculation
        for (int i = 0; i < packet.manual.channels; ++i)
            d->impacts.insert(i, packet.manual.deviations[i]);
    }

}
