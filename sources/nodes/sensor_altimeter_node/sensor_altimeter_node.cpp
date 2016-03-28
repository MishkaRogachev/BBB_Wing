#include "sensor_altimeter_node.h"

// Qt
#include <QDebug>

// Internal
#include "mpl3115a2.h"

#include "topics.h"
#include "config.h"
#include "publisher.h"

#include "alt_packet.h"

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
    d->pub.bind("ipc://alt");
}

SensorAltimeterNode::~SensorAltimeterNode()
{
    delete d;
}

void SensorAltimeterNode::init()
{
    Config::begin("SensorAltimeter");

    if (d->altimeter.isStarted()) d->altimeter.stop();
    d->altimeter.start(Config::value("i2c_path").toString().toLatin1().data());

    Config::end();
}

void SensorAltimeterNode::exec()
{
    if (d->altimeter.isStarted() &&
        d->altimeter.checkDevicePresent())
    {
        d->altimeter.processMeasurement();

        d->pub.publish(topics::altStatus, QByteArray::number(true));

        AltPacket packet;
        packet.altitude = d->altimeter.altitude();
        packet.temperature = d->altimeter.temperature();

        d->pub.publish(topics::altPacket, packet.toByteArray());
    }
    else
    {
        d->pub.publish(topics::altStatus, QByteArray::number(false));
        this->init();
    }
}
