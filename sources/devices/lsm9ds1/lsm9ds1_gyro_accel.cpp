#include "lsm9ds1_gyro_accel.h"
#include "lsm9ds1_registers.h"

using namespace devices;

Lsm9ds1::GyroAccel::GyroAccel():
    I2cDevice(),
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

void Lsm9ds1::GyroAccel::initGyro()
{
    this->i2cWrite(CTRL_REG1_G, 0x38);
    this->i2cWrite(CTRL_REG2_G, 0x00);
    this->i2cWrite(CTRL_REG3_G, 0x00);
    this->i2cWrite(CTRL_REG4, 0x38);

    this->setGyroSampleRate(GyroSampleRate952);
    this->setGyroScale(GyroScale245);
    this->setGyroAxisEnabled(AxisX, true);
    this->setGyroAxisEnabled(AxisY, true);
    this->setGyroAxisEnabled(AxisZ, true);
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

    switch (scale)
    {
    case GyroScale245:
        m_gyroResolution = 245.0f / 32768.0f;
        break;
    case GyroScale500:
        m_gyroResolution = 500.0f / 32768.0f;
        break;
    case GyroScaleNone:
        m_gyroResolution = 1;
        break;
    case GyroScale2000:
        m_gyroResolution = 2000.0f / 32768.0f;
        break;
    }
}

void Lsm9ds1::GyroAccel::setGyroLowPowerEnabled(bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG3_G);
    ctrl |= (enabled << 7);
    this->i2cWrite(CTRL_REG3_G, ctrl);
}

void Lsm9ds1::GyroAccel::setGyroAxisEnabled(Axes axis, bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG4);
    ctrl |= (enabled << axis);
    this->i2cWrite(CTRL_REG4, ctrl);
}

uint16_t Lsm9ds1::GyroAccel::readGyroRaw(Axes axis)
{
    uint8_t regAddrL, regAddrH;

    switch (axis) {
    case AxisX:
        regAddrL = OUT_X_L_G;
        regAddrH = OUT_X_H_G;
        break;
    case AxisY:
        regAddrL = OUT_Y_L_G;
        regAddrH = OUT_Y_H_G;
        break;
    case AxisZ:
        regAddrL = OUT_Z_L_G;
        regAddrH = OUT_Z_H_G;
        break;
    }

    return int16_t(this->i2cRead(regAddrH) << 8 | this->i2cRead(regAddrL));
}

float Lsm9ds1::GyroAccel::readGyro(Axes axis)
{
    return m_gyroResolution * float(this->readGyroRaw(axis));
}

void Lsm9ds1::GyroAccel::initAccel()
{
    this->i2cWrite(CTRL_REG5_XL, 0x38);
    this->i2cWrite(CTRL_REG6_XL, 0xD8);
    this->i2cWrite(CTRL_REG7_XL, 0x00);

    this->setAccelSampleRate(AccelSampleRate952);
    this->setAccelScale(AccelScale2);
    this->setAccelAxisEnabled(AxisX, true);
    this->setAccelAxisEnabled(AxisY, true);
    this->setAccelAxisEnabled(AxisZ, true);
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

    switch (scale)
    {
    case AccelScale2:
        m_accelResolution = 2.0f / 32768.0f;
        break;
    case AccelScale16:
        m_accelResolution = 16.0f / 32768.0f;
        break;
    case AccelScale4:
        m_accelResolution = 4.0f / 32768.0f;
        break;
    case AccelScale8:
        m_accelResolution = 8.0f / 32768.0f;
        break;
    }
}

void Lsm9ds1::GyroAccel::setAccelAxisEnabled(Axes axis, bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG5_XL);
    ctrl |= (enabled << axis);
    this->i2cWrite(CTRL_REG5_XL, ctrl);
}

uint16_t Lsm9ds1::GyroAccel::readAccelRaw(Axes axis)
{
    uint8_t regAddrL, regAddrH;

    switch (axis) {
    case AxisX:
        regAddrL = OUT_X_L_XL;
        regAddrH = OUT_X_H_XL;
        break;
    case AxisY:
        regAddrL = OUT_Y_L_XL;
        regAddrH = OUT_Y_H_XL;
        break;
    case AxisZ:
        regAddrL = OUT_Z_L_XL;
        regAddrH = OUT_Z_H_XL;
        break;
    }

    return int16_t(this->i2cRead(regAddrH) << 8 | this->i2cRead(regAddrL));
}

float Lsm9ds1::GyroAccel::readAccel(Axes axis)
{
    return m_accelResolution * float(this->readAccelRaw(axis));
}
