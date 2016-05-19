#include "init_request_packet.h"

using namespace domain;

QDataStream& InitRequestPacket::operator >>(QDataStream& stream) const
{
    stream << homePoint;

    return stream;
}

QDataStream& InitRequestPacket::operator <<(QDataStream& stream)
{
    stream >> homePoint;

    return stream;
}

InitRequestPacket InitRequestPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    InitRequestPacket packet;
    stream >> packet;
    return packet;
}
