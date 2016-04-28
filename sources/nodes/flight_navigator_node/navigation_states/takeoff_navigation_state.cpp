#include "takeoff_navigation_state.h"

// Internal
#include "publisher.h"
#include "config.h"
#include "core.h"

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

    // TODO: StabilizationState
    //if (m_data->altimeterAltitude > m_takeoffAltitude)
    //    emit requestNewState(new StabilizationState(*this));
}
