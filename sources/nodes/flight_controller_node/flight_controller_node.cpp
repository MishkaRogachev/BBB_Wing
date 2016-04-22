#include "flight_controller_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "core.h"
#include "subscriber.h"
#include "publisher.h"

using namespace domain;

class FlightControllerNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;
};

FlightControllerNode::FlightControllerNode(QObject* parent):
    AbstractNodeFrequency(Config::value("FlightController/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::flightController);
}

FlightControllerNode::~FlightControllerNode()
{
    delete d;
}

void FlightControllerNode::init()
{
    d->sub.connectTo({ endpoints::altimeter,
                       endpoints::ins,
                       endpoints::sns,
                       endpoints::navigator,
                       endpoints::boardGateway });

    d->sub.subscribe(topics::data);
    connect(&d->sub, &Subscriber::received, this,
            &FlightControllerNode::onSubReceived);
}

void FlightControllerNode::exec()
{
    // TODO: FlightControllerNode::exec
}

void FlightControllerNode::onSubReceived(const QString& topic,
                                       const QByteArray& msg)
{
    // TODO: FlightControllerNode::onSubReceived
}
