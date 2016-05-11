#include "elevator_control.h"

using namespace domain;

ElevatorControl::ElevatorControl(int channel, float pitchFactor):
    AbstractAircraftControl(channel)
{}

float ElevatorControl::pitchFactor() const
{
    return m_pitchFactor;
}

void ElevatorControl::setPitchFactor(float pitchFactor)
{
    m_pitchFactor = pitchFactor;
}

float ElevatorControl::processControl(const ControlPacket& packet)
{
    return m_pitchFactor * packet.pitchControl;
}
