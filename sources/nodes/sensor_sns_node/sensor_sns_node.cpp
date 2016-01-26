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
    gpsmm handle;

    Impl():
        handle("localhost", DEFAULT_GPSD_PORT)
    {}
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

}

void SensorSnsNode::exec()
{
    struct gps_data_t* data;

    if ((data = d->handle.read()) == nullptr)
    {
        d->pub.publish("status", QByteArray::number(false));
        return;
    }

    d->pub.publish("status", QByteArray::number(true));
}
