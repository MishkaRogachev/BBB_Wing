#ifndef FLIGHT_PROGRAM_PACKET_H
#define FLIGHT_PROGRAM_PACKET_H

#include "flight_point_packet.h"

namespace domain
{
    class FlightProgramPacket: public Packet
    {
    public:
        QList<FlightPointPacket> points;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static FlightProgramPacket fromByteArray(const QByteArray& data);
    };
}

#endif // FLIGHT_PROGRAM_PACKET_H
