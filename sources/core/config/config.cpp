#include "config.h"
#include "config_impl.h"

#include <QDebug>

using namespace domain;

Config::Config():
    d(new Impl("config.json"))
{}

Config::~Config()
{
    delete d;
}

Config& Config::instance()
{
    static Config config;
    return config;
}

void Config::setValue(const QString& key, const QVariant& value)
{
    Config::instance().d->setValue(key, QJsonValue::fromVariant(value));
}

QVariant Config::value(const QString& key)
{
    QVariant value = Config::instance().d->value(key).toVariant();
    if (value.isNull())
    {
        qCritical("No key '%s'' in config group '%s'!",
                  qPrintable(key),
                  qPrintable(Config::instance().d->group()));
    }
    return value;
}

void Config::begin(const QString& prefix)
{
    Config::instance().d->setGroup(prefix);
}

void Config::end()
{
    Config::instance().d->setGroup(QString());
}

void Config::save()
{
    Config::instance().d->save();
}

void Config::reload()
{
     Config::instance().d->load();
}


