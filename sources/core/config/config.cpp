#include "config.h"

// Qt // TODO: move from QSettings to JSon
#include <QSettings>
#include <QDebug>

using namespace domain;

Config::Config():
    m_settings(new QSettings("config.conf", QSettings::NativeFormat))
{}

Config::~Config()
{
    delete m_settings;
}

Config& Config::instance()
{
    static Config config;
    return config;
}



QVariant Config::value(const QString& key)
{
    if (Config::instance().m_settings->contains(key))
        return Config::instance().m_settings->value(key);

    qCritical("No key '%s'' in config group '%s'!",
              qPrintable(key),
              qPrintable(Config::instance().m_settings->group()));
    return QVariant();
}

void Config::setValue(const QString& key, const QVariant& value)
{
    Config::instance().m_settings->setValue(key, value);
}

void Config::begin(const QString& prefix)
{
    Config::instance().m_settings->beginGroup(prefix);
}

void Config::end()
{
    Config::instance().m_settings->endGroup();
}


