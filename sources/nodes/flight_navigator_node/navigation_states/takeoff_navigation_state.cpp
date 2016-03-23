#include "takeoff_navigation_state.h"

// Internal
#include "publisher.h"
#include "config.h"
#include "topics.h"

using namespace domain;

TakeoffNavigationState::TakeoffNavigationState(QObject* parent):
    AbstractNavigationState(parent)
{
    Config::begin("Navigator");

    m_takeoffPitch = Config::setting("takeoff_pitch").toFloat();
    m_takeoffRoll = Config::setting("takeoff_roll").toFloat();
    m_takeoffVelocity = Config::setting("takeoff_velocity").toFloat();
    m_takeoffAltitude = Config::setting("takeoff_altitude").toFloat();

    Config::end();
}

QString TakeoffNavigationState::stateId() const
{
    return "takeoff";
}

void TakeoffNavigationState::process()
{
    this->publish(topics::controlPitch, QByteArray::number(m_takeoffPitch));
    this->publish(topics::controlRoll, QByteArray::number(m_takeoffRoll));
    this->publish(topics::controlVelocity, QByteArray::number(m_takeoffVelocity));

    // TODO: if reached altitude request new state
}
