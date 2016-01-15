#ifndef MPL3115A2_H
#define MPL3115A2_H

#include "i2c_device.h"

namespace devices
{
    class Mpl3115A2 : public I2cDevice
    {
    public:
        Mpl3115A2();

        bool start(const char* filename = "/dev/i2c-2") override;
        uint8_t i2cAddress() const override;

        void setModeActive();
        void setModeStandby();
        void setModeBarometer();
        void setModeAltimeter();

        void toogleOneShot();

        float readAltitude();
        float readPressure();
        float readTemperature();
    };
}

#endif // MPL3115A2_H
