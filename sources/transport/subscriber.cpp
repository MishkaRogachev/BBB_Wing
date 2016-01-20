#include "subscriber.h"

// ZeroMQ
#include <zmq.hpp>

// Qt
#include <QSocketNotifier>
#include <QDebug>

using namespace domain;

Subscriber::Subscriber(const QString& endpoint, QObject* parent):
    Subscriber(QStringList(endpoint), parent)
{}

Subscriber::Subscriber(const QStringList& endpoints, QObject* parent):
    BaseTransport(ZMQ_SUB, parent)
{
    for (const QString& endpoint: endpoints)
        this->connectTo(endpoint);

    QSocketNotifier* notifier = new QSocketNotifier(this->fileDescriptor(),
                                    QSocketNotifier::Read, this);
    connect(notifier, &QSocketNotifier::activated,
            this, &Subscriber::onActivated, Qt::DirectConnection);
}

void Subscriber::subscribe(const QString& topic)
{
    this->setOption(ZMQ_SUBSCRIBE, topic);
}

void Subscriber::unsubscribe(const QString& topic)
{
    this->setOption(ZMQ_UNSUBSCRIBE, topic);
}

void Subscriber::onActivated()
{
    qDebug() << "activated!";
    emit received("0_0", "data");
}
