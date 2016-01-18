#include "i2c_device.h"

// Linux
#include <cstddef>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

using namespace devices;

const char* I2cDevice::defaultI2cPath = "/dev/i2c-2";

I2cDevice::I2cDevice():
    m_file(-1)
{}

I2cDevice::~I2cDevice()
{
    if (m_file != -1) this->stop();
}

bool I2cDevice::start(const char* filename)
{
    if ((m_file = open(filename, O_RDWR)) < 0)
        return false;

    if (ioctl(m_file, I2C_SLAVE, this->i2cAddress()) < 0)
        return false;

    return true;
}

void I2cDevice::stop()
{
    close(m_file);
}

uint8_t I2cDevice::i2cAddress() const
{
    return 0x0;
}

uint8_t I2cDevice::i2cRead(uint8_t reg)
{
    return i2c_smbus_read_word_data(m_file, reg);
}

void I2cDevice::i2cWrite(uint8_t reg, uint8_t data)
{
    i2c_smbus_write_byte_data(m_file, reg, data);
}

void I2cDevice::setRegisterBit(uint8_t reg, uint8_t bit)
{
    uint8_t value = this->i2cRead(reg);
    value |= (1 << bit);
    this->i2cWrite(reg, value);
}

void I2cDevice::clearRegisterBit(uint8_t reg, uint8_t bit)
{
    uint8_t value = this->i2cRead(reg);
    value &= ~(1 << bit);
    this->i2cWrite(reg, value);
}
