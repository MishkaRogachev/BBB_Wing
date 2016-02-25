#include "board_packet.h"

using namespace domain;

bool BoardPacket::validateCrc()
{
    return crc == data.calcCrc();
}

void BoardPacket::calcCrc()
{
    crc = data.calcCrc();
}

QDataStream& BoardPacket::operator >>(QDataStream& stream) const
{
    stream << crc;
    stream << data;
    return stream;
}

QDataStream& BoardPacket::operator <<(QDataStream& stream)
{
    stream >> crc;
    stream >> data;
    return stream;
}

QDataStream& BoardPacket::BoardDataPacket::operator >>(QDataStream& stream) const
{
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

QDataStream& BoardPacket::BoardDataPacket::operator <<(QDataStream& stream)
{
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
