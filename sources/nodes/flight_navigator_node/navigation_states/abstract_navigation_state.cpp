#include "abstract_navigation_state.h"

// Internal
#include "publisher.h"
#include "topics.h"

using namespace domain;

AbstractNavigationState::AbstractNavigationState(Publisher* pub):
    m_pub(pub)
{}

AbstractNavigationState::~AbstractNavigationState()
{}

void AbstractNavigationState::process()
{
    m_pub->publish(topics::navigationState, this->stateId().toLatin1());
}
