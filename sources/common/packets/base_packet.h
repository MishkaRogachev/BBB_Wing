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
        BasePacket();

        PacketType type;
        quint16 crc;

        virtual QDataStream& operator >>(QDataStream& stream) const;
        virtual QDataStream& operator <<(QDataStream& stream);
    };

    inline QDataStream& operator <<(QDataStream& stream, const BasePacket& packet)
    {
        return (packet >> stream);
    }

    inline QDataStream& operator >>(QDataStream& stream, BasePacket& packet)
    {
        return (packet << stream);
    }
}

#endif // BASE_PACKET_H
