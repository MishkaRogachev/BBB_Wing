#include "sensor_altimeter_node.h"

// Qt
#include <QDebug>

// Internal
#include "mpl3115a2.h"

using namespace domain;

class SensorAltimeterNode::Impl
{
public:
    devices::Mpl3115A2 altimeter;
};

SensorAltimeterNode::SensorAltimeterNode(QObject* parent):
    AbstractNodeFrequency(parent),
    d(new Impl())
{}

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

    qDebug() << "alt:" << d->altimeter.altitude() <<
                "tmp:" << d->altimeter.temperature() <<
                "prs:" << d->altimeter.pressure();
}
