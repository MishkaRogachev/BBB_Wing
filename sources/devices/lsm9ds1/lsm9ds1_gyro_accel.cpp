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
    uint8_t reg = 0;
}

void Lsm9ds1::GyroAccel::initAccel()
{

}
