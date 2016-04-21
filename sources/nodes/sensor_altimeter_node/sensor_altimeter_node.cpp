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
    devices::BarometricAltimeter* altimeter;
};

SensorAltimeterNode::SensorAltimeterNode(QObject* parent):
    AbstractNodeFrequency(Config::value("SensorAltimeter/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::altimeter);

    d->altimeter = new devices::Mpl3115A2(
                       qPrintable(Config::value("SensorAltimeter/i2c_path").toString()));
}

SensorAltimeterNode::~SensorAltimeterNode()
{
    delete d->altimeter;
    delete d;
}

void SensorAltimeterNode::init()
{
    d->altimeter->init();
}

void SensorAltimeterNode::exec()
{
    if (d->altimeter->takeMeasure())
    {
        d->pub.publish(topics::altStatus, QByteArray::number(true));

        AltPacket packet;
        packet.altitude = d->altimeter->altitude();
        packet.temperature = d->altimeter->temperature();

        d->pub.publish(topics::altPacket, packet.toByteArray());
    }
    else
    {
        d->pub.publish(topics::altStatus, QByteArray::number(false));
        d->altimeter->init();
    }
}
