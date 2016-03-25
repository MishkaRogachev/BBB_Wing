#include "sns_packet.h"

using namespace domain;

QDataStream& SnsPacket::operator >>(QDataStream& stream) const
{
    stream << fix;

    stream << latitude;
    stream << longitude;
    stream << velocity;
    stream << yaw;

    stream << altitude;
    stream << climb;

    return stream;
}

QDataStream& SnsPacket::operator <<(QDataStream& stream)
{
    stream >> fix;

    stream >> latitude;
    stream >> longitude;
    stream >> velocity;
    stream >> yaw;

    stream >> altitude;
    stream >> climb;

    return stream;
}

SnsPacket SnsPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    SnsPacket packet;
    stream >> packet;
    return packet;
}
