#include "lsm9ds1.h"
#include "lsm9ds1_gyro_accel.h"
#include "lsm9ds1_mag.h"

using namespace devices;

Lsm9ds1::Lsm9ds1():
    m_gyroAccel(new GyroAccel()),
    m_mag(new Mag())
{}

Lsm9ds1::~Lsm9ds1()
{
    delete m_gyroAccel;
    delete m_mag;
}

bool Lsm9ds1::start(const char* filename)
{
    if (!m_gyroAccel->start(filename) || !m_mag->start(filename)) return false;

    m_gyroAccel->initGyro();
    m_gyroAccel->initAccel();
    m_mag->initMag();

    return true;
}

void Lsm9ds1::stop()
{
    m_gyroAccel->stop();
    m_mag->stop();
}

bool Lsm9ds1::isStarted() const
{
    return m_gyroAccel->isStarted() && m_mag->isStarted();
}

bool Lsm9ds1::checkDevicePresent()
{
    return m_gyroAccel->checkDevicePresent() && m_mag->checkDevicePresent();
}

Lsm9ds1::GyroAccel* Lsm9ds1::gyroAccel() const
{
    return m_gyroAccel;
}

Lsm9ds1::Mag* Lsm9ds1::mag() const
{
    return m_mag;
}
