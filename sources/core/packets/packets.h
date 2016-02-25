#ifndef BASE_PACKET_H
#define BASE_PACKET_H

// Qt
#include <QDataStream>

namespace domain
{
    class Packet
    {
    public:
        virtual QDataStream& operator >>(QDataStream& stream) const = 0;
        virtual QDataStream& operator <<(QDataStream& stream) = 0;
    };

    class DataPacket: public Packet
    {
    public:
        virtual quint16 calcCrc() const;
    };

    inline QDataStream& operator <<(QDataStream& stream, const Packet& packet)
    {
        return (packet >> stream);
    }

    inline QDataStream& operator >>(QDataStream& stream, Packet& packet)
    {
        return (packet << stream);
    }
}

#endif // BASE_PACKET_H
