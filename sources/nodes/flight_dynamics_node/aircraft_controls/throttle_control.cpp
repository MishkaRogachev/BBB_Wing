#include "throttle_control.h"

using namespace domain;

ThrottleControl::ThrottleControl(int channel):
    AbstractAircraftControl(channel)
{}

float ThrottleControl::processControl(const ControlPacket& packet)
{
    return packet.speedControl;
}

