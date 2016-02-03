#ifndef LSM9DS1_GYRO_ACCEL_H
#define LSM9DS1_GYRO_ACCEL_H

#include "lsm9ds1.h"

namespace devices
{
    enum Axes: uint8_t
    {
        AxisX = 0x3,
        AxisY = 0x4,
        AxisZ = 0X5
    };

    enum GyroSampleRate: uint8_t
    {
        GyroSampleNone = 0x0,
        GyroSampleRate14d9 = 0x1,
        GyroSampleRate59d5 = 0x2,
        GyroSampleRate119 = 0x3,
        GyroSampleRate238 = 0x4,
        GyroSampleRate476 = 0x5,
        GyroSampleRate952 = 0x6
    };

    enum GyroScale: uint8_t
    {
        GyroScale245 = 0x0,
        GyroScale500 = 0x1,
        GyroScaleNone = 0x2,
        GyroScale2000 = 0x3
    };

    enum AccelSampleRate: uint8_t
    {
        AccelSampleNone = 0x0,
        AccelSampleRate10 = 0x1,
        AccelSampleRate50 = 0x2,
        AccelSampleRate119 = 0x3,
        AccelSampleRate238 = 0x4,
        AccelSampleRate476 = 0x5,
        AccelSampleRate952 = 0x6
    };

    enum AccelScale: uint8_t
    {
        AccelScale2 = 0x0,
        AccelScale16 = 0x1,
        AccelScale4 = 0x2,
        AccelScale8 = 0x3
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
        void setGyroAxisEnabled(Axes axis, bool enabled);

        void initAccel();
        void setAccelSampleRate(AccelSampleRate rate);
        void setAccelScale(AccelScale scale);
        void setAccelAxisEnabled(Axes axis, bool enabled);
    };
}

#endif // LSM9DS1_GYRO_ACCEL_H
