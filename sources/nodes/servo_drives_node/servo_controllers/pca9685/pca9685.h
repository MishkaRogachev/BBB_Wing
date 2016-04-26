#ifndef PCA9685_H
#define PCA9685_H

#include "i_servo_controller.h"
#include "i2c_device.h"

namespace devices
{
    class Pca9685: public IServoController, public I2cDevice
    {
    public:
        Pca9685(const char* filename, float minAngle, float maxAngle,
                int minDuty, int maxDuty);

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

    private:
        float m_minAngle;
        float m_maxAngle;
        int m_minDuty;
        int m_maxDuty;
    };
}
#endif // PCA9685_H
