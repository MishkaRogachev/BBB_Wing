#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "pub_sub_base.h"

namespace domain
{
    class Subscriber: public PubSubBase
    {
        Q_OBJECT

    public:
        Subscriber(QObject* parent = nullptr);
        Subscriber(const QString& endpoint, QObject* parent = nullptr);
        Subscriber(const QString& endpoint, const QString& topic,
                   QObject* parent = nullptr);

    public slots:
        void subscribe(const QString& topic);
        void unsubscribe(const QString& topic);

    signals:
        void received(const QString& topic, const QByteArray& data);

    private slots:
        void onActivated();
    };
}

#endif // SUBSCRIBER_H
