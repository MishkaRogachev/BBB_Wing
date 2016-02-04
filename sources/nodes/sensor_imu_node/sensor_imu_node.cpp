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

        d->pub.publish("gx", QByteArray::number(d->imu.gyroAccel()->readGyro(devices::AxisX)));
        d->pub.publish("gy", QByteArray::number(d->imu.gyroAccel()->readGyro(devices::AxisY)));
        d->pub.publish("gz", QByteArray::number(d->imu.gyroAccel()->readGyro(devices::AxisZ)));

        d->pub.publish("ax", QByteArray::number(d->imu.gyroAccel()->readAccel(devices::AxisX)));
        d->pub.publish("ay", QByteArray::number(d->imu.gyroAccel()->readAccel(devices::AxisY)));
        d->pub.publish("az", QByteArray::number(d->imu.gyroAccel()->readAccel(devices::AxisZ)));
    }
    else
    {
        d->pub.publish("status", QByteArray::number(false));
        this->init();
    }
}
