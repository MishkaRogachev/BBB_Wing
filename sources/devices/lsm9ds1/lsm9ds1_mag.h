#ifndef LSM9DS1_MAG_H
#define LSM9DS1_MAG_H

#include "lsm9ds1.h"

namespace devices
{
    class Lsm9ds1::Mag: public I2cDevice
    {
    public:
        Mag();

        uint8_t i2cAddress() const override;
        bool checkDevicePresent() override;

        void initMag();
    };
}

#endif // LSM9DS1_MAG_H
