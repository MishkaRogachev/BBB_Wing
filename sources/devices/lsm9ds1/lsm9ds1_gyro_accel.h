#ifndef LSM9DS1_GYRO_ACCEL_H
#define LSM9DS1_GYRO_ACCEL_H

#include "lsm9ds1.h"

namespace devices
{
    class Lsm9ds1::GyroAccel: public I2cDevice
    {
    public:
        GyroAccel();

        uint8_t i2cAddress() const override;
        bool checkDevicePresent() override;

        void initGyro();
        void initAccel();
    };
}

#endif // LSM9DS1_GYRO_ACCEL_H
