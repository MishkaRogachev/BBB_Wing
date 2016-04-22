#ifndef MPL3115A2_H
#define MPL3115A2_H

#include "i2c_device.h"
#include "i_barometric_altimeter.h"

namespace devices
{
    class Mpl3115A2: public I2cDevice, public IBarometricAltimeter
    {
    public:
        Mpl3115A2(const char* filename);

        bool start() override;
        uint8_t i2cAddress() const override;

        bool checkDevicePresent() override;

        void setModeActive();
        void setModeStandby();
        void setModeAltimeter();
        void setModeBarometer();

        void setOversampleRate(int rate);
        void enableEventFlags();

        void toggleOneShot();
        void processMeasurement();

        void init() override;
        bool takeMeasure() override;

        float altitude() const override;
        float temperature() const override;
        float pressure() const override;

    private:
        float m_altitude;
        float m_temperature;
        float m_pressure;
    };
}

#endif // MPL3115A2_H
