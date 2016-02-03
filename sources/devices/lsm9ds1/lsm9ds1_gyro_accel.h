#ifndef LSM9DS1_GYRO_ACCEL_H
#define LSM9DS1_GYRO_ACCEL_H

#include "lsm9ds1.h"

namespace devices
{
    enum GyroSampleRate: uint8_t
    {
        GyroSampleRate0 = 0,
        GyroSampleRate14d9 = 1,
        GyroSampleRate59d5 = 2,
        GyroSampleRate119 = 3,
        GyroSampleRate238 = 4,
        GyroSampleRate476 = 5,
        GyroSampleRate952 = 6
    };

    enum GyroScale: uint8_t
    {
        GyroScale245 = 0x0,
        GyroScale500 = 0x1,
        GyroScaleNone = 0x2,
        GyroScale2000 = 0x3
    };

    class Lsm9ds1::GyroAccel: public I2cDevice
    {
    public:
        GyroAccel();

        uint8_t i2cAddress() const override;
        bool checkDevicePresent() override;

        void initGyro();

        void setGyroSampleRate(GyroSampleRate rate);
        void setGyroScale(GyroScale scale);
        void setGyroLowPowerEnabled(bool enabled);
        void setGyroAxisXEnabled(bool enabled);
        void setGyroAxisYEnabled(bool enabled);
        void setGyroAxisZEnabled(bool enabled);

        void initAccel();
    };
}

#endif // LSM9DS1_GYRO_ACCEL_H
