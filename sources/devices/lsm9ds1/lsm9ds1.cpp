#include "lsm9ds1.h"
#include "lsm9ds1_gyro_accel.h"
#include "lsm9ds1_mag.h"

using namespace devices;

Lsm9ds1::Lsm9ds1():
    gyroAccel(new GyroAccel()),
    mag(new Mag())
{}

Lsm9ds1::~Lsm9ds1()
{
    delete gyroAccel;
    delete mag;
}

bool Lsm9ds1::start(const char* filename)
{
    if (!gyroAccel->start(filename) || !mag->start(filename)) return false;

    gyroAccel->initGyro();
    gyroAccel->initAccel();
    mag->initMag();

    return true;
}

void Lsm9ds1::stop()
{
    gyroAccel->stop();
    mag->stop();
}

bool Lsm9ds1::isStarted() const
{
    return gyroAccel->isStarted() && mag->isStarted();
}

bool Lsm9ds1::checkDevicePresent()
{
    return gyroAccel->checkDevicePresent() && mag->checkDevicePresent();
}
