#include "flight_navigator_node.h"

// Qt
#include <QDebug>

// Internal
#include "core.h"
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

FlightNavigatorNode::FlightNavigatorNode(QObject* parent): // Todo: Rename flight manager
    AbstractNodeFrequency(Config::value("FlightNavigator/frequency").toFloat(),
                          parent),
    d(new Impl())
{
    d->pub.bind(endpoints::navigator);
}

FlightNavigatorNode::~FlightNavigatorNode()
{
    delete d;
}

void FlightNavigatorNode::init()
{
    d->sub.connectTo({ endpoints::altimeter,
                       endpoints::ins,
                       endpoints::sns,
                       endpoints::flightPilot,
                       endpoints::boardTransceiver });

    d->sub.subscribe(topics::data);
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
