#include "automatic_control_packet.h"

using namespace domain;

QDataStream& AutomaticControlPacket::operator >>(QDataStream& stream) const
{
    stream << isAltitudeOverridden;
    if (isAltitudeOverridden) stream << overriddenAltitude;

    stream << isCourseOverridden;
    if (isAltitudeOverridden) stream << overriddenCourse;

    stream << isVelocityOverridden;
    if (isAltitudeOverridden) stream << overriddenVelocity;

    stream << activeProgram;
    stream << activePoint;

    return stream;
}

QDataStream& AutomaticControlPacket::operator <<(QDataStream& stream)
{
    stream >> isAltitudeOverridden;
    if (isAltitudeOverridden) stream >> overriddenAltitude;

    stream >> isCourseOverridden;
    if (isAltitudeOverridden) stream >> overriddenCourse;

    stream >> isVelocityOverridden;
    if (isAltitudeOverridden) stream >> overriddenVelocity;

    stream >> activeProgram;
    stream >> activePoint;

    return stream;
}

AutomaticControlPacket AutomaticControlPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    AutomaticControlPacket packet;
    stream >> packet;
    return packet;
}
