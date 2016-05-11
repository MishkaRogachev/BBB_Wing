#ifndef AIRCRAFT_CONTROL_FACTORY_H
#define AIRCRAFT_CONTROL_FACTORY_H

// Qt
#include <QVariant>

// Internal
#include "abstract_aircraft_control.h"

namespace domain
{
    class AircraftControlFactory
    {
    public:
        AbstractAircraftControl* create(const QVariantMap& settings);
    };
}

#endif // AIRCRAFT_CONTROL_FACTORY_H
