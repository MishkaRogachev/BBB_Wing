#include "connection_status_packet.h"

using namespace domain;

QDataStream& ConnectionStatusPacket::operator >>(QDataStream& stream) const
{
    stream << airLink;
    stream << wireLink;
    stream << packetsPerSecond;
    stream << packetsLost;

    return stream;
}

QDataStream& ConnectionStatusPacket::operator <<(QDataStream& stream)
{
    stream >> airLink;
    stream >> wireLink;
    stream >> packetsPerSecond;
    stream >> packetsLost;

    return stream;
}

ConnectionStatusPacket ConnectionStatusPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    ConnectionStatusPacket packet;
    stream >> packet;
    return packet;
}
