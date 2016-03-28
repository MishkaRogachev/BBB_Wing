#include "flight_controller_node.h"

// Qt
#include <QDebug>

// Internal
#include "config.h"
#include "topics.h"
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
    d->pub.bind("ipc://controller");
}

FlightControllerNode::~FlightControllerNode()
{
    delete d;
}

void FlightControllerNode::init()
{
     d->sub.connectTo("ipc://alt");
     d->sub.connectTo("ipc://ins");
     d->sub.connectTo("ipc://sns");
     d->sub.connectTo("ipc://navigator");
     d->sub.connectTo("ipc://board_gateway");

     d->sub.subscribe(topics::data);
     connect(&d->sub, &Subscriber::received, this,
             &FlightControllerNode::onSubReceived);
}

void FlightControllerNode::exec()
{
    // TODO:
}

void FlightControllerNode::onSubReceived(const QString& topic,
                                       const QByteArray& msg)
{
    // TODO:
}
