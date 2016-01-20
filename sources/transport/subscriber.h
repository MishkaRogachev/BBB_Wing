#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "base_transport.h"

namespace domain
{
    class Subscriber: public BaseTransport
    {
        Q_OBJECT

    public:
        Subscriber(const QString& endpoint, QObject* parent = nullptr);
        Subscriber(const QStringList& endpoints, QObject* parent = nullptr);

        void subscribe(const QString& topic);
        void unsubscribe(const QString& topic);

    signals:
        void received(const QString& topic, const QByteArray& message);

    private slots:
        void onActivated();
    };
}

#endif // SUBSCRIBER_H
