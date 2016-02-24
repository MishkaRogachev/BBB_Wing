#include "base_packet.h"

using namespace domain;

QDataStream& operator <<(QDataStream& stream, const BasePacket& packet)
{
    stream << static_cast<int>(packet.type);
    stream << packet.crc;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, BasePacket& packet)
{
    int type;
    stream >> type;
    packet.type = static_cast<PacketType>(type);
    stream >> packet.crc;
    return stream;
}
