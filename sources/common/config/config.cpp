#include "config.h"

// Qt
#include <QFileInfo>

using namespace domain;

Config::Config():
    m_settings("settings", QSettings::NativeFormat)
{
    if (!QFileInfo(m_settings.fileName()).exists())
    {
        this->makeDefault();
        m_settings.sync();
    }
}

Config& Config::instance()
{
    static Config config;
    return config;
}

QVariant Config::setting(const QString& key)
{
    return Config::instance().m_settings.value(key);
}

void Config::setSetting(const QString& key, const QVariant& value)
{
    Config::instance().m_settings.setValue(key, value);
}

void Config::makeDefault()
{
    m_settings.setValue("FlightRecorder/path", "/media/sd_card");
}


