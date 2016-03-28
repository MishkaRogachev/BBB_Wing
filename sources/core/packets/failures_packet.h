#ifndef FAILURES_PACKET_H
#define FAILURES_PACKET_H

#include "packet.h"

namespace domain
{
    class FailuresPacket: public Packet
    {
    public:
        bool altStatus;
        bool insStatus;
        bool snsStatus;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static FailuresPacket fromByteArray(const QByteArray& data);
    };
}

#endif // FAILURES_PACKET_H
