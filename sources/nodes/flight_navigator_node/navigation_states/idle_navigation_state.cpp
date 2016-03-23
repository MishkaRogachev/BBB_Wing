#include "idle_navigation_state.h"

// Internal
#include "publisher.h"
#include "topics.h"

using namespace domain;

IdleNavigationState::IdleNavigationState(Publisher* pub):
    AbstractNavigationState(pub)
{}

QString IdleNavigationState::stateId() const
{
    return "idle";
}

void IdleNavigationState::process()
{
    m_pub->publish(topics::controlPitch, QByteArray::number(0));
    m_pub->publish(topics::controlRoll, QByteArray::number(0));
    m_pub->publish(topics::controlVelocity, QByteArray::number(0));
}
