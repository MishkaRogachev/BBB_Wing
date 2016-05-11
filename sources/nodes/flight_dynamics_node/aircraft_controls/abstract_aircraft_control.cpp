#include "abstract_aircraft_control.h"

using namespace domain;

AbstractAircraftControl::AbstractAircraftControl(int channel):
    m_channel(channel)
{}

AbstractAircraftControl::~AbstractAircraftControl()
{}

int AbstractAircraftControl::channel() const
{
    return m_channel;
}

void AbstractAircraftControl::setChannel(int channel)
{
    m_channel = channel;
}
