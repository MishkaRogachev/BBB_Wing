#include "sensor_ins_node.h"

// Qt
#include <QDebug>

// Internal
#include "core.h"
#include "config.h"
#include "publisher.h"

#include "ins_packet.h"

#include "lsm9ds1.h"
#include "complementary_filter.h"

using namespace domain;

class SensorInsNode::Impl
{
public:
    Publisher pub;
    devices::IImu* imu;

    ComplementaryFilter filter;
};

SensorInsNode::SensorInsNode(QObject* parent):
    AbstractNodeFrequency(Config::value("SensorIns/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::ins);

    d->imu = new devices::Lsm9ds1(
                 Config::value("SensorIns/i2c_path").toString());
}

SensorInsNode::~SensorInsNode()
{
    delete d->imu;
    delete d;
}

void SensorInsNode::init()
{
    d->imu->init();
}

void SensorInsNode::exec()
{
    InsPacket packet;

    if (d->imu->checkDevicePresent())
    {
        packet.status = true;

        d->filter.setAccelData(d->imu->readAccelX(),
                               d->imu->readAccelY(),
                               d->imu->readAccelZ());

        d->filter.setGyroData(d->imu->readGyroX(),
                              d->imu->readGyroY(),
                              d->imu->readGyroZ());

        d->filter.setMagData(d->imu->readMagX(),
                             d->imu->readMagY(),
                             d->imu->readMagZ());

        d->filter.process(1 / this->frequency());

        packet.pitch = d->filter.pitch();
        packet.roll = d->filter.roll();
        packet.yaw = d->filter.yaw();
    }
    else
    {
        packet.status = false;

        d->filter.reset();
        d->imu->init();
    }
    d->pub.publish(topics::insPacket, packet.toByteArray());
}
