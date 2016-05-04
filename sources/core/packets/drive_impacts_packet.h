#ifndef DRIVE_IMPACTS_PACKET_H
#define DRIVE_IMPACTS_PACKET_H

#include "packet.h"

// Qt
#include <QMap>

namespace domain // TODO: namespaces to node layers
{
    using DriveImpacts = QMap<int, float>;

    class DriveImpactsPacket: public Packet
    {
    public:
        DriveImpacts impacts;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static DriveImpactsPacket fromByteArray(const QByteArray& data);
    };
}

#endif // DRIVE_IMPACTS_PACKET_H
