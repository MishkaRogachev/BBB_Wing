#include "config.h"

using namespace domain;

Config::Config():
    m_settings("settings.ini", QSettings::NativeFormat)
{}

Config& Config::instance()
{
    static Config config;
    return config;
}

QVariant Config::setting(const QString& key)
{
    if (Config::instance().m_settings.contains(key))
        return Config::instance().m_settings.value(key);

    qCritical("No key '%s'' in config group '%s'!",
              qUtf8Printable(key),
              qUtf8Printable(Config::instance().m_settings.group()));
    return QVariant();
}

void Config::setSetting(const QString& key, const QVariant& value)
{
    Config::instance().m_settings.setValue(key, value);
}

void Config::begin(const QString& prefix)
{
    Config::instance().m_settings.beginGroup(prefix);
}

void Config::end()
{
    Config::instance().m_settings.endGroup();
}


