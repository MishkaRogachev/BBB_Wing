#ifndef INIT_REQUEST_PACKET_H
#define INIT_REQUEST_PACKET_H

#include "flight_point_packet.h"

namespace domain
{
    class InitRequestPacket: public Packet
    {
    public:
        FlightPointPacket homePoint;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static InitRequestPacket fromByteArray(const QByteArray& data);
    };
}

#endif // INIT_REQUEST_PACKET_H
