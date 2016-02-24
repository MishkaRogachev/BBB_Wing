#include "base_packet.h"

using namespace domain;
/*
QDataStream& BasePacket::operator >>(QDataStream& stream)
{
//    stream >> static_cast<int>(type);
    stream >> crc;
    return stream;
}

QDataStream& BasePacket::operator <<(QDataStream& stream)
{
//    stream << static_cast<int>(type);
    stream << crc;
    return stream;
}

QDataStream& operator <<(QDataStream& stream, BasePacket& packet)
{
    return (packet << stream);
}

QDataStream& operator >>(QDataStream& stream, BasePacket& packet)
{
    return (packet >> stream);
}

*/
