#include "crc_packet.h"

using namespace domain;

CrcPacket::CrcPacket()
{}

CrcPacket::CrcPacket(const QString& topic, const QByteArray& data):
    topic(topic),
    data(data),
    timeStamp(QTime::currentTime())
{
    this->calcCrc();
}

bool CrcPacket::validateCrc()
{
    return crc == qChecksum(data.data(), data.length());
}

void CrcPacket::calcCrc()
{
    crc = qChecksum(data.data(), data.length());
}

QDataStream& CrcPacket::operator >>(QDataStream& stream) const
{
    stream << topic;
    stream << data;
    stream << timeStamp;
    stream << crc;

    return stream;
}

QDataStream& CrcPacket::operator <<(QDataStream& stream)
{
    stream >> topic;
    stream >> data;
    stream >> timeStamp;
    stream >> crc;

    return stream;
}

CrcPacket CrcPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    CrcPacket packet;
    stream >> packet;
    return packet;
}
