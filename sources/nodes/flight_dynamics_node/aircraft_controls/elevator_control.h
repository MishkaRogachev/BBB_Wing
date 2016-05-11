#ifndef ELEVATOR_CONTROL_H
#define ELEVATOR_CONTROL_H

#include "abstract_aircraft_control.h"

namespace domain
{
    class ElevatorControl: virtual public AbstractAircraftControl
    {
    public:
        ElevatorControl(int channel, float pitchFactor);

        float pitchFactor() const;
        void setPitchFactor(float pitchFactor);

        float processControl(const ControlPacket& packet);

    protected:
        float m_pitchFactor;
    };
}

#endif // ELEVATOR_CONTROL_H
