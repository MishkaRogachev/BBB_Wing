#include "base_packet.h"

using namespace domain;

BasePacket::BasePacket():
    type(PacketType::Base),
    crc(0)
{}

QDataStream& BasePacket::operator >>(QDataStream& stream) const
{
//    int intType = 0;
//    stream >> intType;
//    type = static_cast<PacketType>(intType);

    stream << crc;
    return stream;
}

QDataStream& BasePacket::operator <<(QDataStream& stream)
{
//    stream << static_cast<int>(type);
    stream >> crc;
    return stream;
}
