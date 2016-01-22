#include "subscriber.h"

// ZeroMQ
#include <zmq.hpp>

// Qt
#include <QSocketNotifier>
#include <QDebug>

using namespace domain;

Subscriber::Subscriber(QObject* parent):
    BaseTransport(ZMQ_SUB, parent)
{
    /*QSocketNotifier* notifier = new QSocketNotifier(this->fileDescriptor(),
                                    QSocketNotifier::Read, this);
    connect(notifier, &QSocketNotifier::activated,
            this, &Subscriber::onActivated, Qt::DirectConnection);*/
}

Subscriber::Subscriber(const QString& endpoint, QObject* parent):
    Subscriber(parent)
{
    this->connectTo(endpoint);
}

Subscriber::Subscriber(const QString& endpoint, const QString& topic,
                       QObject* parent):
    Subscriber(endpoint, parent)
{
    this->subscribe(topic);
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
