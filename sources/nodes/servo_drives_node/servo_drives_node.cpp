#include "servo_drives_node.h"

// Qt
#include <QDebug>
#include <QMap>

// Internal
#include "core.h"
#include "config.h"

#include "subscriber.h"

#include "pca9685.h"

using namespace domain;

class ServoDrivesNode::Impl
{
public:
    Subscriber sub;

    QMap<int, float> channelAngles;
    devices::IServoController* servoController;
};

ServoDrivesNode::ServoDrivesNode(QObject* parent):
    AbstractNodeFrequency(Config::value("ServoDrives/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->servoController = new devices::Pca9685(
                             qPrintable(Config::value("ServoDrives/i2c_path").toString()),
                             Config::value("ServoDrives/min_servo_angle").toFloat(),
                             Config::value("ServoDrives/max_servo_angle").toFloat(),
                             Config::value("ServoDrives/min_pwm_duty").toInt(),
                             Config::value("ServoDrives/max_pwm_duty").toInt());
}

ServoDrivesNode::~ServoDrivesNode()
{
    delete d->servoController;
    delete d;
}

void ServoDrivesNode::init()
{
    d->sub.connectTo({ endpoints::flightController,
                       endpoints::ins,
                       endpoints::sns,
                       endpoints::navigator,
                       endpoints::boardGateway });

    d->sub.subscribe(topics::data);
    connect(&d->sub, &Subscriber::received, this,
            &ServoDrivesNode::onSubReceived);

    d->servoController->init();
}

void ServoDrivesNode::exec()
{
    if (d->servoController->checkAvalible())
    {
        for (int channel: d->channelAngles.keys())
        {
            d->servoController->setAngle(channel, d->channelAngles.value(channel));
        }
    }
    else
    {
        d->servoController->init();
    }
}

void ServoDrivesNode::onSubReceived(const QString& topic, const QByteArray& msg)
{
    // TODO: fill d->channelAngles
}
