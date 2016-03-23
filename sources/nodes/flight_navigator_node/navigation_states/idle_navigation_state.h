#ifndef IDLE_NAVIGATION_STATE_H
#define IDLE_NAVIGATION_STATE_H

#include "abstract_navigation_state.h"

namespace domain
{
    class IdleNavigationState: public AbstractNavigationState
    {
    public:
        IdleNavigationState();

        void process() override;
    };
}

#endif // IDLE_NAVIGATION_STATE_H
