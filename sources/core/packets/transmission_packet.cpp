#include "transmission_packet.h"

using namespace domain;

bool TransmissionPacket::validateCrc()
{
    return crc == qChecksum(data.data(), data.length());
}

void TransmissionPacket::calcCrc()
{
    crc = qChecksum(data.data(), data.length());
}

QDataStream& TransmissionPacket::operator >>(QDataStream& stream) const
{
    stream << topic;
    stream << data;
    stream << crc;

    return stream;
}

QDataStream& TransmissionPacket::operator <<(QDataStream& stream)
{
    stream >> topic;
    stream >> data;
    stream >> crc;

    return stream;
}

TransmissionPacket TransmissionPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    TransmissionPacket packet;
    stream >> packet;
    return packet;
}
