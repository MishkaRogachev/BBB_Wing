#include "lsm9ds1.h"
#include "lsm9ds1_devices.h"

using namespace devices;

Lsm9ds1::Lsm9ds1():
    gyroAcel(new GyroAccel()),
    mag(new Mag())
{}

Lsm9ds1::~Lsm9ds1()
{
    delete gyroAcel;
    delete mag;
}

bool Lsm9ds1::start(const char* filename)
{
    return gyroAcel->start(filename) && mag->start(filename);
}

void Lsm9ds1::stop()
{
    gyroAcel->stop();
    mag->stop();
}

bool Lsm9ds1::isStarted() const
{
    return gyroAcel->isStarted() && mag->isStarted();
}

bool Lsm9ds1::checkDevicePresent()
{
    return gyroAcel->checkDevicePresent() && mag->checkDevicePresent();
}
