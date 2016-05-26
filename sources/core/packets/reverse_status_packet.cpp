#include "reverse_status_packet.h"

using namespace domain;

QDataStream& ReverseStatusPacket::operator >>(QDataStream& stream) const
{
    stream << altAvalible;
    stream << insAvalible;
    stream << snsAvalible;
    stream << controlAvalible;

    return stream;
}

QDataStream& ReverseStatusPacket::operator <<(QDataStream& stream)
{
    stream >> altAvalible;
    stream >> insAvalible;
    stream >> snsAvalible;
    stream >> controlAvalible;

    return stream;
}

ReverseStatusPacket ReverseStatusPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    ReverseStatusPacket packet;
    stream >> packet;
    return packet;
}
