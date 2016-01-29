#include "sensor_imu_node.h"

// Qt
#include <QDebug>

// Internal
#include "lsm9ds1.h"
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

    if (d->imu.start())
    {
        // TODO: init
    }
}

void SensorImuNode::exec()
{
    if (d->imu.isStarted() &&
        d->imu.checkDevicePresent())
    {
        // TODO: process

        d->pub.publish("status", QByteArray::number(true));
    }
    else
    {
        d->pub.publish("status", QByteArray::number(false));
        this->init();
    }
}
