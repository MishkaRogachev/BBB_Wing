#include "abstract_navigation_state.h"

// Internal
#include "topics.h"

using namespace domain;

AbstractNavigationState::AbstractNavigationState(QObject* parent):
    QObject(parent)
{}

AbstractNavigationState::~AbstractNavigationState()
{}

void AbstractNavigationState::onSubReceived(const QString& topic,
                                            const QByteArray& msg)
{

}

void AbstractNavigationState::process()
{
    this->publish(topics::navigationState, this->stateId().toLatin1());
}
