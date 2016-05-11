#include "aileron_control.h"

using namespace domain;

AileronControl::AileronControl(int channel, bool left, float rollFactor):
    AbstractWingControl(channel, left),
    m_rollFactor(rollFactor)
{}

float AileronControl::rollFactor() const
{
    return m_rollFactor;
}

void AileronControl::setRollFactor(float rollFactor)
{
    m_rollFactor = rollFactor;
}

float AileronControl::processControl(const ControlPacket& packet)
{
    return m_left ? -m_rollFactor * packet.rollControl :
                     m_rollFactor * packet.rollControl;
}
