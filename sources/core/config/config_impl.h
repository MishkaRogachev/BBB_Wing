#ifndef CONFIG_IMPL_H
#define CONFIG_IMPL_H

#include "config.h"

// Qt
#include <QJsonObject>

namespace domain
{
    class Config::Impl
    {
    public:
        Impl(const QString& filename);

        void load();
        void save();

        void setValue(const QString& key, const QJsonValue& value);
        QJsonValue value(const QString& key) const;

        void setObjectValue(QJsonObject& object, QStringList& keyChain,
                            const QJsonValue& value);
        QJsonValue objectValue(const QJsonObject& object,
                               QStringList& keyChain) const;

        QString group() const;
        void setGroup(const QString& group);

    private:
        QString m_filename;
        QJsonObject m_object;
        QString m_group;
    };
}

#endif // CONFIG_IMPL_H
