#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

// Std
#include <cstdint>

namespace devices
{
    class I2cDevice
    {
    public:
        static const char* defaultI2cPath;

        I2cDevice();
        virtual ~I2cDevice();

        virtual bool start(const char* filename = defaultI2cPath);
        void stop();
        virtual uint8_t i2cAddress() const;

        uint8_t i2cRead(uint8_t reg);
        void i2cWrite(uint8_t reg, uint8_t data);

        void setRegisterBit(uint8_t reg, uint8_t bit);
        void clearRegisterBit(uint8_t reg, uint8_t bit);

        bool isStarted() const;
        virtual bool checkDevicePresent();

    private:
        int m_file;
    };
}

#endif // I2C_DEVICE_H
