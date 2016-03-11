#include "sensor_sns_node.h"

// Gpsd
#include "libgpsmm.h"

// Internal
#include "topics.h"

#include "publisher.h"

using namespace domain;

class SensorSnsNode::Impl
{
public:
    gpsmm handle = gpsmm("localhost", DEFAULT_GPSD_PORT);
    Publisher pub;
};

SensorSnsNode::SensorSnsNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{
    d->pub.bind("ipc://sns");
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

    d->pub.publish(topics::snsStatus, QByteArray::number(true));
    d->pub.publish(topics::snsSatellites,
                   QByteArray::number(data->satellites_used) + "/" +
                   QByteArray::number(data->satellites_visible));

    if (!data->status)
    {
        d->pub.publish(topics::snsFix, QByteArray::number(0));
        return;
    }

    d->pub.publish(topics::snsFix, QByteArray::number(data->fix.mode));

    if (data->fix.mode < 2) return;

    d->pub.publish(topics::snsLatitude, QByteArray::number(data->fix.latitude));
    d->pub.publish(topics::snsLongitude, QByteArray::number(data->fix.longitude));
    d->pub.publish(topics::snsYaw, QByteArray::number(data->fix.track));
    d->pub.publish(topics::snsVelocity, QByteArray::number(data->fix.speed));

    if (data->fix.mode < 3) return;

    d->pub.publish(topics::snsAltitude, QByteArray::number(data->fix.altitude));
    d->pub.publish(topics::snsClimb, QByteArray::number(data->fix.climb));
}
