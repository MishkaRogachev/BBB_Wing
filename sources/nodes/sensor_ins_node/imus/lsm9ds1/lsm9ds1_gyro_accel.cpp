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

    m_gyroResolution = this->calcGyroResolution(scale);
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

int16_t Lsm9ds1::GyroAccel::readGyroRaw(Axes axis)
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

    return this->i2cRead(regAddrH) << 8 | this->i2cRead(regAddrL);
}

float Lsm9ds1::GyroAccel::readGyro(Axes axis)
{
    return m_gyroResolution * this->readGyroRaw(axis);
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

    m_accelResolution = this->calcAccelResolution(scale);
}

void Lsm9ds1::GyroAccel::setAccelAxisEnabled(Axes axis, bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG5_XL);
    ctrl |= (enabled << axis);
    this->i2cWrite(CTRL_REG5_XL, ctrl);
}

int16_t Lsm9ds1::GyroAccel::readAccelRaw(Axes axis)
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

    return this->i2cRead(regAddrH) << 8 | this->i2cRead(regAddrL);
}

float Lsm9ds1::GyroAccel::readAccel(Axes axis)
{
    return m_accelResolution * this->readAccelRaw(axis);
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
