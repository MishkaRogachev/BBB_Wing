#include "drive_impacts_packet.h"

using namespace domain;

QDataStream& DriveImpactsPacket::operator >>(QDataStream& stream) const
{
    stream << impacts;

    return stream;
}

QDataStream& DriveImpactsPacket::operator <<(QDataStream& stream)
{
    stream >> impacts;

    return stream;
}

DriveImpactsPacket DriveImpactsPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    DriveImpactsPacket packet;
    stream >> packet;
    return packet;
}
