#include "sensor_ins_node.h"

// Qt
#include <QDebug>

// Internal
#include "core.h"
#include "config.h"
#include "publisher.h"

#include "ins_packet.h"

#include "lsm9ds1.h"

namespace
{
    const float declination = -8.58;
}

using namespace domain;

class SensorInsNode::Impl
{
public:
    Publisher pub;
    devices::IImu* imu;
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

//        float gx = d->imu.gyroAccel()->readGyro(devices::AxisX);
//        float gy = d->imu.gyroAccel()->readGyro(devices::AxisY);
//        float gz = d->imu.gyroAccel()->readGyro(devices::AxisZ);
        float ax = d->imu->readAccelX();
        float ay = d->imu->readAccelY();
        float az = d->imu->readAccelZ();
//        float temperature = d->imu->gyroAccel()->readTempearture();
        float mx = d->imu->readMagX();
        float my = d->imu->readGyroY();
//        float mz = d->imu->mag()->readMag(devices::AxisZ);

        // TODO: separate this code to INS class
        packet.pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0f / M_PI;
        packet.roll = atan2(ay, az) * 180.0 / M_PI;

        float yaw = qFuzzyCompare(my, 0.0f) ?
                        (mx < 0 ? 180.0f : 0.0f) :
                        atan2(mx ,my);
        if (yaw > M_PI) yaw -= 2 * M_PI;
        else if (yaw < 0) yaw += 2 * M_PI;
        packet.yaw = yaw * 180.0f / M_PI - declination;
    }
    else
    {
        packet.status = false;
        d->imu->init();
    }
    d->pub.publish(topics::insPacket, packet.toByteArray());
}
