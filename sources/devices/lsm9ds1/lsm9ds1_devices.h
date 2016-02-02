#ifndef LSM9DS1_DEVICES_H
#define LSM9DS1_DEVICES_H

// Internal
#include "lsm9ds1.h"
#include "lsm9ds1_registers.h"

namespace devices
{
    class Lsm9ds1::GyroAccel: public I2cDevice
    {
    public:
        uint8_t i2cAddress() const override
        {
            return LSM9DS1_AG;
        }

        bool checkDevicePresent() override
        {
            return this->i2cRead(WHO_AM_I_XG) == WHO_AM_I_AG_RSP;
        }

        void initGyro()
        {

        }

        void initAccel()
        {

        }
    };

    class Lsm9ds1::Mag: public I2cDevice
    {
    public:
        uint8_t i2cAddress() const override
        {
            return LSM9DS1_M;
        }

        bool checkDevicePresent() override
        {
            return this->i2cRead(WHO_AM_I_M) == WHO_AM_I_M_RSP;
        }

        void initMag()
        {

        }
    };
}

#endif // LSM9DS1_DEVICES_H
