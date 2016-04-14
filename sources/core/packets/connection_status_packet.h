#ifndef CONNECTION_STATUS_PACKET_H
#define CONNECTION_STATUS_PACKET_H

#include "packet.h"

namespace domain
{
    class ConnectionStatusPacket: public Packet
    {
    public:
        bool airLink;
        bool wireLink;
        int packetsPerSecond;
        int packetsLost;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static ConnectionStatusPacket fromByteArray(const QByteArray& data);
    };
}

#endif // CONNECTION_STATUS_PACKET_H
