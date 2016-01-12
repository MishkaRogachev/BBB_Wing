#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

// Std
#include <cstdint>

namespace devices
{
    class I2cDevice
    {
    public:
        I2cDevice();
        virtual ~I2cDevice();

        virtual bool start(const char* filename = "/dev/i2c-2");
        void stop();
        virtual int i2cAddress() const;

        uint8_t i2cRead(uint8_t reg);
        void i2cWrite(uint8_t reg, uint8_t data);

    private:
        int m_file;
    };
}

#endif // I2C_DEVICE_H
