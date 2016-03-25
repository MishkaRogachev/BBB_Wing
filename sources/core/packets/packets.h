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

        QByteArray toByteArray();
    };

    template< class T >
    class DataPacket: public Packet
    {
    public:
        T data;
        quint16 crc;

        bool validateCrc();
        void calcCrc();

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;
    };

    inline QDataStream& operator <<(QDataStream& stream, const Packet& packet)
    {
        return (packet >> stream);
    }

    inline QDataStream& operator >>(QDataStream& stream, Packet& packet)
    {
        return (packet << stream);
    }

    template< class T >
    bool DataPacket<T>::validateCrc()
    {
        return crc == data.crc();
    }

    template< class T >
    void DataPacket<T>::calcCrc()
    {
        crc = data.crc();
    }

    template< class T >
    QDataStream& DataPacket<T>::operator >>(QDataStream& stream) const
    {
        stream << crc;
        stream << data;
        return stream;
    }

    template< class T >
    QDataStream& DataPacket<T>::operator <<(QDataStream& stream)
    {
        stream >> crc;
        stream >> data;
        return stream;
    }
}

#endif // BASE_PACKET_H
