#ifndef CONNECTION_STATUS_PACKET_H
#define CONNECTION_STATUS_PACKET_H

#include "packets.h"

namespace domain
{
    class ConnectionStatusPacket: public Packet
    {
    public:
        bool airLine;
        bool wireLine;
        int packetsPerSecond;
        int badPackets;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static ConnectionStatusPacket fromByteArray(const QByteArray& data);
    };
}

#endif // CONNECTION_STATUS_PACKET_H
