#ifndef NAVIGATOR_PACKET_H
#define NAVIGATOR_PACKET_H

#include "packet.h"

namespace domain
{
    class NavigatorPacket: public Packet
    {
    public:
        float course;
        float altitude;
        float velocity;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static NavigatorPacket fromByteArray(const QByteArray& data);
    };
}

#endif // NAVIGATOR_PACKET_H
