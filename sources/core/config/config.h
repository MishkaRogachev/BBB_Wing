#ifndef CONFIG_H
#define CONFIG_H

// Qt
#include <QSettings>

namespace domain
{
    class Config // TODO: separate config files by targets
    {
    public:
        static Config& instance();

        static QVariant setting(const QString& key);
        static void setSetting(const QString& key, const QVariant& setting);

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
