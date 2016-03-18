#ifndef GROUND_PACKET_H
#define GROUND_PACKET_H

#include "packets.h"

namespace domain
{
    class GroundDataPacket: public Packet
    {
    public:
        bool isManual;

        struct ManualPacket
        {
            float setPitch;
            float setRoll;
            short setThrottle;
        };

        struct AutomaticPacket
        {
            quint16 activeProgram;
            short activePoint;

            bool isYawOverriden;
            float overridenYaw;
            bool isAltitudeOverriden;
            float overridenAltitude;
            bool isVelocityOverriden;
            float overridenVelocity;
        };

        union
        {
            ManualPacket manual;
            AutomaticPacket automatic;
        };

        quint16 crc();

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;
    };

    using GroundPacket = DataPacket<GroundDataPacket>;
}

#endif // GROUND_PACKET_H
