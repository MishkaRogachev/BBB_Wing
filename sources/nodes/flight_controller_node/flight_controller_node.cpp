#include "flight_controller_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "ins_packet.h"
#include "sns_packet.h"
#include "drive_impacts_packet.h"

#include "flight_regulator.h"

using namespace domain;


class FlightControllerNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    float pitch;
    float roll;
    float velocity;

    QList<FlightRegulator> regulators;
};

FlightControllerNode::FlightControllerNode(QObject* parent):
    AbstractNodeFrequency(Config::value("FlightController/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::flightController);

    for (const QVariant& regulator:
         Config::value("FlightController/regulators").toList())
    {
        d->regulators.append(FlightRegulator(regulator.toMap()));
    }
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

    for (FlightRegulator& regulator: d->regulators)
    {
        packet.impacts.insert(regulator.channel(),
                              regulator.regulate(0, this->frequency()));
        // TODO: base regulator classes
    }

    d->pub.publish(topics::driveImpactsPacket, packet.toByteArray());
}

void FlightControllerNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    if (topic == topics::insPacket)
    {
        InsPacket ins = InsPacket::fromByteArray(msg);
        d->pitch = ins.pitch;
        d->roll = ins.roll;
    }

    if (topic == topics::snsPacket)
    {
        SnsPacket sns = SnsPacket::fromByteArray(msg);
        d->velocity = sns.groundSpeed; // TODO: airspeed
    }
}
