#ifndef FLIGHT_CONTROL_PACKET_H
#define FLIGHT_CONTROL_PACKET_H

#include "packets.h"

namespace domain
{
    class FlightControlPacket: public Packet
    {
    public:
        float pitch;
        float roll;
        float velocity;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static FlightControlPacket fromByteArray(const QByteArray& data);
    };
}

#endif // FLIGHT_CONTROL_PACKET_H
