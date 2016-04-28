#include "direct_packet.h"

using namespace domain;

QDataStream& DirectPacket::operator >>(QDataStream& stream) const
{
    stream << manual.deviationX;
    stream << manual.deviationY;
    stream << manual.deviationZ;

    return stream;
}

QDataStream& DirectPacket::operator <<(QDataStream& stream)
{
    stream >> manual.deviationX;
    stream >> manual.deviationY;
    stream >> manual.deviationZ;

    return stream;
}

DirectPacket DirectPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    DirectPacket packet;
    stream >> packet;
    return packet;
}
