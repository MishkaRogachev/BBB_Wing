#include "navigator_packet.h"

using namespace domain;

QDataStream& NavigatorPacket::operator >>(QDataStream& stream) const
{
    stream << course;
    stream << altitude;
    stream << velocity;

    return stream;
}

QDataStream& NavigatorPacket::operator <<(QDataStream& stream)
{
    stream >> course;
    stream >> altitude;
    stream >> velocity;

    return stream;
}

NavigatorPacket NavigatorPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    NavigatorPacket packet;
    stream >> packet;
    return packet;
}
