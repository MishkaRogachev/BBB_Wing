#include "sensor_ins_node.h"

// Qt
#include <QDebug>

// Internal
#include "lsm9ds1.h"
#include "lsm9ds1_gyro_accel.h"
#include "lsm9ds1_mag.h"

#include "config.h"
#include "publisher.h"

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

SensorInsNode::SensorInsNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{
    d->pub.bind("ipc://ins");
    d->pub.setTopic("ins_");
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
        d->pub.publish("status", QByteArray::number(true));

        float gx = d->imu.gyroAccel()->readGyro(devices::AxisX);
        float gy = d->imu.gyroAccel()->readGyro(devices::AxisY);
        float gz = d->imu.gyroAccel()->readGyro(devices::AxisZ);
        float ax = d->imu.gyroAccel()->readAccel(devices::AxisX);
        float ay = d->imu.gyroAccel()->readAccel(devices::AxisY);
        float az = d->imu.gyroAccel()->readAccel(devices::AxisZ);
        float temperature = d->imu.gyroAccel()->readTempearture();
        float mx = d->imu.mag()->readMag(devices::AxisX);
        float my = d->imu.mag()->readMag(devices::AxisY);
        float mz = d->imu.mag()->readMag(devices::AxisZ);

        // TODO: separate this code to INS class
        float pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0f / M_PI;
        float roll = atan2(ay, az) * 180.0 / M_PI;

        float yaw = qFuzzyCompare(my, 0.0f) ?
                        (mx < 0 ? 180.0f : 0.0f) :
                        atan2(mx ,my);
        if (yaw > M_PI) yaw -= 2 * M_PI;
        else if (yaw < 0) yaw += 2 * M_PI;
        yaw = yaw * 180.0f / M_PI - declination;

        d->pub.publish("gx", QByteArray::number(gx));
        d->pub.publish("gy", QByteArray::number(gy));
        d->pub.publish("gz", QByteArray::number(gz));
        d->pub.publish("ax", QByteArray::number(ax));
        d->pub.publish("ay", QByteArray::number(ay));
        d->pub.publish("az", QByteArray::number(az));
        d->pub.publish("mx", QByteArray::number(mx));
        d->pub.publish("my", QByteArray::number(my));
        d->pub.publish("mz", QByteArray::number(mz));
        d->pub.publish("temperature", QByteArray::number(temperature));
        d->pub.publish("pitch", QByteArray::number(pitch));
        d->pub.publish("roll", QByteArray::number(roll));
        d->pub.publish("yaw", QByteArray::number(yaw));
    }
    else
    {
        d->pub.publish("status", QByteArray::number(false));
        this->init();
    }
}
