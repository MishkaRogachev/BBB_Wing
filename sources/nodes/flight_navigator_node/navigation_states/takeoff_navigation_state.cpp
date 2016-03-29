#include "takeoff_navigation_state.h"

// Internal
#include "publisher.h"
#include "config.h"
#include "core.h"

#include "flight_control_packet.h"

using namespace domain;

TakeoffNavigationState::TakeoffNavigationState(AbstractNavigationState&& other):
    AbstractNavigationState(other.m_data.take(), other.parent())
{
    Config::begin("FlightNavigator");

    m_takeoffPitch = Config::value("takeoff_pitch").toFloat();
    m_takeoffRoll = Config::value("takeoff_roll").toFloat();
    m_takeoffVelocity = Config::value("takeoff_velocity").toFloat();
    m_takeoffAltitude = Config::value("takeoff_altitude").toFloat();

    Config::end();
}

QString TakeoffNavigationState::stateId() const
{
    return "takeoff";
}

void TakeoffNavigationState::process()
{
    AbstractNavigationState::process();

    FlightControlPacket packet;

    packet.pitch = m_takeoffPitch;
    packet.roll = m_takeoffRoll;
    packet.velocity = m_takeoffVelocity;

    this->publish(topics::flightCtrlPacket, packet.toByteArray());

    // TODO: StabilizationState
    //if (m_data->altimeterAltitude > m_takeoffAltitude)
    //    emit requestNewState(new StabilizationState(*this));
}
