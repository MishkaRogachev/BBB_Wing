#include "regulator_factory.h"

// Internal
#include "pid_regulator.h"

using namespace domain;

AbstractRegulator* RegulatorFactory::create(const QVariantMap& settings,
                                            int frequency)
{
    if (settings.value("type") == "pid")
    {
        return new PidRegulator(settings.value("proportional").toFloat(),
                                settings.value("integral").toFloat(),
                                settings.value("derivative").toFloat(),
                                settings.value("lower_bound").toFloat(),
                                settings.value("upper_bound").toFloat(),
                                settings.value("error_threshold").toFloat(),
                                frequency);
    }
    return nullptr;
}
