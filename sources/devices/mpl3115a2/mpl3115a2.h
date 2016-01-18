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

        void setOversampleRate(int rate);
        void enableEventFlags();

        void toggleOneShot();
        void processMeasurement();

        float altitude() const;
        float temperature() const;
        float pressure() const;

    private:
        float m_altitude;
        float m_temperature;
        float m_pressure;
    };
}

#endif // MPL3115A2_H
