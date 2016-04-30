#ifndef CONFIG_H
#define CONFIG_H

// Qt
#include <QVariant>

namespace domain
{
    class Config
    {
    public:
        static Config& instance();
        ~Config();

        static void setValue(const QString& key, const QVariant& value);
        static QVariant value(const QString& key);

        static void begin(const QString& prefix);
        static void end();

        static void save();
        static void reload();

    private:
        Config();
        Config(const Config&) = delete;
        Config& operator=(const Config&) = delete;

        class Impl;
        Impl* const d;
    };
}

#endif // CONFIG_H
