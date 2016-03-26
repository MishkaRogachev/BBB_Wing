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

    AbstractNavigationState* state = nullptr;
};

FlightNavigatorNode::FlightNavigatorNode(float frequency, QObject* parent):
    AbstractNodeFrequency(frequency, parent),
    d(new Impl())
{
    d->pub.bind("ipc://navigator");
}

FlightNavigatorNode::~FlightNavigatorNode()
{
    delete d;
}

void FlightNavigatorNode::init()
{
     d->sub.connectTo("ipc://alt");
     d->sub.connectTo("ipc://ins");
     d->sub.connectTo("ipc://sns");
     d->sub.connectTo("ipc://board_gateway");

     d->sub.subscribe("");
     this->onStateRequested(new IdleNavigationState(this));
}

void FlightNavigatorNode::exec()
{
    d->state->process();
}

void FlightNavigatorNode::onStateRequested(AbstractNavigationState* state)
{
    if (d->state) delete d->state;

    connect(&d->sub, &Subscriber::received,
            state, &AbstractNavigationState::onSubReceived);
    connect(state, SIGNAL(publish(QString, QByteArray)),
            &d->pub, SLOT(publish(QString, QByteArray)));
    connect(state, &AbstractNavigationState::requestNewState,
            this, &FlightNavigatorNode::onStateRequested);

    d->state = state;
}
