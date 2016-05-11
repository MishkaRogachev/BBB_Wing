#ifndef THROTTLE_CONTROL_H
#define THROTTLE_CONTROL_H

#include "abstract_aircraft_control.h"

namespace domain
{
    class ThrottleControl: public AbstractAircraftControl
    {
    public:
        ThrottleControl(int channel);

        float processControl(const ControlPacket& packet);
    };
}

#endif // THROTTLE_CONTROL_H
