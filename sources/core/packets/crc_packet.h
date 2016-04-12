#ifndef CRC_PACKET_H
#define CRC_PACKET_H

#include "packet.h"

// Qt
#include <QTime>

namespace domain
{
    class CrcPacket: public Packet
    {
    public:
        QString topic;
        QByteArray data;
        QTime timeStamp;
        quint16 crc;

        bool validateCrc();
        void calcCrc();

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static CrcPacket fromByteArray(const QByteArray& data);
    };
}

#endif // CRC_PACKET_H
