#ifndef DIRECTPACKET_H
#define DIRECTPACKET_H

#include "packet.h"

namespace domain
{
    class DirectPacket : public Packet
    {
    public:
        // bool isManual; TODO: manual/automatic

        struct Manual
        {
            float deviationX = 0.0;
            float deviationY = 0.0;
            float deviationZ = 0.0;
        } manual;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static DirectPacket fromByteArray(const QByteArray& data);
    };
}

#endif // DIRECTPACKET_H
