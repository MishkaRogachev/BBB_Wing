#include "connection_status_packet.h"

using namespace domain;

QDataStream& ConnectionStatusPacket::operator >>(QDataStream& stream) const
{
    stream << airLine;
    stream << wireLine;
    stream << packetsPerSecond;
    stream << badPackets;

    return stream;
}

QDataStream& ConnectionStatusPacket::operator <<(QDataStream& stream)
{
    stream >> airLine;
    stream >> wireLine;
    stream >> packetsPerSecond;
    stream >> badPackets;

    return stream;
}

ConnectionStatusPacket ConnectionStatusPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    ConnectionStatusPacket packet;
    stream >> packet;
    return packet;
}
