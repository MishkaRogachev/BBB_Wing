#include "flight_navigator_node.h"

// Qt
#include <QDebug>

// Internal
#include "topics.h"
#include "config.h"
#include "subscriber.h"

using namespace domain;

class FlightNavigatorNode::Impl
{
public:
    Subscriber sub;
};

FlightNavigatorNode::FlightNavigatorNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{}

FlightNavigatorNode::~FlightNavigatorNode()
{
    delete d;
}

void FlightNavigatorNode::init()
{
     d->sub.connectTo("ipc://altimeter");
     d->sub.connectTo("ipc://ins");
     d->sub.connectTo("ipc://sns");
     d->sub.connectTo("ipc://transceiver");

     d->sub.subscribe("");
     connect(&d->sub, &Subscriber::received, this,
             &FlightNavigatorNode::onSubReceived);
}

void FlightNavigatorNode::exec()
{
    // TODO:
}

void FlightNavigatorNode::onSubReceived(const QString& topic,
                                        const QByteArray& msg)
{
    // TODO:
}
