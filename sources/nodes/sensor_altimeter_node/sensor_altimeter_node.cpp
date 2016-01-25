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
    d->altimeter.start();

    d->altimeter.setOversampleRate(7); // Set Oversample to the recommended 128
    d->altimeter.enableEventFlags();
    d->altimeter.setModeAltimeter();
}

void SensorAltimeterNode::exec()
{
    d->altimeter.processMeasurement();

    d->pub.publish("altitude", QByteArray::number(d->altimeter.altitude()));
    d->pub.publish("temperature", QByteArray::number(d->altimeter.temperature()));
}
