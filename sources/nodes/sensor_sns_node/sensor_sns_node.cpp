#include "sensor_sns_node.h"

// Gpsd
#include "libgpsmm.h"

// Qt
#include <QDebug>

// Internal
#include "publisher.h"

using namespace domain;

class SensorSnsNode::Impl
{
public:
    Publisher pub;
    gpsmm handle = gpsmm("localhost", DEFAULT_GPSD_PORT);
};

SensorSnsNode::SensorSnsNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{
    d->pub.bind("ipc://sns"); //inproc://altimeter
    d->pub.setTopic("sns_");
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
        d->pub.publish("status", QByteArray::number(false));
        this->init();
        return;
    }

    d->pub.publish("status", QByteArray::number(true));
    d->pub.publish("satellites", QByteArray::number(data->satellites_used) +
                   "/" + QByteArray::number(data->satellites_visible));

    if (!data->status)
    {
        d->pub.publish("fix", QByteArray::number(0));
        return;
    }

    d->pub.publish("fix", QByteArray::number(data->fix.mode));

    if (data->fix.mode < 2) return;

    d->pub.publish("latitude", QByteArray::number(data->fix.latitude));
    d->pub.publish("longitude", QByteArray::number(data->fix.longitude));
    d->pub.publish("course", QByteArray::number(data->fix.track));
    d->pub.publish("velocity", QByteArray::number(data->fix.speed));

    if (data->fix.mode < 3) return;

    d->pub.publish("altitude", QByteArray::number(data->fix.altitude));
    d->pub.publish("climb", QByteArray::number(data->fix.climb));
}
