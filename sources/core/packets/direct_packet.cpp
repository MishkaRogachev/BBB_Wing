#include "direct_packet.h"

using namespace domain;

QDataStream& DirectPacket::operator >>(QDataStream& stream) const
{
    stream << isManual;

    if (isManual)
    {
        stream << manual.targetPitch;
        stream << manual.targetRoll;
        stream << manual.targetCourse;
    }
    else
    {
        stream << automatic.isAltitudeOverridden;
        if (automatic.isAltitudeOverridden) stream << automatic.overriddenAltitude;

        stream << automatic.isCourseOverridden;
        if (automatic.isAltitudeOverridden) stream << automatic.overriddenCourse;

        stream << automatic.isVelocityOverridden;
        if (automatic.isAltitudeOverridden) stream << automatic.overriddenVelocity;

        stream << automatic.activeProgram;
        stream << automatic.activePoint;
    }

    return stream;
}

QDataStream& DirectPacket::operator <<(QDataStream& stream)
{
    stream >> isManual;

    if (isManual)
    {
        stream >> manual.targetPitch;
        stream >> manual.targetRoll;
        stream >> manual.targetCourse;
    }
    else
    {
        stream >> automatic.isAltitudeOverridden;
        if (automatic.isAltitudeOverridden) stream >> automatic.overriddenAltitude;

        stream >> automatic.isCourseOverridden;
        if (automatic.isAltitudeOverridden) stream >> automatic.overriddenCourse;

        stream >> automatic.isVelocityOverridden;
        if (automatic.isAltitudeOverridden) stream >> automatic.overriddenVelocity;

        stream >> automatic.activeProgram;
        stream >> automatic.activePoint;
    }

    return stream;
}

DirectPacket DirectPacket::fromByteArray(const QByteArray& data)
{
    QDataStream stream(data);
    DirectPacket packet;
    stream >> packet;
    return packet;
}
