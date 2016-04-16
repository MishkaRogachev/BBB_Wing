#ifndef CONFIG_SERVICE_H
#define CONFIG_SERVICE_H

// Qt
#include <QObject>
#include <QVariant>

namespace domain
{
    class ConfigService: public QObject
    {
        Q_OBJECT

    public:
        explicit ConfigService(QObject* parent = nullptr);

        Q_INVOKABLE QVariant value(const QString& key) const;

    public slots:
        void setValue(const QString& key, const QVariant& value);

        void begin(const QString& prefix);
        void end();

    signals:
        void valueChanged(QString key);
    };
}

#endif // CONFIG_SERVICE_H
