#ifndef MPL3115A2_H
#define MPL3115A2_H

#include "i2c_device.h"

namespace devices
{
    class Mpl3115A2 : public I2cDevice
    {
    public:
        enum PowerMode { Standby, Active };
        enum MeasurementMode { Barometer, Altimeter };

        Mpl3115A2();

        bool start(const char* filename = "/dev/i2c-2") override;
        int i2cAddress() const override;

        void setPowerMode(PowerMode mode);
        void setMeasurementMode(MeasurementMode mode);

        void enableEventFlags();
        void toggleOneShot(void);

        float readAltitude();
        float readPressure();
        float readTemperature();
    };
}

#endif // MPL3115A2_H
