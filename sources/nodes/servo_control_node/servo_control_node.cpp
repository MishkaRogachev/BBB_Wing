#include "servo_control_node.h"

// Qt
#include <QDebug>

// Internal
#include "core.h"
#include "config.h"

#include "subscriber.h"

#include "pca9685.h"

using namespace domain;

class SerovoControlNode::Impl
{
public:
    Subscriber sub;

    devices::Pca9685* servoAdapter;
};

SerovoControlNode::SerovoControlNode(QObject* parent):
    AbstractNodeFrequency(Config::value("ServoControl/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->servoAdapter = new devices::Pca9685(
                          qPrintable(Config::value("ServoControl/i2c_path").toString()));
}

SerovoControlNode::~SerovoControlNode()
{
    delete d->servoAdapter;
    delete d;
}

void SerovoControlNode::init()
{
    if (d->servoAdapter->isStarted()) d->servoAdapter->stop();
    d->servoAdapter->start();
}

void SerovoControlNode::exec()
{
    if (d->servoAdapter->isStarted() &&
        d->servoAdapter->checkDevicePresent())
    {
        // TODO: do servo work
    }
    else
    {
        this->init();
    }
}
