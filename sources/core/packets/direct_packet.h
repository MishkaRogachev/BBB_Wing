#ifndef DIRECT_PACKET_H
#define DIRECT_PACKET_H

#include "packet.h"

// Qt
#include <QMap>

namespace domain
{
    class DirectPacket: public Packet
    {
    public:
        bool isManual;

        struct Manual
        {
            float targetPitch;
            float targetRoll;
            float targetCourse;
            float targetSpeed;
        };

        struct Automatic
        {
            bool isAltitudeOverridden;
            float overriddenAltitude;

            bool isCourseOverridden;
            float overriddenCourse;

            bool isVelocityOverridden;
            float overriddenVelocity;

            qint16 activeProgram;
            short activePoint;
        };

        union
        {
            Manual manual;
            Automatic automatic;
        };

        QDataStream& operator >>(QDataStream& stream) const override;
        QDataStream& operator <<(QDataStream& stream) override;

        static DirectPacket fromByteArray(const QByteArray& data);
    };
}

#endif // DIRECT_PACKET_H
