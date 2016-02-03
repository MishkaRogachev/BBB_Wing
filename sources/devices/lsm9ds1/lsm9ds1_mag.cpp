#include "lsm9ds1_mag.h"
#include "lsm9ds1_registers.h"

using namespace devices;

Lsm9ds1::Mag::Mag():
    I2cDevice()
{}

uint8_t Lsm9ds1::Mag::i2cAddress() const
{
    return LSM9DS1_M;
}

bool Lsm9ds1::Mag::checkDevicePresent()
{
    return this->i2cRead(WHO_AM_I_M) == WHO_AM_I_M_RSP;
}

void Lsm9ds1::Mag::initMag()
{

}
