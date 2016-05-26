#ifndef REVERSE_STATUS_PACKET_H
#define REVERSE_STATUS_PACKET_H

#include "packet.h"

namespace domain
{
    class ReverseStatusPacket: public Packet
    {
    public:
        bool altAvalible;
        bool insAvalible;
        bool snsAvalible;
        bool controlAvalible;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static ReverseStatusPacket fromByteArray(const QByteArray& data);
    };
}

#endif // REVERSE_STATUS_PACKET_H
