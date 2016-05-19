#include "init_response_packet.h"

using namespace domain;

QDataStream& InitResponsePacket::operator >>(QDataStream& stream) const
{
    stream << homePointCrc;

    return stream;
}

QDataStream& InitResponsePacket::operator <<(QDataStream& stream)
{
    stream >> homePointCrc;

    return stream;
}

InitResponsePacket InitResponsePacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    InitResponsePacket packet;
    stream >> packet;
    return packet;
}
