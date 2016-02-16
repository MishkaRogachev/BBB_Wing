#include "sensor_altimeter_node.h"

// Qt
#include <QDebug>

// Internal
#include "mpl3115a2.h"
#include "publisher.h"

using namespace domain;

class SensorAltimeterNode::Impl
{
public:
    devices::Mpl3115A2 altimeter;
    Publisher pub;
};

SensorAltimeterNode::SensorAltimeterNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{
    d->pub.bind("ipc://altimeter"); //inproc://altimeter
    d->pub.setTopic("alt_");
}

SensorAltimeterNode::~SensorAltimeterNode()
{
    delete d;
}

void SensorAltimeterNode::init()
{
    if (d->altimeter.isStarted()) d->altimeter.stop();
    d->altimeter.start();
}

void SensorAltimeterNode::exec()
{
    if (d->altimeter.isStarted() &&
        d->altimeter.checkDevicePresent())
    {
        d->altimeter.processMeasurement();

        d->pub.publish("status", QByteArray::number(true));
        d->pub.publish("altitude", QByteArray::number(d->altimeter.altitude()));
        d->pub.publish("temperature", QByteArray::number(d->altimeter.temperature()));
    }
    else
    {
        d->pub.publish("status", QByteArray::number(false));
        this->init();
    }
}
