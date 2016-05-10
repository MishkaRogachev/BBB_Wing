#include "flight_regulator.h"

using namespace domain;

namespace
{
    // TODO: FlightRegulator factory
    FlightRegulatorType typeFromString(const QString& type)
    {
        if (type == "throttle") return FlightRegulatorType::Throttle;
        else if (type == "left_aileron") return FlightRegulatorType::LeftAileron;
        else if (type == "left_elevon") return FlightRegulatorType::LeftElevon;
        else if (type == "left_flap") return FlightRegulatorType::LeftFlap;
        else if (type == "left_flaperon") return FlightRegulatorType::LeftFlaperon;
        else if (type == "left_v_tail") return FlightRegulatorType::LeftVTail;
        else if (type == "right_aileron") return FlightRegulatorType::RightAileron;
        else if (type == "right_elevon") return FlightRegulatorType::RightElevon;
        else if (type == "right_flap") return FlightRegulatorType::RightFlap;
        else if (type == "right_flaperon") return FlightRegulatorType::RightFlaperon;
        else if (type == "right_v_tail") return FlightRegulatorType::RightVTail;
        else if (type == "elevator") return FlightRegulatorType::Elevator;
        else if (type == "ruddler") return FlightRegulatorType::Ruddler;
        else return FlightRegulatorType::Unknown;
    }
}

FlightRegulator::FlightRegulator(const QVariantMap& map):
    PidRegulator(map.value("proportional").toFloat(),
                 map.value("integral").toFloat(),
                 map.value("derivative").toFloat(),
                 map.value("lower_bound").toFloat(),
                 map.value("upper_bound").toFloat(),
                 map.value("error_threshold").toFloat()),
    m_type(::typeFromString(map.value("type").toString())),
    m_channel(map.value("type").toInt())
{}

FlightRegulatorType FlightRegulator::type() const
{
    return m_type;
}

int FlightRegulator::channel() const
{
    return m_channel;
}
