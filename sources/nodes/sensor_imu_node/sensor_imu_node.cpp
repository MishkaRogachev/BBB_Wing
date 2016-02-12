#include "sensor_imu_node.h"

// Qt
#include <QDebug>

// Internal
#include "lsm9ds1.h"
#include "lsm9ds1_gyro_accel.h"
#include "lsm9ds1_mag.h"

#include "publisher.h"

using namespace domain;

class SensorImuNode::Impl
{
public:
    devices::Lsm9ds1 imu;
    Publisher pub;
};

SensorImuNode::SensorImuNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{
    d->pub.bind("ipc://imu");
    d->pub.setTopic("imu_");
}

SensorImuNode::~SensorImuNode()
{
    delete d;
}

void SensorImuNode::init()
{
    if (d->imu.isStarted()) d->imu.stop();
    d->imu.start();
}

void SensorImuNode::exec()
{
    if (d->imu.isStarted() &&
        d->imu.checkDevicePresent())
    {
        d->pub.publish("status", QByteArray::number(true));

        float gx = d->imu.gyroAccel()->readGyro(devices::AxisX);
        float gy = d->imu.gyroAccel()->readGyro(devices::AxisY);
        float gz = d->imu.gyroAccel()->readGyro(devices::AxisZ);
        float ax = d->imu.gyroAccel()->readAccel(devices::AxisX);
        float ay = d->imu.gyroAccel()->readAccel(devices::AxisY);
        float az = d->imu.gyroAccel()->readAccel(devices::AxisZ);
        float pitch = 180.0f * atan2(-ax, sqrt(ay * ay + az * az)) / M_PI;
        float roll = 180.0f * atan2(ay, az) / M_PI;

        d->pub.publish("gx", QByteArray::number(gx));
        d->pub.publish("gy", QByteArray::number(gy));
        d->pub.publish("gz", QByteArray::number(gz));
        d->pub.publish("ax", QByteArray::number(ax));
        d->pub.publish("ay", QByteArray::number(ay));
        d->pub.publish("az", QByteArray::number(az));
        d->pub.publish("pitch", QByteArray::number(pitch));
        d->pub.publish("roll", QByteArray::number(roll));
    }
    else
    {
        d->pub.publish("status", QByteArray::number(false));
        this->init();
    }
}
