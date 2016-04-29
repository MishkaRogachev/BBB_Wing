#ifndef DIRECT_PACKET_H
#define DIRECT_PACKET_H

#include "packet.h"

// Qt
#include <QMap>

namespace domain
{
    class DirectPacket: public Packet
    {
    public:
        // bool isManual; TODO: manual/automatic

        struct Manual
        {
            QMap<int, float> deviations;
        } manual;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static DirectPacket fromByteArray(const QByteArray& data);
    };
}

#endif // DIRECT_PACKET_H
