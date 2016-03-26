#ifndef ALT_PACKET_H
#define ALT_PACKET_H

#include "packet.h"

namespace domain
{
    class AltPacket: public Packet
    {
    public:
        float altitude;
        float temperature;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static AltPacket fromByteArray(const QByteArray& data);
    };
}

#endif // ALT_PACKET_H
