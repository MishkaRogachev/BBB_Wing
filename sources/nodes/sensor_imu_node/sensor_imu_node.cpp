#include "sensor_imu_node.h"

// Qt
#include <QDebug>

// Internal
#include "publisher.h"

using namespace domain;

class SensorImuNode::Impl
{
public:
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
    // TODO: impl
}

void SensorImuNode::exec()
{
    // TODO: impl
}
