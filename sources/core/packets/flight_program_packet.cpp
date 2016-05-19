#include "flight_program_packet.h"

using namespace domain;

QDataStream& FlightProgramPacket::operator >>(QDataStream& stream) const
{
    stream << points.count();
    for (int i = 0; i < points.count(); ++i)
        stream << points[i];

    return stream;
}

QDataStream& FlightProgramPacket::operator <<(QDataStream& stream)
{
    int count;
    stream >> count;
    for (int i = 0; i < count; ++i)
    {
        FlightPointPacket point;
        stream >> point;
        points.append(point);
    }

    return stream;
}

FlightProgramPacket FlightProgramPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    FlightProgramPacket packet;
    stream >> packet;
    return packet;
}
