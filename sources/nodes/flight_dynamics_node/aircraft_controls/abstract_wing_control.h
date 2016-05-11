#ifndef ABSTRACT_WING_CONTROL_H
#define ABSTRACT_WING_CONTROL_H

#include "abstract_aircraft_control.h"

namespace domain
{
    class AbstractWingControl: virtual public AbstractAircraftControl
    {
    public:
        AbstractWingControl(int channel, bool left);

        bool left() const;
        void setLeft(bool left);

    protected:
        bool m_left;
    };
}

#endif // ABSTRACT_WING_CONTROL_H
