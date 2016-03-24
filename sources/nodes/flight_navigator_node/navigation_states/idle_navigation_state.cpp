#include "idle_navigation_state.h"

// Internal
#include "publisher.h"
#include "topics.h"

using namespace domain;

IdleNavigationState::IdleNavigationState(QObject* parent):
    AbstractNavigationState(parent)
{}

QString IdleNavigationState::stateId() const
{
    return "idle";
}

void IdleNavigationState::process()
{
    AbstractNavigationState::process();

    this->publish(topics::controlPitch, QByteArray::number(0));
    this->publish(topics::controlRoll, QByteArray::number(0));
    this->publish(topics::controlVelocity, QByteArray::number(0));
}
