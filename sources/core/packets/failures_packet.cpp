#include "failures_packet.h"

using namespace domain;

QDataStream& FailuresPacket::operator >>(QDataStream& stream) const
{
    stream << altStatus;
    stream << insStatus;
    stream << snsStatus;

    return stream;
}

QDataStream& FailuresPacket::operator <<(QDataStream& stream)
{
    stream >> altStatus;
    stream >> insStatus;
    stream >> snsStatus;

    return stream;
}

FailuresPacket FailuresPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    FailuresPacket packet;
    stream >> packet;
    return packet;
}
