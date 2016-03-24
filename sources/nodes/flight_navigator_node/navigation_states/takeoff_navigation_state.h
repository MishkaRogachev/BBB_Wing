#ifndef TAKEOFF_NAVIGATION_STATE_H
#define TAKEOFF_NAVIGATION_STATE_H

#include "abstract_navigation_state.h"

namespace domain
{
    class TakeoffNavigationState: public AbstractNavigationState
    {
        Q_OBJECT

    public:
        TakeoffNavigationState(AbstractNavigationState&& other);

        QString stateId() const override;

        void process() override;

    private:
        float m_takeoffPitch;
        float m_takeoffRoll;
        float m_takeoffVelocity;
        float m_takeoffAltitude;
    };
}

#endif // TAKEOFF_NAVIGATION_STATE_H
