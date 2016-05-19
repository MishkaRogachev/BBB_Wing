#ifndef INIT_RESPONSE_PACKET_H
#define INIT_RESPONSE_PACKET_H

#include "packet.h"

namespace domain
{
    class InitResponsePacket: public Packet
    {
    public:
        quint16 homePointCrc;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static InitResponsePacket  fromByteArray(const QByteArray& data);
    };
}

#endif // INIT_RESPONSE_PACKET_H
