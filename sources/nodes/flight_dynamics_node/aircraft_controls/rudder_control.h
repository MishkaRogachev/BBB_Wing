#ifndef RUDDER_CONTROL_H
#define RUDDER_CONTROL_H

#include "abstract_aircraft_control.h"

namespace domain
{
    class RudderControl: public AbstractAircraftControl
    {
    public:
        RudderControl(int channel);

        float processControl(const ControlPacket& packet);
    };
}

#endif // RUDDER_CONTROL_H
