#include "sensor_sns_node.h"

// Gpsd
#include "libgpsmm.h"

// Internal
#include "config.h"
#include "core.h"
#include "sns_packet.h"

#include "publisher.h"

using namespace domain;

class SensorSnsNode::Impl
{
public:
    gpsmm handle = gpsmm("localhost", DEFAULT_GPSD_PORT);
    Publisher pub;
};

SensorSnsNode::SensorSnsNode(QObject* parent):
    AbstractNodeFrequency(Config::value("SensorSns/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::sns);
}

SensorSnsNode::~SensorSnsNode()
{
    delete d;
}

void SensorSnsNode::init()
{
    d->handle.stream(WATCH_ENABLE | WATCH_JSON);
}

void SensorSnsNode::exec()
{
    struct gps_data_t* data = nullptr;
    if ((data = d->handle.read()) == nullptr)
    {
        d->pub.publish(topics::snsStatus, QByteArray::number(false));
        this->init();
        return;
    }

    if (!data->status)
    {
        d->pub.publish(topics::snsStatus, QByteArray::number(false));
        return;
    }

    d->pub.publish(topics::snsStatus, QByteArray::number(true));

    SnsPacket packet;

    packet.fix = data->fix.mode;

    if (data->fix.mode > 1)
    {
        packet.latitude = data->fix.latitude;
        packet.longitude = data->fix.longitude;
        packet.yaw = data->fix.track;
        packet.groundSpeed = data->fix.speed;
    }

    if (data->fix.mode > 2)
    {
        packet.altitude = data->fix.altitude;
        packet.climb = data->fix.climb;
    }

    d->pub.publish(topics::snsPacket, packet.toByteArray());
}
