#ifndef TRANSMISSION_PACKET_H
#define TRANSMISSION_PACKET_H

#include "packet.h"

namespace domain
{
    class TransmissionPacket: public Packet
    {
    public:
        QString topic;
        QByteArray data;
        quint16 crc;

        bool validateCrc();
        void calcCrc();

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static TransmissionPacket fromByteArray(const QByteArray& data);
    };
}

#endif // TRANSMISSION_PACKET_H
