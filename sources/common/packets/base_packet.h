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

        inline virtual QDataStream& operator >>(QDataStream& stream)
        {
        //    stream >> static_cast<int>(type);
            stream >> crc;
            return stream;
        }
        inline virtual QDataStream& operator <<(QDataStream& stream)
        {
            //    stream << static_cast<int>(type);
            stream << crc;
            return stream;
        }
    };

    inline QDataStream& operator <<(QDataStream& stream, BasePacket& packet)
    {
        return (packet << stream);
    }
    inline QDataStream& operator >>(QDataStream& stream, BasePacket& packet)
    {
        return (packet >> stream);
    }
}

#endif // BASE_PACKET_H
