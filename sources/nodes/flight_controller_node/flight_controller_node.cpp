#include "flight_controller_node.h"

// Qt
#include <QDebug>

// Internal
#include "topics.h"
#include "config.h"
#include "subscriber.h"

using namespace domain;

class FlightControllerNode::Impl
{
public:
    Subscriber sub;
};

FlightControllerNode::FlightControllerNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{}

FlightControllerNode::~FlightControllerNode()
{
    delete d;
}

void FlightControllerNode::init()
{
     d->sub.connectTo("ipc://altimeter");
     d->sub.connectTo("ipc://ins");
     d->sub.connectTo("ipc://sns");
     d->sub.connectTo("ipc://transceiver");

     d->sub.subscribe("");
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
