#include "lsm9ds1_gyro_accel.h"
#include "lsm9ds1_registers.h"

using namespace devices;

Lsm9ds1::GyroAccel::GyroAccel():
    I2cDevice()
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
}

void Lsm9ds1::GyroAccel::setAccelAxisEnabled(Axes axis, bool enabled)
{
    uint8_t ctrl = this->i2cRead(CTRL_REG5_XL);
    ctrl |= (enabled << axis);
    this->i2cWrite(CTRL_REG5_XL, ctrl);
}
