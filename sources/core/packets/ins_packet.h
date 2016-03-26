#ifndef INS_PACKET_H
#define INS_PACKET_H

#include "packet.h"

namespace domain
{
    class InsPacket: public Packet
    {
    public:
        float pitch;
        float roll;
        float yaw;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static InsPacket fromByteArray(const QByteArray& data);
    };
}

#endif // INS_PACKET_H
