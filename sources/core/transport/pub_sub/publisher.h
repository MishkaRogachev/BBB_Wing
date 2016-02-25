#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "pub_sub_base.h"

namespace domain
{
    class Publisher: public PubSubBase
    {
        Q_OBJECT

    public:
        Publisher(QObject* parent = nullptr);
        Publisher(const QString& endpoint, QObject* parent = nullptr);
        Publisher(const QString& endpoint, const QString& topic,
                  QObject* parent = nullptr);

        QString topic() const;

    public slots:
        void setTopic(const QString& topic);

        void publish(const QByteArray& data);
        void publish(const QString& topic, const QByteArray& data);

    private:
        QString m_topic;
    };
}

#endif // PUBLISHER_H
