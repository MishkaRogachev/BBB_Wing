#ifndef I_SERVO_CONTROLLER_H
#define I_SERVO_CONTROLLER_H

#include <stdint.h>

namespace devices
{
    class IServoController
    {
    public:
        virtual ~IServoController() {}

        virtual void init() = 0;
        virtual bool checkAvalible() = 0;

        virtual void setAngle(uint8_t channel, float angle) = 0;
        virtual float angle(uint8_t channel) const = 0;
    };
}

#endif // I_SERVO_CONTROLLER_H
