#include "rudder_control.h"

using namespace domain;

RudderControl::RudderControl(int channel):
    AbstractAircraftControl(channel)
{}

float RudderControl::processControl(const ControlPacket& packet)
{
    return packet.courseControl;
}
