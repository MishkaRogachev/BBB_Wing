#include "control_packet.h"

using namespace domain;

QDataStream& ControlPacket::operator >>(QDataStream& stream) const
{
    stream << pitchControl;
    stream << rollControl;
    stream << courseControl;
    stream << speedControl;

    return stream;
}

QDataStream& ControlPacket::operator <<(QDataStream& stream)
{
    stream >> pitchControl;
    stream >> rollControl;
    stream >> courseControl;
    stream >> speedControl;

    return stream;
}

ControlPacket ControlPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    ControlPacket packet;
    stream >> packet;
    return packet;
}
