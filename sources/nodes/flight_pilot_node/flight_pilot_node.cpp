#include "flight_pilot_node.h"

// Qt
#include <QDebug>
#include <QScopedPointer>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "control_packet.h"
#include "ins_packet.h"
#include "sns_packet.h"
#include "direct_packet.h"

#include "regulator_factory.h"

using namespace domain;

class FlightPilotNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    QScopedPointer<AbstractRegulator> pitchRegulator;
    QScopedPointer<AbstractRegulator> rollRegulator;
    QScopedPointer<AbstractRegulator> courseRegulator;
    QScopedPointer<AbstractRegulator> speedRegulator;
};

FlightPilotNode::FlightPilotNode(QObject* parent):
    AbstractNodeFrequency(Config::value("FlightPilot/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::flightPilot);

    RegulatorFactory factory;
    d->pitchRegulator.reset(factory.create(
                                Config::value("FlightPilot/pitch_regulator").toMap(),
                                this->frequency()));
    d->rollRegulator.reset(factory.create(
                                Config::value("FlightPilot/roll_regulator").toMap(),
                                this->frequency()));
    d->courseRegulator.reset(factory.create(
                                Config::value("FlightPilot/course_regulator").toMap(),
                                this->frequency()));
    d->speedRegulator.reset(factory.create(
                                Config::value("FlightPilot/speed_regulator").toMap(),
                                this->frequency()));
}

FlightPilotNode::~FlightPilotNode()
{
    delete d;
}

void FlightPilotNode::init()
{
    d->sub.connectTo({ endpoints::altimeter,
                       endpoints::ins,
                       endpoints::sns,
                       endpoints::navigator,
                       endpoints::boardTransceiver });

    d->sub.subscribe(topics::data);
    connect(&d->sub, &Subscriber::received, this,
            &FlightPilotNode::onSubReceived);
}

void FlightPilotNode::exec()
{
    ControlPacket packet;

    packet.pitchControl = d->pitchRegulator ? d->pitchRegulator->regulate() : 0;
    packet.rollControl = d->rollRegulator ? d->rollRegulator->regulate() : 0;
    packet.courseControl = d->courseRegulator ? d->courseRegulator->regulate() : 0;
    packet.speedControl = d->speedRegulator ? d->speedRegulator->regulate() : 0;

    d->pub.publish(topics::controlPacket, packet.toByteArray());
}

void FlightPilotNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    if (topic == topics::insPacket)
    {
        InsPacket ins = InsPacket::fromByteArray(msg);
        if (d->pitchRegulator) d->pitchRegulator->setInputValue(ins.pitch);
        if (d->rollRegulator) d->rollRegulator->setInputValue(ins.roll);

    }
    else if (topic == topics::snsPacket)
    {
        SnsPacket sns = SnsPacket::fromByteArray(msg);

        if (sns.status && sns.fix > 2)
        {
            if (d->courseRegulator)
                d->courseRegulator->setInputValue(sns.fix2d.yaw);
            if (d->speedRegulator)
                d->speedRegulator->setInputValue(sns.fix2d.groundSpeed);
            // TODO: airspeed
        }
    }
    else if (topic == topics::directPacket)
    {
        DirectPacket direct = DirectPacket::fromByteArray(msg);

        if (direct.isManual)
        {
            if (d->pitchRegulator) d->pitchRegulator->setTargetValue(
                        direct.manual.pitchControl);
            if (d->rollRegulator) d->rollRegulator->setTargetValue(
                        direct.manual.rollControl);
            if (d->courseRegulator) d->courseRegulator->setTargetValue(
                        direct.manual.courseControl);
            if (d->speedRegulator) d->speedRegulator->setTargetValue(
                        direct.manual.speedControl);
        }
    }
}
