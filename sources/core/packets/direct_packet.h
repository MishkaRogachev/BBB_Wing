#ifndef DIRECT_PACKET_H
#define DIRECT_PACKET_H

#include "control_packet.h"
#include "automatic_control_packet.h"

// Qt
#include <QMap>

namespace domain
{
    class DirectPacket: public Packet
    {
    public:
        bool isManual;

        ControlPacket manual;
        AutomaticControlPacket automatic;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static DirectPacket fromByteArray(const QByteArray& data);
    };
}

#endif // DIRECT_PACKET_H
