#ifndef LSM9DS1_H
#define LSM9DS1_H

#include "i2c_device.h"

namespace devices
{
    class Lsm9ds1
    {
    public:
        Lsm9ds1();
        ~Lsm9ds1();

        bool start(const char* filename = I2cDevice::defaultI2cPath);
        void stop();
        bool isStarted() const;
        bool checkDevicePresent();

    private:
        class GyroAccel;
        class Mag;
        GyroAccel* gyroAcel;
        Mag* mag;
    };
}

#endif // LSM9DS1_H
