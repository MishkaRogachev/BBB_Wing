#include "lsm9ds1_gyro_accel.h"
#include "lsm9ds1_registers.h"

using namespace devices;

Lsm9ds1::GyroAccel::GyroAccel(const char* filename):
    I2cDevice(filename),
    m_gyroResolution(1.0f),
    m_accelResolution(1.0f)
{}

uint8_t Lsm9ds1::GyroAccel::i2cAddress() const
{
    return LSM9DS1_AG;
}

bool Lsm9ds1::GyroAccel::checkDevicePresent()
{
    return this->i2cRead(WHO_AM_I_XG) == WHO_AM_I_AG_RSP;
}

float Lsm9ds1::GyroAccel::calcGyroResolution(GyroScale scale)
{
    switch (scale)
    {
    case GyroScale245: return  245.0f / 32768.0f;
    case GyroScale500: return 500.0f / 32768.0f;
    case GyroScale2000: return 2000.0f / 32768.0f;
    case GyroScaleNone:
    default:
        return 1.0f;
    }
}

float Lsm9ds1::GyroAccel::gyroResolution() const
{
    return m_gyroResolution;
}

void Lsm9ds1::GyroAccel::initGyro()
{
    this->i2cWrite(CTRL_REG1_G, 0x38);
    this->i2cWrite(CTRL_REG2_G, 0x00);
    this->i2cWrite(CTRL_REG3_G, 0x00);
    this->i2cWrite(CTRL_REG4, 0x38);

    this->setGyroSampleRate(GyroSampleRate952);
    this->setGyroScale(GyroScale245);
    this->setGyroXEnabled(true);
    this->setGyroYEnabled(true);
    this->setGyroZEnabled(true);
}

void Lsm9ds1::GyroAccel::setGyroSampleRate(GyroSampleRate rate)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG1_G);
    ctrl &= 0xFF ^ (0x7 << 5);
    ctrl |= (rate << 5);
    this->i2cWrite(CTRL_REG1_G, ctrl);
}

void Lsm9ds1::GyroAccel::setGyroScale(GyroScale scale)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG1_G);
    ctrl &= 0xFF ^ (0x3 << 3);
    ctrl |= (scale << 3);
    this->i2cWrite(CTRL_REG1_G, ctrl);

    m_gyroResolution = this->calcGyroResolution(scale);
}

void Lsm9ds1::GyroAccel::setGyroLowPowerEnabled(bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG3_G);
    ctrl |= (enabled << 7);
    this->i2cWrite(CTRL_REG3_G, ctrl);
}

void Lsm9ds1::GyroAccel::setGyroXEnabled(bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG4);
    ctrl |= (enabled << 0x3);
    this->i2cWrite(CTRL_REG4, ctrl);
}

void Lsm9ds1::GyroAccel::setGyroYEnabled(bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG4);
    ctrl |= (enabled << 0x4);
    this->i2cWrite(CTRL_REG4, ctrl);
}

void Lsm9ds1::GyroAccel::setGyroZEnabled(bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG4);
    ctrl |= (enabled << 0x5);
    this->i2cWrite(CTRL_REG4, ctrl);
}

int16_t Lsm9ds1::GyroAccel::readGyroXRaw()
{
    return this->i2cRead(OUT_X_H_G) << 8 | this->i2cRead(OUT_X_L_G);
}

int16_t Lsm9ds1::GyroAccel::readGyroYRaw()
{
    return this->i2cRead(OUT_Y_H_G) << 8 | this->i2cRead(OUT_Y_L_G);
}

int16_t Lsm9ds1::GyroAccel::readGyroZRaw()
{
    return this->i2cRead(OUT_Z_H_G) << 8 | this->i2cRead(OUT_Z_L_G);
}

float Lsm9ds1::GyroAccel::calcAccelResolution(AccelScale scale)
{
    switch (scale)
    {
    case AccelScale2: return 2.0f / 32768.0f;
    case AccelScale16: return 16.0f / 32768.0f;
    case AccelScale4: return 4.0f / 32768.0f;
    case AccelScale8: return 8.0f / 32768.0f;
    default:
        return 1.0f;
    }
}

float Lsm9ds1::GyroAccel::accelResolution() const
{
    return m_accelResolution;
}

void Lsm9ds1::GyroAccel::initAccel()
{
    this->i2cWrite(CTRL_REG5_XL, 0x38);
    this->i2cWrite(CTRL_REG6_XL, 0xD8);
    this->i2cWrite(CTRL_REG7_XL, 0x00);

    this->setAccelSampleRate(AccelSampleRate952);
    this->setAccelScale(AccelScale2);
    this->setAccelXEnabled(true);
    this->setAccelYEnabled(true);
    this->setAccelZEnabled(true);
}

void Lsm9ds1::GyroAccel::setAccelSampleRate(AccelSampleRate rate)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG6_XL);
    ctrl &= 0xFF ^ (0x7 << 5);
    ctrl |= (rate << 5);
    this->i2cWrite(CTRL_REG6_XL, ctrl);
}

void Lsm9ds1::GyroAccel::setAccelScale(AccelScale scale)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG6_XL);
    ctrl &= 0xFF ^ (0x3 << 3);
    ctrl |= (scale << 3);
    this->i2cWrite(CTRL_REG6_XL, ctrl);

    m_accelResolution = this->calcAccelResolution(scale);
}

void Lsm9ds1::GyroAccel::setAccelXEnabled(bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG5_XL);
    ctrl |= (enabled << 0x3);
    this->i2cWrite(CTRL_REG5_XL, ctrl);
}

void Lsm9ds1::GyroAccel::setAccelYEnabled(bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG5_XL);
    ctrl |= (enabled << 0x4);
    this->i2cWrite(CTRL_REG5_XL, ctrl);
}

void Lsm9ds1::GyroAccel::setAccelZEnabled(bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG5_XL);
    ctrl |= (enabled << 0x5);
    this->i2cWrite(CTRL_REG5_XL, ctrl);
}

int16_t Lsm9ds1::GyroAccel::readAccelXRaw()
{
    return this->i2cRead(OUT_X_H_XL) << 8 | this->i2cRead(OUT_X_L_XL);
}

int16_t Lsm9ds1::GyroAccel::readAccelYRaw()
{
    return this->i2cRead(OUT_Y_H_XL) << 8 | this->i2cRead(OUT_Y_L_XL);
}

int16_t Lsm9ds1::GyroAccel::readAccelZRaw()
{
    return this->i2cRead(OUT_Z_H_XL) << 8 | this->i2cRead(OUT_Z_L_XL);
}

int16_t Lsm9ds1::GyroAccel::readTempeartureRaw()
{
    return (int16_t(this->i2cRead(OUT_TEMP_H) << 12) |
            (this->i2cRead(OUT_TEMP_L) << 4)) >> 4;
}

float Lsm9ds1::GyroAccel::readTempearture()
{
    return this->readTempeartureRaw();
}
