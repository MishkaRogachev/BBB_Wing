#ifndef LSM9DS1_MAG_H
#define LSM9DS1_MAG_H

#include "lsm9ds1.h"
#include "i2c_device.h"

namespace devices
{
    enum MagSampleRate: uint8_t
    {
        MagSampleRate0d625 = 0x0,
        MagSampleRate1d25 = 0x1,
        MagSampleRate2d5 = 0x2,
        MagSampleRate5 = 0x3,
        MagSampleRate10 = 0x4,
        MagSampleRate20 = 0x5,
        MagSampleRate40 = 0x6,
        MagSampleRate80 = 0x7
    };

    enum MagScale: uint8_t
    {
        MagScale4 = 0x0,
        MagScale8 = 0x1,
        MagScale12 = 0x2,
        MagScale16 = 0x3
    };

    class Lsm9ds1::Mag: public I2cDevice
    {
    public:
        Mag(const char* filename);

        uint8_t i2cAddress() const override;
        bool checkDevicePresent() override;

        static float calcResolution(MagScale scale);

        void initMag();
        void setMagSampleRate(MagSampleRate rate);
        void setMagScale(MagScale scale);
        int16_t readMagRaw(Axes axis);
        float readMag(Axes axis);

    private:
        float m_resolution;
    };
}

#endif // LSM9DS1_MAG_H
