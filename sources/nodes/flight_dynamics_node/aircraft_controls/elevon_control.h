#ifndef ELEVON_CONTROL_H
#define ELEVON_CONTROL_H

#include "aileron_control.h"
#include "elevator_control.h"

namespace domain
{
    class ElevonControl: public AileronControl, public ElevatorControl
    {
    public:
        ElevonControl(int channel, bool left, float rollFactor, float pitchFactor);

        float processControl(const ControlPacket& packet);

    };
}

#endif // ELEVON_CONTROL_H
