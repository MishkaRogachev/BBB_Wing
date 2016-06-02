#include "complementary_filter.h"

// Qt
#include <QtGlobal>

namespace
{
    float filterConstant = 0.40; // Complementary filter constant
}

using namespace domain;

class ComplementaryFilter::Impl
{
public:
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float mx;
    float my;
    float mz;

    float pitch;
    float roll;
    float yaw;
};

ComplementaryFilter::ComplementaryFilter():
    d(new Impl())
{
    this->reset();
}

ComplementaryFilter::~ComplementaryFilter()
{
    delete d;
}

void ComplementaryFilter::setGyroData(float gx, float gy, float gz)
{
    d->gx = gx;
    d->gy= gy;
    d->gz = gz;
}

void ComplementaryFilter::setAccelData(float ax, float ay, float az)
{
    d->ax = ax;
    d->ay= ay;
    d->az = az;
}

void ComplementaryFilter::setMagData(float mx, float my, float mz)
{
    d->mx = mx;
    d->my= my;
    d->mz = mz;
}

void ComplementaryFilter::process(float dt)
{
    // Convert Accelerometer values to degrees
    float accelXAngle = atan2(d->ay, d->az) * 180.0 / M_PI;
    float accelYAngle = atan2(d->ax, sqrt(pow(d->ay, 2) + pow(d->az, 2))) *
                        180.0 / M_PI;

    // Complementary filter used to combine the accelerometer and gyro values.(GAIN?)
    d->pitch = ::filterConstant * (d->pitch + d->gy * dt) +
              (1 - ::filterConstant) * accelYAngle;
    d->roll = ::filterConstant * (d->roll + d->gx * dt) +
               (1 - ::filterConstant) * accelXAngle;

    // Normalize accelerometer raw values
    float l = sqrt(pow(d->ax, 2) + pow(d->ay, 2) + pow(d->az, 2));
    float accXnorm = d->ax / l;
    float accYnorm = d->ay / l;

    // Calculate pitch and roll for compensated yaw
    float magPitch = asin(accXnorm);
    float magRoll = -asin(accYnorm / cos(magPitch));

    // Calculate the new tilt compensated values
    float magXcomp = d->mx * cos(magPitch) + d->mz * sin(magPitch);
    float magYcomp = d->mx * sin(magRoll) * sin(magPitch) + d->my * cos(magRoll) -
                     d->mz * sin(magRoll) * cos(magPitch);

    // Calculate tilt compensated heading
    d->yaw = 180 * atan2(magYcomp, magXcomp) / M_PI;
    if (d->yaw < 0) d->yaw += 360;
}

void ComplementaryFilter::reset()
{
    d->ax = 0.0;
    d->ay = 0.0;
    d->az = 0.0;
    d->gx = 0.0;
    d->gy = 0.0;
    d->gz = 0.0;
    d->mx = 0.0;
    d->my = 0.0;
    d->mz = 0.0;
    d->pitch = 0.0;
    d->roll = 0.0;
    d->yaw = 0.0;
}

float ComplementaryFilter::pitch() const
{
    return d->pitch;
}

float ComplementaryFilter::roll() const
{
    return d->roll;
}

float ComplementaryFilter::yaw() const
{
    return d->yaw;
}
