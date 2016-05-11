#include "flight_controller_node.h"

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

#include "flight_controller_node.h"
#include "regulator_factory.h"

using namespace domain;

class FlightControllerNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    QScopedPointer<AbstractRegulator> pitchRegulator;
    QScopedPointer<AbstractRegulator> rollRegulator;
    QScopedPointer<AbstractRegulator> courseRegulator;
    QScopedPointer<AbstractRegulator> speedRegulator;
};

FlightControllerNode::FlightControllerNode(QObject* parent): // TODO: rename flight regulator node
    AbstractNodeFrequency(Config::value("FlightController/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::flightController);

    RegulatorFactory factory;
    d->pitchRegulator.reset(factory.create(
                                Config::value("FlightController/pitch_regulator").toMap(),
                                this->frequency()));
    d->rollRegulator.reset(factory.create(
                                Config::value("FlightController/roll_regulator").toMap(),
                                this->frequency()));
    d->courseRegulator.reset(factory.create(
                                Config::value("FlightController/course_regulator").toMap(),
                                this->frequency()));
    d->speedRegulator.reset(factory.create(
                                Config::value("FlightController/speed_regulator").toMap(),
                                this->frequency()));
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
    ControlPacket packet;

    packet.pitchControl = d->pitchRegulator ? d->pitchRegulator->regulate() : 0;
    packet.rollControl = d->rollRegulator ? d->rollRegulator->regulate() : 0;
    packet.courseControl = d->courseRegulator ? d->courseRegulator->regulate() : 0;
    packet.speedControl = d->speedRegulator ? d->speedRegulator->regulate() : 0;

    d->pub.publish(topics::controlPacket, packet.toByteArray());
}

void FlightControllerNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    if (topic == topics::insPacket)
    {
        InsPacket ins = InsPacket::fromByteArray(msg);
        if (d->pitchRegulator) d->pitchRegulator->setInputValue(ins.pitch);
        if (d->rollRegulator) d->rollRegulator->setInputValue(ins.roll);
        if (d->courseRegulator) d->courseRegulator->setInputValue(ins.yaw);
    }
    else if (topic == topics::snsPacket)
    {
        SnsPacket sns = SnsPacket::fromByteArray(msg);
        if (d->speedRegulator) d->speedRegulator->setInputValue(sns.groundSpeed);
        // TODO: airspeed
    }
    else if (topic == topics::directPacket)
    {
        DirectPacket direct = DirectPacket::fromByteArray(msg);

        if (direct.isManual)
        {
            if (d->pitchRegulator) d->pitchRegulator->setTargetValue(
                        direct.manual.targetPitch);
            if (d->rollRegulator) d->rollRegulator->setTargetValue(
                        direct.manual.targetRoll);
            if (d->courseRegulator) d->courseRegulator->setTargetValue(
                        direct.manual.targetCourse);
            if (d->speedRegulator) d->speedRegulator->setTargetValue(
                        direct.manual.targetSpeed);
        }
    }
}
