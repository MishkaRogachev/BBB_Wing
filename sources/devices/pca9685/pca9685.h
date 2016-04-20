#ifndef PCA9685_H
#define PCA9685_H

#include "i2c_device.h"

namespace devices
{
    class Pca9685 : public I2cDevice
    {
    public:
        Pca9685();
    };
}
#endif // PCA9685_H
