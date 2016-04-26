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

    devices::IServoController* servoController;
};

SerovoControlNode::SerovoControlNode(QObject* parent):
    AbstractNodeFrequency(Config::value("ServoControl/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->servoController = new devices::Pca9685(
                             qPrintable(Config::value("ServoControl/i2c_path").toString()),
                             Config::value("ServoControl/min_servo_angle").toFloat(),
                             Config::value("ServoControl/max_servo_angle").toFloat(),
                             Config::value("ServoControl/min_pwm_duty").toInt(),
                             Config::value("ServoControl/max_pwm_duty").toInt());
}

SerovoControlNode::~SerovoControlNode()
{
    delete d->servoController;
    delete d;
}

void SerovoControlNode::init()
{
    d->sub.connectTo({ endpoints::flightController,
                       endpoints::ins,
                       endpoints::sns,
                       endpoints::navigator,
                       endpoints::boardGateway });

    d->sub.subscribe(topics::data);
    connect(&d->sub, &Subscriber::received, this,
            &SerovoControlNode::onSubReceived);

    d->servoController->init();
}

void SerovoControlNode::exec()
{
    if (d->servoController->checkAvalible())
    {
        // TODO: do servo work
    }
    else
    {
        d->servoController->init();
    }
}

void SerovoControlNode::onSubReceived(const QString& topic, const QByteArray& msg)
{

}
