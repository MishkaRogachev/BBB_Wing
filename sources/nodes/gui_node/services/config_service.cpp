#include "config_service.h"

// Internal
#include "config.h"

using namespace domain;

ConfigService::ConfigService(QObject* parent):
    QObject(parent)
{}

QVariant ConfigService::value(const QString& key) const
{
    return Config::value(key);
}

void ConfigService::setValue(const QString& key, const QVariant& value)
{
    Config::setValue(key, value);
    emit valueChanged(key);
}

void ConfigService::begin(const QString& prefix)
{
    Config::begin(prefix);
}

void ConfigService::end()
{
    Config::end();
}
