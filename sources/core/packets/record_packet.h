#ifndef RECORD_PACKET_H
#define RECORD_PACKET_H

#include "packet.h"

// Qt
#include <QTime>

namespace domain
{
    class RecordPacket: public Packet
    {
    public:
        RecordPacket();
        RecordPacket(const QString& topic, const QByteArray& data);

        QString topic;
        QByteArray data;
        QTime timeStamp;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static RecordPacket fromByteArray(const QByteArray& data);
    };
}

#endif // RECORD_PACKET_H
