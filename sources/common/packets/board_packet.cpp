#include "board_packet.h"

using namespace domain;

QDataStream& BoardPacket::operator >>(QDataStream& stream) const
{
    BasePacket::operator >>(stream);

    stream << latitude;
    stream << longitude;
    stream << altitude;

    stream << velocity;
    stream << climb;

    stream << pitch;
    stream << roll;
    stream << yaw;

    stream << temperature;

    stream << altimeterStatus;
    stream << insStatus;
    stream << snsStatus;

    return stream;
}

QDataStream& BoardPacket::operator <<(QDataStream& stream)
{
    BasePacket::operator <<(stream);

    stream >> latitude;
    stream >> longitude;
    stream >> altitude;

    stream >> velocity;
    stream >> climb;

    stream >> pitch;
    stream >> roll;
    stream >> yaw;

    stream >> temperature;

    stream >> altimeterStatus;
    stream >> insStatus;
    stream >> snsStatus;

    return stream;
}
