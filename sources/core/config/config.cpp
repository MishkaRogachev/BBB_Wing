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
    // TODO: make target's own configs
    m_settings.beginGroup("FlightRecorder");
    m_settings.setValue("path", "/media/sd_card/records/");
    m_settings.setValue("max_record_size", 3.2e+7);
    m_settings.setValue("file_format","ddMMyyyy_hhmm");
    m_settings.setValue("time_format","hh:mm:ss.zzz");
    m_settings.endGroup();

    m_settings.beginGroup("Transceiver");
    m_settings.setValue("udp_workstation_address", "192.168.7.1");
    m_settings.setValue("udp_workstation_port", 50000);
    m_settings.setValue("udp_board_address", "192.168.7.2");
    m_settings.setValue("udp_board_port", 50001);
    m_settings.endGroup();
}


