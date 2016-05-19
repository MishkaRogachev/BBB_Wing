#include "flight_point_packet.h"

using namespace domain;

FlightPointPacket::FlightPointPacket(
        double latitude, double longitude, float altitude):
    latitude(latitude),
    longitude(longitude),
    altitude(altitude)
{}

QDataStream& FlightPointPacket::operator >>(QDataStream& stream) const
{
    stream << latitude;
    stream << longitude;
    stream << altitude;

    return stream;
}

QDataStream& FlightPointPacket::operator <<(QDataStream& stream)
{
    stream >> latitude;
    stream >> longitude;
    stream >> altitude;

    return stream;
}

FlightPointPacket FlightPointPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    FlightPointPacket packet;
    stream >> packet;
    return packet;
}
