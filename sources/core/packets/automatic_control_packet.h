#ifndef AUTOMATIC_CONTROL_PACKET_H
#define AUTOMATIC_CONTROL_PACKET_H

#include "packet.h"

namespace domain
{
    class AutomaticControlPacket: public Packet
    {
    public:
        bool isAltitudeOverridden;
        float overriddenAltitude;

        bool isCourseOverridden;
        float overriddenCourse;

        bool isVelocityOverridden;
        float overriddenVelocity;

        qint16 activeProgram;
        short activePoint;

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static AutomaticControlPacket fromByteArray(const QByteArray& data);
    };
}

#endif // AUTOMATIC_CONTROL_PACKET_H
