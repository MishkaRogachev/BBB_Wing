#include "idle_navigation_state.h"

// Internal
#include "publisher.h"
#include "core.h"

using namespace domain;

IdleNavigationState::IdleNavigationState(QObject* parent):
    AbstractNavigationState(new NavigationStateData(), parent)
{}

QString IdleNavigationState::stateId() const
{
    return "idle";
}

void IdleNavigationState::process()
{
    AbstractNavigationState::process();
}
