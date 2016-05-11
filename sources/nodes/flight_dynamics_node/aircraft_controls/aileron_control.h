#ifndef AILERON_CONTROL_H
#define AILERON_CONTROL_H

#include "abstract_wing_control.h"

namespace domain
{
    class AileronControl: public AbstractWingControl
    {
    public:
        AileronControl(int channel, bool left, float rollFactor);

        float rollFactor() const;
        void setRollFactor(float rollFactor);

        float processControl(const ControlPacket& packet) override;

    protected:
        float m_rollFactor;
    };
}

#endif // AILERON_CONTROL_H
