#include "config.h"

// Qt
#include <QFileInfo>
#include <QDebug>

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

void Config::begin(const QString& prefix)
{
    Config::instance().m_settings.beginGroup(prefix);
}

void Config::end()
{
    Config::instance().m_settings.endGroup();
}

void Config::makeDefault()
{
    m_settings.beginGroup("FlightRecorder");
    m_settings.setValue("path", "/media/sd_card/records/");
    m_settings.setValue("max_record_size", 3.2e+7);
    m_settings.setValue("time_format","hh:mm:ss.zzz");
    m_settings.endGroup();
}

