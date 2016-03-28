#ifndef CONFIG_H
#define CONFIG_H

// Qt
#include <QSettings>

namespace domain
{
    class Config
    {
    public:
        static Config& instance();

        static QVariant value(const QString& key);
        static void setValue(const QString& key, const QVariant& value);

        static void begin(const QString& prefix);
        static void end();

    private:
        Config();
        Config(const Config&) = delete;
        Config& operator=(const Config&) = delete;

        QSettings m_settings;
    };
}

#endif // CONFIG_H
