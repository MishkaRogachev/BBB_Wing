#include "connection_status_packet.h"

using namespace domain;

QDataStream& ConnectionStatusPacket::operator >>(QDataStream& stream) const
{
    stream << static_cast<int>(line);
    stream << packetsPerSecond;
    stream << badPackets;

    return stream;
}

QDataStream& ConnectionStatusPacket::operator <<(QDataStream& stream)
{
    int lineType;

    stream >> lineType;
    stream >> packetsPerSecond;
    stream >> badPackets;

    line = static_cast<ConnectionLine>(lineType);

    return stream;
}

ConnectionStatusPacket ConnectionStatusPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    ConnectionStatusPacket packet;
    stream >> packet;
    return packet;
}
