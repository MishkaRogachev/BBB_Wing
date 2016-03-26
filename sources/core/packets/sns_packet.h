#ifndef SNS_PACKET_H
#define SNS_PACKET_H

#include "packet.h"

namespace domain
{
    class SnsPacket: public Packet
    {
    public:
        short fix;

        double latitude;
        double longitude;
        float velocity;
        float yaw;

        float altitude;
        float climb;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static SnsPacket fromByteArray(const QByteArray& data);
    };
}

#endif // SNS_PACKET_H
