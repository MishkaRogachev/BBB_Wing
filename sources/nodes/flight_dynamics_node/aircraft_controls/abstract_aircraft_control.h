#ifndef ABSTRACT_AIRCRAFT_CONTROL_H
#define ABSTRACT_AIRCRAFT_CONTROL_H

#include "control_packet.h"

namespace domain
{
    class AbstractAircraftControl
    {
    public:
        AbstractAircraftControl(int channel = -1);
        virtual ~AbstractAircraftControl();

        int channel() const;
        void setChannel(int channel);

        virtual float processControl(const ControlPacket& packet) = 0;

    private:
        int m_channel;
    };
}

#endif // ABSTRACT_AIRCRAFT_CONTROL_H
