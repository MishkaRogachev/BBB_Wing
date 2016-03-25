#ifndef CONNECTION_STATUS_PACKET_H
#define CONNECTION_STATUS_PACKET_H

#include "packets.h"

namespace domain
{
    enum class ConnectionLine
    {
        None,
        Wire,
        Air
    };

    class ConnectionStatusPacket: public Packet
    {
    public:
        ConnectionLine line;
        int packetsPerSecond;
        int badPackets;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static ConnectionStatusPacket fromByteArray(const QByteArray& data);
    };
}

#endif // CONNECTION_STATUS_PACKET_H
