#include "flight_navigator_node.h"

// Qt
#include <QDebug>

// Internal
#include "topics.h"
#include "config.h"

#include "subscriber.h"
#include "publisher.h"

#include "idle_navigation_state.h"

using namespace domain;

class FlightNavigatorNode::Impl
{
public:
    Subscriber sub;
    Publisher pub;

    AbstractNavigationState* state = new IdleNavigationState(&pub);
};

FlightNavigatorNode::FlightNavigatorNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{
    d->pub.bind("ipc://navigator");
}

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
