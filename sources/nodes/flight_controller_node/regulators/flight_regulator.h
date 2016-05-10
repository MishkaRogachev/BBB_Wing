#ifndef FLIGHT_REGULATOR_H
#define FLIGHT_REGULATOR_H

#include "pid_regulator.h"

#include <QVariant>

namespace domain
{
    enum class FlightRegulatorType
    {
        Unknown,
        Throttle,
        LeftAileron,
        LeftElevon,
        LeftFlap,
        LeftFlaperon,
        LeftVTail,
        RightAileron,
        RightElevon,
        RightFlap,
        RightFlaperon,
        RightVTail,
        Elevator,
        Ruddler,
    };

    class FlightRegulator: public PidRegulator
    {
    public:
        FlightRegulator(const QVariantMap& map);

        FlightRegulatorType type() const;
        int channel() const;

    private:
        FlightRegulatorType m_type;
        int m_channel;
    };
}

#endif // FLIGHT_REGULATOR_H
