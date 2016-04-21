#ifndef LSM9DS1_H
#define LSM9DS1_H

#include "i2c_device.h"

namespace devices
{
    enum Axes: uint8_t
    {
        AxisX = 0x3,
        AxisY = 0x4,
        AxisZ = 0X5
    };

    class Lsm9ds1
    {
        class GyroAccel;
        class Mag;

    public:
        Lsm9ds1(const char* filename);
        ~Lsm9ds1();

        bool start();
        void stop();
        bool isStarted() const;
        bool checkDevicePresent();

        GyroAccel* gyroAccel() const;
        Mag* mag() const;

    private:
        GyroAccel* m_gyroAccel;
        Mag* m_mag;
    };
}

#endif // LSM9DS1_H
