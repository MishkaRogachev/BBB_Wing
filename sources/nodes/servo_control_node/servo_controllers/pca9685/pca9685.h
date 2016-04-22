#ifndef PCA9685_H
#define PCA9685_H

#include "i_servo_controller.h"
#include "i2c_device.h"

namespace devices
{
    class Pca9685: public IServoController, public I2cDevice
    {
    public:
        Pca9685(const char* filename);

        bool start() override;
        uint8_t i2cAddress() const override;

        bool checkDevicePresent() override;

        void reset();
        void setFrequency(float frequency);
        void setPwm(uint8_t channel, int value);
        void setPwm(uint8_t channel, int onValue, int offValue);
        int pwm(uint8_t channel);

        void init() override;
        bool checkAvalible() override;

        void setAngle(uint8_t channel, float angle) override;
        float angle(uint8_t channel) const override;
    };
}
#endif // PCA9685_H
