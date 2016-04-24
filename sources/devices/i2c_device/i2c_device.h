#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

// Qt
#include <QString>

namespace devices
{
    class I2cDevice
    {
    public:
        I2cDevice(const QString& filename);
        virtual ~I2cDevice();

        QString filename() const;

        virtual bool start();
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
        QString m_filename;
    };
}

#endif // I2C_DEVICE_H
