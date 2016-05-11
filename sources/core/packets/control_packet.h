#ifndef CONTROL_PACKET_H
#define CONTROL_PACKET_H

#include "packet.h"

namespace domain
{
    class ControlPacket: public Packet
    {
    public:
        float pitchControl; // lateral
        float rollControl; // longitudinal
        float courseControl; // vertical
        float velocityControl;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static ControlPacket fromByteArray(const QByteArray& data);
    };
}


#endif // CONTROL_PACKET_H
