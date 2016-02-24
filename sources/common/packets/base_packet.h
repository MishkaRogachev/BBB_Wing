#ifndef BASE_PACKET_H
#define BASE_PACKET_H

// Qt
#include <QDataStream>

namespace domain
{
    enum class PacketType
    {
        Base,
        Board
    };

    struct BasePacket
    {
        PacketType type;
        quint16 crc;
    };

    QDataStream& operator <<(QDataStream& stream, const BasePacket& packet);
    QDataStream& operator >>(QDataStream& stream, BasePacket& packet);
}

#endif // BASE_PACKET_H
