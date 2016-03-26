#include "flight_control_packet.h"

using namespace domain;

QDataStream& FlightControlPacket::operator >>(QDataStream& stream) const
{
    stream << pitch;
    stream << roll;
    stream << velocity;

    return stream;
}

QDataStream& FlightControlPacket::operator <<(QDataStream& stream)
{
    stream >> pitch;
    stream >> roll;
    stream >> velocity;

    return stream;
}

FlightControlPacket FlightControlPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    FlightControlPacket packet;
    stream >> packet;
    return packet;
}
