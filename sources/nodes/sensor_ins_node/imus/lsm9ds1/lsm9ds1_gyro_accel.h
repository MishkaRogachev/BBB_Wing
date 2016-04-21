#ifndef LSM9DS1_GYRO_ACCEL_H
#define LSM9DS1_GYRO_ACCEL_H

#include "lsm9ds1.h"
#include "i2c_device.h"

namespace devices
{
    enum GyroSampleRate: uint8_t
    {
        GyroSampleNone = 0x0,
        GyroSampleRate14d9 = 0x1,
        GyroSampleRate59d5 = 0x2,
        GyroSampleRate119 = 0x3,
        GyroSampleRate238 = 0x4,
        GyroSampleRate476 = 0x5,
        GyroSampleRate952 = 0x6
    };

    enum GyroScale: uint8_t
    {
        GyroScale245 = 0x0,
        GyroScale500 = 0x1,
        GyroScaleNone = 0x2,
        GyroScale2000 = 0x3
    };

    enum AccelSampleRate: uint8_t
    {
        AccelSampleNone = 0x0,
        AccelSampleRate10 = 0x1,
        AccelSampleRate50 = 0x2,
        AccelSampleRate119 = 0x3,
        AccelSampleRate238 = 0x4,
        AccelSampleRate476 = 0x5,
        AccelSampleRate952 = 0x6
    };

    enum AccelScale: uint8_t
    {
        AccelScale2 = 0x0,
        AccelScale16 = 0x1,
        AccelScale4 = 0x2,
        AccelScale8 = 0x3
    };

    class Lsm9ds1::GyroAccel: public I2cDevice
    {
    public:
        GyroAccel(const char* filename);

        uint8_t i2cAddress() const override;
        bool checkDevicePresent() override;

        static float calcGyroResolution(GyroScale scale);
        float gyroResolution() const;

        void initGyro();
        void setGyroSampleRate(GyroSampleRate rate);
        void setGyroScale(GyroScale scale);
        void setGyroLowPowerEnabled(bool enabled);
        void setGyroXEnabled(bool enabled);
        void setGyroYEnabled(bool enabled);
        void setGyroZEnabled(bool enabled);
        int16_t readGyroXRaw();
        int16_t readGyroYRaw();
        int16_t readGyroZRaw();

        static float calcAccelResolution(AccelScale scale);
        float accelResolution() const;

        void initAccel();
        void setAccelSampleRate(AccelSampleRate rate);
        void setAccelScale(AccelScale scale);
        void setAccelXEnabled(bool enabled);
        void setAccelYEnabled(bool enabled);
        void setAccelZEnabled(bool enabled);
        int16_t readAccelXRaw();
        int16_t readAccelYRaw();
        int16_t readAccelZRaw();

        int16_t readTempeartureRaw();
        float readTempearture();

    private:
        float m_gyroResolution;
        float m_accelResolution;
    };
}

#endif // LSM9DS1_GYRO_ACCEL_H
