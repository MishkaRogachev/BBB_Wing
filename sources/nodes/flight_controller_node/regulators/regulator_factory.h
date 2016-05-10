#ifndef REGULATOR_FACTORY_H
#define REGULATOR_FACTORY_H

#include "abstract_regulator.h"

#include <QVariant>

namespace domain
{
    class RegulatorFactory
    {
    public:
        AbstractRegulator* create(const QVariantMap& settings, int frequency);
    };
}

#endif // REGULATOR_FACTORY_H
