#include "sensor_ins_node.h"

// Qt
#include <QDebug>

// Internal
#include "lsm9ds1.h"
#include "lsm9ds1_gyro_accel.h"
#include "lsm9ds1_mag.h"

#include "topics.h"
#include "config.h"
#include "publisher.h"

#include "ins_packet.h"

namespace
{
    const float declination = -8.58;
}

using namespace domain;

class SensorInsNode::Impl
{
public:
    devices::Lsm9ds1 imu;
    Publisher pub;
};

SensorInsNode::SensorInsNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{
    d->pub.bind("ipc://ins");
}

SensorInsNode::~SensorInsNode()
{
    delete d;
}

void SensorInsNode::init()
{
    Config::begin("SensorIns");

    if (d->imu.isStarted()) d->imu.stop();
    d->imu.start(Config::setting("i2c_path").toString().toLatin1().data());

    Config::end();
}

void SensorInsNode::exec()
{
    if (d->imu.isStarted() &&
        d->imu.checkDevicePresent())
    {
        d->pub.publish(topics::insStatus, QByteArray::number(true));

        InsPacket packet;
//        float gx = d->imu.gyroAccel()->readGyro(devices::AxisX);
//        float gy = d->imu.gyroAccel()->readGyro(devices::AxisY);
//        float gz = d->imu.gyroAccel()->readGyro(devices::AxisZ);
        float ax = d->imu.gyroAccel()->readAccel(devices::AxisX);
        float ay = d->imu.gyroAccel()->readAccel(devices::AxisY);
        float az = d->imu.gyroAccel()->readAccel(devices::AxisZ);
        float temperature = d->imu.gyroAccel()->readTempearture();
        float mx = d->imu.mag()->readMag(devices::AxisX);
        float my = d->imu.mag()->readMag(devices::AxisY);
//        float mz = d->imu.mag()->readMag(devices::AxisZ);

        // TODO: separate this code to INS class
        packet.pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0f / M_PI;
        packet.roll = atan2(ay, az) * 180.0 / M_PI;

        float yaw = qFuzzyCompare(my, 0.0f) ?
                        (mx < 0 ? 180.0f : 0.0f) :
                        atan2(mx ,my);
        if (yaw > M_PI) yaw -= 2 * M_PI;
        else if (yaw < 0) yaw += 2 * M_PI;
        packet.yaw = yaw * 180.0f / M_PI - declination;

        d->pub.publish(topics::insPacket, packet.toByteArray());
    }
    else
    {
        d->pub.publish(topics::insStatus, QByteArray::number(false));
        this->init();
    }
}
