#include "sensor_altimeter_node.h"

// Qt
#include <QDebug>

// Internal
#include "core.h"
#include "config.h"
#include "publisher.h"

#include "alt_packet.h"

#include "mpl3115a2.h"

using namespace domain;

class SensorAltimeterNode::Impl
{
public:
    Publisher pub;
    devices::Mpl3115A2 altimeter;
};

SensorAltimeterNode::SensorAltimeterNode(QObject* parent):
    AbstractNodeFrequency(Config::value("SensorAltimeter/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::altimeter);
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
