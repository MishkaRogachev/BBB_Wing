#ifndef SNS_PACKET_H
#define SNS_PACKET_H

#include "packet.h"

namespace domain
{
    class SnsPacket: public Packet
    {
    public:
        bool status;
        short fix;

        struct
        {
            double latitude;
            double longitude;
            float groundSpeed;
            float yaw;
        } fix2d;

        struct
        {
            float altitude;
            float climb;
        } fix3d;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static SnsPacket fromByteArray(const QByteArray& data);
    };
}

#endif // SNS_PACKET_H
