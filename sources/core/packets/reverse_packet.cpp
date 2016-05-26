#include "reverse_packet.h"

using namespace domain;

ReverseStatusPacket ReversePacket::status() const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    ReverseStatusPacket::operator >>(stream);
    return ReverseStatusPacket::fromByteArray(data);
}

QDataStream& ReversePacket::operator >>(QDataStream& stream) const
{
    stream << altAvalible;
    if (altAvalible) stream << alt;

    stream << insAvalible;
    if (insAvalible) stream << ins;

    stream << snsAvalible;
    if (snsAvalible) stream << sns;

    stream << controlAvalible;
    if (controlAvalible) stream << control;

    return stream;
}

QDataStream& ReversePacket::operator <<(QDataStream& stream)
{
    stream >> altAvalible;
    if (altAvalible) stream >> alt;

    stream >> insAvalible;
    if (insAvalible) stream >> ins;

    stream >> snsAvalible;
    if (snsAvalible) stream >> sns;

    stream >> controlAvalible;
    if (controlAvalible) stream >> control;

    return stream;
}

ReversePacket ReversePacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    ReversePacket packet;
    stream >> packet;
    return packet;
}
