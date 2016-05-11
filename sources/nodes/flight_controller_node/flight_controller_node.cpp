#include "flight_controller_node.h"

// Qt
#include <QDebug>
#include <QScopedPointer>

// Internal
#include "config.h"
#include "core.h"

#include "subscriber.h"
#include "publisher.h"

#include "ins_packet.h"
#include "sns_packet.h"
#include "control_packet.h"

#include "flight_controller_node.h"
#include "regulator_factory.h"

using namespace domain;

//enum class FlightRegulatorType
//{
//    Unknown,
//    Throttle,
//    AirBrake
//    LeftAileron,
//    LeftElevon,
//    LeftDeceleron,
//    LeftFlap,
//    LeftFlaperon,
//    LeftSpoiler,
//    LeftVTail,
//    RightAileron,
//    RightElevon,
//    RightDeceleron,
//    RightFlap,
//    RightFlaperon,
//    RightSpoiler,
//    RightVTail,
//    Elevator,
//    Ruddler,
//};
//
//namespace
//{
//    // TODO: FlightRegulator factory
//    FlightRegulatorType typeFromString(const QString& type)
//    {
//        if (type == "throttle") return FlightRegulatorType::Throttle;
//        else if (type == "left_aileron") return FlightRegulatorType::LeftAileron;
//        else if (type == "left_elevon") return FlightRegulatorType::LeftElevon;
//        else if (type == "left_flap") return FlightRegulatorType::LeftFlap;
//        else if (type == "left_flaperon") return FlightRegulatorType::LeftFlaperon;
//        else if (type == "left_v_tail") return FlightRegulatorType::LeftVTail;
//        else if (type == "right_aileron") return FlightRegulatorType::RightAileron;
//        else if (type == "right_elevon") return FlightRegulatorType::RightElevon;
//        else if (type == "right_flap") return FlightRegulatorType::RightFlap;
//        else if (type == "right_flaperon") return FlightRegulatorType::RightFlaperon;
//        else if (type == "right_v_tail") return FlightRegulatorType::RightVTail;
//        else if (type == "elevator") return FlightRegulatorType::Elevator;
//        else if (type == "ruddler") return FlightRegulatorType::Ruddler;
//        else return FlightRegulatorType::Unknown;
//    }
//}

class FlightControllerNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    QScopedPointer<AbstractRegulator> pitchRegulator;
    QScopedPointer<AbstractRegulator> rollRegulator;
    QScopedPointer<AbstractRegulator> courseRegulator;
    QScopedPointer<AbstractRegulator> velocityRegulator;
};

FlightControllerNode::FlightControllerNode(QObject* parent):
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
    d->velocityRegulator.reset(factory.create(
                                Config::value("FlightController/velocity_regulator").toMap(),
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
    packet.velocityControl = d->velocityRegulator ? d->velocityRegulator->regulate() : 0;

    d->pub.publish(topics::controlPacket, packet.toByteArray());
}

void FlightControllerNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    // TODO: regulatos target value
    if (topic == topics::insPacket)
    {
        InsPacket ins = InsPacket::fromByteArray(msg);
        if (d->pitchRegulator) d->pitchRegulator->setInputValue(ins.pitch);
        if (d->rollRegulator) d->rollRegulator->setInputValue(ins.roll);
        if (d->courseRegulator) d->courseRegulator->setInputValue(ins.yaw);
    }

    if (topic == topics::snsPacket)
    {
        SnsPacket sns = SnsPacket::fromByteArray(msg);
        if (d->velocityRegulator) d->velocityRegulator->setInputValue(sns.groundSpeed);
        // TODO: airspeed
    }
}
