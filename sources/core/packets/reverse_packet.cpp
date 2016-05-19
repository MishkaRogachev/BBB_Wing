#include "reverse_packet.h"

using namespace domain;

void ReversePacket::reset()
{
    altAvalible = false;
    insAvalible = false;
    snsAvalible = false;
    controlAvalible = false;
}

QDataStream& ReversePacket::operator >>(QDataStream& stream) const
{
    stream << altAvalible;
    if (altAvalible) stream << alt;

    stream << insAvalible;
    if (altAvalible) stream << ins;

    stream << snsAvalible;
    if (altAvalible) stream << sns;

    stream << controlAvalible;
    if (controlAvalible) stream << control;

    return stream;
}

QDataStream& ReversePacket::operator <<(QDataStream& stream)
{
    stream >> altAvalible;
    if (altAvalible) stream >> alt;

    stream >> insAvalible;
    if (altAvalible) stream >> ins;

    stream >> snsAvalible;
    if (altAvalible) stream >> sns;

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
