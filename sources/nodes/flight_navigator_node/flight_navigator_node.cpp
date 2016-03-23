#include "flight_navigator_node.h"

// Qt
#include <QDebug>

// Internal
#include "topics.h"
#include "config.h"
#include "subscriber.h"

#include "idle_navigation_state.h"

using namespace domain;

class FlightNavigatorNode::Impl
{
public:
    Subscriber sub;
    AbstractNavigationState* state = new IdleNavigationState();
};

FlightNavigatorNode::FlightNavigatorNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{}

FlightNavigatorNode::~FlightNavigatorNode()
{
    delete d->state;
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
    d->state->process();
}

void FlightNavigatorNode::onSubReceived(const QString& topic,
                                        const QByteArray& msg)
{
    // TODO:
}
