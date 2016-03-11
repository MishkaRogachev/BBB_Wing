#include "sensor_altimeter_node.h"

// Qt
#include <QDebug>

// Internal
#include "mpl3115a2.h"

#include "topics.h"
#include "config.h"
#include "publisher.h"

using namespace domain;

class SensorAltimeterNode::Impl
{
public:
    devices::Mpl3115A2 altimeter;
    Publisher pub;
};

SensorAltimeterNode::SensorAltimeterNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{
    d->pub.bind("ipc://altimeter");
}

SensorAltimeterNode::~SensorAltimeterNode()
{
    delete d;
}

void SensorAltimeterNode::init()
{
    Config::begin("SensorAltimeter");

    if (d->altimeter.isStarted()) d->altimeter.stop();
    d->altimeter.start(Config::setting("i2c_path").toString().toLatin1().data());

    Config::end();
}

void SensorAltimeterNode::exec()
{
    if (d->altimeter.isStarted() &&
        d->altimeter.checkDevicePresent())
    {
        d->altimeter.processMeasurement();

        d->pub.publish(topics::altimeterStatus, QByteArray::number(true));
        d->pub.publish(topics::altimeterAltitude,
                       QByteArray::number(d->altimeter.altitude()));
        d->pub.publish(topics::altimeterTemperature,
                       QByteArray::number(d->altimeter.temperature()));
    }
    else
    {
        d->pub.publish(topics::altimeterStatus, QByteArray::number(false));
        this->init();
    }
}
