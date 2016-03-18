#include "ground_packet.h"

using namespace domain;

quint16 GroundDataPacket::crc()
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << *this;
    return qChecksum(array.data(), array.length());
}

QDataStream& GroundDataPacket::operator >>(QDataStream& stream) const
{
    stream << isManual;

    if (isManual)
    {
        stream << manual.setPitch;
        stream << manual.setRoll;
        stream << manual.setThrottle;
    }
    else
    {
        stream << automatic.activeProgram;
        stream << automatic. activePoint;

        stream << automatic.isYawOverriden;
        stream << automatic.overridenYaw;
        stream << automatic.isAltitudeOverriden;
        stream << automatic.overridenAltitude;
        stream << automatic.isVelocityOverriden;
        stream << automatic.overridenVelocity;
    }

    return stream;
}

QDataStream& GroundDataPacket::operator <<(QDataStream& stream)
{
    stream >> isManual;

    if (isManual)
    {
        stream >> manual.setPitch;
        stream >> manual.setRoll;
        stream >> manual.setThrottle;
    }
    else
    {
        stream >> automatic.activeProgram;
        stream >> automatic. activePoint;

        stream >> automatic.isYawOverriden;
        stream >> automatic.overridenYaw;
        stream >> automatic.isAltitudeOverriden;
        stream >> automatic.overridenAltitude;
        stream >> automatic.isVelocityOverriden;
        stream >> automatic.overridenVelocity;
    }

    return stream;
}
