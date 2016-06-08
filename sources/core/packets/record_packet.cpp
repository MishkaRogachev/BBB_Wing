#include "record_packet.h"

using namespace domain;

RecordPacket::RecordPacket()
{}

RecordPacket::RecordPacket(const QString& topic, const QByteArray& data):
    topic(topic),
    data(data),
    timeStamp(QTime::currentTime())
{}

QDataStream& RecordPacket::operator >>(QDataStream& stream) const
{
    stream << topic;
    stream << data;
    stream << timeStamp;

    return stream;
}

QDataStream& RecordPacket::operator <<(QDataStream& stream)
{
    stream >> topic;
    stream >> data;
    stream >> timeStamp;

    return stream;
}

RecordPacket RecordPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    RecordPacket packet;
    stream >> packet;
    return packet;
}
