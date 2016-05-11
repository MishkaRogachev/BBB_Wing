#include "abstract_wing_control.h"

using namespace domain;

AbstractWingControl::AbstractWingControl(int channel, bool left):
    AbstractAircraftControl(channel),
    m_left(left)
{}

bool AbstractWingControl::left() const
{
    return m_left;
}

void AbstractWingControl::setLeft(bool left)
{
    m_left = left;
}
