#ifndef REGULATOR_FACTORY_H
#define REGULATOR_FACTORY_H

// Qt
#include <QVariant>

// Internal
#include "abstract_regulator.h"

namespace domain
{
    class RegulatorFactory
    {
    public:
        AbstractRegulator* create(const QVariantMap& settings, int frequency);
    };
}

#endif // REGULATOR_FACTORY_H
