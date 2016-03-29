#include "idle_navigation_state.h"

// Internal
#include "publisher.h"
#include "core.h"

#include "flight_control_packet.h"

using namespace domain;

IdleNavigationState::IdleNavigationState(QObject* parent):
    AbstractNavigationState(new NavigationStateData(), parent)
{}

QString IdleNavigationState::stateId() const
{
    return "idle";
}

void IdleNavigationState::process()
{
    AbstractNavigationState::process();

    FlightControlPacket packet;

    packet.pitch = 0.0;
    packet.roll = 0.0;
    packet.velocity = 0.0;

    this->publish(topics::flightCtrlPacket, packet.toByteArray());
}
