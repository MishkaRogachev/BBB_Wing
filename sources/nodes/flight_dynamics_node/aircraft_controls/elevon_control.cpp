#include "elevon_control.h"

using namespace domain;

ElevonControl::ElevonControl(int channel, bool left,
                             float rollFactor, float pitchFactor):
    AileronControl(channel, left, rollFactor),
    ElevatorControl(channel, pitchFactor)
{
    this->setChannel(channel); // virtual inheritance use default constructor
}

float ElevonControl::processControl(const ControlPacket& packet)
{
    return AileronControl::processControl(packet) +
            ElevatorControl::processControl(packet);
}
