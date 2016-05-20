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
    devices::IBarometricAltimeter* altimeter;
};

SensorAltimeterNode::SensorAltimeterNode(QObject* parent):
    AbstractNodeFrequency(Config::value("SensorAltimeter/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::altimeter);

    d->altimeter = new devices::Mpl3115A2(
                       Config::value("SensorAltimeter/i2c_path").toString());
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
    AltPacket packet;

    if (d->altimeter->takeMeasure())
    {
        packet.status = true;

        packet.altitude = d->altimeter->altitude();
        packet.temperature = d->altimeter->temperature();
    }
    else
    {
        packet.status = false;
        d->altimeter->init();
    }

    d->pub.publish(topics::altPacket, packet.toByteArray());
}
