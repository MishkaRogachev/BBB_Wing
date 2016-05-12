#include "config_impl.h"

// Qt
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

namespace
{
    const char separator = '/';
}

using namespace domain;

Config::Impl::Impl(const QString& filename):
    m_filename(filename)
{
    this->load();
}

void Config::Impl::load()
{
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &error);

    if (error.error == QJsonParseError::NoError)
    {
        m_object = document.object();
    }
    else
    {
        qCritical("JSon config parse error: %s",
                  qPrintable(error.errorString().toUtf8()));
    }

    file.close();
}

void Config::Impl::save()
{
    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly)) return;

    QJsonDocument document(m_object);
    file.write(document.toJson());
    file.close();
}

void Config::Impl::setValue(const QString& key, const QJsonValue& value)
{
    QStringList keyChain = key.split(::separator);
    if (!m_group.isEmpty()) keyChain.prepend(m_group);
    this->setObjectValue(m_object, keyChain, value);
}

QJsonValue Config::Impl::value(const QString& key) const
{
    QStringList keyChain = key.split(::separator);
    if (!m_group.isEmpty()) keyChain.prepend(m_group);
    return this->objectValue(m_object, keyChain);
}

void Config::Impl::setObjectValue(QJsonObject& object, QStringList& keyChain,
                                  const QJsonValue& value)
{
    if (keyChain.isEmpty()) return;
    QString key = keyChain.takeFirst();

    if (keyChain.isEmpty())
    {
        object.insert(key, value);
        return;
    }

    QJsonObject childObject = object.contains(key) ?
                             object.value(key).toObject() : QJsonObject();
    this->setObjectValue(childObject, keyChain, value);
    object.insert(key, childObject);
}

QJsonValue Config::Impl::objectValue(const QJsonObject& object,
                                     QStringList& keyChain) const
{
    if (keyChain.isEmpty()) return QJsonValue();
    QString key = keyChain.takeFirst();

    if (keyChain.isEmpty())
        return object.value(key);

    return this->objectValue(object.value(key).toObject(), keyChain);
}

QString Config::Impl::group() const
{
    return m_group;
}

void Config::Impl::setGroup(const QString& group)
{
    m_group = group;
}
